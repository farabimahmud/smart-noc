/*
 * Copyright (c) 2020 Inria
 * Copyright (c) 2016 Georgia Institute of Technology
 * Copyright (c) 2008 Princeton University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "mem/ruby/network/garnet/InputUnit.hh"

#include "debug/RubyNetwork.hh"
#include "debug/credit.hh"
#include "debug/smart.hh"
#include "mem/ruby/network/garnet/Credit.hh"
#include "mem/ruby/network/garnet/Router.hh"

namespace gem5
{

namespace ruby
{

namespace garnet
{

InputUnit::InputUnit(int id, PortDirection direction, Router *router)
  : Consumer(router), m_router(router), m_id(id), m_direction(direction),
    m_vc_per_vnet(m_router->get_vc_per_vnet())
{
    const int m_num_vcs = m_router->get_num_vcs();
    m_num_buffer_reads.resize(m_num_vcs/m_vc_per_vnet);
    m_num_buffer_writes.resize(m_num_vcs/m_vc_per_vnet);
    for (int i = 0; i < m_num_buffer_reads.size(); i++) {
        m_num_buffer_reads[i] = 0;
        m_num_buffer_writes[i] = 0;
    }

    // Instantiating the virtual channels
    virtualChannels.reserve(m_num_vcs);
    for (int i=0; i < m_num_vcs; i++) {
        virtualChannels.emplace_back();
    }
}

/*
 * The InputUnit wakeup function reads the input flit from its input link.
 * Each flit arrives with an input VC.
 * For HEAD/HEAD_TAIL flits, performs route computation,
 * and updates route in the input VC.
 * The flit is buffered for (m_latency - 1) cycles in the input VC
 * and marked as valid for SwitchAllocation starting that cycle.
 *
 */

void
InputUnit::wakeup()
{
    flit *t_flit;
    if (m_in_link->isReady(curTick())) {

        t_flit = m_in_link->consumeLink();
        DPRINTF(RubyNetwork, "Router[%d] Consuming:%s Width: %d Flit:%s\n",
        m_router->get_id(), m_in_link->name(),
        m_router->getBitWidth(), *t_flit);
        assert(t_flit->m_width == m_router->getBitWidth());
        int vc = t_flit->get_vc();
        // t_flit->increment_hops(); // for stats

        if ((t_flit->get_type() == HEAD_) ||
            (t_flit->get_type() == HEAD_TAIL_)) {

            assert(virtualChannels[vc].get_state() == IDLE_);
            set_vc_active(vc, curTick());

            // Route computation for this vc
            int outport = m_router->route_compute(t_flit->get_route(),
                m_id, m_direction);

            // Update output port in VC
            // All flits in this packet will use this output port
            // The output port field in the flit is updated after it wins SA
            grant_outport(vc, outport);

        } else {
            assert(virtualChannels[vc].get_state() == ACTIVE_);
        }


        // Buffer the flit
        virtualChannels[vc].insertFlit(t_flit);

        int vnet = vc/m_vc_per_vnet;
        // number of writes same as reads
        // any flit that is written will be read only once
        m_num_buffer_writes[vnet]++;
        m_num_buffer_reads[vnet]++;

        Cycles pipe_stages = m_router->get_pipe_stages();
        if (pipe_stages == 1) {
            // 1-cycle router
            // Flit goes for SA directly
            t_flit->advance_stage(SA_, curTick());
        } else {
            assert(pipe_stages > 1);
            // Router delay is modeled by making flit wait in buffer for
            // (pipe_stages cycles - 1) cycles before going for SA

            Cycles wait_time = pipe_stages - Cycles(1);
            t_flit->advance_stage(SA_, m_router->clockEdge(wait_time));

            // Wakeup the router in that cycle to perform SA
            m_router->schedule_wakeup(Cycles(wait_time));
        }

        if (m_in_link->isReady(curTick())) {
            m_router->schedule_wakeup(Cycles(1));
        }
    }
}

// Send a credit back to upstream router for this VC.
// Called by SwitchAllocator when the flit in this VC wins the Switch.
void
InputUnit::increment_credit(int in_vc, bool free_signal, Tick curTime)
{
    DPRINTF(RubyNetwork, "Router[%d]: Sending a credit vc:%d free:%d to %s\n",
    m_router->get_id(), in_vc, free_signal, m_credit_link->name());
    Credit *t_credit = new Credit(in_vc, free_signal, curTime+ Cycles(1));
    DPRINTF(credit, "[InputUnit:increment_credit]"
    " Credit is incremented and inserted in creditQueue"
    " %s at Router %d InputUnit %s\n",
    *t_credit, m_router->get_id(), m_direction);

    creditQueue.insert(t_credit);
    m_credit_link->scheduleEvent(Cycles(1));
    // m_credit_link->scheduleEventAbsolute(m_router->clockEdge(Cycles(1)));
}


uint32_t
InputUnit::functionalWrite(Packet *pkt)
{
    uint32_t num_functional_writes = 0;
    for (auto& virtual_channel : virtualChannels) {
        num_functional_writes += virtual_channel.functionalWrite(pkt);
    }

    return num_functional_writes;
}

bool
InputUnit::functionalRead(Packet *pkt){
    bool read = false;
    for (auto& virtual_channel : virtualChannels) {
        read = virtual_channel.functionalRead(pkt);
        if (read)return read;
    }

    return read;
}

void
InputUnit::resetStats()
{
    for (int j = 0; j < m_num_buffer_reads.size(); j++) {
        m_num_buffer_reads[j] = 0;
        m_num_buffer_writes[j] = 0;
    }
}

inline int InputUnit::get_inlink_id(){
    return m_in_link->get_id();
}



// SMART NoC
bool
InputUnit::try_smart_bypass(flit *t_flit)
{
    // Check if router is setup for SMART bypass this cycle
    DPRINTF(smart, "Router %d Inport %s trying to bypass flit %s\n",
                 m_router->get_id(), m_direction, *t_flit);

//    PortDirection outport_dirn = t_flit->get_route()->outport_dirn;
//    return m_router->try_smart_bypass(m_id, outport_dirn, t_flit);

    // Check SSR Grant for this cycle

    while (!ssr_grant.empty()) {
        SSR *t_ssr = ssr_grant.top();
        if (t_ssr->get_time() < m_router->curCycle()) {
            ssr_grant.pop();
            delete t_ssr;
        } else if (t_ssr->get_time() == m_router->curCycle()) {
            if (t_ssr->get_ref_flit() != t_flit) {
                // (i) this flit lost arbitration to a local flit, or
                // (ii) wanted to stop, and hence its SSR was not sent to
                //      this router, and some other SSR won.

                return false;
            } else {

                DPRINTF(RubyNetwork, "Router %d Inport %s"
                        " Trying SMART Bypass for Flit %s\n",
                        m_router->get_id(), m_direction, *t_flit);

                // SSR for this flit won arbitration last cycle
                // and wants to bypass this router
                assert(t_ssr->get_bypass_req());
                bool smart_bypass =
                    m_router->try_smart_bypass(m_id,
                                               t_ssr->get_outport_dirn(),
                                               t_flit);

                ssr_grant.pop();
                delete t_ssr;

                return smart_bypass;
            }
        } else {
            break;
        }
    }

    return false;
}

void
InputUnit::grantSSR(SSR *t_ssr)
{
    DPRINTF(RubyNetwork, "Router %d Inport %s granted SSR"
            " for flit %d from src_hops %d for bypass = %d for Outport %s\n",
            m_router->get_id(),
            m_direction,
            *(t_ssr->get_ref_flit()),
            t_ssr->get_src_hops(),
            t_ssr->get_bypass_req(),
            t_ssr->get_outport_dirn());

    // Update valid time to next cycle
    t_ssr->set_time(m_router->curCycle() + Cycles(1));
    ssr_grant.push(t_ssr);
}



} // namespace garnet
} // namespace ruby
} // namespace gem5

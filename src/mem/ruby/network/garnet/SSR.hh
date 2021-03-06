/*
 * Copyright (c) 2008 Princeton University
 * Copyright (c) 2016 Georgia Institute of Technology
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


#ifndef __MEM_RUBY_NETWORK_GARNET_0_SSR_HH__
#define __MEM_RUBY_NETWORK_GARNET_0_SSR_HH__

#include <cassert>
#include <iostream>

#include "base/types.hh"
#include "mem/ruby/network/garnet/CommonTypes.hh"
#include "mem/ruby/network/garnet/GarnetNetwork.hh"
#include "mem/ruby/network/garnet/flit.hh"

namespace gem5
{

namespace ruby
{

namespace garnet
{

class SSR
{
  public:
    SSR() {}
    SSR(int vnet, int src_hops, bool bypass_req,
        PortDirection outport_dirn, flit * ref_flit,
        Cycles curTime
        );

    virtual ~SSR(){};

    int get_vnet() {return m_vnet;}
    int get_src_hops() {return m_src_hops;}
    bool get_bypass_req() {return m_bypass_req;}
    
    void set_bypass_req(bool x){
        m_bypass_req =x; 
    }
    
    void set_inport(int inport){
        m_inport = inport;
    }

    int get_inport() {return m_inport;}

    PortDirection get_outport_dirn() {
        return m_outport_dirn;
    }

    void set_outport_dirn(PortDirection outport){
        m_outport_dirn = outport; 
    }

    flit * get_ref_flit() {return m_ref_flit;}
    Cycles get_time() {return m_time;}
    void set_time(Cycles x) {
        m_time = x; 
    }


    int m_vnet;
    int m_src_hops;
    bool m_bypass_req; 
    int m_inport;
    PortDirection m_outport_dirn;
    flit * m_ref_flit;
    Cycles m_time;
};

} // namespace garnet
} // namespace ruby
} // namespace gem5

#endif // __MEM_RUBY_NETWORK_GARNET_0_SSR_HH__

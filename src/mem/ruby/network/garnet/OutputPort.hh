#ifndef __MEM_RUBY_NETWORK_GARNET_0_OUTPUTPORT_HH__
#define __MEM_RUBY_NETWORK_GARNET_0_OUTPUTPORT_HH__


#include <cassert>
#include <cmath>

#include "base/cast.hh"
#include "debug/RubyNetwork.hh"
#include "debug/smart.hh"
#include "mem/ruby/network/MessageBuffer.hh"
#include "mem/ruby/network/garnet/Credit.hh"
#include "mem/ruby/network/garnet/NetworkLink.hh"
#include "mem/ruby/network/garnet/flitBuffer.hh"
#include "mem/ruby/slicc_interface/Message.hh"

namespace gem5 {

namespace ruby {
class MessageBuffer;

namespace garnet {
class flitBuffer;
class CreditLink;

class OutputPort
{
    public:
        OutputPort(NetworkLink *outLink, CreditLink *creditLink,
            int routerID);
        flitBuffer *
        outFlitQueue()
        {
            return _outFlitQueue;
        }

        NetworkLink *
        outNetLink()
        {
            return _outNetLink;
        }

        CreditLink *
        inCreditLink()
        {
            return _inCreditLink;
        }

        int
        routerID()
        {
            return _routerID;
        }

        uint32_t bitWidth()
        {
            return _bitWidth;
        }

        bool isVnetSupported(int pVnet);

        std::string
        printVnets();
        int vcRoundRobin()
        {
            return _vcRoundRobin;
        }

        void vcRoundRobin(int vc)
        {
            _vcRoundRobin = vc;
        }


    private:
        std::vector<int> _vnets;
        flitBuffer *_outFlitQueue;

        NetworkLink *_outNetLink;
        CreditLink *_inCreditLink;

        int _vcRoundRobin; // For round robin scheduling

        int _routerID;
        uint32_t _bitWidth;
};
}  // namespace garnet
}  // namespace ruby
}  // namespace gem5
#endif
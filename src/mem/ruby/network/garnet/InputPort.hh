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

class InputPort
{
 private:
  std::vector<int> _vnets;
  flitBuffer *_outCreditQueue;

  NetworkLink *_inNetLink;
  CreditLink *_outCreditLink;
  uint32_t this_bitwidth;

 public:
  InputPort(NetworkLink *inLink, CreditLink *creditLink);
  flitBuffer *outCreditQueue() { return _outCreditQueue; }

  NetworkLink *inNetLink() { return _inNetLink; }

  CreditLink *outCreditLink() { return _outCreditLink; }

  bool isVnetSupported(int pVnet);
  void sendCredit(Credit *cFlit);

  uint32_t bitWidth() { return this_bitwidth; }

  std::string printVnets();

  // Queue for stalled flits
  std::deque<flit *> m_stall_queue;
  bool messageEnqueuedThisCycle;
};

}  // namespace garnet
}  // namespace ruby
}  // namespace gem5

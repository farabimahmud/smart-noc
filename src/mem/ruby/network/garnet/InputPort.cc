#include "mem/ruby/network/garnet/InputPort.hh"

#include <cassert>
#include <cmath>

namespace gem5 {

namespace ruby {

namespace garnet {


  InputPort::InputPort(NetworkLink *inLink, CreditLink *creditLink) {
    _vnets = inLink->mVnets;
    _outCreditQueue = new flitBuffer();

    _inNetLink = inLink;
    _outCreditLink = creditLink;
    this_bitwidth = inLink->bitWidth;
  }


  bool InputPort::isVnetSupported(int pVnet) {
    if (!_vnets.size()) {
      return true;
    }

    for (auto &it : _vnets) {
      if (it == pVnet) {
        return true;
      }
    }
    return false;
  }

  void InputPort::sendCredit(Credit *cFlit) {
     DPRINTF(smart, "sending credit flit %s\n", *cFlit);
    _outCreditQueue->insert(cFlit);
  }

  std::string InputPort::printVnets() {
    std::stringstream ss;
    for (auto &it : _vnets) {
      ss << it;
      ss << " ";
    }
    return ss.str();
  }

}  // namespace garnet
}  // namespace ruby
}  // namespace gem5

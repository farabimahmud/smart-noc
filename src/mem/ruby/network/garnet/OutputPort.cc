#include "mem/ruby/network/garnet/OutputPort.hh"

#include <cassert>
#include <cmath>

#include "debug/credit.hh"

namespace gem5 {

namespace ruby {

namespace garnet {

OutputPort::OutputPort(NetworkLink *outLink, CreditLink *creditLink,
                       int routerID) {
  _vnets = outLink->mVnets;
  _outFlitQueue = new flitBuffer();

  _outNetLink = outLink;
  _inCreditLink = creditLink;

  _routerID = routerID;
  _bitWidth = outLink->bitWidth;
  _vcRoundRobin = 0;
}

bool OutputPort::isVnetSupported(int pVnet) {
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

std::string OutputPort::printVnets() {
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

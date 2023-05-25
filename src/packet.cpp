#include "../include/packet.hpp"

template<class T>
ostream& operator<<(ostream& os, const Packet<T>& pkt){
  os << "<" << pkt.source << ", " << pkt.destination;
  os << ", [" << pkt.data << "]>";
  return os;
}
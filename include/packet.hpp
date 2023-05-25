#ifndef PACKET_HPP
#define PACKET_HPP

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

template<class T>
struct Packet
{
  T data;
  string source;
  string destination;
};

template<class T>
ostream& operator<<(ostream& os, const Packet<T>& pkt){
  os << "<" << pkt.source << ", " << pkt.destination;
  os << ", " << pkt.data << ">";
  return os;
}

#endif
#ifndef MUX_HPP
#define MUX_HPP

#include <cadmium/core/modeling/atomic.hpp>
#include <vector>
#include <string>
#include <limits>
#include <assert.h>

#include "../include/packet.hpp"

using namespace std;
using namespace cadmium;

template <class T>
struct MuxState {
  vector<string> portNames;
  MuxState(vector<string> ports): portNames(ports){}
};

template <class T>
ostream& operator<<(ostream& os, const MuxState<T>& state) {
  os << "<<";
  for (auto name: state.portNames) {
    os << name << ",";
  }
  os << ">";
  return os;
}

template <class T>
class Mux: public Atomic<MuxState<T>> {
  public:

    BigPort<Packet<T>> in;
    vector<BigPort<T>> out;

    Mux(string id, MuxState<T> initialState): Atomic<MuxState<T>>(id, initialState) {
      this->in = this->template addInBigPort<Packet<T>>("in");
      for (auto name: initialState.portNames) {
        this->out.push_back(this->template addOutBigPort<T>(name));
      }
    }

    double timeAdvance(const MuxState<T>& state) const override {
      return numeric_limits<double>::infinity();
    }

    void externalTransition(MuxState<T>& state, double e) const override {
      for (const auto& m : this->in->getBag()) {
        cout << "Received packet: " << m->data << " Destination: " << m->destination << endl;
        string name = m->destination;
        for (int i = 0; i < state.portNames.size(); ++i) {
          if (state.portNames[i] == name) {
            this->out[i]->addMessage(m->data);
            cout << "Sent packet: " << m->data << " to port: " << state.portNames[i] << endl;
            break;
          }
        }
      }
      this->in->clear();
    }
    void output(const MuxState<T>& state) const override {
      // No implementation needed
    }

    void internalTransition(MuxState<T>& state) const override {
      // No implementation needed
    }
};

#endif
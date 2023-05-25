#include <cadmium/core/modeling/coupled.hpp>
#include <vector>
#include <string>

#include "../include/packet.hpp"
#include "mux.hpp"

class TestMux: public cadmium::Coupled {
  public:
  cadmium::BigPort<Packet<std::string>> in; 

  TestMux(std::string id): cadmium::Coupled(id) {
    in = addInBigPort<Packet<std::string>>("in");
    std::vector<std::string> names = {
      "a",
      "b",
      "c",
      "d",
    };

    auto a = addOutBigPort<std::string>("a");
    auto b = addOutBigPort<std::string>("b");
    auto c = addOutBigPort<std::string>("c");
    auto d = addOutBigPort<std::string>("d");

    auto mux = addComponent<Mux<std::string>>("mux", names);
    addCoupling(in, mux->in);
    addCoupling(mux->out[0], a);
    addCoupling(mux->out[1], b);
    addCoupling(mux->out[2], c);
    addCoupling(mux->out[3], d);

  }

};
#ifndef ATOMIC_MODEL_NAME_HPP
#define ATOMIC_MODEL_NAME_HPP
//Include simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
//Include other headers needed for the C++ implementation of the model
#include <limits>
#include <math.h>
#include <assert.h>
//Include the relative path to the message types
using namespace cadmium;
using namespace std;
//Port definition
struct model_name_ports_defs{
struct out_port_name1 : public out_port<message_type_1> {};
struct out_port_name2 : public out_port<message_type_2> {};
struct in_port_name1 : public in_port<message_type_3> {};
struct in_port_name2 : public in_port<message_type_4> {};
};
//Atomic model class
template<typename TIME> class model_name {
public:
//Ports definition
using input_ports = tuple<typename model_name_ports_defs:: in_port_name1,
typename model_name_ports_defs:: in_port_name2>;
using output_ports = tuple<typename model_name_ports_defs:: out_port_name1,
typename model_name_ports_defs:: out_port_name2>;
//Model parameters to be overwritten during instantiation
struct state_type{
//Declare the state variables here
};
state_type state;
//Default constructor without parameters
model_name () noexcept{
//Define the default constructor here
}
//Constructor with parameters if needed
void internal_transition() {
  //Define internal transition here
}
void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
//Define external transition here
}
void confluence_transition(TIME e,typename make_message_bags<input_ports>::type mbs){
//Define confluence transition here
//Default definition
internal_transition();
external_transition(TIME(), std::move(mbs));
}
typename make_message_bags<output_ports>::type output() const {
typename make_message_bags<output_ports>::type bags;
//Define output function here
return bags;
}
TIME time_advance() const {
TIME next_internal;
//Define time advance function here
return next_internal;
}
friend ostringstream& operator<<(ostringstream& os, const typename
Subnet<TIME>::state_type& state) {
//Define how to log the state here
return os;
}
};
#endif //ATOMIC_MODEL_NAME_HPP
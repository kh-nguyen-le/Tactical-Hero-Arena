#ifndef HERO_EVENT_HPP
#define HERO_EVENT_HPP

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

struct Event{
  Event(){}
  Event(string i_type, double i_amt, string i_src, string i_dst)
    :type(i_type), amount(i_amt), source(i_src), destination(i_dst){}
    string type;
    double amount;
    string source;
    string destination;
    string team;
};

ostream& operator<<(ostream& os, const Event evt);

#endif
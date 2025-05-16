// Class for the circuit //

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include"components.h"
#include<vector>
#include<memory>

class Circuit{
private:
  std::vector<std::unique_ptr<Components>> elements;
};

#endif
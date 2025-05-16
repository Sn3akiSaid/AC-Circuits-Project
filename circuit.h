// Class for the circuit //

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include"components.h"
#include<vector>
#include<memory>

enum class ConnectionType {Series, Parallel};

class Circuit{
private:
  std::vector<std::unique_ptr<Components>> elements;
  ConnectionType connType;
  std::string name;

public:
  void addComponent(std::unique_ptr<Components> component);
  std::complex<double> getImpedance() const;
  void Display() const;


};

#endif
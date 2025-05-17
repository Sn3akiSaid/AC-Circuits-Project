#include"resistor.h"
#include"circuit.h"
#include<iostream>
#include<memory>

int main(){

  Circuit myCircuit;

  myCircuit.addComponent(std::make_unique<Resistor>(100.0));
  myCircuit.addComponent(std::make_unique<Resistor>(150.0));
  myCircuit.circuitVisualiser();

  return 0;
}
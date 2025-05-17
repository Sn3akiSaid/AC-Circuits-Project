#include"resistor.h"
#include"circuit.h"
#include<iostream>
#include<memory>

int main(){

  Circuit seriesCircuit;

  seriesCircuit.addComponent(std::make_unique<Resistor>(100.0, 10));
  seriesCircuit.addComponent(std::make_unique<Resistor>(150.0, 10));
  seriesCircuit.circuitVisualiser();

  Circuit parallelCircuit("Parallel", ConnectionType::Parallel);
  parallelCircuit.addComponent(std::make_unique<Resistor>(100, 1000));
  
  parallelCircuit.addComponent(std::make_unique<Resistor>(130, 1000));
  
  parallelCircuit.addComponent(std::make_unique<Resistor>(150, 1000));

  parallelCircuit.circuitVisualiser();
  return 0;
}
#include"Resistor.h"
#include"Circuit.h"
#include<iostream>
#include<memory>

int main(){
  try
  {
    Circuit seriesCircuit;

    seriesCircuit.addComponent(std::make_unique<Resistor>(100.0, 10));
    seriesCircuit.addComponent(std::make_unique<Resistor>(150.0, 10));
    // seriesCircuit.circuitVisualiser();
    seriesCircuit.detailedCircuitVisualiser();
    seriesCircuit.numberedCircuitVisualiser();
    Circuit parallelCircuit("Parallel", ConnectionType::Parallel);
    parallelCircuit.addComponent(std::make_unique<Resistor>(100, 1000));
    
    // parallelCircuit.addComponent(std::make_unique<Resistor>(130, 1000));
    
    parallelCircuit.addComponent(std::make_unique<Resistor>(150, 1000));

    // parallelCircuit.circuitVisualiser();
    parallelCircuit.detailedCircuitVisualiser();
    parallelCircuit.numberedCircuitVisualiser();

    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "" << e.what() << std::endl;
    return 1;
  }
  return 0;

}
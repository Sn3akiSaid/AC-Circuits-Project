#include"Resistor.h"
#include"Circuit.h"
#include<iostream>
#include<memory>

int main(){
  try
  {
    Circuit seriesCircuit("Simple Series", ConnectionType::Series);

    seriesCircuit.addComponent(std::make_unique<Resistor>(100.0, 10));
    seriesCircuit.addComponent(std::make_unique<Resistor>(150.0, 10));
    // seriesCircuit.circuitVisualiser();
    std::cout << "\n---- Simple Series Circuit ----\n";
    seriesCircuit.asciiSchematicVisualiser();
    // seriesCircuit.numberedCircuitVisualiser();
    Circuit parallelCircuit("Simple Parallel", ConnectionType::Parallel);
    parallelCircuit.addComponent(std::make_unique<Resistor>(100, 1000));
    parallelCircuit.addComponent(std::make_unique<Resistor>(130, 1000));
    parallelCircuit.addComponent(std::make_unique<Resistor>(150, 1000));

    // parallelCircuit.circuitVisualiser();
    std::cout << "\n---- Simple Series Circuit ----\n";
    parallelCircuit.asciiSchematicVisualiser();
    // parallelCircuit.numberedCircuitVisualiser();

    // TESTING NESTING //
    // Series with a paralel group
    std::cout << "\n---- Nest Test ----\n";

    // Series: 100 Ohm + [220 Ohm || 330 Ohm] + 470 Ohm
    Circuit nestedSeries("Nested Series", ConnectionType::Series);
    // Start with the 100 Ohm resistor
    nestedSeries.addComponent(std::make_unique<Resistor>(100, 1000));

    // Make the parallel group [220 Ohm || 330 Ohm]
    auto parallelGroup = std::make_unique<Circuit>("Parallel", ConnectionType::Parallel);
    parallelGroup->addComponent(std::make_unique<Resistor>(220,1000));
    parallelGroup->addComponent(std::make_unique<Resistor>(330,1000));
    // Add parallel group to the series
    nestedSeries.addComponent(std::move(parallelGroup));
    // End with the 470 Ohm resistor
    nestedSeries.addComponent(std::make_unique<Resistor>(470,1000));

    // Visualise this circuit
    std::cout << "\n--- Series Circuit with parallel subcircuit ---\n";
    nestedSeries.detailedCircuitVisualiser();
    nestedSeries.asciiSchematicVisualiser();
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "" << e.what() << std::endl;
    return 1;
  }
  return 0;

}
#include"Resistor.h"
#include"Capacitor.h"
#include"Inductor.h"
#include"Circuit.h"
#include<iostream>
#include<memory>

int main(){
  try
  {
    // Simple Series Circuit //
    Circuit seriesCircuit("Simple Circuit", ConnectionType::Series);

    seriesCircuit.addComponent(std::make_unique<Resistor>(100.0, 10));   // 100Ohm
    seriesCircuit.addComponent(std::make_unique<Resistor>(150.0, 10));   // 150Ohm
    seriesCircuit.addComponent(std::make_unique<Capacitor>(0.0001, 10)); // 100uF
    // seriesCircuit.circuitVisualiser();
    std::cout << "\n---- Simple Series Circuit ----\n";
    seriesCircuit.asciiSchematicVisualiser();
    seriesCircuit.detailedCircuitVisualiser();

    // Simple Parallel Circuit //
    Circuit parallelCircuit("Simple Circuit", ConnectionType::Parallel);
    parallelCircuit.addComponent(std::make_unique<Resistor>(100, 1000));
    parallelCircuit.addComponent(std::make_unique<Capacitor>(0.00013, 1000));
    parallelCircuit.addComponent(std::make_unique<Resistor>(150, 1000));
    parallelCircuit.addComponent(std::make_unique<Capacitor>(0.00015, 1000));
    parallelCircuit.addComponent(std::make_unique<Resistor>(150, 1000));
    parallelCircuit.addComponent(std::make_unique<Inductor>(0.00015, 1000));
    std::cout << "\n---- Simple Parallel Circuit ----\n";
    parallelCircuit.asciiSchematicVisualiser();
    parallelCircuit.detailedCircuitVisualiser();

    // TESTING NESTING //
    // Series with a paralel group
    std::cout << "\n---- Nest Test 1----\n";

    // Series: 100 Ohm + [220 Ohm || 330 Ohm] + 470 Ohm
    Circuit nestedSeries("Circuit", ConnectionType::Series);
    // Start with the 100 Ohm resistor
    nestedSeries.addComponent(std::make_unique<Resistor>(100, 1000));

    // Make the parallel group [220 Ohm || 330 Ohm]
    auto parallelGroup = std::make_unique<Circuit>("Group", ConnectionType::Parallel);
    parallelGroup->addComponent(std::make_unique<Resistor>(220,1000));
    parallelGroup->addComponent(std::make_unique<Resistor>(330,1000));
    Circuit* parallelGroupPtr = parallelGroup.get(); // Keep raw pointer
    // Add parallel group to the series by moving ownership
    nestedSeries.addComponent(std::move(parallelGroup));
    // End with the 470 Ohm resistor
    nestedSeries.addComponent(std::make_unique<Resistor>(470,1000));

    // Visualise this circuit //
    nestedSeries.asciiSchematicVisualiser();    // Draw schematic for whole circuit
    nestedSeries.detailedCircuitVisualiser();   // Output data table for components
    parallelGroupPtr->asciiSchematicVisualiser();   // Visualise the parallel subcircuit through raw pointer


    std::cout << "\n---- Nest Test 2----\n";
    // Parallel with a series group
    // Parallel: 100 Ohm || [220 Ohm + 330 Ohm] || 470 Ohm
    Circuit nestedParallel("Circuit", ConnectionType::Parallel);
    // Start with the 100 Ohm resistor
    nestedParallel.addComponent(std::make_unique<Resistor>(100, 1000));

    // Make the serial group [220 Ohm + 330 Ohm]
    auto serialGroup = std::make_unique<Circuit>("Group", ConnectionType::Series);
    serialGroup->addComponent(std::make_unique<Capacitor>(0.00013,1000));
    serialGroup->addComponent(std::make_unique<Resistor>(330,1000));
    Circuit* serialGroupPtr = serialGroup.get(); // Keep raw pointer
    // Add parallel group to the series by moving ownership
    nestedParallel.addComponent(std::move(serialGroup));
    // End with the 470 Ohm resistor
    nestedParallel.addComponent(std::make_unique<Inductor>(0.0003,1000));

    // Visualise this circuit //
    nestedParallel.asciiSchematicVisualiser();    // Draw schematic for whole circuit
    nestedParallel.detailedCircuitVisualiser();   // Output data table for components
    serialGroupPtr->asciiSchematicVisualiser();   // Visualise the serial subcircuit
    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
  return 0;

}
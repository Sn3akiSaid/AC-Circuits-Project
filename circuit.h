// Class for the circuit //

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include"components.h"
#include<vector>
#include<memory>

// Class defining connection types between components in the circuit
enum class ConnectionType {Series, Parallel};

class Circuit{
private:
  std::vector<std::unique_ptr<Components>> components;   // Storage for components
  ConnectionType connectionType;
  std::string circuitName;  

public:

  // Constructor
  Circuit(const std::string& circName = "Circuit",
          ConnectionType connType = ConnectionType::Series);
  
  // Add component methods
  void addComponent(std::unique_ptr<Components> component);

// Calculations for Impedance //

  // Methods 
  std::complex<double> getImp() const; // Returns complex impedance of circuit
  double getMagn() const;              // Resulting impedance magnitude
  double getPhsDiff() const;           // Phase shift of impedance

  // Setters
  void setFreq(double freq);
  
  // Basic Visualisation 
  void circuitVisualiser() const;

// Accessor methods //
  ConnectionType getConnType() const {return connectionType;} // Connection type
  std::string getName() const {return circuitName;}            // Name of circuti
  size_t getCompCount() const {return components.size();} // Return # of components in circuit

};

#endif
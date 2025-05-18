// Class for the circuit //

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include"Components.h"
#include<vector>
#include<memory>

// Class defining connection types between components in the circuit
enum class ConnectionType {Series, Parallel};

class Circuit : public Components{
private:
  std::vector<std::unique_ptr<Components>> components;   // Storage for components
  ConnectionType connectionType;
  std::string circuitName;
  // Helper method for recursive display of nested circuits
  void displayComponentsDetailed(const std::vector<std::unique_ptr<Components>>& comps,
                                 int depth, int& index) const;
public:

  // Constructor
  Circuit(const std::string& name = "Circuit",
          ConnectionType connType = ConnectionType::Series);
  
  // Add component methods
  void addComponent(std::unique_ptr<Components> component);

// Calculations for Impedance- these override component interface //

  // Getters 
  std::complex<double> getImp() const override; // Returns complex impedance of circuit
  double getMagn() const override;              // Resulting impedance magnitude
  double getPhsDiff() const override;           // Phase shift of impedance
  void setFreq(double freq) override;           // 
  
// Methods for interface //

  std::string getType() const override;
  double getFreq() const override;

  void setType(const std::string &compType) override;
  void setImp(std::complex<double> impIn) override;
  void setMagn(double magnIn) override;
  void setPhsDiff(double phsDiffIn) override; 
  std::unique_ptr<Components> clone() const override;

// Nested circuit helper methods //
  void addSeriesComponent(std::unique_ptr<Components> component);
  void addParallelComponent(std::unique_ptr<Components> component);
  std::unique_ptr<Circuit> createSeriesCircuit();
  std::unique_ptr<Circuit> createParallelCircuit();
  // Overloaded wrapper initialising index for nesting
  void displayComponentsDetailed(const std::vector<std::unique_ptr<Components>>& comps,
                                int depth = 0) const;

  // Visualisation Methods
  void detailedCircuitVisualiser() const; // Table with data
  void asciiSchematicVisualiser() const;  // ASCII of circuit diagram

// Accessor methods //
  ConnectionType getConnType() const {return connectionType;} // Connection type
  std::string getName() const {return circuitName;}           // Explicit circuit name getter
  void setName(const std::string& name) {circuitName = name;} // Optional setter
  size_t getCompCount() const {return components.size();}     // Return # of components in circuit

};

#endif
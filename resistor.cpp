// Implementation of the derived Resistor class //

#include"resistor.h"
#include<iostream>
#include<cmath>
#include<stdexcept>

// Constructor
Resistor::Resistor(double resIn,
                   double freqIn) :
                   Components("Resistor",
                              std::complex<double>(resIn, 0.0),
                              resIn,
                              freqIn,
                              0.0) ,
                   Resistance(resIn)
  {
    // Input validation
    if (resIn < 0.0)
    {
      throw std::invalid_argument("Resistance cannot be negative.");
    }
    updateImpedance();
  }

// Using Rule of Five //

// Implementation of the Constructors

  // Copy Constructor
  Resistor::Resistor(const Resistor& other) :
                     Components(other),
                     Resistance(other.Resistance) {}

  // Move Constructor
  Resistor::Resistor(Resistor&& other) noexcept :
                     Components(std::move(other)), // Calling the base move constructor
                     Resistance(other.Resistance) {}

// Implementation of the Assignment operators

  // Copy Assignment operator
  Resistor& Resistor::operator=(const Resistor& other)
  {
    if (this != &other)
    {
      Components::operator=(other); // Calls base assignment
      Resistance = other.Resistance;
    }
    return *this;
  }

  // Move Assignment operator
  Resistor& Resistor::operator=(Resistor&& other) noexcept
  {
    if (this != &other)
    {
      Components::operator=(std::move(other));
      Resistance = other.Resistance;
    }
    return *this;
  }

  // Use the clone method from the base components class
  std::unique_ptr<Components> Resistor::clone() const
  {return std::make_unique<Resistor>(*this);}

// Implementation of the Resistor specific methods //

  // Getter
  double Resistor::getResistance() const
  {return Resistance;}

  // Setter
  void Resistor::setResistance(double resIn)
  { // Validation for resistance
    if (resIn)
    {
      throw std::invalid_argument("Resistance not allowed to be negative.");
    }
    Resistance = resIn;
    updateImpedance();
  }

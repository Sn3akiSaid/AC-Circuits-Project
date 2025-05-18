// Implementation of the derived Resistor class //

#include"Resistor.h"
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
                              0.0),
                   Resistance(resIn)
  {
    // Input validation
    if (resIn < 0.0)
    {
      throw std::invalid_argument("Resistance cannot be negative.");
    }
    updateImpedance(); // Use helper method
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
    if (resIn < 0.0)
    {
      throw std::invalid_argument("Resistance not allowed to be negative.");
    }
    Resistance = resIn;
    updateImpedance(); // Use helper method
  }

  // Implementation of the helper method to update the impedance
  void Resistor::updateImpedance()
  { // In a resistor: Resistance = Re[Impedance] = |Impedance| ; no phase shift
    Impedance = std::complex<double>(Resistance, 0.0);
    magnitudeOfImpedance = Resistance;
    phaseDifference = 0.0;
  }

// Implementation of the Components methods

  // The Getters
  std::string Resistor::getType() const
  {return componentType;} // Returns "Resistor" from parameterized constructor

  std::complex<double> Resistor::getImp() const
  {return Impedance;}

  double Resistor::getMagn() const
  {return magnitudeOfImpedance;}

  double Resistor::getFreq() const
  {return Frequency;}
  
  double Resistor::getPhsDiff() const
  {return phaseDifference;}
  // The Setters
  void Resistor::setType(const std::string &compType)
  {componentType = compType;}

  void Resistor::setImp(std::complex<double> impIn)
  { // Here will now use R=Re[I] and phasedifference=Arg[I]
    Impedance = impIn;
    Resistance = impIn.real();
    magnitudeOfImpedance = std::abs(impIn);
    phaseDifference = std::arg(impIn);
  }

  void Resistor::setMagn(double magnIn)
  { // Check if magnitude is negative, mustn't be 
    if (magnIn < 0.0)
    {
      throw std::invalid_argument("Impedance magnitude cannot be negative. ");
    }
    magnitudeOfImpedance = magnIn;
    // Magnitude changes update resistance
    Resistance = magnIn;
    Impedance = std::complex<double>(Resistance, 0.0);
    phaseDifference = 0.0;
  }
  
  void Resistor::setFreq(double freqIn)
  { // Check for negative frequency
    if (freqIn < 0.0)
    {throw std::invalid_argument("Frequency cannot be negative. ");
    }
    Frequency = freqIn;
    // In ideal resistors frequency doesn't change the impedances, but maintain helper method for concsistency
    updateImpedance();
  }

  void Resistor::setPhsDiff(double phsDiffIn)
  { // Ideal resistor have 0 phase so check if phase is non-0
    if (phsDiffIn != 0.0)
    {
      std::cerr << "Warning: Ideal resistor should not have a phase difference." << std::endl;
    }
    phaseDifference = phsDiffIn;
  }
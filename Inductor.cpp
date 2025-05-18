#include"Inductor.h"
#include<iostream>
#include<cmath>
#include<stdexcept>

#ifndef pi
#define pi 3.14159265358979323846
#endif

// Constructor
Inductor::Inductor(double indIn,
                     double freqIn) :
                   Components("Inductor",
                              std::complex<double>(0.0, 0.0),
                              indIn,
                              freqIn,
                              pi/2), // Incudctors have +90 degree phase shift
                   Inductance(indIn)
  {
    if (indIn < 0.0)
    {
      throw std::invalid_argument("Inductance cannot be negative.");
    }
    updateImpedance(); // Use helper method
  }

  // Using Rule of Five //

// Implementation of the Constructors

  // Copy Constructor
  Inductor::Inductor(const Inductor& other) :
                       Components(other),
                       Inductance(other.Inductance) {}

  // Move Constructor
  Inductor::Inductor(Inductor&& other) noexcept :
                       Components(std::move(other)), // Calling the base move constructor
                       Inductance(other.Inductance) {}

// Implementation of the Assignment operators

  // Copy Assignment operator
  Inductor& Inductor::operator=(const Inductor& other)
  {
    if (this != &other)
    {
      Components::operator=(other); // Calls base assignment
      Inductance = other.Inductance;
    }
    return *this;
  }

  // Move Assignment operator
  Inductor& Inductor::operator=(Inductor&& other) noexcept
  {
    if (this != &other)
    {
      Components::operator=(std::move(other));
      Inductance = other.Inductance;
    }
    return *this;
  }

  // Use the clone method from the base components class
  std::unique_ptr<Components> Inductor::clone() const
  {return std::make_unique<Inductor>(*this);}

// Implementation of the Inductor specific methods //

  // Getter
  double Inductor::getInductance() const
  {return Inductance;}

  // Setter
  void Inductor::setInductance(double indIn)
  { // Validation for Inductance
    if (indIn < 0.0)
    {
      throw std::invalid_argument("Inductance not allowed to be negative.");
    }
    Inductance = indIn;
    updateImpedance(); // Use helper method
  }

  // Implementation of the helper method to update the impedance
  void Inductor::updateImpedance()
  { // In a Inductor: Resistance = Re[Impedance] = |Impedance| ; no phase shift
    if (Frequency > 0.0)
    {
      // Z = jX = jwL; So X (reactance) = wL = (2*pi*f*L)
      double reactance = (2.0 * pi * Frequency * Inductance);
      Impedance = std::complex<double>(0.0, reactance);
      magnitudeOfImpedance = std::abs(Impedance);
      phaseDifference = pi/2;
    }
    else
    { // 0 impedance case for 0 Frequency - short circuit
      Impedance = std::complex<double>(0.0, 0.0);
      magnitudeOfImpedance = 0.0;
      phaseDifference = 0.0;
    }
  }

// Implementation of the Components methods

  // The Getters
  std::string Inductor::getType() const
  {return componentType;} // Returns "Inductor" from parameterized constructor

  std::complex<double> Inductor::getImp() const
  {return Impedance;}

  double Inductor::getMagn() const
  {return magnitudeOfImpedance;}

  double Inductor::getFreq() const
  {return Frequency;}
  
  double Inductor::getPhsDiff() const
  {return phaseDifference;}
  // The Setters
  void Inductor::setType(const std::string &compType)
  {componentType = compType;}

  void Inductor::setImp(std::complex<double> impIn)
  { // Here will now use R=Re[I] and phasedifference=Arg[I]
    Impedance = impIn;
    magnitudeOfImpedance = std::abs(impIn);
    phaseDifference = std::arg(impIn);
  }

  void Inductor::setMagn(double magnIn)
  { // Check if magnitude is negative, mustn't be 
    if (magnIn < 0.0)
    {
      throw std::invalid_argument("Impedance magnitude cannot be negative.");
    }
    magnitudeOfImpedance = magnIn;
    Impedance = std::polar(magnIn, pi/2); // Z = |Z|exp(arg(phi))

    if (Frequency > 0.0)
    {
      Inductance = magnIn / (2.0 * pi * Frequency); // L = |Z|/(w*f) = |Z|/(2*pi)
    }
  }

  void Inductor::setFreq(double freqIn)
  {
    if (freqIn < 0.0)
    {throw std::invalid_argument("Frequency cannot be negative");}

    Frequency = freqIn;
    updateImpedance();
  }

  void Inductor::setPhsDiff(double phsDiffIn)
  { // Check if phase is set to something other than 90 deg
    if (std::abs(phsDiffIn - pi/2) > 1e-6)
    {
      std::cerr << "Ideal Inductor should have a phase of +90 degrees." << std::endl;
    }
    phaseDifference = phsDiffIn;
  }

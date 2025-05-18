#include"Capacitor.h"
#include<iostream>
#include<cmath>
#include<stdexcept>

#ifndef pi
#define pi 3.14159265358979323846
#endif

// Constructor
Capacitor::Capacitor(double capIn,
                     double freqIn) :
                   Components("Capacitor",
                              std::complex<double>(0.0, 0.0),
                              capIn,
                              freqIn,
                              -pi/2), // Capacitors have -90 degree phase shift
                   Capacitance(capIn)
  {
    if (capIn < 0.0)
    {
      throw std::invalid_argument("Capacitance cannot be negative.");
    }
    updateImpedance(); // Use helper method
  }

  // Using Rule of Five //

// Implementation of the Constructors

  // Copy Constructor
  Capacitor::Capacitor(const Capacitor& other) :
                       Components(other),
                       Capacitance(other.Capacitance) {}

  // Move Constructor
  Capacitor::Capacitor(Capacitor&& other) noexcept :
                       Components(std::move(other)), // Calling the base move constructor
                       Capacitance(other.Capacitance) {}

// Implementation of the Assignment operators

  // Copy Assignment operator
  Capacitor& Capacitor::operator=(const Capacitor& other)
  {
    if (this != &other)
    {
      Components::operator=(other); // Calls base assignment
      Capacitance = other.Capacitance;
    }
    return *this;
  }

  // Move Assignment operator
  Capacitor& Capacitor::operator=(Capacitor&& other) noexcept
  {
    if (this != &other)
    {
      Components::operator=(std::move(other));
      Capacitance = other.Capacitance;
    }
    return *this;
  }

  // Use the clone method from the base components class
  std::unique_ptr<Components> Capacitor::clone() const
  {return std::make_unique<Capacitor>(*this);}

  // Implementation of the Capacitor specific methods //

  // Getter
  double Capacitor::getCapacitance() const
  {return Capacitance;}

  // Setter
  void Capacitor::setCapacitance(double capIn)
  { // Validation for Capacitance
    if (capIn < 0.0)
    {
      throw std::invalid_argument("Capacitance not allowed to be negative.");
    }
    Capacitance = capIn;
    updateImpedance(); // Use helper method
  }

   // Implementation of the helper method to update the impedance
  void Capacitor::updateImpedance()
  { // In a Capacitor: Resistance = Re[Impedance] = |Impedance| ; no phase shift
    if (Frequency > 0.0)
    {
      // Z = jX = 1/(jwC) = -j/(wC) ; So X (reactance) = -1/wC = 1/(2*pi*f*C)
      double reactance = - 1.0 / (2.0 * pi * Frequency * Capacitance);
      Impedance = std::complex<double>(0.0, reactance);
      magnitudeOfImpedance = std::abs(Impedance);
      phaseDifference = -pi/2;
    }
    else
    { // Infinite impedance case for 0 Frequency
      // Set a really large value to simulate infinity ---> Turns into D.C. component
      Impedance = std::complex<double>(0.0, -1.0e15);
      magnitudeOfImpedance = 1.0e15;
      phaseDifference = -pi/2;
    }
  }

// Implementation of the Components methods

  // The Getters
  std::string Capacitor::getType() const
  {return componentType;} // Returns "Capacitor" from parameterized constructor

  std::complex<double> Capacitor::getImp() const
  {return Impedance;}

  double Capacitor::getMagn() const
  {return magnitudeOfImpedance;}

  double Capacitor::getFreq() const
  {return Frequency;}
  
  double Capacitor::getPhsDiff() const
  {return phaseDifference;}
  // The Setters
  void Capacitor::setType(const std::string &compType)
  {componentType = compType;}

  void Capacitor::setImp(std::complex<double> impIn)
  { // Here will now use R=Re[I] and phasedifference=Arg[I]
    Impedance = impIn;
    magnitudeOfImpedance = std::abs(impIn);
    phaseDifference = std::arg(impIn);
  }

  void Capacitor::setMagn(double magnIn)
  { // Check if magnitude is negative, mustn't be 
    if (magnIn < 0.0)
    {
      throw std::invalid_argument("Impedance magnitude cannot be negative.");
    }
    magnitudeOfImpedance = magnIn;
    Impedance = std::polar(magnIn, -pi/2); // Z = |Z|exp(arg(phi))

    if (Frequency > 0.0)
    {
      Capacitance = 1.0 / (2.0 * pi * Frequency * magnIn); // C = 1/(w*f*|Z|) = 1/(2*pi*|Z|)
    }
  }

  void Capacitor::setFreq(double freqIn)
  {
    if (freqIn < 0.0)
    {throw std::invalid_argument("Frequency cannot be negative");}

    Frequency = freqIn;
    updateImpedance();
  }

  void Capacitor::setPhsDiff(double phsDiffIn)
  { // Check if phase is set to something other than 90 deg
    if (std::abs(phsDiffIn + pi/2) > 1e-6)
    {
      std::cerr << "Ideal capacitor should have a phase of -90 degrees." << std::endl;
    }
    phaseDifference = phsDiffIn;
  }
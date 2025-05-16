// Implementation of the derived Resistor class //

#include"resistor.h"
#include<iostream>
#include<cmath>
#include<stdexcept>

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

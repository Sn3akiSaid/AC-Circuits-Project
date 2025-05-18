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
      throw std::invalid_argument("Capacitance cannot be negative.");
    }
    updateImpedance(); // Use helper method
  }
#include"components.h"
#include<iostream>
#include<utility>
#include<stdexcept>

  // Constructor implementation
  Components::Components(const std::string &compType, 
                         std::complex<double> impIn,
                         double magnIn,
                         double freqIn,
                         double phsDiffIn) :
                         componentType{compType},
                         Impedance{impIn},
                         magnitudeOfImpedance{magnIn},
                         Frequency{freqIn},
                         phaseDifference{phsDiffIn}
                         {
                          // Checks to be added here
                         }

  Components::~Components(){}

  std::string Components::getType() const {return componentType;}
  // Use getters to return the Magnitude and Frequency from the impedance
  double Components::getMagn() const {return abs(Impedance);}
  double Components::getFreq() const {return arg(Impedance);}
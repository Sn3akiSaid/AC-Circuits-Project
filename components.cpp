#include"components.h"
#include<iostream>
#include<utility>
#include<stdexcept>

  Components::Components(const std::string &compType = "none", 
                         std::complex<double> impIn = 0.0,
                         double magnIn = 0.0,
                         double freqIn=0.0,
                         double phsDiffIn = 0.0) :
                         componentType{compType},
                         Impedance{impIn},
                         magnitudeOfImpedance{magnIn},
                         Frequency{freqIn},
                         phaseDifference{phsDiffIn}{}

  Components::~Components(){}

  std::string Components::getType() const {return componentType;}
  // Use getters to return the Magnitude and Frequency from the impedance
  double Components::getMagn() const {return abs(Impedance);}
  double Components::getFreq() const {return arg(Impedance);}
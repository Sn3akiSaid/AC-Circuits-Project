#ifndef COMPONENTS_H
#define COMPONENTS_H
#include<iostream>
#include<memory>
#include<string>
#include<complex>
#include<vector>
#include<cmath>
#include<initializer_list>

class Component {
protected:
  std::string componentType;
  std::complex<double> Impedance;
  double magnitudeOfImpedance;
  double Frequency;
  double phaseDifference;
  

public:
  Component(const std::string &compType = "none", std::complex<double> impIn = 0.0, double magnIn = 0.0, double freqIn=0.0, double phsDiffInn = 0.0);
  virtual ~Component() = default;

  // Getters
  std::string getType() const {return componentType;}
  std::complex<double> getImp() const {return Impedance;}
  double getMagn() const {return magnitudeOfImpedance;}
  double getFreq() const {return Frequency;}
  double getPhsDiff() const {return phaseDifference;}



};

#endif
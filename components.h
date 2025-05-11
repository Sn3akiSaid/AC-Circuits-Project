#ifndef COMPONENTS_H
#define COMPONENTS_H
#include<iostream>
#include<memory>
#include<string>
#include<complex>
#include<vector>
#include<cmath>
#include<initializer_list>

class Components {
protected:
  std::string componentType;
  std::complex<double> Impedance;
  double magnitudeOfImpedance;
  double Frequency;
  double phaseDifference;
  

public:
  Components(const std::string &compType = "none", std::complex<double> impIn = 0.0, double magnIn = 0.0, double freqIn=0.0, double phsDiffIn = 0.0);
  virtual ~Components() = default;

  // Getters
  std::string getType() const {return componentType;}
  std::complex<double> getImp() const {return Impedance;}
  double getMagn() const {return magnitudeOfImpedance;}
  double getFreq() const {return Frequency;}
  double getPhsDiff() const {return phaseDifference;}

  // Setters
  void setType(std::string &compType) {componentType = compType;}
  void setImp(std::complex<double> impIn) {Impedance = impIn;}
  void setMagn(double magnIn) {magnitudeOfImpedance = magnIn;}
  void setFreq(double freqIn) {Frequency = freqIn;}
  void setPhsDiff(double phsDiffIn) {phaseDifference = phsDiffIn;}



};

#endif
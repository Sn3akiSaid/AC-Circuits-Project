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
  virtual std::string getType() const = 0;
  virtual std::complex<double> getImp() const = 0;
  virtual double getMagn() const = 0;
  virtual double getFreq() const = 0;
  virtual double getPhsDiff() const = 0;

  // Setters
  virtual void setType(std::string &compType) = 0;
  virtual void setImp(std::complex<double> impIn) = 0;
  virtual void setMagn(double magnIn) = 0;
  virtual void setFreq(double freqIn) = 0;
  virtual void setPhsDiff(double phsDiffIn) = 0;



};

#endif
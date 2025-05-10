#ifndef RESISTOR_H
#define RESISTOR_H
#include"components.h"
#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<cmath>
#include<initializer_list>

class Resistor : public Component {
protected:
  double Resistance;

public:
    Resistor(double resistanceIn = 0.0);
    ~Resistor() override;


    double getResistance() const;
    void setResistance(double resistanceIn);

    // void print() const override {
    //     std::cout << "Resistor: " << name << ", Value: " << value << " Ohm" << std::endl;
    // }}
};
#endif
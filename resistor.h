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
    Resistor(std::string name, double value) : name(name), value(value) {}
    ~Resistor() override = default;

    std::string getName() const override {
        return name;
    }

    double getValue() const override {
        return value;[]
    }

    void setValue(double newValue) override {
        value = newValue;
    }

    void print() const override {
        std::cout << "Resistor: " << name << ", Value: " << value << " Ohm" << std::endl;
    }}

#endif
#ifndef COMPONENTS_H
#define COMPONENTS_H
#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<cmath>
#include<initializer_list>

class Component {
public:
    virtual ~Component() = default;
    virtual std::string getName() const = 0;
    virtual double getValue() const = 0;
    virtual void setValue(double value) = 0;
    virtual void print() const = 0;
};

#endif
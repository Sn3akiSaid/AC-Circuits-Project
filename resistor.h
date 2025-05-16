#ifndef RESISTOR_H
#define RESISTOR_H
#include"components.h"
#include<iostream>
#include<complex>
#include<memory>
#include<cmath>

class Resistor : public Components {
protected:
	double Resistance; // R in Ohms

public:

	// Constructor with resistance and frequency parameters
	Resistor(double resistanceIn = 0.0, double freqIn = 0.0);


	// Using Rule of Five
	// Going to use virtual methods here to allow for derived class later

	// Virtual destructor
	virtual ~Resistor() override = default;

	// Copy operations
	Resistor(const Resistor& other);												// Non virtual copy constructor
	virtual Resistor& operator=(const Resistor& other);			// Virtual copy assignment

	// Move Operations
	Resistor(Resistor&& other) noexcept;										// Non virtual move constructor
	virtual Resistor& operator=(Resistor&& other) noexcept; // Virtual move assignment

	// Clone method using "Virtual constructor idiom"
	virtual std::unique_ptr<Components> clone() const override;

	// The Resistor specific virtual getters and setters
	virtual double getResistance() const;
	virtual void setResistance(double resistanceIn);

	// Override ALL of the Components virtual methods

	// Getters
	virtual std::string getType() const override;
	virtual std::complex<double> getImp() const override;
	virtual double getMagn() const override;
	virtual double getFreq() const override;
	virtual double getPhsDiff() const override;

	// Setters
	virtual void setType(std::string &compType) override;
	virtual void setImp(std::complex<double> impIn) override;
	virtual void setMagn(double magnIn) override;
	virtual void setFreq(double freqIn) override;
	virtual void setPhsDiff(double phsDiffIn) override;

		// void print() const override {
		//     std::cout << "Resistor: " << name << ", Value: " << value << " Ohm" << std::endl;
		// }}
};
#endif
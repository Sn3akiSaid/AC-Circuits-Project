#ifndef CAPACITOR_H
#define CAPACITOR_H
#include"Components.h"
#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<cmath>
#include<initializer_list>

class Capacitor : public Components {
protected:
	double Capacitance; // C in Farads

public:

	// Constructor with Capacitance and frequency parameters
	Capacitor(double capIn = 0.0, double freqIn = 0.0);


	// Using Rule of Five
	// Going to use virtual methods here to allow for derived class later

	// Virtual destructor
	virtual ~Capacitor() override = default;

	// Copy operations
	Capacitor(const Capacitor& other);												// Non virtual copy constructor
	virtual Capacitor& operator=(const Capacitor& other);			// Virtual copy assignment

	// Move Operations
	Capacitor(Capacitor&& other) noexcept;										// Non virtual move constructor
	virtual Capacitor& operator=(Capacitor&& other) noexcept; // Virtual move assignment

	// Clone method using "Virtual constructor idiom"
	virtual std::unique_ptr<Components> clone() const override;

	// The Capacitor specific virtual getters and setters
	virtual double getCapacitance() const;
	virtual void setCapacitance(double resIn);

	// Override ALL of the Components virtual methods

	// Getters
	virtual std::string getType() const override;
	virtual std::complex<double> getImp() const override;
	virtual double getMagn() const override;
	virtual double getFreq() const override;
	virtual double getPhsDiff() const override;

	// Setters
	virtual void setType(const std::string &compType) override;
	virtual void setImp(std::complex<double> impIn) override;
	virtual void setMagn(double magnIn) override;
	virtual void setFreq(double freqIn) override;
	virtual void setPhsDiff(double phsDiffIn) override;

	// Helper methods
	virtual void updateImpedance();
};
#endif
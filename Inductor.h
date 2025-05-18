#ifndef INDUCTOR_H
#define INDUCTOR_H
#include"Components.h"
#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<cmath>
#include<initializer_list>

class Inductor : public Components {
protected:
	double Inductance; // L in Henry

public:

	// Constructor with Inductance and frequency parameters
	Inductor(double resIn = 0.0, double freqIn = 0.0);


	// Using Rule of Five
	// Going to use virtual methods here to allow for derived class later

	// Virtual destructor
	virtual ~Inductor() override = default;

	// Copy operations
	Inductor(const Inductor& other);												// Non virtual copy constructor
	virtual Inductor& operator=(const Inductor& other);			// Virtual copy assignment

	// Move Operations
	Inductor(Inductor&& other) noexcept;										// Non virtual move constructor
	virtual Inductor& operator=(Inductor&& other) noexcept; // Virtual move assignment

	// Clone method using "Virtual constructor idiom"
	virtual std::unique_ptr<Components> clone() const override;

	// The Inductor specific virtual getters and setters
	virtual double getInductance() const;
	virtual void setInductance(double resIn);

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
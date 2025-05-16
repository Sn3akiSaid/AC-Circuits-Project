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
//  Protected data members
protected:
	std::string componentType;
	std::complex<double> Impedance;
	double magnitudeOfImpedance;
	double Frequency;
	double phaseDifference;
	
// Public containing objects to be accessed by users
public:
	// Constructor declaration
	Components(const std::string &compType = "none",
						 std::complex<double> impIn = 0.0, 
						 double magnIn = 0.0,
						 double freqIn=0.0,
						 double phsDiffIn = 0.0);

	// Using Rule of Five

	// Virtual destructor
	virtual ~Components() = default;

	// Copy Operations
	Components(const Components& other) = default; 									// Non virtual copy constructor
	virtual Components& operator=(const Components& other);     		// Virtual copy assignment

	// Move Operations
	Components(Components&& other) noexcept;												// Non virtual move constructor
	virtual Components& operator=(Components&& other) noexcept; 		// Virtual move assignment

	// Virtual clone method implementing "Virtual Constructor idiom"
	virtual std::unique_ptr<Components> clone() const = 0;

	// Create purely virtual getters and setters
	
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
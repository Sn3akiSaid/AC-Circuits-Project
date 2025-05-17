#include"Components.h"
#include<iostream>
#include<utility>
#include<stdexcept>

  // Constructor implementation
  Components::Components(const std::string &compType, 
                         std::complex<double> impIn,
                         double magnIn,
                         double freqIn,
                         double phsDiffIn) :
                         componentType{compType},
                         Impedance{impIn},
                         magnitudeOfImpedance{magnIn},
                         Frequency{freqIn},
                         phaseDifference{phsDiffIn}
                         {
                          // Checks to be added here
                         }

  // Using Rule of Five

  // Call destructor
  // Components::~Components(){}

  // Implementation of the Constructors

	// Copy constructor
  Components::Components(const Components& other) :
                         componentType{other.componentType},
												 Impedance{other.Impedance},
												 magnitudeOfImpedance{other.magnitudeOfImpedance},
												 Frequency{other.Frequency},
												 phaseDifference{other.phaseDifference}{}
  
  // Move constructor
  Components::Components(Components&& other) noexcept :
                         componentType{std::move(other.componentType)}, // Use std::move only for string, larger than double and complex
												 Impedance{other.Impedance},
												 magnitudeOfImpedance{other.magnitudeOfImpedance},
												 Frequency{other.Frequency},
												 phaseDifference{other.phaseDifference}{}

  
  // Implementation of Assignments

	// Copy assignment operator
	Components& Components::operator=(const Components& other)
	{
		if (this != &other)
		{ // Checking for self assignments
			componentType = other.componentType;
			Impedance = other.Impedance;
			magnitudeOfImpedance = other.magnitudeOfImpedance;
			Frequency = other.Frequency;
			phaseDifference = other.phaseDifference;
		} 
		return *this;
	}

	// Move assignment operator
	Components& Components::operator=(Components&& other) noexcept
	{ // Checking for self assignments
		if (this != &other)
		{
			componentType = std::move(other.componentType); // Again use move only for string
			Impedance = other.Impedance;
			magnitudeOfImpedance = other.magnitudeOfImpedance;
			Frequency = other.Frequency;
			phaseDifference = other.phaseDifference;
		}
		return *this;
	}



  // std::string Components::getType() const {return componentType;}
  // // Use getters to return the Magnitude and Frequency from the impedance
  // double Components::getMagn() const {return abs(Impedance);}
  // double Components::getFreq() const {return arg(Impedance);}
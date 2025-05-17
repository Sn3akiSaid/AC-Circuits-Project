#include"circuit.h"
#include<iostream>
#include<iomanip>

  Circuit::Circuit(const std::string& circName,
                   ConnectionType connType) :
                   circuitName(circName),
                   connectionType(connType) {}

  void Circuit::addComponent(std::unique_ptr<Components> component)
  {
    components.push_back(std::move(component));
  }

  std::complex<double> Circuit::getImp() const
  {
    if (components.empty())
    { // Check if there are components present
      return std::complex<double>(0.0,0.0);
    }
    std::complex<double> totalImp(0.0, 0.0);

    if (connectionType == ConnectionType::Series)
    {
      for (const auto& comp : components)
      {
        totalImp += comp->getImp();
      }
    }
    else
    { // Else calculate total for parallel configuration
      // 1/Z_t = 1/Z_1 + 1/Z_2 + ... 1/Z_n
      // Y=1/Z - This is called the Admittance
      std::complex<double> totalAdm(0.0, 0.0);

      // Take each component out of all components
      for (const auto& comp : components)
      { // Extract impedance for each component
        std::complex<double> impComp = comp->getImp();

        // Check if there for division by 0 cases
        if (impComp != std::complex<double>(0.0, 0.0))
         // Compute the total admitance
        {totalAdm += std::complex<double>(1.0, 0.0) / impComp;}
      }
      // Do another check for division by 0 
      if (totalAdm != std::complex<double>(0.0, 0.0))
      {totalImp = std::complex<double>(0.0,0.0) / totalAdm;}
    }
    return totalImp;
  }

  // Get absolute and argument of impedance = magnitude and phase shift
  double Circuit::getMagn() const
  {return std::abs(getImp());}

  double Circuit::getPhsDiff() const
  {return std::arg(getImp());}

  void Circuit::setFreq(double freq)
  {for (auto& comp : components) {comp->setFreq(freq);}  }


//--- CIRCUIT VISUALISER ---//
  void Circuit::circuitVisualiser() const
  {
    std::cout << "Circuit with " << components.size() << " components:\n";
    for (const auto& comp : components)
    {
      std::cout << "- " << comp->getType() << ":"
                << comp->getMagn() << " Ω\n";
    } 
    std::complex<double> Z = getImp();
    std::cout << "Total impedance: " << std::abs(Z) << " Ω\n";
  }
  
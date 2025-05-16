#include"circuit.h"
#include<iostream>
#include<iomanip>

  Circuit::Circuit(const std::string& circName,
                   ConnectionType connType) :
                   circuitName(circName),
                   connectionType(connType) {}

  void Circuit::addComponent(std::unique_ptr<Components> component)
  {
    elements.push_back(std::move(component));
  }

  std::complex<double> Circuit::getImp() const
  {
    if (elements.empty())
    { // Check if there are components present
      return std::complex<double>(0.0,0.0);
    }
    std::complex<double> totalImp(0.0, 0.0);

    if (connectionType == ConnectionType::Series)
    {
      for (const auto& component : elements)
      {
        totalImp += component->getImp();
      }
    }
    else
    { // Else calculate total for parallel configuration
      // 1/Z_t = 1/Z_1 + 1/Z_2 + ... 1/Z_n
      // Y=1/Z - This is called the Admittance
      std::complex<double> totalAdm(0.0, 0.0);
    }

    for (const auto& comp : elements)
    {
      totalImp += comp->getImp();
    }
    return totalImp;
  }

  void Circuit::circuitVisualiser() const
  {
    std::cout << "Circuit with " << elements.size() << " components:\n";
    for (const auto& comp : elements)
    {
      std::cout << "- " << comp->getType() << ":"
                << comp->getMagn() << " Ω\n";
    } 
    std::complex<double> Z = getImp();
    std::cout << "Total impedance: " << std::abs(Z) << " Ω\n";
  }
  
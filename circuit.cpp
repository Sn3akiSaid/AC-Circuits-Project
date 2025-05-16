#include"circuit.h"
#include<iostream>

  void Circuit::addComponent(std::unique_ptr<Components> component)
  {
    elements.push_back(std::move(component));
  }

  std::complex<double> Circuit::getImpedance() const
  {
    std::complex<double> totalZ(0.0, 0.0);
    for (const auto& comp : elements)
    {
      totalZ += comp->getImp();
    }
    return totalZ;
  }

  void Circuit::Display() const
  {
    std::cout << "Circuit with " << elements.size() << " components:\n";
    for (const auto& comp : elements)
    {
      std::cout << "- " << comp->getType() << ":"
                << comp->getMagn() << " Ω\n";
    } 
    std::complex<double> Z = getImpedance();
    std::cout << "Total impedance: " << std::abs(Z) << " Ω\n";
  }
  
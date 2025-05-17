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
    std::cout << "\n=====" << circuitName << " (" << (connectionType == ConnectionType::Series ? "Series" : "Parallel") 
              << ") =====\n";

    if (components.empty())
    {
      std::cout << "This circuit is empty.\n";
      return;
    }



    if (connectionType == ConnectionType::Series)
    {
      std::cout << "---";
      for (const auto& comp : components)
      {
        std::cout << "[" << comp->getType() << ":"
                  << comp->getMagn() << "Ω]---";
      }
      std::cout << "\n";
    } 
    else
    {
      std::cout << " ";
      for (size_t i = 0; i < components.size(); i++)
      {
        std::cout <<  "┌──[" << components[i]->getType() << ":" 
                  << components[i]->getMagn() << "Ω]──┐";
        if (i < components.size() - 1) std::cout << "\n ";
      }
      std::cout << "\n";
    }
    std::complex<double> impedance = getImp();
    std::cout << "\nTotal impedance: " << std::abs(impedance) << " Ω\n"
              << " Ω ∠ " << (std::arg(impedance) * 180.0 / M_PI) << "°\n";
  }
  
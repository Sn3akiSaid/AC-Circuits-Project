#include"Circuit.h"
#include<iostream>
#include<iomanip>
#ifndef pi
#define pi 3.14159265358979323846
#endif
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
      {totalImp = std::complex<double>(1.0,0.0) / totalAdm;}
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
  { // Output the type of circuit
    std::cout << "\n=====" << circuitName << " (" << (connectionType == ConnectionType::Series ? "Series" : "Parallel") 
              << ") =====\n";

    if (components.empty())
    { // Empty circuit checks
      std::cout << "This circuit is empty.\n";
      return;
    }



    if (connectionType == ConnectionType::Series)
    { // Visualisation for SERIES Circuit
      std::cout << "---";
      for (const auto& comp : components)
      {
        std::cout << "[" << comp->getType() << ":"
                  << comp->getMagn() << "Ω]---";
      }
      std::cout << "\n";
    } 
    else
    { // Visualisation for PARALLEL Circuit
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
              << " Ω ∠ " << (std::arg(impedance) * 180.0 / pi) << "°\n";
  }
  
//--- Circuit with detailed components ---//
  void Circuit::detailedCircuitVisualiser() const
  {
    std::cout << "\n===== " << circuitName << " ("
              << (connectionType == ConnectionType::Series ? "Series" : "Parallel")
              << ")=====\n\n";

    if (components.empty())
    { // Check for empty circuit
      std::cout << "This circuit is empty.\n";
      return;
    }

    // Display the basic circuit schematic
    // circuitVisualiser();

    // Now add detailed component info
    std::cout << "\nComponent Details:\n";
    std::cout << std::string(50, '-') << "\n"; // Add 50 dashed lines
    std::cout << std::left << std::setw(5) << "#" // Use left positioning
              << std::setw(12) << "Type"
              << std::setw(15) << "Z (Ω)"
              << std::setw(15) << "|Z| (Ω)"
              << "Δφ (°)\n";

              // Non - ASCII for compatibility

              // << std::setw(12) << "Type"
              // << std::setw(15) << "Z (Ohms)"
              // << std::setw(15) << "|Z| (Ohms)"
              // << "Phase Difference (deg)\n";
    std::cout << std::string(50, '-') << "\n";

    for (size_t i = 0; i <components.size(); i++)
    {
      std::complex<double> imp = components[i]->getImp();
      std::ostringstream impStream;
      impStream << std::fixed << std::setprecision(2) << imp.real() << " + j" << imp.imag();
      std::cout << std::left << std::setw(5) << (i+1)
                << std::setw(12) << components[i]->getType()
                << std::setw(15) << impStream.str()
                << std::setw(15) << components[i]->getMagn()
                << std::fixed << std::setprecision(1)
                << (components[i]->getPhsDiff() * 180.0 / pi) << "\n";
    }

    std::cout << std::string(50, '-') << "\n";
    std::ostringstream totalImpStream;
    std::complex<double> totalImp = getImp();
    std::cout << std::left << std::setw(5) << "Total "
              << std::setw(12) << "Circuit"
              << std::setw(15) << totalImpStream.str()
              << std::setw(15) << getMagn()
              << std::fixed << std::setprecision(1)
              << (getPhsDiff() * 180.0 / pi) << "\n";
    std::cout << std::string(50, '-') << "\n\n";
  }

  void Circuit::numberedCircuitVisualiser() const
  {
    std::cout << "\n===== " << circuitName << " ("
              << (connectionType == ConnectionType::Series ? "Series" : "Parallel")
              << ") with Nodes =====\n\n";

    if (components.empty())
    { // Check if circuit is empty
      std::cout << "This circuit is empty.\n";
      return;
    }

    if (connectionType == ConnectionType::Series)
    { // Add nodes in a sequence for series
      std::cout << "[0]";
      for (size_t i = 0; i <components.size(); i++)
      {
        std::cout << "---[" << components[i]->getType() << ":"
                  << components[i]->getMagn() << " Ohm]---["
                  << (i+1) << "]";
      }
      std::cout << "\n\n";

      // Information table for the nodes in the circuit
      std::cout << "Node Information:\n";
      std::cout << std::string(30, '-') << "\n";
      std::cout << "Node | Connected Components\n";
      std::cout << std::string(30, '-') << "\n";

  //---- Connections ----//
      // Connect first node to first component
      std::cout << "0  | " << components[0]->getType() << "\n";

      // Middle nodes connect to one on each side
      for (size_t i = 1; i < components.size(); i++)
      {
        std::cout << " " << i << "  | " << components[i-1]->getType()
                  << ", " << components[i]->getType() << "\n";
      }

      // Connect final node to last component
      std::cout << " " << components.size() 
                << "  | " << components[components.size()-1]->getType() << "\n";
      std::cout << std::string(30, '-') << "\n";
    }
    else
    { // Add nodes in parallel 
      std::cout << "[0]";
      for (size_t i = 0; i < components.size(); i++)
      {
        if (i == 0) std::cout << "---";
                    std::cout << "\n  ";
                    std::cout << "+---[" << components[i]->getType() << ":"
                                         << components[i]->getMagn() << " Ohm]---+";
        if (i == components.size() - 1) std::cout << "\n  ---";
      }
      std::cout << "[1]\n\n";

      // Node information for the parallel connections
      std::cout << "Node information:\n";
      std::cout << std::string(40, '-') << "\n";
      std::cout << "Node | Connected Components\n";
      std::cout << std::string(40, '-') << "\n";
    }
  }
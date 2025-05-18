#include"Circuit.h"
#include<iostream>
#include<iomanip>
#ifndef pi
#define pi 3.14159265358979323846
#endif

  Circuit::Circuit(const std::string& name, ConnectionType connType) :
                   Components("Circuit", std::complex<double>(0.0, 0.0), 0.0, 0.0, 0.0),
                   circuitName(name),
                   connectionType(connType){}

  void Circuit::addComponent(std::unique_ptr<Components> component)
  {components.push_back(std::move(component));}

  std::complex<double> Circuit::getImp() const
  {
    if (components.empty())
    { // Check if there are components present
      return std::complex<double>(0.0, 0.0);
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

  std::string Circuit::getType() const
  {return componentType;}
  
  double Circuit::getFreq() const
  {
    if (!components.empty())
    {
      double totalFreq = 0.0;
      for (const auto& comp : components)
      {totalFreq += comp->getFreq();}
      return totalFreq / components.size();
    }
    return Frequency;
  }

  // Setters
  void Circuit::setType(const std::string &compType)
  {componentType = compType;}


  // Setters for Z, |Z| and arg(Z) - These do not affect individual components values
  void Circuit::setImp(std::complex<double> impIn)
  {
    Impedance = impIn;
    magnitudeOfImpedance = std::abs(impIn);
    phaseDifference = std::arg(impIn);
  }

  void Circuit::setMagn(double magnIn)
  { // Check for invalid impedance magnitude
    if (magnIn < 0.0)
    {throw std::invalid_argument("|Z| cannot be negative.");}

    // Keep phase, update magnitude
    magnitudeOfImpedance = magnIn;
    Impedance = std::polar(magnIn, phaseDifference); // Use polar coordinates Z = |Z|e^(j*arg(Z))
  }

  void Circuit::setPhsDiff(double phsDiffIn)
  {
    // Keep magnitude, update phase
    phaseDifference = phsDiffIn;
    Impedance = std::polar(magnitudeOfImpedance, phsDiffIn); // Use polar coordinates Z = |Z|e^(j*arg(Z))
  }

  // Implement the clone method
  std::unique_ptr<Components> Circuit::clone() const
  { // Create new circuit with same name and type
    auto circuitCopy = std::make_unique<Circuit>(circuitName, connectionType);

    // Clone + Add all components
    for (const auto& comp : components)
    {circuitCopy->addComponent(comp->clone());}

    return circuitCopy;
  }


// Implementation of Nested Circuits //

  // SERIES //
  void Circuit::addSeriesComponent(std::unique_ptr<Components> component)
  {
    if (connectionType == ConnectionType::Series)
    { // Check if already in series, if so just add component
      components.push_back(std::move(component));
    } 
    else
    { // Check if parallel circuit, create a series Nested Circuit
      auto seriesCircuit = std::make_unique<Circuit>("Series Nested Circuit", ConnectionType::Series);
      seriesCircuit->addComponent(std::move(component));
      components.push_back(std::move(seriesCircuit));
    }
  }

  // PARALLEL //
  void Circuit::addParallelComponent(std::unique_ptr<Components> component)
  {
    if (connectionType == ConnectionType::Parallel)
    { // Check if already in parallel, if so just add the component
      components.push_back(std::move(component));
    } 
    else
    { // Check if series circuit, create a parallel Nested Circuit
      auto parallelCircuit = std::make_unique<Circuit>("Parallel Nested Circuit", ConnectionType::Parallel);
      parallelCircuit->addComponent(std::move(component));
      components.push_back(std::move(parallelCircuit));
    }
  }

  // Create and return a new series circuit
  std::unique_ptr<Circuit> Circuit::createSeriesCircuit()
  {return std::make_unique<Circuit>("Series Nested Circuit", ConnectionType::Series);}

  // Create and return a new parallel circuit
  std::unique_ptr<Circuit> Circuit::createParallelCircuit()
  {return std::make_unique<Circuit>("Parallel Nested Circuit", ConnectionType::Parallel);}

  void Circuit::displayComponentsDetailed(const std::vector<std::unique_ptr<Components>>& comps, 
                                       int depth, int& index) const
  {
    std::string indent(depth * 2, ' ');
    
    for (const auto& comp : comps)
    { // Check if component is a actually a nested circuit-not an actual component
      // if yes -> assigns the circuit pointer to a nested circuit
      if (auto nestedCircuit = dynamic_cast<const Circuit*>(comp.get()))
      { // Display nested circuit header
        if (nestedCircuit->getCompCount() == 1)
        { // Checks if nested circuit has only one component (so not a nested circuit)
          // and processes it like a normal component
          displayComponentsDetailed(nestedCircuit->components, depth, index);
        }
        else
        { // If there are more components and it is nested, start treating it as so
        std::complex<double> imp = nestedCircuit->getImp();
        // Display the Z=R+jX in Cartesian
        std::ostringstream impStream;
        impStream << std::fixed << std::setprecision(2) 
                  << imp.real() << " + j" << imp.imag();
        
        // Process the nest, find out what type of configuration it has by 
        // passing pointer to connection type getter
        std::string label = (nestedCircuit->getConnType() == ConnectionType::Series)
                          ? "Series Group" : "Parallel Group";
        label += " (" + std::to_string(nestedCircuit->getCompCount()) + " items)";
        std::cout << std::left
                  << std::setw(5) << (++index)
                  << std::setw(35) << (indent + label)
                  << std::setw(20) << impStream.str()
                  << std::setw(15) << nestedCircuit->getMagn()
                  << std::fixed << std::setprecision(1)
                  << (nestedCircuit->getPhsDiff() * 180.0 / pi) << "\n";
        // Recursively show its contents, with increased depth
        displayComponentsDetailed(nestedCircuit->components, depth + 1, index);
        }
      }
      else
      { // Display for individual components
        std::complex<double> imp = comp->getImp();
        std::ostringstream impStream;
        impStream << std::fixed << std::setprecision(2) 
                  << imp.real() << " + j" << imp.imag();
                     
        // Create a string that will differentiate between individual components
        // and individual components within a group/nest
        std::string componentLabel;
        if (depth > 0)
        { // If there is nesting detected, will add symbols to visualise parallel subcircuit
          componentLabel = indent + "+--" + comp->getType() + "--+";
        }
        else
        { // Else (no nesting, just regular series) only show the component type
          componentLabel = indent + comp->getType();
        }
        std::cout << std::left
                  << std::setw(5) << (++index)
                  << std::setw(35) << componentLabel
                  << std::setw(20) << impStream.str()
                  << std::setw(15) << comp->getMagn()
                  << std::fixed << std::setprecision(1)
                  << (comp->getPhsDiff() * 180.0 / pi) << "\n";
        }
    }
}

// Public wrapper that initializes the index variable
  void Circuit::displayComponentsDetailed(const std::vector<std::unique_ptr<Components>>& comps,
                                          int depth) const
  {
    int startIndex = 0;
    displayComponentsDetailed(comps, depth, startIndex);
  }


//--- Circuit with detailed components ---//
  void Circuit::detailedCircuitVisualiser() const
  {
    std::cout << "\n===== " 
              << (connectionType == ConnectionType::Series ? "Series" : "Parallel")
              << " Circuit (" << getCompCount() << " items)" 
              << "=====\n\n";

    if (components.empty())
    { // Check for empty circuit
      std::cout << "This circuit is empty.\n";
      return;
    }
    // Now add detailed component info
    std::cout << "\nComponent Details:\n";
    std::cout << std::string(90, '-') << "\n"; // Add 50 dashed lines
    std::cout << std::left
              << std::setw(5) << "#" // Use left positioning
              << std::setw(35) << "Component"
              << std::setw(20) << "Impedance, Z (Ohm)"
              << std::setw(15) << "|Z| (Ohm)"
              << "Phase (degrees)\n";

    std::cout << std::string(90, '-') << "\n";

    displayComponentsDetailed(components, 0);

    std::cout << std::string(90, '-') << "\n";
    std::complex<double> totalImp = getImp();
    std::ostringstream totalImpStream;
    totalImpStream << std::fixed << std::setprecision(2) 
                   << totalImp.real() << " + j" << totalImp.imag();

    std::cout << std::left
              << std::setw(5) << "Total "
              << std::setw(35) << "Circuit"
              << std::setw(20) << totalImpStream.str()
              << std::setw(15) << getMagn()
              << std::fixed << std::setprecision(1)
              << (getPhsDiff() * 180.0 / pi) << "\n";
    std::cout << std::string(90, '-') << "\n\n";
  }

//// ------------------------ ////
////--- CIRCUIT VISUALISER ---////
//// ------------------------ ////

  // Implementation of the ASCII visualiser
  void Circuit::asciiSchematicVisualiser() const
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
      std::cout << "---";
      for (size_t i = 0; i <components.size(); i++)
      {
        std::cout << "[" << components[i]->getType() << ":"
                  << components[i]->getMagn() << " Ohm]---";
      }
      std::cout << "\n\n";
    }
    else
    { // Add nodes in PARALLEL 
      size_t maxLen = 0;
      std::vector<std::string> branches;
      for (const auto& comp : components)
      {
        std::ostringstream oss;
        oss << "   |---[" << comp->getType() << ":" << comp->getMagn() << " Ohm]---|";
        std::string s = oss.str();
        if (s.size() > maxLen) maxLen = s.size();
        branches.push_back(s);
      }
      
      // Go through each branch
      for (size_t i = 0; i < branches.size(); ++i)
      {
        std::cout << branches[i] << "\n";
          if (i != branches.size() - 1)
          { // Add connection between parallel branches
            std::cout << "   |" << std::string(maxLen-5, ' ') << "|\n";
          }
          else
          { // Add simple buses 
            std::cout << "---|" << std::string(maxLen-5, ' ') << "|---\n";
          }
      }
    }
  }

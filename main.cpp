#include"resistor.h"
#include"circuit.h"
#include<iostream>
#include<memory>

int main(){

  Circuit myCircuit;

  myCircuit.addComponent(std::make_unique<Resistor>(100.0));

  myCircuit.Display();

  return 0;
}
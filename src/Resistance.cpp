#include "Resistance.hpp"


void    Resistance::setValue(double Value){
    if (this->CheckValue(Value)) this->Value = Value;
    else throw std::underflow_error("Bad resistance value detected");
}


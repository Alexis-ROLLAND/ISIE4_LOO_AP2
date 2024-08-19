#include "Resistance.hpp"


void    Resistance::setValue(double Value){
    if (this->CheckValue(Value)) this->Value = Value;
    else throw std::underflow_error("Bad resistance value detected");
}

PositiveResistance  makeParallelResistance(const PositiveResistance &r1, const PositiveResistance &r2){
    double parValue = (r1.getValue() * r2.getValue()) / (r1.getValue() + r2.getValue());
    return PositiveResistance{parValue};
}

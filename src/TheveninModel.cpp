#include "TheveninModel.hpp"

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
[[nodiscard]]   Voltage  TheveninModel::getOutputVoltageByCurrent(Current Iout) const{

    Voltage Vab = this->getEth() - this->getRth().getValue() * Iout;

    // If Vab and Eth aren't of same sign - Current is too high !
    if (std::signbit(Vab) != std::signbit(this->getEth())) throw std::overflow_error{"Current is too High"}; 

    return Vab;
}
//----------------------------------------------------------------------------
[[nodiscard]]   double  TheveninModel::getOutputVoltageByCharge(PositiveResistance Charge) const noexcept{

    double Coef = Charge.getValue() / (this->getRth().getValue() + Charge.getValue());

    return this->getEth() * Coef;
}
//----------------------------------------------------------------------------
std::tuple<Voltage, Current> TheveninModel::getOutputVoltageAndCurrent(PositiveResistance Charge) const noexcept{

    double Iout = this->getEth() / (this->getRth().getValue() + Charge.getValue());
    double Vab = this->getOutputVoltageByCharge(Charge);

    return std::make_tuple(Vab,Iout);
}
//----------------------------------------------------------------------------




#include "TheveninModel.hpp"

TheveninModel::TheveninModel(double E, double R){
    this->setEth(E);
    this->setRth(R);
}


[[nodiscard]]   double  TheveninModel::getOutputVoltageByCurrent(double Current) const {

double Vab = this->getEth() - this->getRth() * Current;

// If Vab and Eth aren't of same sign - Current is too high !
if (std::signbit(Vab) != std::signbit(this->getEth())) throw std::overflow_error{"Current is too High"}; 

return Vab;
}

[[nodiscard]]   double  TheveninModel::getOutputVoltageByCharge(double Charge) const {
    if (Charge < 0) throw NegativeResistance{};
    double Coeff{};
    try {
        Coeff = Charge / (this->getRth() + Charge);
    }
    catch (const std::exception& e) { 
        throw;  //**< Rethrow exception if divide by zero is caught */
    }

    return this->getEth() * Coeff;
}

std::tuple<double, double> TheveninModel::getOutputVoltageAndCurrent(double Charge) const {
    if (Charge < 0) throw NegativeResistance{};

    double Iout = this->getEth() / (this->getRth() + Charge);
    double Vab = this->getOutputVoltageByCharge(Charge);

    return std::make_tuple(Vab,Iout);
}





#include "TheveninModel.hpp"

//----------------------------------------------------------------------------
TheveninModel::TheveninModel(double E, Resistance R){
    this->setEth(E);
    this->setRth(R);
    this->setModelOK();
}
//----------------------------------------------------------------------------
void    TheveninModel::setEth(double Eth){
    if (typeid(*this) != typeid(TheveninModel)) throw std::bad_typeid{}; 
    this->Eth = Eth;
}
//----------------------------------------------------------------------------
void    TheveninModel::setRth(const Resistance &Rth){
    if (typeid(*this) != typeid(TheveninModel)) throw std::bad_typeid{}; 
    this->Rth = Rth;
}
//----------------------------------------------------------------------------
[[nodiscard]]   double  TheveninModel::getOutputVoltageByCurrent(double Current) const {

    if (!this->isModelOK()) this->updateModel();
   
    double Vab = this->getEth() - this->getRth().getValue() * Current;

    // If Vab and Eth aren't of same sign - Current is too high !
    if (std::signbit(Vab) != std::signbit(this->getEth())) throw std::overflow_error{"Current is too High"}; 

    return Vab;
}
//----------------------------------------------------------------------------
[[nodiscard]]   double  TheveninModel::getOutputVoltageByCharge(PositiveResistance Charge) const {
    if (!this->isModelOK()) this->updateModel();

    double Coef = Charge.getValue() / (this->getRth().getValue() + Charge.getValue());

    return this->getEth() * Coef;
}
//----------------------------------------------------------------------------
std::tuple<double, double> TheveninModel::getOutputVoltageAndCurrent(PositiveResistance Charge) const {
if (!this->isModelOK()) this->updateModel();

    double Iout = this->getEth() / (this->getRth().getValue() + Charge.getValue());
    double Vab = this->getOutputVoltageByCharge(Charge);

    return std::make_tuple(Vab,Iout);
}
//----------------------------------------------------------------------------




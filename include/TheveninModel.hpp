#ifndef __THEVENIN_MODEL_HPP__
#define __THEVENIN_MODEL_HPP__

#include <cmath>    /**< for std::signbit */
#include <stdexcept>
#include <tuple>

#include "Resistance.hpp"

class TheveninModel
{
private:
    double      Eth{0};
    Resistance  Rth{0};
    mutable     bool        modelIsOK{true};
protected:
    [[nodiscard]]   bool    isModelOK() const noexcept {return this->modelIsOK;};
    void    setModelOK() const noexcept {this->modelIsOK = true;};
    void    setModelNotOK() const noexcept {this->modelIsOK = false;};
    virtual void updateModel() const {};
public:
    TheveninModel() = default;
    virtual ~TheveninModel() = default;
    TheveninModel(double E, Resistance R);

    void    setEth(double Eth); 
    [[nodiscard]]   double  getEth() const noexcept {if (!this->isModelOK()){this->updateModel();}; return this->Eth;};

    void    setRth(const Resistance &Rth);
    [[nodiscard]]   Resistance  getRth() const noexcept {if (!this->isModelOK()){this->updateModel();}; return this->Rth;};

    [[nodiscard]]   double  getOutputVoltageByCurrent(double Current) const ;   /**< Current is the output current in A */
    [[nodiscard]]   double  getOutputVoltageByCharge(PositiveResistance Charge) const ;     /**< Charge is the charge in Ohm */

    [[nodiscard]]  std::tuple<double, double> getOutputVoltageAndCurrent(PositiveResistance Charge) const ; /**<  Charge is the charge in Ohm  */ 
};

#endif  /*  __THEVENIN_MODEL_HPP__  */


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
public:
    TheveninModel() = default;
    virtual ~TheveninModel() = default;
    TheveninModel(double E, Resistance R);

    void    setEth(double Eth) noexcept {this->Eth = Eth;};
    [[nodiscard]]   double  getEth() const noexcept {return this->Eth;};

    void    setRth(const Resistance &Rth)  {this->Rth = Rth;};
    [[nodiscard]]   Resistance  getRth() const noexcept {return this->Rth;};

    [[nodiscard]]   double  getOutputVoltageByCurrent(double Current) const ;   /**< Current is the output current in A */
    [[nodiscard]]   double  getOutputVoltageByCharge(PositiveResistance Charge) const ;     /**< Charge is the charge in Ohm */

    [[nodiscard]]  std::tuple<double, double> getOutputVoltageAndCurrent(PositiveResistance Charge) const ; /**<  Charge is the charge in Ohm  */ 
};

#endif  /*  __THEVENIN_MODEL_HPP__  */


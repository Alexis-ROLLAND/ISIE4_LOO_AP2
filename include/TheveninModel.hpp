#ifndef __THEVENIN_MODEL_HPP__
#define __THEVENIN_MODEL_HPP__

#include <cmath>    /**< for std::signbit */
#include <stdexcept>
#include <tuple>

#include "Resistance.hpp"

using   Voltage = double;   /**< Alias to double for Voltage variables */
using   Current = double;   /**< Alias to double for Current variables */

class TheveninModel
{
private:
    Voltage     Eth{0};     /**< Eth in Volt */
    Resistance  Rth{0};     /**< Rth in Ohm */
    
protected:
    
    
    void    _setEth(Voltage Eth) noexcept {this->Eth = Eth;}; 
    void    _setRth(const Resistance &Rth) noexcept {this->Rth = Rth;};
    
public:
    TheveninModel() = default;              /**< Default constructor given by compilator */
    virtual ~TheveninModel() = default;     /**< Defaulted destructor */
    TheveninModel(Voltage E, Resistance R):Eth{E},Rth{R}{};  /**< Overloaded constructor */

    [[nodiscard]]   Voltage     getEth() const noexcept {return this->Eth;};
    [[nodiscard]]   Resistance  getRth() const noexcept {return this->Rth;};

    [[nodiscard]]   Voltage  getOutputVoltageByCurrent(Current Iout) const;   /**< Current is the output current in A */
    [[nodiscard]]   Voltage  getOutputVoltageByCharge(PositiveResistance Charge) const noexcept;     /**< Charge is the charge in Ohm */

    [[nodiscard]]   std::tuple<Voltage, Current> getOutputVoltageAndCurrent(PositiveResistance Charge) const noexcept; /**<  Charge is the charge in Ohm  */ 
};

class RealTheveninModel : public TheveninModel{
    private:

    protected:
        
    public:
        RealTheveninModel() = default;
        virtual ~RealTheveninModel() = default;
        RealTheveninModel(Voltage E, Resistance R):TheveninModel{E,R}{};

        void    setEth(Voltage Eth) noexcept {this->_setEth(Eth);};
        void    setRth(const Resistance &Rth) noexcept {this->_setRth(Rth);};

};


#endif  /*  __THEVENIN_MODEL_HPP__  */


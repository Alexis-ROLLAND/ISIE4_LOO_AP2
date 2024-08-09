#ifndef __THEVENIN_MODEL_HPP__
#define __THEVENIN_MODEL_HPP__

#include <stdexcept>
#include <tuple>

//----------------------------------------------------------------------------
// Déclaration de la classe d'exception personnalisée
class NegativeResistance : public std::underflow_error {
public:
    // Constructeur qui initialise l'exception avec un message fixe
    NegativeResistance() 
        : std::underflow_error("Resistance cannot be negative") {}
};
//----------------------------------------------------------------------------
class TheveninModel
{
private:
    double  Eth{0};
    double  Rth{0};
public:
    TheveninModel() = default;
    virtual ~TheveninModel() = default;
    TheveninModel(double E, double R);

    void    setEth(double Eth) noexcept {this->Eth = Eth;};
    [[nodiscard]]   double  getEth() const noexcept {return this->Eth;};

    void    setRth(double Rth)  {(Rth < 0.0) ? throw NegativeResistance{}  : this->Rth = Rth;};
    [[nodiscard]]   double  getRth() const noexcept {return this->Rth;};

    [[nodiscard]]   double  getOutputVoltageByCurrent(double Current) const ;   /**< Current is the output current in A */
    [[nodiscard]]   double  getOutputVoltageByCharge(double Charge) const ;     /**< Charge is the charge in Ohm */

    [[nodiscard]]  std::tuple<double, double> getOutputVoltageAndCurrent(double Charge) const ; /**<  Charge is the charge in Ohm  */ 
};
//----------------------------------------------------------------------------
class PontDiviseur : public TheveninModel{
    private:
        
        double  Vexcitation{};   /** Bridge's excitation voltage (in Volt) - Ground referenced  */
        double  Rhigh{};        /** High side resistor */
        double  Rlow{};        /** Low side resistor */
    
        void    Update();       /**< Updates the Eth and Rth values (if possible) */

    public:
        PontDiviseur() = default;
        virtual ~PontDiviseur() = default;

        [[nodiscard]] double getVexcitation() const noexcept {return this->Vexcitation;};
        [[nodiscard]] double getRhigh() const noexcept {return this->Rhigh;};
        [[nodiscard]] double getRlow() const noexcept {return this->Rlow;};

        void    setVexcitation(double Vcc) noexcept {this->Vexcitation = Vcc;this->Update();}; 
        void    setRhigh(double Res) { if(Res < 0.0){throw NegativeResistance{};} else {this->Rhigh = Res; this->Update();}};
        void    setRlow(double Res) { if (Res < 0.0){throw NegativeResistance{};} else {this->Rlow = Res; this->Update();}};

        double  getTensionAVide() noexcept {this->Update(); return this->getEth();};
        double  getOutputResistance() noexcept {this->Update(); return this->getRth();};
};









#endif  /*  __THEVENIN_MODEL_HPP__  */


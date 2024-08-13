#ifndef __PONT_DIVISEUR_HPP__
#define __PONT_DIVISEUR_HPP__

#include "TheveninModel.hpp"


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



#endif/*    __PONT_DIVISEUR_HPP__   */


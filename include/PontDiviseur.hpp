#ifndef __PONT_DIVISEUR_HPP__
#define __PONT_DIVISEUR_HPP__

#include "TheveninModel.hpp"

/**
 * Version "sécurisée" V2
 * Sécurisation par utilisation des types Resistance et PositiveResistance
 * 
 */
//----------------------------------------------------------------------------


class PontDiviseur : public TheveninModel{
    private:
        
        double  Vexcitation{};   /** Bridge's excitation voltage (in Volt) - Ground referenced  */
        PositiveResistance  Rhigh;        /** High side resistor */
        PositiveResistance  Rlow;        /** Low side resistor */
    
        virtual void updateModel() const  override  ;

    public:

        PontDiviseur() = delete;
        virtual ~PontDiviseur() = default;

        PontDiviseur(double Valim, const PositiveResistance &Rh, const PositiveResistance &Rl);

        [[nodiscard]] double getVexcitation() const noexcept {return this->Vexcitation;};
        [[nodiscard]] PositiveResistance getRhigh() const noexcept {return this->Rhigh;};
        [[nodiscard]] PositiveResistance getRlow() const noexcept {return this->Rlow;};

        void    setVexcitation(double Valim) noexcept {this->Vexcitation = Valim; this->setModelNotOK();};
        void    setRhigh(const PositiveResistance &Res) noexcept {this->Rhigh = Res; this->setModelNotOK();};
        void    setlow(const PositiveResistance &Res) noexcept {this->Rlow = Res; this->setModelNotOK();};




};



#endif/*    __PONT_DIVISEUR_HPP__   */


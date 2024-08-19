#ifndef __PONT_DIVISEUR_HPP__
#define __PONT_DIVISEUR_HPP__

#include "TheveninModel.hpp"

/**
 * Version "sécurisée" V2
 * Sécurisation par utilisation des types Resistance et PositiveResistance
 * et la transformation de la classe TheveninModel en classe virtuelle pure
 * (classe abstraite).
 */
//----------------------------------------------------------------------------


class PontDiviseur : public TheveninModel{
    private:
        
        Voltage  Vexcitation{};         /** Bridge's excitation voltage (in Volt) - Ground referenced  */
        PositiveResistance  Rhigh;        /** High side resistor */
        PositiveResistance  Rlow;        /** Low side resistor */
    
    protected:
       

    public:

        PontDiviseur() = delete;
        virtual ~PontDiviseur() = default;

        PontDiviseur(Voltage Valim, const PositiveResistance &Rh, const PositiveResistance &Rl);

        [[nodiscard]] Voltage getVexcitation() const noexcept {return this->Vexcitation;};
        [[nodiscard]] PositiveResistance getRhigh() const noexcept {return this->Rhigh;};
        [[nodiscard]] PositiveResistance getRlow() const noexcept {return this->Rlow;};

        void    setVexcitation(Voltage Valim) noexcept;        
        void    setRhigh(const PositiveResistance &Res) noexcept;
        void    setRlow(const PositiveResistance &Res) noexcept;
        

        Voltage getVoutAVide() const noexcept {return this->getEth();};
        PositiveResistance getOutputResistance() const noexcept {return PositiveResistance{this->getRth().getValue()};};


};



#endif/*    __PONT_DIVISEUR_HPP__   */


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
    


    public:




};



#endif/*    __PONT_DIVISEUR_HPP__   */


#ifndef __PONT_DIVISEUR_HPP__
#define __PONT_DIVISEUR_HPP__

#include "TheveninModel.hpp"

/**
 * Version "sécurisée" V1
 * Sécurisation par suppression du constructeur par défaut et assurance que les valeurs de Rhigh et Rlow ne sont pas nulles.
 * Création d'une exception spécifique "Resistance must be higher than zero"
 */
// Déclaration de la classe d'exception personnalisée
class NonPositiveResistance : public std::underflow_error {
public:
    // Constructeur qui initialise l'exception avec un message fixe
    NonPositiveResistance() 
        : std::underflow_error("Resistance must be higher than zero") {}
};
//----------------------------------------------------------------------------
class PontDiviseur : public TheveninModel{
    private:
        
        double  Vexcitation{};   /** Bridge's excitation voltage (in Volt) - Ground referenced  */
        double  Rhigh{};        /** High side resistor */
        double  Rlow{};        /** Low side resistor */
    
        void    Update();       /**< Updates the Eth and Rth values (if possible) */

    public:
        PontDiviseur() = delete;
        virtual ~PontDiviseur() = default;

        PontDiviseur(double Vexcitation, double Rhigh, double Rlow);

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


#include "PontDiviseur.hpp"

//----------------------------------------------------------------------------
//  Pont Diviseur class
//----------------------------------------------------------------------------
PontDiviseur::PontDiviseur(double Valim, const PositiveResistance &Rh, const PositiveResistance &Rl):Vexcitation{Valim}, Rhigh{Rh}, Rlow{Rl}{
    this->updateModel();
}

void PontDiviseur::updateModel() const {

    this->setModelOK();
}

#include "PontDiviseur.hpp"

//----------------------------------------------------------------------------
//  Pont Diviseur class
//----------------------------------------------------------------------------
PontDiviseur::PontDiviseur(double Vexcitation, double Rhigh, double Rlow):Vexcitation{Vexcitation}{
    if (Rhigh > 0.0) this->setRhigh(Rhigh);
    else throw NonPositiveResistance{};

    if (Rlow > 0.0) this->setRlow(Rlow);
    else throw NonPositiveResistance{};

    this->Update();
}
//----------------------------------------------------------------------------
void    PontDiviseur::Update(){
    if ((this->getRlow() <= 0.0) || (this->getRhigh() <= 0.0)) return;  

    double tmp = this->getVexcitation();

    // Let's begin with Eth
    tmp *= this->getRlow();
    tmp /= (this->getRhigh() + this->getRlow()); 

    this->setEth(tmp);

    // then, let's work with Rth
    tmp = this->getRhigh() * this->getRlow();
    tmp /= (this->getRhigh() + this->getRlow()); 

    this->setRth(tmp);

}


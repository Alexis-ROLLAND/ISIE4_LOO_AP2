#include "PontDiviseur.hpp"

//----------------------------------------------------------------------------
//  Pont Diviseur class
//----------------------------------------------------------------------------
void    PontDiviseur::Update(){
    if ((this->getRlow() == 0.0) || (this->getRhigh() == 0.0)) return;  /** One or both resistors are null, nothing can be done */

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


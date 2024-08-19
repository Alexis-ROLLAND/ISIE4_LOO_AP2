#include "PontDiviseur.hpp"

//----------------------------------------------------------------------------
//  Pont Diviseur class
//----------------------------------------------------------------------------
PontDiviseur::PontDiviseur(Voltage Valim, const PositiveResistance &Rh, const PositiveResistance &Rl):Vexcitation{Valim},
                                                                                                        Rhigh{Rh},
                                                                                                        Rlow{Rl}
                                                                                                    ,TheveninModel{Valim * (Rl.getValue() / (Rl.getValue() + Rh.getValue())),
                                                                                                    makeParallelResistance(Rh,Rl)}{                                                                                                                 

}

void    PontDiviseur::setVexcitation(Voltage Valim) noexcept{
    this->Vexcitation = Valim;

    double newEth = this->getVexcitation() * ( this->getRlow().getValue() / ( this->getRhigh().getValue() + this->getRlow().getValue() ) );
    this->_setEth(newEth);
}

void    PontDiviseur::setRhigh(const PositiveResistance &Res) noexcept{
    this->Rhigh = Res;

    double newEth = this->getVexcitation() * ( this->getRlow().getValue() / ( this->getRhigh().getValue() + this->getRlow().getValue() ) );
    this->_setEth(newEth);

    PositiveResistance newRth = makeParallelResistance(this->getRhigh(), this->getRlow());
    this->_setRth(newRth);

}

void    PontDiviseur::setRlow(const PositiveResistance &Res) noexcept{
    this->Rlow = Res;

    double newEth = this->getVexcitation() * ( this->getRlow().getValue() / ( this->getRhigh().getValue() + this->getRlow().getValue() ) );
    this->_setEth(newEth);

    PositiveResistance newRth = makeParallelResistance(this->getRhigh(), this->getRlow());
    this->_setRth(newRth);
}

#include <print>

#include "TheveninModel.hpp"


int main(){
    std::println("-- Test TheveninModel --");

    TheveninModel Th1{};

    std::println("Eth = {0:.2f} V - Rth = {1:.2f} Ohm",Th1.getEth(),Th1.getRth());

    TheveninModel Th2(5,12);

    std::println("Vab = {0:.2f} V",Th2.getOutputVoltageByCurrent(0.1));
    std::println("Vab = {0:.2f} V",Th2.getOutputVoltageByCharge(12));

    auto [Vab, Iout] = Th2.getOutputVoltageAndCurrent(12);

    std::println("Vab = {0:.2f} V - Iout = {1:.2f}",Vab, Iout);

    PontDiviseur    myPont{};

    myPont.setVexcitation(5);
    myPont.setRhigh(10e3);
    myPont.setRlow(10e3);

    std::println("Vout = {0:.2f} V - Rs = {1:.02f} Ohm",myPont.getTensionAVide(), myPont.getOutputResistance());





}


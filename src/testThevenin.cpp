#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Resistance.hpp"
#include "TheveninModel.hpp"
#include "PontDiviseur.hpp"


TEST_CASE("Resistance - Full Test"){
    const Resistance R10k{10e3};
    CHECK(R10k.getValue() == doctest::Approx(10e3));

    Resistance myRes{120.0};
    CHECK(myRes.getValue() == doctest::Approx(120));

    myRes.setValue(0);
    CHECK(myRes.getValue() == doctest::Approx(0));

    myRes.setValue(240);
    CHECK(myRes.getValue() == doctest::Approx(240));

    CHECK_THROWS_WITH_AS(myRes.setValue(-240), "Bad resistance value detected", std::underflow_error);
}

TEST_CASE("Positive Resistance - Full Test"){
    const PositiveResistance R10k{10e3};
    CHECK(R10k.getValue() == doctest::Approx(10e3));

    PositiveResistance myRes{120.0};
    CHECK(myRes.getValue() == doctest::Approx(120));

    myRes.setValue(240);
    CHECK(myRes.getValue() == doctest::Approx(240));

    CHECK_THROWS_WITH_AS(myRes.setValue(-240), "Bad resistance value detected", std::underflow_error);
    CHECK_THROWS_WITH_AS(myRes.setValue(0.0), "Bad resistance value detected", std::underflow_error);
}

TEST_CASE("Resistance - Test Helper functions"){
    PositiveResistance Ra{10e3};
    PositiveResistance Rb{10e3};

    PositiveResistance Rp = makeParallelResistance(Ra,Rb);

    CHECK(Rp.getValue() == doctest::Approx(5e3));

    
}

TEST_CASE("Thevenin Model - Ctor & Accessors"){
    RealTheveninModel   testModel{};

    CHECK(testModel.getEth() == doctest::Approx(0));
    CHECK(testModel.getRth().getValue() == doctest::Approx(0));   

    testModel.setEth(5.0);
    CHECK(testModel.getEth() == doctest::Approx(5));

    Resistance  testRes{1.0};
    testModel.setRth(testRes);
    CHECK(testModel.getRth().getValue() == doctest::Approx(1));

    testRes.setValue(12);
    RealTheveninModel   testModel2{12,testRes};

    CHECK(testModel2.getEth() == doctest::Approx(12));
    CHECK(testModel2.getRth().getValue() == doctest::Approx(12)); 
    
    const RealTheveninModel constModel{3.3,Resistance{5}};
    CHECK(constModel.getEth() == doctest::Approx(3.3));
    CHECK(constModel.getRth().getValue() == doctest::Approx(5)); 
}

TEST_CASE("Thevenin Model - Lasts tests"){

        
    RealTheveninModel testModel{5.0, Resistance{10}};

    REQUIRE(testModel.getEth() == doctest::Approx(5.0) );
    REQUIRE(testModel.getRth().getValue() == doctest::Approx(10.0) );

    CHECK(testModel.getOutputVoltageByCurrent(0.1) == doctest::Approx(4.0));
    CHECK(testModel.getOutputVoltageByCurrent(0.2) == doctest::Approx(3.0));

    CHECK_THROWS_WITH_AS(testModel.getOutputVoltageByCurrent(1), "Current is too High", std::overflow_error); 

    testModel.setEth(-5.0);

    CHECK(testModel.getOutputVoltageByCurrent(-0.1) == doctest::Approx(-4.0));
    CHECK(testModel.getOutputVoltageByCurrent(-0.2) == doctest::Approx(-3.0));

    CHECK_THROWS_WITH_AS(testModel.getOutputVoltageByCurrent(-1), "Current is too High", std::overflow_error); 

    testModel.setEth(5.0);
    
    CHECK(testModel.getOutputVoltageByCharge(PositiveResistance{10}) == doctest::Approx(2.5));
    CHECK(testModel.getOutputVoltageByCharge(PositiveResistance{40}) == doctest::Approx(4));

    auto [Vout, Iout] = testModel.getOutputVoltageAndCurrent(PositiveResistance{10});

    CHECK(Vout == doctest::Approx(2.5)); // Voltage must be 2,5V 
    CHECK(Iout == doctest::Approx(0.25)); // Current must be 250mA 
    
    
}


TEST_CASE("Pont diviseur - Ctor & accessors"){
    
    
    PontDiviseur    testBridge{5.0, PositiveResistance{10e3}, PositiveResistance{20e3}};

    CHECK(testBridge.getVexcitation() == doctest::Approx(5.0));
    CHECK(testBridge.getRhigh().getValue() == doctest::Approx(10e3));
    CHECK(testBridge.getRlow().getValue() == doctest::Approx(20e3));

    CHECK(testBridge.getEth() == doctest::Approx(5.0*(2.0/3.0)));
    CHECK(testBridge.getRth().getValue() == doctest::Approx((10e3 * 20e3) / (30e3)));

    testBridge.setVexcitation(3.3);
    CHECK(testBridge.getEth() == doctest::Approx(3.3*(2.0/3.0)));
    CHECK(testBridge.getRth().getValue() == doctest::Approx((10e3 * 20e3) / (30e3)));

    testBridge.setRlow(PositiveResistance{10e3});
    CHECK(testBridge.getEth() == doctest::Approx(3.3*(1.0/2.0)));
    CHECK(testBridge.getRth().getValue() == doctest::Approx((10e3 * 10e3) / (20e3)));

    testBridge.setRhigh(PositiveResistance{20e3});
    CHECK(testBridge.getEth() == doctest::Approx(3.3*(1.0/3.0)));
    CHECK(testBridge.getRth().getValue() == doctest::Approx((20e3 * 10e3) / (30e3)));


    const   PontDiviseur testConstBridge{12.0,PositiveResistance{20e3},PositiveResistance{20e3}};

    CHECK(testConstBridge.getVexcitation() == doctest::Approx(12.0));
    CHECK(testConstBridge.getRhigh().getValue() == doctest::Approx(20e3));
    CHECK(testConstBridge.getRlow().getValue() == doctest::Approx(20e3));
    CHECK(testConstBridge.getEth() == doctest::Approx(12.0*(2.0/4.0)));
    CHECK(testConstBridge.getRth().getValue() == doctest::Approx((20e3 * 20e3) / (40e3)));



}

TEST_CASE("Pont diviseur - Full tests"){
    
    PontDiviseur    testBridge{5.0, PositiveResistance{10e3}, PositiveResistance{10e3}};

    CHECK(testBridge.getVoutAVide() == doctest::Approx(2.5));
    CHECK(testBridge.getOutputResistance().getValue() == doctest::Approx(5e3));

    
}

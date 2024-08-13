#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "TheveninModel.hpp"
#include "PontDiviseur.hpp"


TEST_CASE("TheveninModel - Construtors and accessors test"){

    // First tests with default Ctor
    TheveninModel firstModel{};

    CHECK(firstModel.getEth() == doctest::Approx(0) );  /**< Use of doctest::approx to test floating point values */
    CHECK(firstModel.getRth() == doctest::Approx(0) );  /**< Use of doctest::approx to test floating point values */

    firstModel.setEth(5.0);                             
    CHECK(firstModel.getEth() == doctest::Approx(5.0) );  /**< Use of doctest::approx to test floating point values */

    firstModel.setRth(12.0);
    CHECK(firstModel.getRth() == doctest::Approx(12.0) );  /**< Use of doctest::approx to test floating point values */

    CHECK_THROWS_AS(firstModel.setRth(-12.0), NegativeResistance);  /**< Check if the NegativeResistance exception is raised if Rth is negative */

    // Second tests with overloaded Ctor
    TheveninModel secondModel{12.0,1.2};    /**< Create new object : Eth = 12V, Rth = 1.2 Ohm */
    CHECK(secondModel.getEth() == doctest::Approx(12.0) );  /**< Use of doctest::approx to test floating point values */
    CHECK(secondModel.getRth() == doctest::Approx(1.2) );  /**< Use of doctest::approx to test floating point values */

    // Third tests with const object (just in case...)
    const TheveninModel thirdModel{5.0,10.0};
    CHECK(thirdModel.getEth() == doctest::Approx(5.0) );  /**< Use of doctest::approx to test floating point values */
    CHECK(thirdModel.getRth() == doctest::Approx(10) );  /**< Use of doctest::approx to test floating point values */
}

TEST_CASE("TEST getOutputVoltageByCurrent"){
    TheveninModel testModel{5.0,1.0};   /**< Create a new model Eth = 5V, Rth = 1 Ohm */

    REQUIRE(testModel.getEth() == doctest::Approx(5.0) );
    REQUIRE(testModel.getRth() == doctest::Approx(1.0) );

    CHECK(testModel.getOutputVoltageByCurrent(1) == doctest::Approx(4.0));  /** Iout = 1A -> Vout = 5 - (1 * 1) = 4 */
    CHECK_THROWS_WITH_AS(testModel.getOutputVoltageByCurrent(10), "Current is too High", std::overflow_error); /**< Check if the exception is raised if current is to high */

    testModel.setEth(-5.0);
    REQUIRE(testModel.getEth() == doctest::Approx(-5.0) );

    CHECK(testModel.getOutputVoltageByCurrent(-1) == doctest::Approx(-4.0));  /** Iout = 1A -> Vout = 5 - (1 * 1) = 4 */
    CHECK_THROWS_WITH_AS(testModel.getOutputVoltageByCurrent(-10), "Current is too High", std::overflow_error); /**< Check if the exception is raised if current is to high */
}

TEST_CASE("TEST getOutputVoltageByCharge"){
    TheveninModel testModel{5.0,1.0};   /**< Create a new model Eth = 5V, Rth = 1 Ohm */

    REQUIRE(testModel.getEth() == doctest::Approx(5.0) );
    REQUIRE(testModel.getRth() == doctest::Approx(1.0) );

    CHECK_THROWS_AS(testModel.getOutputVoltageByCharge(-12.0), NegativeResistance); /**< Check exception if Charge is < 0 */

    CHECK(testModel.getOutputVoltageByCharge(1.0) == doctest::Approx(2.5)); /** With Charge == Rth, Vout = Eth/2 */

    testModel.setEth(-5);
    REQUIRE(testModel.getEth() == doctest::Approx(-5.0) );
    CHECK(testModel.getOutputVoltageByCharge(1.0) == doctest::Approx(-2.5)); /** With Charge == Rth, Vout = Eth/2 */
}

TEST_CASE("TEST getOutputVoltageAndCurrent"){
    TheveninModel testModel{5.0,1.0};   /**< Create a new model Eth = 5V, Rth = 1 Ohm */

    CHECK_THROWS_AS(testModel.getOutputVoltageAndCurrent(-12.0), NegativeResistance); /**< Check exception if Charge is < 0 */

    auto [Voltage, Current] = testModel.getOutputVoltageAndCurrent(1);  /**< Use of structured binding (>C++17) for getting tuple values - Possible use of std::get<>() instead */

    CHECK(Voltage == doctest::Approx(2.5)); /** Voltage must be 2,5V */
    CHECK(Current == doctest::Approx(2.5)); /** Current must be 2,5A */
}

//  PontDiviseur class tests
TEST_CASE("TEST - PontDiviseur - Ctor & accessors"){
    PontDiviseur    pont{};

    CHECK(pont.getVexcitation() == doctest::Approx(0));
    CHECK(pont.getRlow() == doctest::Approx(0));
    CHECK(pont.getRhigh() == doctest::Approx(0));

    pont.setVexcitation(5.0);
    CHECK(pont.getVexcitation() == doctest::Approx(5.0));

    pont.setRhigh(10e3);
    CHECK(pont.getRhigh() == doctest::Approx(10e3));
    CHECK_THROWS_AS(pont.setRhigh(-10e3), NegativeResistance); /**< Check exception if Charge is < 0 */

    pont.setRlow(10e3);
    CHECK(pont.getRlow() == doctest::Approx(10e3));
    CHECK_THROWS_AS(pont.setRlow(-10e3), NegativeResistance); /**< Check exception if Charge is < 0 */
}

TEST_CASE("TEST - getTensionAVide / getOutputResistance"){
    PontDiviseur pont{};
    pont.setVexcitation(5.0);
    pont.setRhigh(10e3);
    pont.setRlow(10e3);

    REQUIRE(pont.getVexcitation() == doctest::Approx(5.0));
    REQUIRE(pont.getRhigh() == doctest::Approx(10e3));
    REQUIRE(pont.getRlow() == doctest::Approx(10e3));

    CHECK(pont.getTensionAVide() == doctest::Approx(2.5));      /** V0 must be VCC/2 */
    CHECK(pont.getOutputResistance() == doctest::Approx(5e3)); /** Rout must be Rh // Rl */



}




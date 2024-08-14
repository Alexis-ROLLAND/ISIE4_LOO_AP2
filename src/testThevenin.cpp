#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Resistance.hpp"
//#include "TheveninModel.hpp"
//#include "PontDiviseur.hpp"


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


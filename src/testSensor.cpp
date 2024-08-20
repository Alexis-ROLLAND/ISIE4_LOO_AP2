#include <print>

#include "Sensor.hpp"

constexpr   uint32_t    SIMPLE_SENSOR_UID{0xAA000001};

int main(void){
    std::println("--- Test Sensor Classes ---");

    TC74    tc74a0(0x48);

    std::println("Sensor UID = {0:08x}",tc74a0.getUID());
    //std::println("Sensor Unit : {0}",SimpleSensor.getUnit());

    


}



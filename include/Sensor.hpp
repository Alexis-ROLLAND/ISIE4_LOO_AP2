#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

#include <cstdint>
#include <string>
#include <concepts>
#include <print>

//----------------------------------------------------------------------------
template <typename OutputType>
concept Numeric = std::is_arithmetic_v<OutputType>; /**< Use of concepts to ensure Output value is a numeric type */

template <Numeric OutputType>
class Sensor{

private:
    const uint32_t UID{};   /**< Each Sensor has a Unique ID (32 bits) */
    const std::string   Unit{}; /**< Unit of the output  */
    OutputType outputValue{};
protected:
    [[nodiscard]]   std::string getUnit() const noexcept {return this->Unit;};
    void setOutputValue(OutputType newValue) noexcept {this->outputValue = newValue;};
    
public:
    Sensor() = delete;  /**< Ctor by default is deleted */
    Sensor(uint32_t uid, const std::string &unit):UID{uid},Unit{unit}{};
    virtual ~Sensor() = default;    /**< Dtor is defaulted */

    [[nodiscard]] uint32_t  getUID() const noexcept {return this->UID;};
    [[nodiscard]] OutputType getOutputValue() const noexcept {return this->outputValue;};

    virtual void    elaborateNewValue() = 0;   /**< Pure virtual method -> class is now abract */ 

    void    dump() const noexcept {std::println("{} {}",this->getOutputValue,this->getUnit());};
};
//----------------------------------------------------------------------------
template <Numeric OutputType>
class TempCelciusSensor : public Sensor<OutputType>{
    private:

    public:
        TempCelciusSensor() = delete;
        virtual ~TempCelciusSensor() = default;

        TempCelciusSensor(uint32_t uid):Sensor<OutputType>(uid,"°C"){};
};






#endif  /*  __SENSOR_HPP__  */
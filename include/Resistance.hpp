#ifndef __RESISTANCE_HPP__
#define __RESISTANCE_HPP__

#include <cmath>
#include <stdexcept>

class   Resistance{
    private:
        double  Value{};    /**< Resistance value in Ohm */
    protected:
        /**
         * @brief Checks if the resistance value is correct : non-négative
         * 
         * @param   double Value : Value of the desired resistance, in Ohm
         * 
         * @return  true if Value is >= 0.0, false if value < 0.
         * 
         */
        [[nodiscard]] virtual bool CheckValue(double Value){return !(std::signbit(Value));};  
    public:
        Resistance() = delete;
        virtual ~Resistance() = default;

        explicit    Resistance(double Value) {this->setValue(Value);};  /** setValues issues the only call to CheckValue */

        [[nodiscard]]   double  getValue() const noexcept {return this->Value;};
        void    setValue(double Value);
};

class   PositiveResistance : public Resistance{
    private:
        [[nodiscard]] virtual bool CheckValue(double Value) override {return std::isgreater(Value, 0.0);};  /** Marked override to indicate this is a redefinition  */
    public:
        PositiveResistance() = delete;
        virtual ~PositiveResistance() = default;
        explicit PositiveResistance(double Value) : Resistance{Value}{}; 

};

// Helper functions
PositiveResistance  makeParallelResistance(const PositiveResistance &r1, const PositiveResistance &r2);





#endif  /*  __RESISTANCE_HPP__ */


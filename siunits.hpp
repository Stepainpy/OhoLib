#pragma once
#include <ostream>

namespace si {

// Defenition
template <char L = 0, char M = 0, char T = 0, char I = 0,
          char O = 0, char N = 0, char J = 0, class Type = float>
struct unit {
    Type value;
};

// Alias
template <class Type> using Length            = unit<1, 0, 0, 0, 0, 0, 0, Type>;
template <class Type> using Mass              = unit<0, 1, 0, 0, 0, 0, 0, Type>;
template <class Type> using Time              = unit<0, 0, 1, 0, 0, 0, 0, Type>;
template <class Type> using Amperage          = unit<0, 0, 0, 1, 0, 0, 0, Type>;
template <class Type> using Temperature       = unit<0, 0, 0, 0, 1, 0, 0, Type>;
template <class Type> using AmountOfSubstance = unit<0, 0, 0, 0, 0, 1, 0, Type>;
template <class Type> using LuminousIntensity = unit<0, 0, 0, 0, 0, 0, 1, Type>;

template <class Type> using Area         = unit<2, 0,  0, 0, 0, 0, 0, Type>;
template <class Type> using Volume       = unit<3, 0,  0, 0, 0, 0, 0, Type>;
template <class Type> using Speed        = unit<1, 0, -1, 0, 0, 0, 0, Type>;
template <class Type> using Acceleration = unit<1, 0, -2, 0, 0, 0, 0, Type>;

template <class Type> using Force    = unit< 1, 1, -2, 0, 0, 0, 0, 0, Type>;
template <class Type> using Energy   = unit< 2, 1, -2, 0, 0, 0, 0, 0, Type>;
template <class Type> using Power    = unit< 2, 1, -3, 0, 0, 0, 0, 0, Type>;
template <class Type> using Pressure = unit<-1, 1, -2, 0, 0, 0, 0, 0, Type>;

template <class Type> using Frequency = unit<0, 0, -1, 0, 0, 0, 0, 0, Type>;

// Output in console
template <char L, char M, char T, char I,
          char O, char N, char J, class Type>
std::ostream& operator<<(std::ostream& out, const unit<L, M, T, I, O, N, J, Type>& _unit) {
    out << _unit.value;
    return out;
}

// Addition
template <char L, char M, char T, char I,
          char O, char N, char J, class Type>
unit<L, M, T, I, O, N, J, Type> operator+(
    const unit<L, M, T, I, O, N, J, Type>& u1,
    const unit<L, M, T, I, O, N, J, Type>& u2
) {
    return unit<L, M, T, I, O, N, J, Type> { u1.value + u2.value };
}

// Subtraction
template <char L, char M, char T, char I,
          char O, char N, char J, class Type>
unit<L, M, T, I, O, N, J, Type> operator-(
    const unit<L, M, T, I, O, N, J, Type>& u1,
    const unit<L, M, T, I, O, N, J, Type>& u2
) {
    return unit<L, M, T, I, O, N, J, Type> { u1.value - u2.value };
}

// Multiplication
template <char L1, char M1, char T1, char I1, char O1, char N1, char J1,
          char L2, char M2, char T2, char I2, char O2, char N2, char J2,
          class Type>
unit<L1 + L2, M1 + M2, T1 + T2, I1 + I2, O1 + O2, N1 + N2, J1 + J2, Type> operator*(
    const unit<L1, M1, T1, I1, O1, N1, J1, Type>& u1,
    const unit<L2, M2, T2, I2, O2, N2, J2, Type>& u2
) {
    return unit<L1 + L2, M1 + M2, T1 + T2, I1 + I2, O1 + O2, N1 + N2, J1 + J2, Type> { u1.value * u2.value }; 
}

// Division
template <char L1, char M1, char T1, char I1, char O1, char N1, char J1,
          char L2, char M2, char T2, char I2, char O2, char N2, char J2,
          class Type>
unit<L1 - L2, M1 - M2, T1 - T2, I1 - I2, O1 - O2, N1 - N2, J1 - J2, Type> operator/(
    const unit<L1, M1, T1, I1, O1, N1, J1, Type>& u1,
    const unit<L2, M2, T2, I2, O2, N2, J2, Type>& u2
) {
    return unit<L1 - L2, M1 - M2, T1 - T2, I1 - I2, O1 - O2, N1 - N2, J1 - J2, Type> { u1.value / u2.value }; 
}

}; // end namespace si
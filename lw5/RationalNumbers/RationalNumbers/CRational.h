#pragma once
#include <iostream>
#include <stdexcept>
#include <numeric>

class CRational
{
public:
    //  онструирует рациональное число, равное нулю (0/1)
    CRational();

    //  онструирует рациональное число, равное value (value/1)
    CRational(int value);

    //  онструирует рациональное число, равное numerator/denominator
    // –ациональное число должно хранитьс€ в нормализованном виде:
    // знаменатель положительный (числитель может быть отрицательным)
    // числитель и знаменатель не имеют общих делителей (6/8 => 3/4 и т.п.)
    // ≈сли знаменатель равен нулю, должно конструироватьс€ рациональное число, равное нулю,
    // либо должно быть выброшено исключение std::invalid_argument.
    CRational(int numerator, int denominator);

    // ¬озвращает числитель
    int GetNumerator() const;

    // ¬озвращает знаменатель (натуральное число)
    int GetDenominator() const;

    // ¬озвращает отношение числител€ и знаменател€ в виде числа double
    double ToDouble() const;

    // ¬озвращает представление рационального числа в виде смешанной дроби
    std::pair<int, CRational> ToCompoundFraction() const;

    //унарные +, -, мен€ют знак дроби либо не мен€ют
    CRational operator +() const;
    CRational operator -();

    // +=, -=, *=, /=
    CRational& operator +=(const CRational& number);
    CRational& operator -=(const CRational& number);
    CRational& operator *=(const CRational& number);
    CRational& operator /=(const CRational& number);

private:
    int m_numerator, m_denominator;

    void Normalize();
};

//=, -, *, /
CRational operator +(const CRational& lhs, const CRational& rhs);
CRational operator -(const CRational& lhs, const CRational& rhs);
CRational operator *(const CRational& lhs, const CRational& rhs);
CRational operator /(const CRational& lhs, const CRational& rhs);

// ==, !=, <, <=, >, >=
bool operator ==(const CRational& lhs, const CRational& rhs);
bool operator !=(const CRational& lhs, const CRational& rhs);
bool operator >(const CRational& lhs, const CRational& rhs);
bool operator <(const CRational& lhs, const CRational& rhs);
bool operator >=(const CRational& lhs, const CRational& rhs);
bool operator <=(const CRational& lhs, const CRational& rhs);

std::ostream& operator <<(std::ostream& stream, const CRational& number);
std::istream& operator >>(std::istream& stream, CRational& number);
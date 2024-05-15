#include "CRational.h"

const char SLASH = '/';

CRational::CRational()
    :m_numerator(0)
    , m_denominator(1)
{}

CRational::CRational(int value)
    :m_numerator(value)
    , m_denominator(1)
{}

void CRational::Normalize()
{
    int gcd = std::gcd(m_numerator, m_denominator);
    if (m_denominator < 0)
    {
        m_numerator *= -1;
        m_denominator *= -1;
    }

    m_numerator /= gcd;
    m_denominator /= gcd;
}

CRational::CRational(int numerator, int denominator)
    :m_numerator(numerator)
    , m_denominator(denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument("Invalid value of denominator: it must be not null");
    }
    else
    {
        Normalize();
    }
}

int CRational::GetNumerator() const
{
    return m_numerator;
}

int CRational::GetDenominator() const
{
    return m_denominator;
}

double CRational::ToDouble() const
{
    return static_cast<double>(m_numerator) / m_denominator;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
    int intPart = m_numerator / m_denominator;
    return std::make_pair(intPart, CRational(m_numerator - intPart * m_denominator, m_denominator));
}

CRational CRational::operator +() const
{
    return *this;
}

CRational CRational::operator -()
{    
    return CRational(m_numerator * (-1), m_denominator);
}

CRational operator +(const CRational& lhs, const CRational& rhs)
{
    int commonDenominator = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int numerator = lhs.GetNumerator() * (commonDenominator / lhs.GetDenominator()) +
        rhs.GetNumerator() * (commonDenominator / rhs.GetDenominator());

    return CRational(numerator, commonDenominator);
}

CRational operator -(const CRational& lhs, const CRational& rhs)
{
    int commonDenominator = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int numerator = lhs.GetNumerator() * (commonDenominator / lhs.GetDenominator()) -
        rhs.GetNumerator() * (commonDenominator / rhs.GetDenominator());

    return CRational(numerator, commonDenominator);
}

CRational operator *(const CRational& lhs, const CRational& rhs)
{
    int numerator = lhs.GetNumerator() * rhs.GetNumerator();
    int denominator = lhs.GetDenominator() * rhs.GetDenominator();

    return CRational(numerator, denominator);
}

CRational operator /(const CRational& lhs, const CRational& rhs)
{
    int numerator = lhs.GetNumerator() * rhs.GetDenominator();
    int denominator = lhs.GetDenominator() * rhs.GetNumerator();

    return CRational(numerator, denominator);
}

CRational& CRational::operator +=(const CRational& number)
{
    *this = *this + number;
    return *this;
}

CRational& CRational::operator -=(const CRational& number)
{
    *this = *this - number;
    return *this;
}

CRational& CRational::operator *=(const CRational& number)
{
    *this = *this * number;
    return *this;
}

CRational& CRational::operator /=(const CRational& number)
{
    *this = *this / number;
    return *this;
}

bool operator ==(const CRational& lhs, const CRational& rhs)
{
    return (lhs.GetNumerator() == rhs.GetNumerator()) &&
        (lhs.GetDenominator() == rhs.GetDenominator());
}

bool operator !=(const CRational& lhs, const CRational& rhs)
{
    return !(lhs == rhs);
}

bool operator >(const CRational& lhs, const CRational& rhs)
{
    int commonDenominator = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    int leftNumerator = lhs.GetNumerator() * (commonDenominator / lhs.GetDenominator());
    int rightNumerator = rhs.GetNumerator() * (commonDenominator / rhs.GetDenominator());
    return leftNumerator > rightNumerator;
}

bool operator <(const CRational& lhs, const CRational& rhs)
{
    return !(lhs > rhs) && lhs != rhs;
}

bool operator >=(const CRational& lhs, const CRational& rhs)
{
    return !(lhs < rhs);
}

bool operator <=(const CRational& lhs, const CRational& rhs)
{
    return !(lhs > rhs);
}

std::ostream& operator <<(std::ostream& stream, const CRational& number)
{
    stream << number.GetNumerator() << SLASH << number.GetDenominator();
    return stream;
}

std::istream& operator >>(std::istream& stream, CRational& number)
{
    int numerator = 0;
    int denominator = 0;
    if ((stream >> numerator) &&
        (stream.get() == SLASH) &&
        (stream >> denominator))
    {
        number = CRational(numerator, denominator);
    }
    else
    {
        stream.setstate(std::ios_base::failbit | stream.rdstate());
    }

    return stream;
}
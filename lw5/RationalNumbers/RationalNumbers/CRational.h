#pragma once
#include <iostream>
#include <stdexcept>
#include <numeric>

class CRational
{
public:
    // ������������ ������������ �����, ������ ���� (0/1)
    CRational();

    // ������������ ������������ �����, ������ value (value/1)
    CRational(int value);

    // ������������ ������������ �����, ������ numerator/denominator
    // ������������ ����� ������ ��������� � ��������������� ����:
    // ����������� ������������� (��������� ����� ���� �������������)
    // ��������� � ����������� �� ����� ����� ��������� (6/8 => 3/4 � �.�.)
    // ���� ����������� ����� ����, ������ ���������������� ������������ �����, ������ ����,
    // ���� ������ ���� ��������� ���������� std::invalid_argument.
    CRational(int numerator, int denominator);

    // ���������� ���������
    int GetNumerator() const;

    // ���������� ����������� (����������� �����)
    int GetDenominator() const;

    // ���������� ��������� ��������� � ����������� � ���� ����� double
    double ToDouble() const;

    // ���������� ������������� ������������� ����� � ���� ��������� �����
    std::pair<int, CRational> ToCompoundFraction() const;

    //������� +, -, ������ ���� ����� ���� �� ������
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
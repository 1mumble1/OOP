#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <memory>

class CMyString
{
public:
	// ����������� �� ���������
	CMyString();

	// �����������, ���������������� ������ ������� ������
	// � ����������� ������� ��������
	CMyString(const char* pString);

	// �����������, ���������������� ������ ������� �� 
	// ����������� ������� �������� �����
	CMyString(const char* pString, size_t length);

	// ����������� �����������
	CMyString(CMyString const& other);

	// ������������ �����������
	//  ����������� ��������� � ������������ ���������� ������������ 
	CMyString(CMyString&& other) noexcept;

	// �����������, ���������������� ������ ������� �� 
	// ������ ����������� ���������� C++
	CMyString(std::string const& stlString);

	// ���������� ������ - ����������� ������, ���������� ��������� ������
	~CMyString();

	// ���������� ����� ������ (��� ����� ������������ �������� �������)
	size_t GetLength() const;

	// ���������� ��������� �� ������ �������� ������.
	// � ����� ������� ����������� ������ ���� ����������� ������� ������
	// ���� ���� ������ ������ 
	const char* GetStringData() const;

	// ���������� ��������� � �������� ������� ������ �� ������ length ��������
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// ������� ������ (������ ���������� ����� ������� �����)
	void Clear();

	// ���������� ����������� ������
	size_t GetCapacity() const;

	// ������������ �������� ������������
	CMyString& operator=(CMyString&& other) noexcept;

	// ���������� �������� ������������
	CMyString& operator=(const CMyString& other);

	// +=
	CMyString& operator+=(const CMyString& other);

	// read
	const char& operator[](size_t index) const;
	// write
	char& operator[](size_t index);

private:
	inline static char m_emptyString[] = { '\0' };
	char* m_chars;
	size_t m_length, m_capacity;
};

// +
CMyString operator+(const CMyString& lhs, const CMyString& rhs);

// ==, !=, >, <, >=, <=
bool operator==(const CMyString& lhs, const CMyString& rhs);
bool operator!=(const CMyString& lhs, const CMyString& rhs);
bool operator>(const CMyString& lhs, const CMyString& rhs);
bool operator<(const CMyString& lhs, const CMyString& rhs);
bool operator>=(const CMyString& lhs, const CMyString& rhs);
bool operator<=(const CMyString& lhs, const CMyString& rhs);

// <<, >>
std::ostream& operator<<(std::ostream& stream, const CMyString& str);
std::istream& operator>>(std::istream& stream, CMyString& str);
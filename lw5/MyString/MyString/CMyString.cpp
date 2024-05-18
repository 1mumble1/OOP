#include "CMyString.h"

const char END_OF_STRING = '\0';
const char SPACE = ' ';
const char ENTER = '\n';

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_capacity = length * 2;
	m_chars = new char[m_capacity + 1];
	memcpy(m_chars, pString, m_length);
	m_chars[m_length] = m_emptyString[0];
}

CMyString::CMyString()
	:CMyString(nullptr, 0)
{}

CMyString::CMyString(const char* pString)
	:CMyString(pString, strlen(pString))
{}

CMyString::CMyString(CMyString const& other)
	:CMyString(other.GetStringData(), other.GetLength())
{}

//CMyString::CMyString(CMyString&& other) noexcept
//{
//    m_length = other.m_length;
//    m_capacity = other.m_capacity;
//    m_chars = other.m_chars;
//
//    other.m_length = 0;
//    other.m_chars = new char[1];
//    other.m_chars[0] = END_OF_STRING;
//}

CMyString::CMyString(CMyString&& other) noexcept
{
	m_length = 0;
	m_capacity = 0;
	delete[] m_chars;
	m_chars = new char[1];
	m_chars[0] = END_OF_STRING;
	std::swap(m_length, other.m_length);
	std::swap(m_chars, other.m_chars);
	std::swap(m_capacity, other.m_capacity);
}

CMyString::CMyString(std::string const& stlString)
	:CMyString(stlString.c_str(), stlString.length())
{}

CMyString::~CMyString()
{
	delete[] m_chars;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_chars;
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}

void CMyString::Clear()
{
	delete[] m_chars;
	m_length = 0;
	m_chars = new char[1];
	m_chars[0] = m_emptyString[0];
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start < 0 || start > m_length)
	{
		throw std::out_of_range("Invalid value of start position: it is out of range.");
	}

	if (length > m_length - start)
	{
		length = m_length - start;
	}

	return CMyString(&m_chars[start], length);
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other) {
		std::swap(m_length, other.m_length);
		std::swap(m_capacity, other.m_capacity);
		std::swap(m_chars, other.m_chars);
	}
	return *this;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other) {
		if (m_capacity >= other.m_length && m_chars != m_emptyString)
		{
			std::destroy_n(m_chars, m_length + 1);
			std::uninitialized_copy_n(other.m_chars, m_length + 1, m_chars);
			m_length = other.m_length;
		}
		else
		{
			// Используем идиому copy-and-swap
			CMyString copy{ other };
			std::swap(m_length, copy.m_length);
			std::swap(m_capacity, copy.m_capacity);
			std::swap(m_chars, copy.m_chars);
		}
	}
	return *this;
}

CMyString operator+(const CMyString& lhs, const CMyString& rhs)
{
	size_t newLength = lhs.GetLength() + rhs.GetLength();
	char* newChars = new char[newLength + 1];
	memcpy(newChars, lhs.GetStringData(), lhs.GetLength());
	memcpy(newChars + lhs.GetLength(), rhs.GetStringData(), rhs.GetLength());
	return CMyString(newChars, newLength);
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	*this = *this + other;
	return *this;
}

bool operator==(const CMyString& lhs, const CMyString& rhs)
{
	return (lhs.GetLength() == rhs.GetLength()) &&
		memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) == 0;
}

bool operator!=(const CMyString& lhs, const CMyString& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const CMyString& lhs, const CMyString& rhs)
{
	if (lhs.GetLength() == rhs.GetLength())
	{
		return memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) > 0;
	}
	else if (lhs.GetLength() > rhs.GetLength())
	{
		if (memcmp(lhs.GetStringData(), rhs.GetStringData(), rhs.GetLength()) < 0)
		{
			return false;
		}
		return true;
	}
	else
	{
		if (memcmp(lhs.GetStringData(), rhs.GetStringData(), lhs.GetLength()) > 0)
		{
			return true;
		}
		return false;
	}
	/*return memcmp(lhs.GetStringData(), rhs.GetStringData(), std::min(lhs.GetLength(), rhs.GetLength())) > 0;*/
}

bool operator<(const CMyString& lhs, const CMyString& rhs)
{
	return !(lhs > rhs) && lhs != rhs;
}

bool operator>=(const CMyString& lhs, const CMyString& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const CMyString& lhs, const CMyString& rhs)
{
	return !(lhs > rhs);
}

std::ostream& operator<<(std::ostream& stream, const CMyString& str)
{
	stream << str.GetStringData();
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& str)
{
	size_t length = 1;
	size_t index = 0;
	char* chars = new char[length];
	char ch;

	while (stream.get(ch) && ch != SPACE && ch != ENTER)
	{
		chars[index++] = ch;

		if (index == length)
		{
			char* largeStr = new char[length + 1];
			memcpy(largeStr, chars, length);
			delete[] chars;
			chars = largeStr;
			length++;
		}
	}
	chars[index] = END_OF_STRING;

	str = CMyString(chars, length);

	return stream;
}

// оператор индексированного доступа для чтения
const char& CMyString::operator[](size_t index) const
{
	if (index < 0 || index > m_length)
	{
		throw std::out_of_range("Invalid value of index: it is out of range.");
	}
	return m_chars[index];
}

// оператор индексированного доступа для записи
char& CMyString::operator[](size_t index)
{
	if (index < 0 || index > m_length)
	{
		throw std::out_of_range("Invalid value of index: it is out of range.");
	}
	return m_chars[index];
}

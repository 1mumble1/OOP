#pragma once
#include <string>
#include <iostream>
#include <stdexcept>
#include <memory>

class CMyString
{
public:
	// конструктор по умолчанию
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из 
	// символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор
	//  реализуется совместно с перемещающим оператором присваивания 
	CMyString(CMyString&& other) noexcept;

	// конструктор, инициализирующий строку данными из 
	// строки стандартной библиотеки C++
	CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	size_t GetLength() const;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая 
	const char* GetStringData() const;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();

	// Возвращает вместимость строки
	size_t GetCapacity() const;

	// перемещающий оператор присваивания
	CMyString& operator=(CMyString&& other) noexcept;

	// копирующий оператор присваивания
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
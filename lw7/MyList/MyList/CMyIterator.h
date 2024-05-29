#pragma once
#include "Node.h"
#include <iterator>

template <typename T>
class CMyList;

template <typename T>
class CMyIterator
{
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	explicit CMyIterator(Node<T>* ptr, Node<T>* end)
		: m_ptr(ptr)
		, m_end(end)
	{}

	reference operator*() const
	{
		if (m_ptr == m_end)
		{
			throw std::out_of_range("Dereferencing end iterator");
		}
		return m_ptr->data;
	}
	pointer operator->() const
	{
		if (m_ptr == m_end)
		{
			throw std::out_of_range("Dereferencing end iterator");
		}
		return &(m_ptr->data);
	}

	CMyIterator& operator++()
	{
		if (m_ptr == m_end)
		{
			throw std::out_of_range("Cant increase end iterator");
		}
		m_ptr = m_ptr->next;
		return *this;
	}

	CMyIterator operator++(int)
	{
		if (m_ptr == m_end)
		{
			throw std::out_of_range("Cant increase end iterator");
		}
		CMyIterator temp = *this;
		m_ptr = m_ptr->next;
		return temp;
	}

	CMyIterator& operator--()
	{
		m_ptr = m_ptr->prev;
		return *this;
	}

	CMyIterator operator--(int)
	{
		CMyIterator temp = *this;
		m_ptr = m_ptr->prev;
		return temp;
	}

	bool operator==(const CMyIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	bool operator!=(const CMyIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	friend class CMyList<T>;
private:
	Node<T>* m_ptr;
	Node<T>* m_end;
};

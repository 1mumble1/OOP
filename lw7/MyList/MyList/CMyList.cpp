#ifndef CMYLIST_CPP
#define CMYLIST_CPP
#include "CMyList.h"

template<typename T>
CMyList<T>::CMyList()
	: m_begin(std::shared_ptr<Node>())
	, m_end(std::shared_ptr<Node>())
	, m_size(0)
{}

template<typename T>
CMyList<T>::CMyList(const CMyList& other)
{
	for (const auto& value : other)
	{
		PushBack(value);
	}
}

template<typename T>
CMyList<T>::CMyList(CMyList&& other) noexcept
{
	this->~CMyList();
	std::swap(m_size, other.m_size);
	std::swap(m_begin, other.m_begin);
	std::swap(m_end, other.m_end);
}

template<typename T>
CMyList<T>::~CMyList() noexcept
{
	while (m_begin)
	{
		m_begin = m_begin->next;
		m_begin->prev = nullptr;
	}

	m_end = nullptr;
	m_size = 0;
}

template<typename T>
CMyList<T>& CMyList<T>::operator=(const CMyList& other)
{
	if (this != &other)
	{
		this->~CMyList();
		for (const auto& value : other)
		{
			PushBack(value);
		}
	}
	return *this;
}

template<typename T>
CMyList<T>& CMyList<T>::operator=(CMyList&& other) noexcept
{
	if (this != &other)
	{
		this->~CMyList();
		std::swap(m_size, other.m_size);
		std::swap(m_begin, other.m_begin);
		std::swap(m_end, other.m_end);
	}
	return *this;
}

template<typename T>
size_t CMyList<T>::GetSize() const
{
	return m_size;
}

template<typename T>
void CMyList<T>::PushFront(const T& value)
{
	auto newNode = std::make_shared<Node>(value);

	if (m_size == 0)
	{
		m_begin = newNode;
		m_begin->next = m_end;
		auto end = std::make_shared<Node>();
		end->prev = m_begin;
		m_end = end;
	}
	else
	{
		newNode->next = m_begin;
		m_begin->prev = newNode;
		m_begin = newNode;
	}

	++m_size;
}

template<typename T>
void CMyList<T>::PushBack(const T& value)
{
	auto newNode = std::make_shared<Node>(value);

	if (m_size == 0)
	{
		m_begin = newNode;
		m_begin->next = m_end;
		m_end->prev = m_begin;
	}
	else
	{
		newNode->prev = m_end->prev;
		newNode->next = m_end;
		m_end->prev->next = newNode;
		m_end->prev = newNode;
	}
	//newNode->prev = m_end;
	//if (m_end)
	//{
	//	m_end->next = newNode;
	//}
	//else
	//{
	//	m_begin = newNode;
	//}
	//m_end = newNode;

	++m_size;
}



//iter
template<typename T>
CMyList<T>::Iterator::~Iterator()
{
	m_ptr = nullptr;
}

template<typename T>
typename T& CMyList<T>::Iterator::operator*()
{
	if (!m_ptr)
	{
		throw std::invalid_argument("Iterator is empty");
	}

	return m_ptr->data;
}

template<typename T>
typename T* CMyList<T>::Iterator::operator->()
{
	return &(m_ptr->data);
}

template<typename T>
typename CMyList<T>::Iterator& CMyList<T>::Iterator::operator++()
{
	if (!m_ptr->next && !m_ptr)
	{
		throw std::out_of_range("Iterator is out of range");
	}
	m_ptr = m_ptr->next;
	return *this;
}

template<typename T>
typename CMyList<T>::Iterator CMyList<T>::Iterator::operator++(int)
{
	Iterator tmp(*this);
	++(*this);
	return tmp;
}

template<typename T>
typename CMyList<T>::Iterator& CMyList<T>::Iterator::operator--()
{
	if (!m_ptr && !m_ptr->prev)
	{
		throw std::out_of_range("Iterator is out of range");
	}

	m_ptr = m_ptr->prev;
	return *this;
}

template<typename T>
typename CMyList<T>::Iterator CMyList<T>::Iterator::operator--(int)
{
	Iterator tmp(*this);
	--(*this);
	return tmp;
}

template<typename T>
typename bool CMyList<T>::Iterator::operator==(const Iterator& other) const
{
	return m_ptr == other.m_ptr;
}

template<typename T>
typename bool CMyList<T>::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

// reverse iter
template<typename T>
CMyList<T>::ReverseIterator::~ReverseIterator()
{
	m_ptr = nullptr;
}

template<typename T>
typename T& CMyList<T>::ReverseIterator::operator*()
{
	if (!m_ptr)
	{
		throw std::invalid_argument("Iterator is out of range");
	}

	return m_ptr->data;
}

template<typename T>
typename T* CMyList<T>::ReverseIterator::operator->()
{
	return &(m_ptr->data);
}

template<typename T>
typename CMyList<T>::ReverseIterator& CMyList<T>::ReverseIterator::operator++()
{
	if (!m_ptr && !m_ptr->prev)
	{
		throw std::out_of_range("Iterator is out of range");
	}
	m_ptr = m_ptr->prev;
	return *this;
}

template<typename T>
typename CMyList<T>::ReverseIterator CMyList<T>::ReverseIterator::operator++(int)
{
	ReverseIterator tmp(*this);
	++(*this);
	return tmp;
}

template<typename T>
typename CMyList<T>::ReverseIterator& CMyList<T>::ReverseIterator::operator--()
{
	if (!m_ptr && !m_ptr->next)
	{
		throw std::out_of_range("Iterator is out of range");
	}
	m_ptr = m_ptr->next;
	return *this;
}

template<typename T>
typename CMyList<T>::ReverseIterator CMyList<T>::ReverseIterator::operator--(int)
{
	ReverseIterator tmp(*this);
	--(*this);
	return tmp;
}

template<typename T>
typename bool CMyList<T>::ReverseIterator::operator==(const ReverseIterator& other) const
{
	return m_ptr == other.m_ptr;
}

template<typename T>
typename bool CMyList<T>::ReverseIterator::operator!=(const ReverseIterator& other) const
{
	return !(*this == other);
}

template<typename T>
typename CMyList<T>::Iterator CMyList<T>::begin() const
{
	return Iterator(m_begin);
}

template<typename T>
typename CMyList<T>::Iterator CMyList<T>::end() const
{
	return Iterator(m_end);
}

template<typename T>
typename CMyList<T>::ReverseIterator CMyList<T>::rbegin() const
{
	return ReverseIterator(m_end);
}

template<typename T>
typename CMyList<T>::ReverseIterator CMyList<T>::rend() const
{
	return ReverseIterator(m_begin->prev);
}

template<typename T>
typename void CMyList<T>::Insert(CMyList<T>::Iterator pos, const T& value)
{
	if (pos == begin())
	{
		PushFront(value);
		return;
	}

	if (pos == end())
	{
		PushBack(value);
		return;
	}

	auto newNode = std::make_shared<Node<T>>(value);
	newNode->next = pos->prev->next;
	newNode->prev = pos->prev;
	pos->prev->next = newNode;
	pos->prev = newNode;

	++m_size;
}

template<typename T>
typename void CMyList<T>::Erase(CMyList<T>::Iterator pos)
{
	if (pos == end())
	{
		throw std::invalid_argument("Can't erase element in this position");
	}

	if (pos == begin())
	{
		m_begin = m_begin->next;
		m_begin->prev = nullptr;
		return;
	}

	CMyList<T>::Iterator tmp = begin();
	while (tmp->next != pos->prev->next)
	{
		++tmp;
	}
	tmp->next = pos->next;
	pos->next->prev = tmp;

	--m_size;
}

#endif
#include "CStringList.h"

CStringList::CStringList()
	: m_begin(nullptr)
	, m_end(std::shared_ptr<Node>())
	, m_size(0)
{}

CStringList::CStringList(const CStringList& other)
{
	for (auto it = other.begin(); it != other.end(); ++it)
	{
		PushBack(*it);
	}
}

CStringList::CStringList(CStringList&& other) noexcept
{
	Clear();
	std::swap(m_size, other.m_size);
	std::swap(m_begin, other.m_begin);
	std::swap(m_end, other.m_end);
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (this != &other)
	{
		Clear();
		for (auto it = other.begin(); it != other.end(); ++it)
		{
			PushBack(*it);
		}
	}
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{
	if (this != &other)
	{
		Clear();
		std::swap(m_size, other.m_size);
		std::swap(m_begin, other.m_begin);
		std::swap(m_end, other.m_end);
	}
	return *this;
}

bool CStringList::Empty() const
{
	return m_size == 0;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::PushFront(const std::string& str)
{
	auto newNode = std::make_shared<Node>(str);

	if (Empty())
	{
		m_begin = m_end = newNode;
	}
	else
	{
		newNode->next = m_begin;
		m_begin->prev = newNode;
		m_begin = newNode;
	}

	m_size++;
}

void CStringList::PushBack(const std::string& str)
{
	auto newNode = std::make_shared<Node>(str);

	if (Empty())
	{
		m_begin = m_end = newNode;
	}
	else
	{
		newNode->prev = m_end;
		m_end->next = newNode;
		m_end = newNode;
	}

	m_size++;
}

void CStringList::Clear() noexcept
{
	while (m_begin)
	{
		m_begin = m_begin->next;
	}

	m_end = nullptr;
	m_size = 0;
}

CStringList::~CStringList() noexcept
{
	Clear();
}

CStringList::Iterator::Iterator()
	: m_ptr(nullptr)
{}

CStringList::Iterator::Iterator(std::shared_ptr<Node> ptr)
	: m_ptr(ptr)
{}

CStringList::Iterator::~Iterator()
{
	m_ptr = nullptr;
}

std::string& CStringList::Iterator::operator*()
{
	if (!m_ptr)
	{
		throw CStringListOutOfRangeException("Iterator is out of range");
	}
	return m_ptr->data;
}

std::shared_ptr<Node> CStringList::Iterator::operator->()
{
	return m_ptr;
}

CStringList::Iterator& CStringList::Iterator::operator++()
{
	if (!m_ptr)
	{
		throw CStringListOutOfRangeException("Iterator is out of range");
	}
	m_ptr = m_ptr->next;
	return *this;
}

CStringList::Iterator CStringList::Iterator::operator++(int)
{
	Iterator tmp(*this);
	++(*this);
	return tmp;
}

CStringList::Iterator& CStringList::Iterator::operator--()
{
	if (!m_ptr)
	{
		throw CStringListOutOfRangeException("Iterator is out of range");
	}
	m_ptr = m_ptr->prev;
	return *this;
}

CStringList::Iterator CStringList::Iterator::operator--(int)
{
	Iterator tmp(*this);
	--(*this);
	return tmp;
}

bool CStringList::Iterator::operator==(const Iterator& other) const
{
	return m_ptr == other.m_ptr;
}

bool CStringList::Iterator::operator!=(const Iterator& other) const
{
	return !(*this == other);
}

CStringList::ReverseIterator::ReverseIterator()
	: m_ptr{ nullptr }
{}

CStringList::ReverseIterator::ReverseIterator(std::shared_ptr<Node> ptr)
	: m_ptr(ptr)
{}

CStringList::ReverseIterator::~ReverseIterator()
{
	m_ptr = nullptr;
}

std::string& CStringList::ReverseIterator::operator*()
{
	if (!m_ptr)
	{
		throw CStringListOutOfRangeException("Iterator is out of range");
	}
	return m_ptr->data;
}

std::shared_ptr<Node> CStringList::ReverseIterator::operator->()
{
	return m_ptr;
}

CStringList::ReverseIterator& CStringList::ReverseIterator::operator++()
{
	if (!m_ptr)
	{
		throw CStringListOutOfRangeException("Iterator is out of range");
	}
	m_ptr = m_ptr->prev;
	return *this;
}

CStringList::ReverseIterator CStringList::ReverseIterator::operator++(int)
{
	ReverseIterator tmp(*this);
	++(*this);
	return tmp;
}

CStringList::ReverseIterator& CStringList::ReverseIterator::operator--()
{
	if (!m_ptr)
	{
		throw CStringListOutOfRangeException("Iterator is out of range");
	}
	m_ptr = m_ptr->next;
	return *this;
}

CStringList::ReverseIterator CStringList::ReverseIterator::operator--(int)
{
	ReverseIterator tmp(*this);
	--(*this);
	return tmp;
}

bool CStringList::ReverseIterator::operator==(const ReverseIterator& other) const
{
	return m_ptr == other.m_ptr;
}

bool CStringList::ReverseIterator::operator!=(const ReverseIterator& other) const
{
	return !(*this == other);
}

CStringList::Iterator CStringList::begin()
{
	return Iterator(m_begin);
}

CStringList::Iterator CStringList::end()
{
	return Iterator(nullptr);
}

CStringList::Iterator CStringList::begin() const
{
	return Iterator(m_begin);
}

CStringList::Iterator CStringList::end() const
{
	return Iterator(nullptr);
}

CStringList::ReverseIterator CStringList::rbegin()
{
	return ReverseIterator(m_end);
}

CStringList::ReverseIterator CStringList::rend()
{
	return ReverseIterator(nullptr);
}

CStringList::ReverseIterator CStringList::rbegin() const
{
	return ReverseIterator(m_end);
}

CStringList::ReverseIterator CStringList::rend() const
{
	return ReverseIterator(nullptr);
}

void CStringList::Insert(CStringList::Iterator pos, const std::string& str)
{
	if (pos == begin())
	{
		PushFront(str);
		return;
	}
	if (pos == end())
	{
		PushBack(str);
		return;
	}

	auto newPtr = std::make_shared<Node>(str);
	newPtr->prev = pos->prev;
	newPtr->next = pos->prev->next;
	pos->prev->next = newPtr;
	pos->prev = newPtr;
	m_size++;
}

void CStringList::Erase(CStringList::Iterator pos)
{
	if (pos == end())
	{
		throw CStringListOutOfRangeException("Iterator is out of range");
	}
	if (pos == begin())
	{
		m_begin = m_begin->next;
		return;
	}
	CStringList::Iterator prev = begin();
	while (prev->next != pos->prev->next)
	{
		++prev;
	}
	prev->next = pos->next;

	m_size--;
}
#pragma once
#ifndef CMYLIST_H
#define CMYLIST_H
#include <memory>
#include <stdexcept>
#include <iterator>

template<typename T>
class CMyList
{
private:
    struct Node
    {
        T data;
        std::shared_ptr<Node> prev;
        std::shared_ptr<Node> next;

        Node(const T& value)
            : data(value)
            , prev(nullptr)
            , next(nullptr)
        {}
    };

public:
    // ����������� �� ���������
    CMyList();

    // ����������� �����������
    CMyList(const CMyList& other);

    // ����������� �����������
    CMyList(CMyList&& other) noexcept;

    // �������� ������������ ������������
    CMyList& operator=(const CMyList& other);

    // �������� ������������ ������������
    CMyList& operator=(CMyList&& other) noexcept;

    // ����������
    ~CMyList() noexcept;

    // ��������� ���������� ��������� � ������
    size_t GetSize() const;

    // ���������� �������� � ������ ������
    void PushFront(const T& value);

    // ���������� �������� � ����� ������
    void PushBack(const T& value);

    class Iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator() : m_ptr(nullptr) {};
        Iterator(std::shared_ptr<Node> ptr) : m_ptr(ptr) {};
        ~Iterator();

        reference operator*();
        pointer operator->();

        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        std::shared_ptr<Node> m_ptr;
    };

    class ReverseIterator : public std::reverse_iterator<CMyList::Iterator>
    {
    public:
        using pointer = T*;
        using reference = T&;

        ReverseIterator() : m_ptr(nullptr) {};
        ReverseIterator(std::shared_ptr<Node> ptr) : m_ptr(ptr) {};
        ~ReverseIterator();

        reference operator*();
        pointer operator->();

        ReverseIterator& operator++();
        ReverseIterator operator++(int);
        ReverseIterator& operator--();
        ReverseIterator operator--(int);

        bool operator==(const ReverseIterator& other) const;
        bool operator!=(const ReverseIterator& other) const;

    private:
        std::shared_ptr<Node> m_ptr;
    };

    Iterator begin() const;
    Iterator end() const;

    ReverseIterator rbegin() const;
    ReverseIterator rend() const;

    void Insert(Iterator pos, const T& value);
    void Erase(Iterator pos);


private:
    std::shared_ptr<Node> m_begin;
    std::shared_ptr<Node> m_end;
	size_t m_size;
};

#include "CMyList.cpp"
#endif
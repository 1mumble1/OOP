#pragma once
#include <memory>
#include <string>
#include <stdexcept>
#include "CStringListOutOfRangeException.h"

struct Node
{
    std::string data;
    std::shared_ptr<Node> prev;
    std::shared_ptr<Node> next;

    Node(const std::string& str)
        : data(str)
        , prev(nullptr)
        , next(nullptr)
    {}
};

class CStringList {
public:
    // Конструктор по умолчанию
    CStringList();

    // Конструктор копирования
    CStringList(const CStringList& other);

    // Конструктор перемещения
    CStringList(CStringList&& other) noexcept;

    // Оператор присваивания копированием
    CStringList& operator=(const CStringList& other);

    // Оператор присваивания перемещением
    CStringList& operator=(CStringList&& other) noexcept;

    // Деструктор
    ~CStringList() noexcept;

    // Добавление строки в начало списка
    void PushFront(const std::string& str);

    // Добавление строки в конец списка
    void PushBack(const std::string& str);

    // Удаление всех элементов из списка
    void Clear() noexcept;

    // Получение количества элементов в списке
    size_t GetSize() const;

    // Проверка, пуст ли список
    bool Empty() const;

    class Iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::string;
        using difference_type = std::ptrdiff_t;
        using pointer = std::string*;
        using reference = std::string&;
        Iterator();
        Iterator(std::shared_ptr<Node> p);
        ~Iterator();

        std::string& operator*();
        std::shared_ptr<Node> operator->();

        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        std::shared_ptr<Node> m_ptr;
    };

    class ReverseIterator : public std::reverse_iterator<CStringList::Iterator>
    {
    public:
        ReverseIterator();
        ReverseIterator(std::shared_ptr<Node> ptr);
        ~ReverseIterator();

        std::string& operator*();
        std::shared_ptr<Node> operator->();

        ReverseIterator& operator++();
        ReverseIterator operator++(int);
        ReverseIterator& operator--();
        ReverseIterator operator--(int);

        bool operator==(const ReverseIterator& other) const;
        bool operator!=(const ReverseIterator& other) const;

    private:
        std::shared_ptr<Node> m_ptr;
    };

    void Insert(Iterator pos, const std::string& str);
    void Erase(CStringList::Iterator pos);

    Iterator begin();
    Iterator end();

    Iterator begin() const;
    Iterator end() const;

    ReverseIterator rbegin();
    ReverseIterator rend();

    ReverseIterator rbegin() const;
    ReverseIterator rend() const;

private:
    std::shared_ptr<Node> m_begin;
    std::shared_ptr<Node> m_end;
    size_t m_size;
};
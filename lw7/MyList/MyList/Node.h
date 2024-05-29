#pragma once

template <typename T>
struct Node
{
	T data;
	std::shared_ptr<Node<T>> prev;
	std::shared_ptr<Node<T>> next;

	Node(const T& value)
		: data(value)
		, prev(nullptr)
		, next(nullptr)
	{}
};
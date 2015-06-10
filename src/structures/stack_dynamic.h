#ifndef __STACK_DYNAMIC_H_INCLUDED__
#define __STACK_DYNAMIC_H_INCLUDED__

#include <stdexcept>

template <typename T>
class StackDynamic
{
private:
	struct Node
	{
		Node(T const& _value, Node* _next = nullptr) : value(_value), next(_next)
		{};
		T value;
		Node* next;
	};
	Node* head;
	std::size_t count;
public:
	StackDynamic() : head(nullptr), count(nullptr){};
	StackDynamic(StackDynamic const&);
	void push(T const&);
	void pop();
	const T& top() const; // const T& -  i promise i'll not change the top value
	bool empty() const;
	std::size_t size() const;
};

template <typename T>
StackDynamic<T>::StackDynamic(StackDynamic<T> const& s)
{
	Node* tmp = s.head;
	count = s.count;
	while (tmp) {
		push(tmp);
		tmp = tmp->next;
	}
}

template <typename T>
void StackDynamic<T>::push(T const& t)
{
	if (!head)
		head = new Node(t);
	else
		head = new Node(t, head);
	++count;
}

template <typename T>
void StackDynamic<T>::pop()
{
	if (!head) {
		throw std::runtime_error("StackDynamic<T>::pop: empty StackDynamic");
	} else {
		Node* tmp = head->next;
		head->next = nullptr;
		delete head;
		head = tmp;
		--count;
	}
}

template <typename T>
const T& StackDynamic<T>::top() const
{
	if (!head)
		throw std::runtime_error("StackDynamic<T>::top: empty StackDynamic");
	else
		return head->value;
}

template <typename T>
bool StackDynamic<T>::empty() const
{
	return !count;
}

template <typename T>
std::size_t StackDynamic<T>::size() const
{
	return count;
}

#endif
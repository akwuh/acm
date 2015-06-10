// static binary heap
// example of using:
// ::BinaryHeapStatic<double> bhs();
// ::BinaryHeapStatic<double> bhs(1000);
// ::BinaryHeapStatic<double> bhs(1000, true);
// bhs.push(2.);
// if (!bhs.empty()) bhs.pop();

#ifndef __BINARY_HEAP_STATIC_H_INCLUDED__
#define __BINARY_HEAP_STATIC_H_INCLUDED__

#define DEFAULT_SIZE 100000
#define DEFAULT_HEAP_TYPE true

#include <cassert>

template <typename T>
class BinaryHeapStatic
{
private:
	T* ptr;
	unsigned int size, count;
	bool heap_type;
public:
	BinaryHeapStatic(unsigned int /*size*/ = DEFAULT_SIZE, 
	bool /*heap_type*/ = DEFAULT_HEAP_TYPE);
	bool empty() const { return !count; }
	void balance(unsigned int /*index*/);
	void push(T const& /*el*/);
	const T& top() const;
	void pop();
};

template <typename T>
BinaryHeapStatic<T>::BinaryHeapStatic(unsigned int _size, bool _heap_type) : size(_size), count(0), heap_type(_heap_type)
{
	assert(size > 0);
	ptr = new T[size];
}

template <typename T>
void BinaryHeapStatic<T>::balance(unsigned int index)
{
	assert(index < count);
	if (index > 0 && (ptr[index] > ptr[(index - 1) / 2]) == heap_type)
	{
		std::swap(ptr[index], ptr[(index - 1) / 2]);
		balance((index - 1) / 2);
	}
	if (index * 2 + 1 < count && (ptr[index] < ptr[index * 2 + 1]) == heap_type)
	{
		std::swap(ptr[index], ptr[index * 2 + 1]);
		balance(index * 2 + 1);
	}
	if (index * 2 + 2 < count && (ptr[index] < ptr[index * 2 + 2]) == heap_type)
	{
		std::swap(ptr[index], ptr[index * 2 + 2]);
		balance(index * 2 + 2);
	}
}

template <typename T>
void BinaryHeapStatic<T>::push(T const& el)
{
	assert(count < size);
	ptr[count++] = el;
	balance(count - 1);
}

template <typename T>
const T& BinaryHeapStatic<T>::top() const
{
	assert(count > 0);
	return ptr[0];
}

template <typename T>
void BinaryHeapStatic<T>::pop()
{
	assert(count > 0);
	if (--count) {
		std::swap(ptr[0], ptr[count]);
		balance(0);
	}
}	

#endif
#include "stack.h"
#include <iostream>

//constexpr auto obj_stack = "Stack";

using namespace std;
using namespace ds_modals;

template<typename T>
stack<T>::stack(unsigned short length) : dsa_obj("Stack"), len_(length)
{
	arr_fixed_ = new T(length);
	top_ = -1;
}

template<typename T>
stack<T>::~stack()
{
	delete[] arr_fixed_;
}

template <typename T>
size_t stack<T>::size() const
{
	return sizeof(arr_fixed_) / sizeof(arr_fixed_[0]);
}

template<typename T>
bool stack<T>::is_empty() const
{
	return size() == 0;
}

template<typename T>
void stack<T>::push(T obj)
{
	if (top_ == len_ - 1)
	{
		// Stack is full
		cout << "Stack is full" << endl;
		return;
	}
	else
	{
		arr_fixed_[++top_] = obj;
	}
}

template<typename T>
T* stack<T>::pop()
{
	return nullptr;
}

template<typename T>
vector<string> stack<T>::str_out()
{
	return vector<string>();
}

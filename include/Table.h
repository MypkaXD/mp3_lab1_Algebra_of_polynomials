#pragma once
template<class Tkey, class T>
class Table {
public:
	virtual T find(Tkey key) const = 0;
	virtual void push(Tkey key, T value) = 0;
	virtual void erase(Tkey key) = 0;
};
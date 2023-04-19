#pragma once
#include "Table.h"
#include <functional>

template <class Tkey, class T>
class compare {
	int (*comp)(Tkey, Tkey);
public:
	compare(int (*compPtr)(Tkey, Tkey)) {
		comp = compPtr;
	}
	bool operator() (std::pair<Tkey, T> left, std::pair<Tkey, T> right) {
		return comp(left.first, right.first) == -1;
	}
};

template <class Tkey, class T>
class OrderedMap : public Table<Tkey, T> {
	std::vector<std::pair<Tkey, T>> data;
	int (*comp)(Tkey, Tkey);
public:

	OrderedMap(int (*compPtr)(Tkey, Tkey)) {
		comp = compPtr;
	}

	T find(Tkey key) const {
		return (*std::lower_bound(data.begin(), data.end(), std::make_pair(key, T()), compare<Tkey, T>(comp))).second;
	}

	typename std::vector<std::pair<Tkey, T>>::iterator findIter(Tkey key) {
		return std::lower_bound(data.begin(), data.end(), std::make_pair(key, T()), compare<Tkey, T>(comp));
	}

	void push(Tkey key, T value) {
		auto i = findIter(key);
		if (!data.empty()) {
			if (i == data.end())
				data.insert(i, std::make_pair(key, value));
			else
				(*i).second = value;
		}
		else
			data.push_back({ key,value });
	}

	void erase(Tkey key) {
		auto i = findIter(key);
		if (i != data.end())
			data.erase(findIter(key));
	}

	void print() {
		for (auto count = data.begin(); count != data.end(); ++count)
			std::cout << (*count).first << " " << (*count).second << std::endl;
	}
};
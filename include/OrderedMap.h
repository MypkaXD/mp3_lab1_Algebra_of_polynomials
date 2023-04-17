#pragma once

template<class Tkey, class T>
class OrderedMap {
	std::vector<std::pair<Tkey, T>> data;
	int (*comp)(Tkey, Tkey);
public:

	OrderedMap(int (*compPtr)(Tkey, Tkey)) {
		comp = compPtr;
	}

	inline bool compare(std::pair<Tkey, T> left, std::pair<Tkey, T> right) {
		return comp(left.first, right.first) == -1;
	}

	typename std::vector<std::pair<Tkey, T>>::iterator find(Tkey key) {
		return std::lower_bound(data.begin(), data.end(), std::make_pair(key, T()), compare);
	}

	void push(Tkey key, T value) {
		auto i = find(key);
		if (!data.empty()) {
			if (i == data.end())
				data.insert(i, std::make_pair(key, value));
			else
				(*i).second = value;
		}
		else
			data.push_back({ key,value });
	}

	typename std::vector<std::pair<Tkey, T>>::iterator erase(Tkey key) {
		auto i = find(key);
		if (i == data.end())
			throw std::exception("ERROR: can't delete");
		return data.erase(find(key));
	}

	void print() {
		for (auto count = data.begin(); count != data.end(); ++count)
			std::cout << (*count).first << " " << (*count).second << std::endl;
	}
};
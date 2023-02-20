#pragma once

template<class T>
inline bool comp(std::pair<int, T> left, std::pair<int, T> right) {
	return left.first < right.first;
}

template<class T>
class OrderedMap {
	std::vector<std::pair<int, T>> data;
public:

	OrderedMap() {
	}

	typename std::vector<std::pair<int, T>>::iterator find(int key) {
		return std::lower_bound(data.begin(), data.end(), std::make_pair(key, T()), comp<T>);
	}

	void push(int key, T value) {
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

	typename std::vector<std::pair<int, T>>::iterator erase(int key) {
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
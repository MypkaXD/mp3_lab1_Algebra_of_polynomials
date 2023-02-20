#pragma once

template<class T>
class MapOnList {
	std::list <std::pair<int, T>> data;
public:
	MapOnList() {
	}

	typename std::list<std::pair<int, T>>::iterator find(int key) {
		auto count = data.begin();
		for (count; count != data.end(); ++count) {
			if ((*count).first == key)
				return count;
		}
		return data.end();
	}

	void push(int key, T value) {
		auto i = find(key);
		if (i == data.end())
			data.push_back({ key,value });
		else {
			(*i).second = value;
		}
	}

	void erase(int key) {
		auto i = find(key);
		if (i == data.end())
			throw std::exception("ERROR: can't delete");
		else {
			(*i).first = data.back().first;
			(*i).second = data.back().second;
			data.pop_back();
		}
	}

	void print() {
		for (auto count = data.begin(); count != data.end(); ++count)
			std::cout << (*count).first << " " << (*count).second << std::endl;
	}
};
#pragma once

template<class Tkey, class T>
class UnorderedMap {
	std::vector<std::pair<Tkey, T>> data;
	int (*comp)(Tkey, Tkey);
public:
	UnorderedMap(int (*compPtr)(Tkey , Tkey)) {
		comp = compPtr;
	}


	typename std::vector<std::pair<Tkey, T>>::iterator find(Tkey key) {
		auto count = data.begin();
		for (count; count != data.end(); ++count) {
			if (comp((*count).first, key) == 0)
				return count;
		}
		return data.end();
	}

	void push(Tkey key, T value) {
		auto i = find(key);
		if (i == data.end())
			data.push_back({ key,value });
		else {
			(*i).second = value;
		}
	}

	void erase(Tkey key) {
		auto i = find(key);
		if (i == data.end())
			throw std::exception("ERROR: can't delete");
		else {
			(*i).first = data[data.size() - 1].first;
			(*i).second = data[data.size() - 1].second;
			data.pop_back();
		}
	}

	void print() {
		for (auto count = data.begin(); count != data.end(); ++count)
			std::cout << (*count).first << " " << (*count).second << std::endl;
	}
};
#pragma once
#include "Forward_List.h"
#include <exception>
#include <vector>
#include <string>

template<class T>
class HashChain {
	std::vector<List<std::pair<std::string, T>>> data;
	const int X = 3;
	const int M = 101;
public:
	HashChain() {
		data = std::vector<List<typename std::pair<std::string, T>>>(M);
	}

	int hash(std::string s) {
		int h = 0;
		int i = 0;
		int x = 1;
		for (char i : s) {
			h += (int)i * x;
			x *= X;
		}
		return h % M;
	}

	T find(std::string key) {
		int h = hash(key);
		for (auto it = data[h].begin(); it != data[h].end(); ++it) {
			if ((*it).first == key) {
				return (*it).second;
			}
		}
		return T();
	}

	void push(std::string key, T value) {
		int h = hash(key);
		bool f = true;
		for (auto it = data[h].begin(); it != data[h].end(); ++it) {
			if ((*it).first == key) {
				f = false;
				(*it).second = value;
				break;
			}
		}
		if (f) {
			data[h].push_front(std::make_pair(key, value));
		}
	}

	void erase(std::string key) {
		int h = hash(key);
		bool f = true;
		if ((*(data[h].begin())).first == key)
			data[h].pop_front();
		else {
			for (auto it = data[h].begin(); !it.isLast(); ++it) {
				if (it.next().first == key) {
					f = false;
					data[h].erase_after(it);
					break;
				}
			}
		}

	}

	void print() {
		for(int h = 0; h < M; h++)
			for (auto count = data[h].begin(); count != data[h].end(); ++count)
				std::cout << (*count).first << " " << (*count).second << std::endl;
	}
};
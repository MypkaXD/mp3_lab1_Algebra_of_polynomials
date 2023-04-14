#pragma once
#include "Forward_List.h"
#include <exception>
#include <vector>
#include <string.h>

template<class T>
class HashChain {
	std::vector<List<std::pair<const char*, T>>> data;
	const int X = 3;
	const int M = 101;
public:
	HashChain() {
		data = std::vector<List<typename std::pair<const char*, T>>>(M);
	}

	int hash(const char* s) {
		int h = 0;
		int i = 0;
		int x = 1;
		while (s[i] != '\0') {
			h += (int)s[i] * x;
			x *= X;
			i++;
		}
		return h % M;
	}

	T find(const char* key) {
		int h = hash(key);
		for (auto it = data[h].begin(); it != data[h].end(); ++it) {
			if (strcmp((*it).first, key) == 0) {
				return (*it).second;
			}
		}
		return T();
	}

	void push(const char* key, T value) {
		int h = hash(key);
		bool f = true;
		for (auto it = data[h].begin(); it != data[h].end(); ++it) {
			if (strcmp((*it).first, key) == 0) {
				f = false;
				(*it).second = value;
				break;
			}
		}
		if (f) {
			data[h].push_front(std::make_pair(key, value));
		}
	}

	void erase(const char* key) {
		int h = hash(key);
		bool f = true;
		if (strcmp((*(data[h].begin())).first, key) == 0)
			data[h].pop_front();
		else {
			for (auto it = data[h].begin(); !it.isLast(); ++it) {
				if (strcmp(it.next().first, key) == 0) {
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
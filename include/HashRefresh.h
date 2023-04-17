#pragma once
#include <exception>
#include <vector>
#include <string>

template<class T>
class HashRefresh {
	std::vector<std::pair<std::string, T>> data;
	std::vector<bool> isValid;                  //was this thing deleted
	std::vector<bool> isFilled;                 //is there anything
	const int X = 3;
	const int M = 101;
	const int STEP = 3;
	int N;

public:
	HashRefresh() {
		data = std::vector<std::pair<std::string, T>>(M);
		isValid = std::vector<bool>(M);
		isFilled = std::vector<bool>(M);
		for (int i = 0; i < M; i++) {
			isValid[i] = false;
			isFilled[i] = false;
		}
		N = 0;
	}

	int hash(std::string s) {
		int h = 0;
		int i = 0;
		int x = 1;
		for (char i: s) {
			h += (int)i * x;
			x *= X;
		}
		return h % M;
	}

	T find(std::string key) {
		int h = hash(key);
		
		while (isFilled[h]) {
			if (data[h].first == key && isValid[h])
				return data[h].second;
			h = (h + STEP) % M;
		}

		return T();
	}

	void push(std::string key, T value) {
		if (N == M) {
			throw std::exception("hash overflow");
		}
		N++;
		int h = hash(key);
		while (isValid[h] && data[h].first != key)
			h = (h + STEP) % M;

		isValid[h] = true;
		isFilled[h] = true;

		data[h] = std::make_pair(key, value);

	}

	void erase(std::string key) {
		if (N == 0)
			return;
		else
			N--;
		int h = hash(key);
		
		while (isFilled[h]) {
			if (data[h].first == key)
				isValid[h] = false;
			h = (h + STEP) % M;
		}

	}

	void print() {
		for (int h = 0; h < M; h++)
			if(isValid[h])
				std::cout << (data[h]).first << " " << (data[h]).second << std::endl;
	}
};
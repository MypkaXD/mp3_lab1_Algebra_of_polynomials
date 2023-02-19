#pragma once
#include "Forward_List.h"
#include <iostream>
#include <exception>

class Polynom {

	class Monom {
		double coef;
		int x;
		int y;
		int z;

	public:

		Monom() : coef(0), x(0), y(0), z(0) {}

		Monom(double c, int nx, int ny, int nz) : coef(c), x(nx), y(ny), z(nz) {}

		Monom(const Monom& m) {
			coef = m.coef;
			x = m.x;
			y = m.y;
			z = m.z;
		}

		Monom& operator=(const Monom& m) {
			coef = m.coef;
			x = m.x;
			y = m.y;
			z = m.z;
			return *this;
		}

		// other comparing to this is: -1 less 0 equal 1 greater
		int comp(Monom& other) {

			if (x != other.x)
				if (x > other.x)
					return -1;
				else
					return 1;
			if (y != other.y)
				if (y > other.y)
					return -1;
				else
					return 1;
			if (z != other.z)
				if (z > other.z)
					return -1;
				else
					return 1;

			return 0;

		}

		double getCoef() {
			return coef;
		}

		int getX() {
			return x;
		}

		int getY() {
			return y;
		}

		int getZ() {
			return z;
		}

		void changeX(int i) {
			x += i;
		}

		void changeY(int i) {
			y += i;
		}

		void changeZ(int i) {
			z += i;
		}

		//for division
		int isNotLessInEveryVariable(const Monom& m) const {
			if (x >= m.x && y >= m.y && z >= m.z) {
				return true;
			}
			else
				return false;
		}

		Monom& operator+=(const Monom& m) {

			if (x == m.x && y == m.y && z == m.z)
				coef += m.coef;
			else
				throw std::exception("CANT SUM UNEQUAL MONOMS");

			return *this;
		}

		Monom operator+(const Monom& m) const {

			if (x == m.x && y == m.y && z == m.z)
				return Monom(coef + m.coef, x, y, z);
			else
				throw std::exception("CANT SUM UNEQUAL MONOMS");

		}

		Monom operator-(const Monom& m) const {

			if (x == m.x && y == m.y && z == m.z)
				return Monom(coef - m.coef, x, y, z);
			else
				throw std::exception("CANT SUM UNEQUAL MONOMS");

		}

		Monom operator/(const Monom& m) const {

			return Monom(coef / m.coef, x - m.x, y - m.y, z - m.z);

		}

		Monom operator*(const Monom& m) const {

			return Monom(coef * m.coef, x + m.x, y + m.y, z + m.z);

		}

		Monom operator*(int c) const {

			return Monom(coef * c, x, y, z);

		}

	};

	List<Monom> data;

	void addMonom(Monom& m) {

		if (data.empty()) {
			data.push_front(m);
			return;
		}

		auto it = data.begin();
		auto prev = data.begin();
		//regressive order
		while (it != data.end()) {
			if (m.comp(*it) == 0) {
				*it += m;
				return;
			}
			if (m.comp(*it) == -1) {

				if (it == data.begin()) {
					data.push_front(m);
					return;
				}

				data.insert_after(prev, m);
				return;

			}
			prev = it;
			++it;
		}

		data.insert_after(prev, m);

	}

public:

	Polynom() {
		data = List<Monom>();
	}

	Polynom(const Polynom& p) {
		data = p.data;
	}

	Polynom(Monom& m) {
		data = List<Monom>();
		addMonom(m);
	}

	Polynom& operator=(const Polynom& p) {
		data = p.data;
		return *this;
	}

	double stod(const char* str, int n) {
		double res = 0;
		double power = 1;                                //after dot
		int i = 0;
		bool f = false;

		if (str[0] == '-') {
			f = true;
			i++;
		}

		while (str[i] != '.') {
			if (i == n) {
				if (f)
					return -res;
				else
					return res;
			}
			res *= 10.0;
			res += (double)((int)str[i] - 48);
			i++;
		}
		i++;

		while (i < n) {
			power /= 10.0;
			res += power * ((double)((int)str[i] - 48));
			i++;
		}

		if (f)
			return -res;
		else
			return res;
	}

	int stoi(const char* str, int n) {
		int res = 0;
		int i = 0;
		while (i < n) {
			res += ((int)str[i] - 48);
			res *= 10;
			i++;
		}
		return res / 10;
	}


	//Assuming that str contains only one polinom and it is valid. Example: "12 4 15 1 .4 21 1 1 9.7 0 1 0"
	Polynom(const char* str) {

		int counter = 0;
		int i = 0;

		double c;
		int nx, ny, nz;
		int j;

		for (j = 0; true; j++) {
			if (str[j] == ' ' || str[j] == '\0') {
				if (counter == 0) {                         //coefficient
					c = stod(str + i, j - i);
					j++;
					i = j;
					counter++;
				}

				else if (counter == 1) {                    //x
					nx = stoi(str + i, j - i);
					j++;
					i = j;
					counter++;
				}

				else if (counter == 2) {                    //y
					ny = stoi(str + i, j - i);
					j++;
					i = j;
					counter++;
				}

				else if (counter == 3) {                    //z + push parsed monom
					nz = stoi(str + i, j - i);
					j++;
					i = j;
					addMonom(Monom(c, nx, ny, nz));
					counter = 0;
					if (str[j - 1] == '\0')
						break;
				}

			}
		}

	}

	bool operator==(const Polynom& other) const noexcept { // вопрос про сравнения длин xDD
		for (auto count = data.begin(), count_other = other.data.begin(); count != data.end(), count_other != other.data.end(); ++count, ++count_other)
			if ((*count).getCoef() != (*count_other).getCoef() || (*count).getX() != (*count_other).getX() || (*count).getY() != (*count_other).getY() || (*count).getZ() != (*count_other).getZ())
				return false;
		return true;
	}

	bool operator!=(const Polynom& other) const noexcept {
		return (!(*this == other));
	}

	List<Monom>::iterator begin() const {
		return data.begin();
	}

	List<Monom>::iterator end() const {
		return data.end();
	}

	//operations with polynoms
	Polynom operator+(const Polynom& p) const {
		Polynom res;
		auto it = begin();
		auto pit = p.begin();
		List<Monom>::iterator i;
		while (it != end() && pit != end()) {
			int c = (*it).comp(*pit);
			if (c == 0) {
				if (res.data.empty()) {
					res.data.push_front((*it) + (*pit));
					i = res.begin();
				}
				else {
					res.data.insert_after(i, (*it) + (*pit));
					++i;
				}
				++it;
				++pit;
			}

			if (c == -1) {
				if (res.data.empty()) {
					res.data.push_front((*it));
					i = res.begin();
				}
				else {
					res.data.insert_after(i, (*it));
					++i;
				}
				++it;
			}

			if (c == 1) {
				if (res.data.empty()) {
					res.data.push_front((*pit));
					i = res.begin();
				}
				else {
					res.data.insert_after(i, (*pit));
					++i;
				}
				++pit;
			}

		}
		return res;

	}

	Polynom operator-(const Polynom& p) const {
		Polynom res;
		auto it = begin();
		auto pit = p.begin();
		while (it != end()) {
			res.addMonom(*it);
			++it;
		}
		while (pit != p.end()) {
			res.addMonom((*pit) * (-1));
			++pit;
		}
		return res;
	}

	Polynom operator*(const Polynom& p) const {
		Polynom res;
		for (auto pit = begin(); pit != p.end(); ++pit) {
			for (auto it = p.begin(); it != end(); ++it) {
				res.addMonom((*it) * (*pit));
			}
		}
		return res;
	}

	/*
	//erase zero monoms ()
	void flush() {
		while ((*begin()).getCoef() > -0.00001 && (*begin()).getCoef() < 0.00001) {
			data.pop_front();
		}
		auto prev = begin();
		for (auto it = begin(); it != end(); ++it) {
			if ((*it).getCoef() > -0.00001 && (*it).getCoef() < 0.00001) {
				data.erase_after(prev);
			}
			prev = it;
		}
	}
	*/

	Polynom operator/(const Polynom& p) const {     //integer division
		Polynom cp(*this);
		Polynom res;
		auto it1 = cp.begin();
		auto it2 = p.begin();
		while (it1 != cp.end() && (*it1).isNotLessInEveryVariable(*it2)) {
			Monom m = (*it1) / (*it2);
			res.addMonom(m);
			cp -= p * Polynom(m);
			cp.data.pop_front();
			it1 = cp.begin();
		}
		return res;
	}

	Polynom& operator+=(const Polynom& p) {
		auto pit = p.begin();
		while (pit != p.end()) {
			addMonom(*pit);
			++pit;
		}
		return *this;
	}

	Polynom& operator-=(const Polynom& p) {
		auto pit = p.begin();
		while (pit != p.end()) {
			addMonom((*pit) * (-1));
			++pit;
		}
		return *this;
	}

	Polynom& operator*=(const Polynom& p) {
		Polynom cp;
		for (auto pit = begin(); pit != end(); ++pit) {
			for (auto it = p.begin(); it != p.end(); ++it) {
				addMonom((*it) * (*pit));
			}
		}
		*this = cp;
		return *this;
	}

	Polynom& operator/=(const Polynom& p) {
		Polynom cp(*this);
		Polynom res;
		auto it1 = cp.begin();
		auto it2 = p.begin();
		while ((*it1).isNotLessInEveryVariable(*it2) && it1 != cp.end()) {
			Monom m = (*it1) / (*it2);
			res.addMonom(m);
			cp -= p * Polynom(m);
			it1 = cp.begin();
		}
		*this = res;
		return *this;
	}

	void print() {
		for (auto it = data.begin(); it != data.end(); ++it) {
			std::cout << (*it).getCoef() << " " << (*it).getX() << " " << (*it).getY() << " " << (*it).getZ() << '\n';
		}

	}

	void differentiationX() { // дифференцируем по переменной x
		for (auto count = data.begin(); count != data.end(); ++count) {
			if ((*count).getX() == 0)
				continue;
			else
				(*count).changeX(-1);
		}
	}

	void differentiationY() { // дифференцируем по переменной y
		for (auto count = data.begin(); count != data.end(); ++count) {
			if ((*count).getY() == 0)
				continue;
			else
				(*count).changeY(-1);
		}
	}

	void differentiationZ() { // дифференцируем по переменной z
		for (auto count = data.begin(); count != data.end(); ++count) {
			if ((*count).getZ() == 0)
				continue;
			else
				(*count).changeZ(-1);
		}
	}

	void integrationX() { // интегрирование по переменной x
		for (auto count = data.begin(); count != data.end(); ++count) {
			(*count).changeX(+1);
		}
	}

	void integrationY() { // интегрирование по переменной y
		for (auto count = data.begin(); count != data.end(); ++count) {
			(*count).changeY(+1);
		}
	}

	void integrationZ() { // интегрирование по переменной z
		for (auto count = data.begin(); count != data.end(); ++count) {
			(*count).changeZ(+1);
		}
	}

	double point_calculation(double x, double y, double z) {
		double sum = .0;

		for (auto count = data.begin(); count != data.end(); ++count)
			sum += (*count).getCoef() * pow(x, (*count).getX()) * pow(y, (*count).getY()) * pow(z, (*count).getZ());

		return sum;
	}

};

﻿#pragma once
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

		Monom& operator=(const Monom& other) {
			coef = other.coef;
			x = other.x;
			y = other.y;
			z = other.z;
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

		void changeCoef(double value) {
			coef = value;
		}

		//for division
		int isNotLessInEveryVariable(const Monom& m) const {
			if (x >= m.x && y >= m.y && z >= m.z) {
				return true;
			}
			else
				return false;
		}

		Monom& operator+=(const Monom& other) {

			if (x == other.x && y == other.y && z == other.z)
				coef += other.coef;
			else
				throw std::exception("CANT SUM UNEQUAL MONOMS");

			return *this;
		}

		Monom operator+(const Monom& other) const {

			if (x == other.x && y == other.y && z == other.z)
				return Monom(coef + other.coef, x, y, z);
			else
				throw std::exception("CANT SUM UNEQUAL MONOMS");
		}

		Monom operator-(const Monom& other) const {

			if (x == other.x && y == other.y && z == other.z)
				return Monom(coef - other.coef, x, y, z);
			else
				throw std::exception("CANT SUM UNEQUAL MONOMS");

		}

		Monom operator/(const Monom& other) const {

			return Monom(coef / other.coef, x - other.x, y - other.y, z - other.z);

		}

		Monom operator*(const Monom& other) const {

			return Monom(coef * other.coef, x + other.x, y + other.y, z + other.z);

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

	bool isDigit(char c) {
		if (((int)c - 48) < 0 || (((int)c - 48)) > 9)
			return false;
		else
			return true;
	}

	int firstNonDigitOrDot(const char* s) {
		int i = 0;
		while (isDigit(s[i]) || s[i] == '.')
			i++;
		return i;
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

			if (!isDigit(str[i]))
				throw std::exception("invalid input");

			res += (double)((int)str[i] - 48);
			i++;
		}
		i++;

		while (i < n) {
			power /= 10.0;

			if (!isDigit(str[i]))
				throw std::exception("invalid input");

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

			if (!isDigit(str[i]))
				throw std::exception("invalid input");

			res *= 10;
			i++;
		}
		return res / 10;
	}

	/*
	Polynom(const std::string& other) {

		state cv = Polynom::state::wait_coef;

		for (size_t count = 0; count < other.size(); ++count) {
			switch (cv)
			{
			case Polynom::state::wait_coef:
				if ((other[count] >= (int)'0' && other[count] <= (int)'9'))
					cv = Polynom::state::wait_coef_or_point_or_letters;
				else
					cv = Polynom::state::error;
				break;
			case Polynom::state::wait_coef_or_point_or_letters:

				break;
			default:
				break;
			}
		}
	}
	*/
	Polynom(const char* str) {

		int i = 0;

		double c = 0;
		int nx = 0, ny = 0, nz = 0;
		int j;
		bool writing = false;
		bool negative = false;

		for (j = 0; true; j++) {
			
			if (isDigit(str[j]) || str[j] == 'x' || str[j] == 'y' || str[j] == 'z' || str[j] == '.')
				writing = true;
			if (str[j] == '+') {
				writing = true;
				negative = false;
			}
			if (str[j] == '-') {
				if (negative || writing)
					throw std::exception("invalid input");
				writing = true;
				negative = true;
			}

			if (writing) {

				if (isDigit(str[j]) || str[j] == '.') {                         //coefficient
					i = firstNonDigitOrDot(str + j);
					
					if(negative)
						c = -stod(str + j, i);
					else {
						c = stod(str + j, i);
					}
					j += i - 1;
					negative = false;
				}

				else if (str[j] == 'x') {                    //x
					if (str[j + 1] != '^')
						throw std::exception("invalid input");
					i = firstNonDigitOrDot(str + j + 2);

					nx = stoi(str + j + 2, i);
					j += i + 1;
				}

				else if (str[j] == 'y') {                    //y
					if (str[j + 1] != '^')
						throw std::exception("invalid input");
					i = firstNonDigitOrDot(str + j + 2);

					ny = stoi(str + j + 2, i);
					j += i + 1;
				}

				else if (str[j] == 'z') {                    //z + push parsed monom
					if (str[j + 1] != '^')
						throw std::exception("invalid input");
					i = firstNonDigitOrDot(str + j + 2);

					nz = stoi(str + j + 2, i);
					j += i + 1;
				}

				else if (str[j] == ' ') {
					addMonom(Monom(c, nx, ny, nz));
					c = 1.0;
					nx = 0;
					ny = 0;
					nz = 0;
					writing = false;
				}

				else if (str[j] == '\0') {
					addMonom(Monom(c, nx, ny, nz));
					c = 1.0;
					nx = 0;
					ny = 0;
					nz = 0;
					writing = false;
					break;
				}
			}
		}
	}

	bool operator==(const Polynom& other) const noexcept { // ������ ��� ��������� ���� xDD
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
		List<Monom>::iterator i;
		while (it != end() && pit != end()) {
			int c = (*it).comp(*pit);
			if (c == 0) {
				if (res.data.empty()) {
					res.data.push_front((*it) + (*pit));
					i = res.begin();
				}
				else {
					res.data.insert_after(i, (*it) - (*pit));
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
					res.data.push_front((*pit) * (-1));
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
		*this = res;
		return *this;
	}

	Polynom& operator-=(const Polynom& p) {

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
					res.data.insert_after(i, (*it) - (*pit));
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
					res.data.push_front((*pit) * (-1));
					i = res.begin();
				}
				else {
					res.data.insert_after(i, (*pit));
					++i;
				}
				++pit;
			}

		}
		*this = res;
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

	void differentiationX() { // �������������� �� ���������� x
		for (auto count = data.begin(); count != data.end(); ++count) {
			if ((*count).getX() == 0)
				(*count).changeCoef(0);
			else {
				(*count).changeCoef((*count).getCoef() * (*count).getX());
				(*count).changeX(-1);
			}
		}
	}

	void differentiationY() { // �������������� �� ���������� y
		for (auto count = data.begin(); count != data.end(); ++count) {
			if ((*count).getY() == 0)
				(*count).changeCoef(0);
			else {
				(*count).changeCoef((*count).getCoef() * (*count).getY());
				(*count).changeY(-1);
			}
		}
	}

	void differentiationZ() { // �������������� �� ���������� z
		for (auto count = data.begin(); count != data.end(); ++count) {
			if ((*count).getZ() == 0)
				(*count).changeCoef(0);
			else {
				(*count).changeCoef((*count).getCoef() * (*count).getZ());
				(*count).changeZ(-1);
			}
		}
	}

	void integrationX() { // �������������� �� ���������� x
		for (auto count = data.begin(); count != data.end(); ++count) {
			(*count).changeX(+1);
			(*count).changeCoef((*count).getCoef() / (*count).getX());
		}
	}

	void integrationY() { // �������������� �� ���������� y
		for (auto count = data.begin(); count != data.end(); ++count) {
			(*count).changeY(+1);
			(*count).changeCoef((*count).getCoef() / (*count).getY());
		}
	}

	void integrationZ() { // �������������� �� ���������� z
		for (auto count = data.begin(); count != data.end(); ++count) {
			(*count).changeZ(+1);
			(*count).changeCoef((*count).getCoef() / (*count).getZ());
		}
	}

	double point_calculation(double x, double y, double z) {
		double sum = .0;

		for (auto count = data.begin(); count != data.end(); ++count)
			sum += (*count).getCoef() * pow(x, (*count).getX()) * pow(y, (*count).getY()) * pow(z, (*count).getZ());

		return sum;
	}

	void pow_polinom(int n) {
		if (n < 0)
			throw std::exception("CANT POW WITH N LESS THAN ZERO");
		else if (n == 0) {
			data.clear();
			data.push_front(Monom(1, 0, 0, 0));
			return;
		}
		else {
			Polynom temp = *this;
			for (int count = 1; count < n; ++count) {
				*this = temp * *this;
			}
		}
	}
};
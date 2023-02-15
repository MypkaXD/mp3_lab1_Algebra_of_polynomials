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

		// other comparing to this is: -1 less 0 equal 1 greater
		int comp(Monom& other) {

			if (x != other.x)
				return (x > other.x) ? -1 : 1;
			if (y != other.y)
				return (y > other.y) ? -1 : 1;
			if (z != other.z)
				return (z > other.z) ? -1 : 1;

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

		Monom& operator+=(const Monom& m) {

			if (x == m.x && y == m.y && z == m.z)
				coef += m.coef;
			else
				throw std::exception("CANT SUM UNEQUAL MONOMS");

			return *this;
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

	double stod(const char* str, int n) {
		double res;
		double power = 1;                                //after dot
		int i = 1;
		
		if (str[0] != '.') {
			res = (double)((int)str[0] - 48);
			while (str[i] != '.') {
				if (i == n)
					return res;
				res *= 10.0;
				res += (double)((int)str[i] - 48);
				i++;
			}
			i++;
		}
		else 
			res = 0;


		while (i < n) {
			power /= 10.0;
			res += power * ((double)((int)str[i] - 48));
			i++;
		}
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

		for (int j = 0; true; j++) {
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
					if (str[j] == '\0')
						break;
				}

			}
		}

	}

	List<Monom>::iterator begin() {
		return data.begin();
	}

	List<Monom>::iterator end() {
		return data.end();
	}

	void print() {
		for (auto it = data.begin(); it != data.end(); ++it) {
			std::cout << (*it).getCoef() << " " << (*it).getX() << " " << (*it).getY() << " " << (*it).getZ() << '\n';
		}

	}

};


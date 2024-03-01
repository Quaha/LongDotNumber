#include "libs.h"
#include "Vector.h"

#include "LongNumber.h"

void LongNumber::makeCorrect() {
	for (int i = 0; i < number.size(); i++) {
		if (number[i] >= BASE) {
			if (i + 1 == number.size()) {
				number.push_back(0);
			}
			number[i + 1] += number[i] / BASE;
			number[i] %= BASE;
		}
		if (number[i] < 0) {
			number[i] += BASE;
			if (i + 1 != number.size()) {
				number[i + 1]--;
			}
		}
	}
	while (number.size() > 1 && number.back() == 0) {
		number.pop_back();
	}
	if (number.size() == 1 && number.back() == 0) {
		sign = 1;
	}
}

LongNumber LongNumber::stringToLongNumber(const std::string& S) {
	if (S[0] == '-') {
		sign = -1;
		int sz = (S.size() - 1) / BASE_SIZE + (int)(((S.size() - 1) % BASE_SIZE) != 0);
		number.resize(sz, 0);
		for (int i = 0, j = S.size(); i < size(); i++, j -= BASE_SIZE) {
			int st = j - BASE_SIZE;
			if (st <= 0) st = 1;
			int d = j - st;
			number[i] = stoi(S.substr(st, d));
		}
	}
	else {
		int sz = S.size() / BASE_SIZE + (int)((S.size() % BASE_SIZE) != 0);
		number.resize(sz, 0);
		for (int i = 0, j = S.size(); i < size(); i++, j -= BASE_SIZE) {
			int st = j - BASE_SIZE;
			if (st < 0) st = 0;
			int d = j - st;
			number[i] = stoi(S.substr(st, d));
		}
	}
	return (*this);
}

LongNumber LongNumber::divisionByTwo() {
	for (int i = 0; i < number.size(); i++) {
		if (number[i] % 2 == 0) {
			number[i] /= 2;
		}
		else {
			number[i] /= 2;
			if (i != 0) {
				number[i - 1] += BASE / 2;
			}
		}
	}
	makeCorrect();
	return (*this);
}

LongNumber LongNumber::abs() const{
	LongNumber temp = (*this);
	temp.sign = 1;
	return temp;
}

LongNumber::LongNumber() {
	number.push_back(0);
}

LongNumber::LongNumber(const char* S) {
	std::string temp = "";
	if (S[0] != '-') {
		temp.push_back(S[0]);
	}
	else {
		sign = -1;
	}
	for (int i = 1; S[i] != '\0'; i++) {
		temp.push_back(S[i]);
	}
	(*this) = stringToLongNumber(temp);
}

LongNumber::LongNumber(int V) {
	if (V < 0) {
		sign = -1;
		V = -V;
	}
	(*this) = stringToLongNumber(std::to_string(V));
}

unsigned int LongNumber::size() const {
	return number.size();
}

LongNumber LongNumber::operator-() {
	sign = -sign;
	return (*this);
}

LongNumber LongNumber::operator+(const LongNumber& V) const {
	if (this->sign == -1 && V.sign == -1) {
		return -((*this).abs() + V.abs());
	}
	if (this->sign == -1 && V.sign == 1) {
		return V - this->abs();
	}
	if (this->sign == 1 && V.sign == -1) {
		return (*this) - V.abs();
	}
	LongNumber res;
	int sz = V.size();
	if ((*this).size() > sz) {
		sz = (*this).size();
	}
	for (int i = 0; i < sz; i++) {
		if (i == res.size()) {
			res.number.push_back(0);
		}
		if (i < V.size()) {
			res.number[i] += V.number[i];
		}
		if (i < (*this).size()) {
			res.number[i] += (*this).number[i];
		}
	}
	res.makeCorrect();
	return res;
}

LongNumber LongNumber::operator-(const LongNumber& V) const {
	if (this->sign == -1 && V.sign == -1) {
		return V.abs() - this->abs();
	}
	if (this->sign == -1 && V.sign == 1) {
		return -((*this).abs() + V);
	}
	if (this->sign == 1 && V.sign == -1) {
		return (*this) + V.abs();
	}
	LongNumber res;
	int sz = V.size();
	if ((*this).size() > sz) {
		sz = (*this).size();
	}
	for (int i = 0; i < sz; i++) {
		if (i == res.size()) {
			res.number.push_back(0);
		}
		if (i < V.size()) {
			res.number[i] -= V.number[i];
		}
		if (i < (*this).size()) {
			res.number[i] += (*this).number[i];
		}
	}
	res.makeCorrect();
	return res;
}

LongNumber LongNumber::operator*(const LongNumber& V) const {
	LongNumber res;
	res = 0;

	for (int i = 0; i < V.number.size(); i++) {
		LongNumber temp = (*this);
		for (int j = 0; j < i; j++) {
			temp.number.insert(0, 0);
		}
		for (int j = 0; j < temp.number.size(); j++) {
			temp.number[j] *= V.number[i];
		}
		res = res + temp;
	}
	
	res.sign = (this->sign * V.sign);
	res.makeCorrect();
	return res;
}

LongNumber LongNumber::operator/(const LongNumber& V) const {
	LongNumber l, r, m;
	l = 0;
	r = (*this);
	int cnt = 0;
	while (r - l > 1) {
		m = (l + r).divisionByTwo();
		if (m * V <= (*this)) {
			l = m;
		}
		else {
			r = m;
		}
	}
	l.sign = (this->sign * V.sign);
	l.makeCorrect();
	return l;
}

bool LongNumber::operator<(const LongNumber& V) const {
	if (this->sign == -1 && V.sign == 1) return true;
	if (this->sign == 1 && V.sign == -1) return false;
	if (this->number.size() < V.size()) return true;
	if (this->number.size() > V.size()) return false;
	for (int i = V.size() - 1; i >= 0; i--) {
		if (this->number[i] < V.number[i]) return true;
		if (this->number[i] > V.number[i]) return false;
	}
	return false;
}

bool LongNumber::operator==(const LongNumber& V) const {
	if ((*this) < V || V < (*this)) return false;
	return true;
}

bool LongNumber::operator!=(const LongNumber& V) const {
	return !((*this) == V);
}

bool LongNumber::operator<=(const LongNumber & V) const {
	return (*this) < V || (*this) == V;
}

bool LongNumber::operator>(const LongNumber& V) const {
	return V < (*this);
}
bool LongNumber::operator>=(const LongNumber& V) const {
	return (*this) > V || (*this) == V;
}

std::ostream& operator << (std::ostream& out, const LongNumber& V) {
	if (V.sign == -1) {
		std::cout << '-';
	}
	for (int i = V.size() - 1; i >= 0; i--) {
		if (i == V.size() - 1) {
			std::cout << V.number[i];
		}
		else {
			std::cout << std::setfill('0') << std::setw(4) << V.number[i];
		}
	}
	return out;
}

std::istream& operator >> (std::istream& in, LongNumber& V) {
	std::string S;
	in >> S;
	V.stringToLongNumber(S);
	return in;
}
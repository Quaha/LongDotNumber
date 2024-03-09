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
	}

	for (int i = 0; i < number.size(); i++) {
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

LongNumber LongNumber::stringToLongNumber(std::string S) {
	if (S[0] == '-') {
		sign = -1;
		S = S.substr(1, S.size() - 1);
	}
	else {
		sign = 1;
	}

	number.clear();
	for (int end_of_digit = S.size();end_of_digit > 0;end_of_digit -= BASE_SIZE) {
		int start_of_digit = end_of_digit - BASE_SIZE;
		if (start_of_digit < 0) {
			start_of_digit = 0;
		}
		number.push_back(stoi(S.substr(start_of_digit, end_of_digit - start_of_digit)));
	}

	makeCorrect();
	return (*this);
}

LongNumber LongNumber::divisionByTwo() {
	for (int i = 0; i < number.size(); i++) {
		if (number[i] % 2 != 0 && i != 0) {
			number[i - 1] += BASE / 2;
		}
		number[i] /= 2;
	}

	makeCorrect();
	return (*this);
}

LongNumber LongNumber::abs() const{
	LongNumber res = (*this);
	res.sign = 1;

	return res;
}

LongNumber::LongNumber() {
	number.push_back(0);
}

LongNumber::LongNumber(const char* S) {
	std::string res = "";
	for (int i = 0; S[i] != '\0'; i++) {
		res.push_back(S[i]);
	}

	stringToLongNumber(res);
}

LongNumber::LongNumber(int V) {
	stringToLongNumber(std::to_string(V));
}

unsigned int LongNumber::size() const {
	return number.size();
}

LongNumber LongNumber::operator-() const {
	LongNumber res = (*this);
	res.sign = -res.sign;

	return res;
}

LongNumber LongNumber::operator+(const LongNumber& V) const {
	if (this->sign == -1 && V.sign == -1) {
		return -(this->abs() + V.abs());
	}
	if (this->sign == -1 && V.sign == 1) {
		return V - this->abs();
	}
	if (this->sign == 1 && V.sign == -1) {
		return (*this) - V.abs();
	}

	LongNumber res;
	int sz = V.size();
	if (this->size() > sz) {
		sz = this->size();
	}
	for (int i = 0; i < sz; i++) {
		res.number.push_back(0);
		if (i < V.size()) {
			res.number[i] += V.number[i];
		}
		if (i < this->size()) {
			res.number[i] += this->number[i];
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
		return -(this->abs() + V);
	}
	if (this->sign == 1 && V.sign == -1) {
		return (*this) + V.abs();
	}

	if ((*this) < V) {
		return -(V - (*this));
	}

	LongNumber res;
	int sz = V.size();
	if (this->size() > sz) {
		sz = this->size();
	}
	for (int i = 0; i < sz; i++) {
		if (i == res.size()) {
			res.number.push_back(0);
		}
		if (i < V.size()) {
			res.number[i] -= V.number[i];
		}
		if (i < this->size()) {
			res.number[i] += this->number[i];
		}
	}

	res.makeCorrect();
	return res;
}

LongNumber LongNumber::operator*(const LongNumber& V) const {
	// Column multiplication
	LongNumber result = 0;
	for (int i = 0; i < V.number.size(); i++) {
		LongNumber temp = (*this);

		for (int j = 0; j < i; j++) {
			temp.number.insert(0, 0);
		}

		for (int j = 0; j < temp.number.size(); j++) {
			temp.number[j] *= V.number[i];
		}
		result = result + temp;
	}
	result.sign = (this->sign * V.sign);

	result.makeCorrect();
	return result;
}

LongNumber LongNumber::operator/(const LongNumber& V) const {
	if (V == 0) throw "Division by zero error!";
	LongNumber l, r, m;
	l = 0;
	r = (*this).abs() + 1;
	int cnt = 0;
	while (r - l > 1) {
		m = (l + r).divisionByTwo();
		if (m * V.abs() <= (*this).abs()) {
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

Vector LongNumber::__get_number() const {
	return number;
}

int LongNumber::__get_sign() const {
	return sign;
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
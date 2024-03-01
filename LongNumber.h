#pragma once

#include "libs.h"
#include "Vector.h"

class LongNumber {

private:

	Vector number;
	int sign = 1;

	void makeCorrect();
	LongNumber stringToLongNumber(const std::string &S);
	LongNumber divisionByTwo();
	LongNumber abs() const;

public:

	LongNumber();
	LongNumber(const char* S);
	LongNumber(int V);

	unsigned int size() const;

	LongNumber operator-();
	LongNumber operator+(const LongNumber& V) const;
	LongNumber operator-(const LongNumber& V) const;
	LongNumber operator*(const LongNumber& V) const;
	LongNumber operator/(const LongNumber& V) const;

	bool operator<(const LongNumber& V) const;
	bool operator==(const LongNumber& V) const;
	bool operator!=(const LongNumber& V) const;
	bool operator<=(const LongNumber& V) const;
	bool operator>(const LongNumber& V) const;
	bool operator>=(const LongNumber& V) const;

	friend std::ostream& operator << (std::ostream& out, const LongNumber& V);
	friend std::istream& operator >> (std::istream& in, LongNumber& V);
};
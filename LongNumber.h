#pragma once

#include "libs.h"
#include "Vector.h"

class LongNumber {

	friend class LongDotNumber;

protected:
	
	Vector number;
	int sign = 1;

	void makeCorrect();
	LongNumber stringToLongNumber(std::string S);
	LongNumber divisionByTwo();
	LongNumber abs() const;

public:

	LongNumber();
	LongNumber(const char* S);
	LongNumber(int V);

	unsigned int size() const;

	LongNumber operator-() const;
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

	Vector __get_number() const;
	int __get_sign() const;

	friend std::ostream& operator << (std::ostream& out, const LongNumber& V);
	friend std::istream& operator >> (std::istream& in, LongNumber& V);
};
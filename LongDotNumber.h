#pragma once

#include "libs.h"
#include "LongNumber.h"

class LongDotNumber {

protected:

	LongNumber number;
	int degree = 0;

	LongDotNumber stringToLongDotNumber(std::string S);
	std::string longDotNumberToString() const;
	void removingExtraDecimalPlaces();

public:

	LongDotNumber();
	LongDotNumber(std::string S);

	void __clear();

	LongDotNumber operator-() const;
	LongDotNumber operator+(const LongDotNumber& V) const;
	LongDotNumber operator-(const LongDotNumber& V) const;
	LongDotNumber operator*(const LongDotNumber& V) const;
	LongDotNumber operator/(const LongDotNumber& V) const;

	friend std::ostream& operator << (std::ostream& out, const LongDotNumber& V);
	friend std::istream& operator >> (std::istream& in, LongDotNumber& V);
};
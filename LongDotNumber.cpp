#include "libs.h"
#include "LongNumber.h"

#include "LongDotNumber.h"

LongDotNumber LongDotNumber::stringToLongDotNumber(std::string S) {
    __clear();
    int pointIndex = -1;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == '.') {
            if (pointIndex == -1) {
                pointIndex = i;
            }
            else {
                throw "More than 1 point in number";
            }
        }
    }

    if (pointIndex != -1) {
        while (S.back() == '0' && S.back() != '.') {
            S.pop_back();
        }
    }

    degree = 0;
    if (pointIndex != -1) {
        degree = -((int)S.size() - pointIndex) + 1;
    }

    if (pointIndex != -1) {
        S.erase(pointIndex, 1);
    }
    number.stringToLongNumber(S);
    removingExtraDecimalPlaces();

    return (*this);
}

std::string LongDotNumber::longDotNumberToString() const {
    std::string result = "";

    for (int i = (int)number.number.size() - 1; i >= 0; i--) {
        std::string temp = std::to_string(number.number[i]);
        if (i != (int)number.number.size() - 1 && temp.size() < 4) {
            for (int j = 0; j < 4 - temp.size(); j++) {
                result.push_back('0');
            }
        }
        for (char C : temp) {
            result.push_back(C);
        }
    }

    if (result.size() <= -degree) {
        int cnt = -degree - result.size() + 1;
        std::string temp = "";
        for (int i = 0; i < cnt; i++) {
            temp.push_back('0');
        }
        result = temp + result;
    }

    if (degree != 0) {
        result.insert((int)result.size() - (-degree), 1, '.');
    }

    if (degree != 0) {
        while (result.back() == '0') {
            result.pop_back();
        }
        if (result.back() == '.') {
            result.pop_back();
        }
    }

    if (number.__get_sign() == -1) {
        result = "-" + result;
    }
    return result;
}

void LongDotNumber::removingExtraDecimalPlaces() {
    if (degree >= -NUMBER_OF_DECIMAL_PLACES) {
        return;
    }

    LongNumber extra_digits = 10;
    LongNumber increase_for_rounding = 5 * number.__get_sign();

    for (int i = 1; i < -degree - NUMBER_OF_DECIMAL_PLACES; i++) {
        extra_digits = extra_digits * 10;
        increase_for_rounding = increase_for_rounding * 10;
    }
    number = (number + increase_for_rounding) / extra_digits;
    degree = std::max(degree, -NUMBER_OF_DECIMAL_PLACES);

}

LongDotNumber::LongDotNumber() {
    number = 0;
}

LongDotNumber::LongDotNumber(std::string S) {
    stringToLongDotNumber(S);
}

void LongDotNumber::__clear() {
    number = 0;
    degree = 0;
}

LongDotNumber LongDotNumber::operator-() const {
    LongDotNumber result = (*this);
    result.number = -result.number;

    return result;
}

LongDotNumber LongDotNumber::operator+(const LongDotNumber& V) const {
    LongDotNumber A = (*this);
    LongDotNumber B = V;

    while (A.degree < B.degree) {
        B.degree--;
        B.number = B.number * 10;
    }
    while (A.degree > B.degree) {
        A.degree--;
        A.number = A.number * 10;
    }

    LongDotNumber result;
    result.number = A.number + B.number;
    result.degree = A.degree;

    result.removingExtraDecimalPlaces();
    return result;
}

LongDotNumber LongDotNumber::operator-(const LongDotNumber& V) const {
    LongDotNumber A = (*this);
    LongDotNumber B = V;

    while (A.degree < B.degree) {
        B.degree--;
        B.number = B.number * 10;
    }
    while (A.degree > B.degree) {
        A.degree--;
        A.number = A.number * 10;
    }

    LongDotNumber result;
    result.number = A.number - B.number;
    result.degree = A.degree;

    result.removingExtraDecimalPlaces();
    return result;
}

LongDotNumber LongDotNumber::operator*(const LongDotNumber& V) const {
    LongDotNumber A = (*this);
    LongDotNumber B = V;

    while (A.degree < B.degree) {
        B.degree--;
        B.number = B.number * 10;
    }
    while (A.degree > B.degree) {
        A.degree--;
        A.number = A.number * 10;
    }

    LongDotNumber result;
    result.number = A.number * B.number;
    result.degree = A.degree + B.degree;

    result.removingExtraDecimalPlaces();
    return result;
}

LongDotNumber LongDotNumber::operator/(const LongDotNumber& V) const {
    if (V.number == 0) throw "Division by zero error!";

    LongDotNumber A = (*this);
    LongDotNumber B = V;

    while (A.degree > -NUMBER_OF_DECIMAL_PLACES * 2) {
        A.degree--;
        A.number = A.number * 10;
    }

    LongDotNumber result;
    result.number = A.number / B.number;
    result.degree = A.degree - B.degree;

    result.removingExtraDecimalPlaces();
    return result;
}

std::ostream& operator << (std::ostream& out, const LongDotNumber& V) {
    std::cout << V.longDotNumberToString();
    return out;
}

std::istream& operator >> (std::istream& in, LongDotNumber& V) {
    std::string S;
    in >> S;
    V.stringToLongDotNumber(S);
    return in;
}
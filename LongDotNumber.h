#pragma once

#include "libs.h"
#include "LongNumber.h"

class LongDotNumber:public LongNumber {

private:
	LongNumber integer_part;
	LongNumber fractional_part;

};
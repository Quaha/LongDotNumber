#include "libs.h"

#include "Vector.h"

Vector::Vector() {
	real_size = 0;
	storage_size = 1;
	storage_ptr = new int[1];
}

Vector::Vector(const Vector& V) {
	*this = V;
}

Vector::~Vector() {
	delete[] storage_ptr;
}

Vector& Vector::operator=(const Vector& V) {
	int* temp_storage_ptr = new int[V.storage_size];
	for (int i = 0; i < V.real_size; i++) {
		temp_storage_ptr[i] = V.storage_ptr[i];
	}

	this->real_size = V.real_size;
	this->storage_size = V.storage_size;
	delete[] this->storage_ptr;
	this->storage_ptr = temp_storage_ptr;

	return (*this);
}

unsigned int Vector::size() const {
	return real_size;
}

bool Vector::empty() const {
	return (real_size == 0);
}

void Vector::storage_expansion() {
	if (real_size == storage_size) {
		int* temp_storage_ptr = new int[storage_size * 2];
		for (int i = 0; i < storage_size; i++) {
			temp_storage_ptr[i] = this -> storage_ptr[i];
		}

		this -> storage_size *= 2;
		delete[] this -> storage_ptr;
		this -> storage_ptr = temp_storage_ptr;
	}
}

void Vector::push_back(int value) {
	storage_ptr[real_size++] = value;
	storage_expansion();
}

void Vector::storage_decrease() {
	if ((real_size + 1 <= storage_size / 4) && (storage_size != 1)) {
		int* temp_storage_ptr = new int[storage_size / 2];
		for (int i = 0; i < real_size; i++) {
			temp_storage_ptr[i] = this -> storage_ptr[i];
		}

		this -> storage_size /= 2;
		delete[] this -> storage_ptr;
		this -> storage_ptr = temp_storage_ptr;
	}
}

void Vector::pop_back() {
	if (real_size == 0) throw "The absence of the last element of the empty Vector!";

    real_size--;
	storage_decrease();
}

int Vector::back() const {
	if (real_size == 0) throw "The absence of the last element of the empty Vector!";

	return storage_ptr[real_size - 1];
}

void Vector::resize(unsigned int new_size, int value) {
	while (real_size > new_size) {
		pop_back();
	}
	while (real_size < new_size) {
		push_back(value);
	}
}

void Vector::erase(unsigned int i) {
	if (i >= real_size) throw "The Vector index out of range!";

	for (int j = i; j < real_size - 1; j++) {
		storage_ptr[j] = storage_ptr[j + 1];
	}
	pop_back();
}

void Vector::insert(unsigned int i, int value) {
	if (i > real_size) throw "The Vector index out of range!";

	push_back(INT_MAX);
	for (int j = real_size - 2; j >= (int)i; j--) {
		storage_ptr[j + 1] = storage_ptr[j];
	}
	storage_ptr[i] = value;
}

std::ostream& operator << (std::ostream& out, const Vector& V) {
	for (int i = 0; i < V.real_size; i++) {
		out << V.storage_ptr[i] << " ";
	}
	return out;
}

int& Vector::operator[](unsigned int i) {
	if (i >= real_size) throw "The Vector index out of range!";

	return storage_ptr[i];
}

int Vector::operator[](unsigned int i) const{
	if (i >= real_size) throw "The Vector index out of range!";
	return storage_ptr[i];
}

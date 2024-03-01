#pragma once

class Vector {

protected:
	unsigned int real_size = 0;
	unsigned int storage_size = 0; // only 2 ^ N after creating
	int* storage_ptr = nullptr;

	void storage_expansion();
	void storage_decrease();

public:
	Vector();
	Vector(const Vector& V);
	~Vector();

	Vector& operator=(const Vector& V);

	unsigned int size() const;
	bool empty() const;

	void push_back(int value);
	void pop_back();
	int back() const;

	void resize(unsigned int new_size, int value);

	void erase(unsigned int i); // i in [0 ... real_size - 1]
	void insert(unsigned int i, int value); // i in [0 ... real_size]

	friend std::ostream& operator << (std::ostream& out, const Vector& V);

	int& operator[](unsigned int i);
	int operator[](unsigned int i) const;

};
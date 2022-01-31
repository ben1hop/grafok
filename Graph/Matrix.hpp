#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <stdexcept>
#include <string>

// egyszeru negyzetesmatrix implementacio
class Matrix {
	void Flush() {
		for (int i = 0; i < size;i++)
			delete[] values[i];
		delete[] values;
	}
	int** values;
	int size;

public:

	Matrix(const int size) {
		Resize(size);
	}

	~Matrix() {
		Flush();
	}

	static void tempPrintState(int** values, int size, const char* msg) {
		std::cout << msg << std::endl;
		for (int i = 0; i < size;i++) {
			for (int j = 0; j < size;j++)
				std::cout << values[i][j];
			std::cout << std::endl;
		}
		std::cout << "------------------------\n";
	}

	void setValue(const int i, const int j, const int v) {
		if (i < size && j < size && i >= 0 && j >= 0)
			values[i][j] = v;
		else
			throw std::out_of_range("out of range matrix index");
	}

	//// Dinamikusan valtoztatja a matrix meretet megtarva az elemeit
	//void ResizeAndCopy(const int newSize) {
	//	// 1. lementjuk a regit
	//	tempPrintState(values, size, true);
	//	int** old = values; 
	//	tempPrintState(old, size, true);
	//	// 2. toroljuk a jelenlegit
	//	//Flush();
	//	// 3. letrehozzuk az ujat a jelenlegin ( newSize )
	//	values = new int* [newSize];
	//	for (int i = 0; i < newSize;i++) {
	//		values[i] = new int[newSize];
	//		// 4. atmasoljuk a regibol a jelenlegibe az ertekeket
	//		for (int j = 0; j < newSize;j++)
	//			// ha az uj/sor oszlopban jarunk akkor default erteket veszunk mivel az az index nemletezik a regiben
	//			values[i][j] = (i == newSize -1 || j == newSize - 1) ? 0 : old[i][j];	
	//	}
	//	// 5. toroljuk a regit ( oldSize )
	//	for (int i = 0; i < size;i++)
	//		delete[] old[i];
	//	delete[] old;
	//	// 6. noveljuk a meretet
	//	this->size = newSize;
	//	tempPrintState(values, newSize, true);
	//}

	void ResizeAndCopy(const int newSize) {
		int** temp = NULL;
		temp = new int* [newSize];
		// atmasoljuk a regibol a tempbe az ertekeket
		for (int i = 0; i < newSize;i++) {
			temp[i] = new int[newSize];
			for (int j = 0; j < newSize;j++)
				// ha az uj/sor oszlopban jarunk akkor default erteket veszunk mivel az az index nemletezik a regiben
				temp[i][j] = (i == newSize - 1 || j == newSize - 1) ? 0 : values[i][j];
		}
		Flush();
		values = temp;
		this->size = newSize;
		tempPrintState(values, newSize, "copyvalues");
	}

	// Dinamikusan valtoztatja a matrix meretet elvetve az ertekeit
	void Resize(const int newSize) {
		Flush();
		this->size = newSize;
		values = new int* [newSize];
		for (int i = 0; i < newSize;i++) {
			values[i] = new int[newSize];
			for (int j = 0; j < newSize;j++)
				values[i][j] = 0;
		}
		tempPrintState(values, newSize, "resize");
	}
};

#endif // !MATRIX_HPP
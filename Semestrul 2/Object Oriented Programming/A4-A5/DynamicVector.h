#pragma once
#include "movie.h"
#include<iostream>

	
template <typename T>
class DynamicVector

{
private:
	T* allElementsOfMovie;
	int size;
	int capacity;

public:

	DynamicVector(int capacity = 2);

	DynamicVector(const DynamicVector& currentVector);
	~DynamicVector();

	DynamicVector& operator = (const DynamicVector& currentVector);

	void add(const T& inputtedMovie);
	void remove(const T& inputtedMovie);
	void printVector()const;
	void printVectorByGenre(std::string genre)const;
	T& operator[](int position);
	void update(T& availableMovie, T& newMovie);
	bool checkAuthenticity(T& inputtedMovie);
	int getSize() const;
	void resize(int factor = 2);
	

};

template <typename T>
DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->allElementsOfMovie = new T[capacity];

}
//template <typename T>
//void DynamicVector<T>::testDynamicVector()
//{
//	DynamicVector vector{ 5 };
//
//	Movie movie("Terminator", "Action",14000,1984,"https://www.youtube.com/watch?v=k64P4l2Wmeg");
//
//	assert(vector.getSize() == 0);
//
//	vector.add(movie);
//
//	assert(vector.getSize() == 1);
//
//	DynamicVector vector2 = vector;
//	assert(vector2.getSize() == 1);
//
//	DynamicVector vector3{};
//	assert(vector3.getSize() == 0);
//	vector3 = vector2;
//	assert(vector3.getSize() == 1);
//	Movie movie1("Terminator", "Action", 14000, 1984, "https://www.youtube.com/watch?v=k64P4l2Wmeg");
//	vector3.add(movie1);
//	assert(vector3.getSize() == 2);
//	assert(vector.checkAuthenticity(movie) == true);
//	vector.remove(movie);
//	assert(vector.getSize() == 0);
//	vector.add(movie);
//	vector.update(movie, movie1);
//	assert(vector.checkAuthenticity(movie1) == true);
//
//
//}
template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector& currentVector)
{
	this->size = currentVector.size;
	this->capacity = currentVector.capacity;
	this->allElementsOfMovie = new T[this->capacity];
	for (int index = 0; index < this->capacity; index++) {
		this->allElementsOfMovie[index] = currentVector.allElementsOfMovie[index];
	}
}
template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->allElementsOfMovie;
}

//template <typename T>
//void DynamicVector<T>::printVectorByGenre(std::string genre) const{
//	for (int index = 0; index < this->size; index++) {
//		if (this->allElementsOfMovie[index].getGenre() == genre)
//			return true;
//	}
//	return false;
//
//}
//printing all the elements in the Dynamic vector
template <typename T>
void DynamicVector<T>::printVector() const {
	for (int index = 0; index < this->size; index++) {
		std::cout << this->allElementsOfMovie[index] << " ";
	}
}


//goes through all the elements in the dynamic vector and checks if it is available
// return true if it is present and false otherwise
template <typename T>
bool DynamicVector<T>::checkAuthenticity(T& inputtedMovie) {
	for (int index = 0; index < this->size; index++) {
		if (this->allElementsOfMovie[index] == inputtedMovie)
			return true;
	}
	return false;
}

//implementation for == between two Movie type variables
template <typename T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& currentVector) {
	if (this == &currentVector)
		return *this;
	this->size = currentVector.size;
	this->capacity = currentVector.capacity;

	delete[] this->allElementsOfMovie;
	this->allElementsOfMovie = new T[this->capacity];
	for (int index = 0; index < this->size; index++)
		this->allElementsOfMovie[index] = currentVector.allElementsOfMovie[index];
	return *this;

}

// add a new movie inputted by the user
template <typename T>
void DynamicVector<T>::add(const T& inputtedMovie) {
	if (this->size == this->capacity)
		this->resize(2);
	this->allElementsOfMovie[this->size] = inputtedMovie;
	this->size++;

}

//removing a movie from the vector
template <typename T>
void DynamicVector<T>::remove(const T& inputtedMovie) {
	for (int i = 0; i < this->size; i++) {
		if ((inputtedMovie == this->allElementsOfMovie[i]))
		{
			for (int j = i + 1; j < this->size; j++)
			{
				this->allElementsOfMovie[j] = this->allElementsOfMovie[j + 1];
			}
			this->allElementsOfMovie[i] = this->allElementsOfMovie[i + 1];
			break;
		}
	}
	this->size--;

}
//updating a movie from the vector
template <typename T>
void DynamicVector<T>::update(T& availableMovie, T& newMovie) {
	for (int i = 0; i < this->size; i++) {
		if (availableMovie == this->allElementsOfMovie[i])
		{
			this->allElementsOfMovie[i] = newMovie;
			break;
		}}
}

//resizing the dynamic vector if the number of elements excceds capacity of it
template <typename T>
void DynamicVector<T>::resize(int factor)
{
	this->capacity = this->capacity * factor;
	T* resizedVector = new T[this->capacity];
	for (int index = 0; index < this->size; index++) {
		resizedVector[index] = this->allElementsOfMovie[index];		
	}
	delete[] this->allElementsOfMovie;
	this->allElementsOfMovie = resizedVector;
}

//implementation for accessing the elements of the vector via []
template <typename T>
T& DynamicVector<T>::operator[](int pos)
{
	return this->allElementsOfMovie[pos];
}

// returning the size of the dynamic vector
template <typename T>
int DynamicVector<T>::getSize() const
{
	return this->size;
}


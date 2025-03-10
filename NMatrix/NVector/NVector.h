#ifndef NVECTOR_NVECTOR_H_
#define NVECTOR_NVECTOR_H_
#include <stdexcept>
#include <memory>
#include <iostream>
#include <cstdint>

class Vector{
	public:
		int rows;
		double* values;
		virtual void reInit(uint dim, double* arr = NULL, bool handle_arr = true, bool delete_old = false);
		Vector(uint dim, double* arr = NULL,bool handle_arr=true);
		Vector();
		virtual ~Vector();
		virtual void copyToValue(double* arr);
		Vector& operator=(Vector other)
			{
				std::swap((*this).rows,other.rows);
				std::swap((*this).tight,other.tight);
				std::swap((*this).values,other.values);
				return *this;
			}
	private:
		bool tight;
};

class NVector {
public:

	double* values;
	double dimension;
	NVector(double* values, uint dimension);
	static Vector* createVectorP(double x, double y, double z);

	static Vector* createVectorP(double* vals, uint dimension);
	static Vector createVector(double*vals, uint dimension);
	static void addVectors(Vector*consumed, Vector* other);
	static void subVectors(Vector*consumed, Vector* other);
	static double dotVectors(Vector*left, Vector* other);
	static void scalarVectors(Vector*consumed, double scalar);
	static void flatten(float* consumed, Vector* vector);



};
#include "VectorTypes/Vector2.h"
#include "VectorTypes/Vector3.h"
#include "VectorTypes/Vector4.h"


#endif /* NVECTOR_NVECTOR_H_ */

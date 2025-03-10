#include "gtest/gtest.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include "../NMatrix/NVector/VectorArray.h"

#define NVectorCreateSize 1000000
TEST(NVectorCreateOptimal, positive) {
	double* p = (double*)std::malloc(sizeof(double)*NVectorCreateSize*3);
	for(int i = 0; i < NVectorCreateSize*3; i= i + 3){
		p[i] = 1;
		p[i+1] = 2;
		p[i+2] = 3;
		EXPECT_DOUBLE_EQ(p[i],1);
		EXPECT_DOUBLE_EQ(p[i+1],2);
		EXPECT_DOUBLE_EQ(p[i+2],3);

		//new(p[i]) Vector(0,1);
	}
	delete(p);
}

TEST(NVectorCreateInOrder, positive) {
	double vals[] = {1,2,3};
	for(int i = 0; i < NVectorCreateSize;i++){
		Vector* p = NVector::createVectorP(vals, 3);
		EXPECT_DOUBLE_EQ(p->values[0],1);
		EXPECT_DOUBLE_EQ(p->values[1],2);
		EXPECT_DOUBLE_EQ(p->values[2],3);


		delete(p);
	}

	//std::this_thread::sleep_for(std::chrono::seconds(60));
}

TEST(NVectorCreateStack, positive) {
	for(int i = 0; i < NVectorCreateSize; i++){
		Vector p = NVector::createVector((double[]){1,2},2);
		EXPECT_DOUBLE_EQ(p.values[0],1);
		EXPECT_DOUBLE_EQ(p.values[1],2);
		p = NVector::createVector((double[]){6,9},2);
		EXPECT_DOUBLE_EQ(p.values[0],6);
		EXPECT_DOUBLE_EQ(p.values[1],9);
	}
}

TEST(createTightVectorArray, positive) {
	for(uint t = 0; t < 8; t++){
		VectorArray* p = VectorArray::createTightVectorArray(3,NVectorCreateSize);

		for(uint i = 0; i < NVectorCreateSize; i++){

			Vector* vec = p->getVec(i);

			EXPECT_DOUBLE_EQ(vec->rows,3);

		}

		delete(p);
	}

}


TEST(NVectorAdd, positive) {
	VectorArray* varray = VectorArray::createTightVectorArray(3,3);
	Vector* v0 = varray->getVec(0);
	Vector* v1 = varray->getVec(1);;
	Vector* v2 = varray->getVec(2);
	v0->copyToValue((double[]){0,1,2});
	v1->copyToValue((double[]){3,4,5});
	v2->copyToValue((double[]){6,7,8});
	NVector::addVectors(v0,v1);
	EXPECT_DOUBLE_EQ(v0->values[0],3);
	EXPECT_DOUBLE_EQ(v0->values[1],5);
	EXPECT_DOUBLE_EQ(v0->values[2],7);


	delete(varray);
}

TEST(NVectorScalar, positive) {
	VectorArray* varray = VectorArray::createTightVectorArray(3,3);
	Vector* v0 = varray->getVec(0);
	Vector* v1 = varray->getVec(1);
	Vector* v2 = varray->getVec(02);
	v0->copyToValue((double[]){0,1,2});
	v1->copyToValue((double[]){3,4,5});
	v2->copyToValue((double[]){6,7,8});
	NVector::scalarVectors(v0,3);
	EXPECT_DOUBLE_EQ(v0->values[0],0);
	EXPECT_DOUBLE_EQ(v0->values[1],3);
	EXPECT_DOUBLE_EQ(v0->values[2],6);
	delete(varray);
}

TEST(NVectorDot, positive) {
	VectorArray* varray = VectorArray::createTightVectorArray(3,3);
	Vector* v0 = varray->getVec(0);
	Vector* v1 = varray->getVec(1);
	Vector* v2 = varray->getVec(2);
	v0->copyToValue((double[]){0,1,2});
	v1->copyToValue((double[]){3,4,5});
	v2->copyToValue((double[]){6,7,8});
	double ex = NVector::dotVectors(v0,v1);
	EXPECT_DOUBLE_EQ(ex, 0 + 4 + 2*5);
	delete(varray);
}

TEST(NVectorDotFlatten, positive) {
	VectorArray* varray = VectorArray::createTightVectorArray(3,3);
	Vector* v0 = varray->getVec(0);
	Vector* v1 = varray->getVec(1);
	Vector* v2 = varray->getVec(2);
	v0->copyToValue((double[]){0,1,2});
	v1->copyToValue((double[]){3,4,5});
	v2->copyToValue((double[]){6,7,8});
	float vals[3] = {0,0,0};
	NVector::flatten(vals,v0);
	EXPECT_FLOAT_EQ(vals[0],0);
	EXPECT_FLOAT_EQ(vals[1],1);
	EXPECT_FLOAT_EQ(vals[2],2);
	delete(varray);
}

TEST(NVectorArrayValuesInitAndEqual,positive){
	VectorArray* array = VectorArray::createTightVectorArray(3,3, (double[])
			{1,2,3,
			4,5,6,
			7,8,9});
	Vector* v0 = array->getVec(0);
	Vector* v1 = array->getVec(1);
	Vector* v2 = array->getVec(2);
	EXPECT_DOUBLE_EQ(v0->values[0],1);
	EXPECT_DOUBLE_EQ(v0->values[1],4);
	EXPECT_DOUBLE_EQ(v0->values[2],7);

	EXPECT_DOUBLE_EQ(v1->values[0],2);
	EXPECT_DOUBLE_EQ(v1->values[1],5);
	EXPECT_DOUBLE_EQ(v1->values[2],8);

	EXPECT_DOUBLE_EQ(v2->values[0],3);
	EXPECT_DOUBLE_EQ(v2->values[1],6);
	EXPECT_DOUBLE_EQ(v2->values[2],9);
	EXPECT_DOUBLE_EQ(array->isEqual(array),true);
	delete(array);
}

TEST(NVectorArrayValuesEliminateRow,positive){
	VectorArray* array = VectorArray::createTightVectorArray(3,3, (double[])
			{1,2,3,
			4,5,6,
			7,8,9});

	VectorArray eliminated = array->eliminateRowAndColumn(1,1);
	Vector* v0 = eliminated.getVec(0);
	Vector* v1 = eliminated.getVec(1);

	EXPECT_DOUBLE_EQ(v0->values[0],1);
	EXPECT_DOUBLE_EQ(v0->values[1],7);

	EXPECT_DOUBLE_EQ(v1->values[0],3);
	EXPECT_DOUBLE_EQ(v1->values[1],9);

	delete(array);
}

TEST(NVectorArrayDeterminant,positive){
	VectorArray array = VectorArray(3,3, (double[])
			{13,14,2,
			1,7,3,
			6,8,5});
	VectorArray array2 = VectorArray(3,3, (double[])
				{2,1,2,
				4,5,0,
				2,0,1});
	EXPECT_DOUBLE_EQ(array.getDeterminent(),257);
	EXPECT_DOUBLE_EQ(array2.getDeterminent(),-14);

}

TEST(NVectorArrayAdjoint,positive){
	VectorArray array = VectorArray(3,3, (double[])
			{1,2,3,
			4,5,6,
			7,8,9});
	VectorArray expected = VectorArray(3,3,(double[]){
		-3, 6, -3,
        6, -12, 6,
         -3, 6, -3
	});
	VectorArray returned = array.getAdjoint();
	EXPECT_EQ(expected.isEqual(&returned),true);


}

TEST(NVectorArrayTranspose,positive){
	VectorArray array = VectorArray(3,2, (double[])
			{1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0});
	VectorArray expected = VectorArray(2,3,(double[]){
		1.0, 3.0, 5.0,
		2.0, 4.0, 6.0
	});
	VectorArray returned = array.getTranspose();
	EXPECT_EQ(expected.isEqual(&returned),true);

	VectorArray array2 = VectorArray(5,3,(double[]){
	   1.0, 2.0, 3.0,
	   4.0, 5.0, 6.0,
	   7.0, 8.0, 9.0,
	   10.0, 11.0, 12.0,
	   13.0, 14.0, 15.0
	});
	expected = VectorArray(3,5,(double[]){
		 1, 4, 7, 10, 13,
		2, 5, 8, 11, 14,
		3, 6, 9, 12, 15
	});
	VectorArray returned2 = array2.getTranspose();

	EXPECT_EQ(expected.isEqual(&returned2),true);

}


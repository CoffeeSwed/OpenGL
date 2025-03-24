#include "gtest/gtest.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include "../NMatrix/NMatrix.h"

TEST(NMatrixCreate, positive) {

		NMatrix matrix = NMatrix(3,3,(double[]){
			1,2,3,
			4,5,6,
			7,8,9
		});
		NMatrix acopy = matrix;
		EXPECT_EQ(acopy.isSameMatrix(&matrix),NMatrix::EqualReturnRes::REPRESENT_SAME);
		NMatrix two = std::move(acopy);
		EXPECT_EQ(acopy.isSameMatrix(&matrix),NMatrix::EqualReturnRes::POINTS_TO_NULL);
		EXPECT_EQ(two.isSameMatrix(&matrix),NMatrix::EqualReturnRes::REPRESENT_SAME);
		acopy = two;
		EXPECT_EQ(acopy.isSameMatrix(&matrix),NMatrix::EqualReturnRes::REPRESENT_SAME);
		NMatrix sweden = NMatrix(2,3,(double[]){
			1,2,3,
			4,5,6
		});
		EXPECT_EQ(acopy.isSameMatrix(&sweden),NMatrix::EqualReturnRes::DIMENSION_DONT_MATCH);
		NMatrix ouch = sweden;
		EXPECT_EQ(ouch.isSameMatrix(&sweden),NMatrix::EqualReturnRes::REPRESENT_SAME);
		ouch = std::move(sweden);
		EXPECT_EQ(ouch.isSameMatrix(&sweden),NMatrix::EqualReturnRes::POINTS_TO_NULL);
		ouch = std::move(ouch);
		EXPECT_EQ(ouch.isSameMatrix(&ouch),NMatrix::EqualReturnRes::POINTS_TO_SAME);



}

TEST(NMatrixGetIndex,positive){
	NMatrix matrix = NMatrix(3,3,(double[]){
				1,2,3,
				4,5,6,
				7,8,9
	});
	EXPECT_EQ(matrix.values[matrix.getIndex(0,0)],1);
	EXPECT_EQ(matrix.values[matrix.getIndex(0,1)],2);
	EXPECT_EQ(matrix.values[matrix.getIndex(0,2)],3);

	EXPECT_EQ(matrix.values[matrix.getIndex(1,0)],4);
	EXPECT_EQ(matrix.values[matrix.getIndex(1,1)],5);
	EXPECT_EQ(matrix.values[matrix.getIndex(1,2)],6);

	EXPECT_EQ(matrix.values[matrix.getIndex(2,0)],7);
	EXPECT_EQ(matrix.values[matrix.getIndex(2,1)],8);
	EXPECT_EQ(matrix.values[matrix.getIndex(2,2)],9);

}

TEST(NMatrixGetRow,positive){
	NMatrix matrix = NMatrix(3,3,(double[]){
				1,2,3,
				4,5,6,
				7,8,9
	});
	uint index = 0;
	for(uint row = 0; row < 3; row++){
		for(uint p = 0; p < 3;p++){
			EXPECT_EQ(matrix.getRow(index),row);
			index++;
		}
	}

}

TEST(NMatrixGetColumn,positive){
	NMatrix matrix = NMatrix(3,3,(double[]){
				1,2,3,
				4,5,6,
				7,8,9
	});
	uint index = 0;
	for(uint row = 0; row < 3; row++){
		for(uint p = 0; p < 3;p++){
			EXPECT_EQ(matrix.getColumn(index),p);
			index++;
		}
	}

}


TEST(NMatrixGetTranspose,positive){
	NMatrix matrix = NMatrix(3,2,(double[]){
		 1.0, 2.0,
		3.0, 4.0,
		5.0, 6.0
	});
	NMatrix expected = NMatrix(2,3,(double[]){
		 1.0, 3.0, 5.0,
		2.0, 4.0, 6.0
	});
	EXPECT_EQ(matrix.getTranspose().isSameMatrix(&expected),NMatrix::EqualReturnRes::REPRESENT_SAME);

	matrix = NMatrix(5,3,(double[]){
		1.0, 2.0, 3.0,
	   4.0, 5.0, 6.0,
	   7.0, 8.0, 9.0,
	   10.0, 11.0, 12.0,
	   13.0, 14.0, 15.0
	});
	expected = NMatrix(3,5,(double[]){
		  1, 4, 7, 10, 13,
		2, 5, 8, 11, 14,
		3, 6, 9, 12, 15
	});
	EXPECT_EQ(matrix.getTranspose().isSameMatrix(&expected),NMatrix::EqualReturnRes::REPRESENT_SAME);

}

TEST(NMatrixGetMinor,positive){
	NMatrix matrix = NMatrix(3,3,(double[]){
		 1.0, 2.0, 3.0,
		2.0, 0.0, 1.0,
		5.0, 3.0, 6.0
	});
	NMatrix expected = NMatrix(2,2,(double[]){
		 1.0, 3.0,
		5.0, 6.0
	});
	EXPECT_EQ(matrix.getMinor(1,1).isSameMatrix(&expected),NMatrix::EqualReturnRes::REPRESENT_SAME);

	matrix = NMatrix(3,3,(double[]){
		  1.0, 0, 4.0,
		3.0, 5.0, -1.0,
		0.0, 1.0, 2.0
	});
	expected = NMatrix(2,2,(double[]){
		  1, 4,
		  3, -1
	});
	EXPECT_EQ(matrix.getMinor(2,1).isSameMatrix(&expected),NMatrix::EqualReturnRes::REPRESENT_SAME);

}

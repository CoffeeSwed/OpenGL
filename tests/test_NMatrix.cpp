#include "gtest/gtest.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include "../NMatrix/NMatrix.h"
#include <numbers>
#define NMATRIXCREATEAMOUNT 10E6

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

TEST(NMatrixGetDeterminant, positive){
	NMatrix matrix = NMatrix(2,2,(double[]){
		3, 5,
		8, 1
	});
	EXPECT_EQ(matrix.getDeterminant(), -37);
	
	matrix = NMatrix(2,2,(double[]){
		-13, 5,
		9, 3
	});
	EXPECT_EQ(matrix.getDeterminant(), -84);

	matrix = NMatrix(3,3,(double[]){
		-13, 5, 3,
		9, 3, 9,
		3, 4, 5
	});
	EXPECT_EQ(matrix.getDeterminant(), 264);


	matrix = NMatrix(3,3,(double[]){
		4.0, 5.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0
	});
	EXPECT_EQ(matrix.getDeterminant(), 9);

	matrix = NMatrix(4,4,(double[]){
		4.0, 77.0, 4.0, 6.0,
		9.0, 7.0, 2.0, 44.0,
		34.0, 6456.0, 75.0, 69.0,
		64.0, 54, 63, 1.0
	});
	EXPECT_EQ(matrix.getDeterminant(), -7075500);

}

TEST(NMatrixMultiply,positive){
	NMatrix A = NMatrix(2,2,(double[]){
		2, 3,
		4, 5
	});
	NMatrix B = NMatrix(2,2,(double[]){
		9,8,
		7,6
	});

	NMatrix AB = NMatrix(2,2,(double[]){
		39.0, 34.0, 71.0, 62
	});
	EXPECT_EQ(A.multiply(B).isSameMatrix(&AB),NMatrix::EqualReturnRes::REPRESENT_SAME);


	NMatrix C = NMatrix(3,3,(double[]){
		1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0
	});
	
	NMatrix D = NMatrix(3,2,(double[]){
		1.0, 2.0,
		3.0, 4.0,
		5.0, 6.0
	});

	NMatrix CD = NMatrix(3,2,(double[]){
		22.0, 28.0,
		49.0, 64.0,
		76.0, 100.0
	});

	EXPECT_EQ(C.multiply(D).isSameMatrix(&CD),NMatrix::EqualReturnRes::REPRESENT_SAME);
}

TEST(NMatrixGetAdjoint,positive){
	NMatrix A =  NMatrix(2,2,(double[]){
		2, 3,
		4, 5
	 });
	
	 NMatrix AT = NMatrix(2,2,(double[]){
		5, -3,
		-4, 2
	 });

	 NMatrix B = NMatrix(3,3,(double[]){
		1,2,3,
		4,5,6,
		7,8,9
	 });
	 NMatrix BT = NMatrix(3,3,(double[]){
		-3, 6, -3,
		6, -12, 6,
		-3, 6, -3
	 });
	 EXPECT_EQ(A.getAdjoint().isSameMatrix(&AT),NMatrix::EqualReturnRes::REPRESENT_SAME);
	 EXPECT_EQ(B.getAdjoint().isSameMatrix(&BT),NMatrix::EqualReturnRes::REPRESENT_SAME);
}

TEST(NMatrixGetCofactor,positive){
	NMatrix B = NMatrix(3,3,(double[]){
		1.0, 2.0, 3.0,
		4.0, 4.0, 5.0,
		6.0, 1.0, 3.0
	});
	EXPECT_EQ(B.getCoFactor(0,0),7);
	EXPECT_EQ(B.getCoFactor(0,1),18);
	EXPECT_EQ(B.getCoFactor(0,2),-20);
	EXPECT_EQ(B.getCoFactor(1,0),-3);
	EXPECT_EQ(B.getCoFactor(1,1),-15);
	EXPECT_EQ(B.getCoFactor(1,2),11);
	EXPECT_EQ(B.getCoFactor(2,0),-2);
	EXPECT_EQ(B.getCoFactor(2,1),7);
	EXPECT_EQ(B.getCoFactor(2,2),-4);




}

TEST(NMatrixGetInverse,positive){
	NMatrix A = NMatrix(2,2,(double[]){
		2,2,
		4,5
	});

	NMatrix B = NMatrix(3,3,(double[]){
		1.0, 2.0, 3.0,
		4.0, 4.0, 5.0,
		6.0, 1.0, 3.0
	});

	NMatrix AI = NMatrix(2,2,(double[]){
		1,0,
		0,1
	});

	NMatrix BI = NMatrix(3,3,(double[]){
		1,0,0,
		0,1,0,
		0,0,1
	});

	EXPECT_EQ(A.multiply(A.getInverse()).isSameMatrix(&AI),NMatrix::EqualReturnRes::REPRESENT_SAME);
	//EXPECT_EQ(B.multiply(B.getInverse()).isSameMatrix(&BI),NMatrix::EqualReturnRes::REPRESENT_SAME);
	std::string str = B.multiply(B.getInverse()).toString();
	std::string expected = "{1.000000, -0.000000, 0.000000\n0.000000, 1.000000, 0.000000\n0.000000, -0.000000, 1.000000}";
	EXPECT_EQ(str == expected,1);
}

TEST(Rotation2DTestAndTranslation,positive){
	NMatrix position = NMatrix(2,2,(double[]){
		69,0,
		69,0
	});
	std::setprecision(20);
	NMatrix rotation = NMatrix::createRotation2D(std::numbers::pi);
	position = position.multiply(rotation);
	NMatrix expected = NMatrix(2,2,(double[]){
		-69,0,
		-69,0
	});
	EXPECT_EQ(expected.isSameMatrix(&position,0.000000001),NMatrix::EqualReturnRes::REPRESENT_SAME);
	NMatrix translation = NMatrix::createTranslation2D(70,70);
	position = translation.multiply(position.terminateColumn(1).appendRow((double[]){1}));
	
	expected = NMatrix(3,1,(double[]){
		1,
		1,
		1
	});
	EXPECT_EQ(expected.isSameMatrix(&position,0.1),NMatrix::EqualReturnRes::REPRESENT_SAME);
}
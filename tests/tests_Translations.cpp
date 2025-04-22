#include "../Graphics/Translations.h"
#include "gtest/gtest.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include "../NMatrix/NMatrix.h"
#include <numbers>
TEST(Rotation2DTestAndTranslation,positive){
	NMatrix position = NMatrix(2,2,(double[]){
		69,0,
		69,0
	});
	std::setprecision(20);
	NMatrix rotation = Translations::createRotation2D(std::numbers::pi);
	position = position.multiply(rotation);
	NMatrix expected = NMatrix(2,2,(double[]){
		-69,0,
		-69,0
	});
	EXPECT_EQ(expected.isSameMatrix(&position,0.000000001),NMatrix::EqualReturnRes::REPRESENT_SAME);
	NMatrix translation = Translations::createTranslation2D(70,70);
	position = translation.multiply(position.terminateColumn(1).appendRow((double[]){1}));
	
	expected = NMatrix(3,1,(double[]){
		1,
		1,
		1
	});
	EXPECT_EQ(expected.isSameMatrix(&position,0.1),NMatrix::EqualReturnRes::REPRESENT_SAME);
}

TEST(AspectRatioTest,positive){
    std::setprecision(20);
    NMatrix projection = Translations::createProjectionTransformation(21.0/9.0,std::numbers::pi/4,0,30);
}
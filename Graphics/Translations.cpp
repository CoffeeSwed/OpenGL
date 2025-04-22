#ifndef TRANSLATIONS_CPP
#define TRANSLATIONS_CPP
#include "Translations.h"
NMatrix Translations::createTranslation3D(double r, double s, double t){
	NMatrix res = NMatrix(4,4,(double[]){
		1,0,0,r,
		0,1,0,s,
		0,0,1,t,
		0,0,0,1
	});
	

	return res;
}

NMatrix Translations::createTranslation2D(double r, double s){
	NMatrix res = NMatrix(3,3,(double[]){
		1,0,r,
		0,1,s,
		0,0,1
	});
	return res;
}

NMatrix Translations::createRotation2D(double r){
	NMatrix res = NMatrix(2,2);
	res.values[0] = cos(r);
	res.values[1] = -sin(r);
	res.values[2] = sin(r);
	res.values[3] = cos(r);
	return res;
}

NMatrix Translations::createRotation3DX(double r){
	NMatrix res = NMatrix(3,3,(double[]){
		1, 0, 0,
		0, cos(r), -sin(r),
		0, sin(r), cos(r)
	});return res;
}

NMatrix Translations::createRotation3DY(double r){
	NMatrix res = NMatrix(3,3,(double[]){
		cos(r), 0, sin(r),
		0, 1, 0,
		-sin(r), 0, cos(r)
	});return res;
}

NMatrix Translations::createRotation3DZ(double r){
	NMatrix res = NMatrix(3,3,(double[]){
		cos(r), -sin(r), 0,
		sin(r), cos(r), 0,
		0, 0, 1
	});return res;
}

NMatrix Translations::createProjectionTransformation(double r, double a, double n, double f){
    NMatrix res = NMatrix(4,4,(double[]){
        1/(r*tan(a/2)),0,0,0,
        0,1/tan(a/2),0,0,
        0,0,(n+f)/(n-f),2*n*f/(n-f),
        0,0,-1,0
    });

    return res;
}

#endif
#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include "../NMatrix/NMatrix.h"
#include <cmath>
class Translations{
    public:
    static NMatrix createTranslation3D(double r, double s, double t);
    static NMatrix createTranslation2D(double r, double s);

    static NMatrix createRotation2D(double r);
    static NMatrix createRotation3DX(double r);
    static NMatrix createRotation3DY(double r);
    static NMatrix createRotation3DZ(double r);
    static NMatrix createProjectionTransformation(double r, double a, double n, double f);
};
#endif
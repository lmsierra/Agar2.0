#include "Math.h"
#include <math.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

double Log2(double x) {
    return log(x) / log(2.0);
}

double DegSin(double degrees) {
    return sin(DEG2RAD * degrees);
}

double DegCos(double degrees) {
    return cos(DEG2RAD * degrees);
}

double DegTan(double degrees) {
    return tan(DEG2RAD * degrees);
}

double DegASin(double sin) {
    return asin(sin) * RAD2DEG;
}

double DegACos(double cos) {
    return acos(cos) * RAD2DEG;
}

double DegATan(double tan) {
    return atan(tan) * RAD2DEG;
}

double DegATan2(double y, double x) {
    return atan2(y, x) * RAD2DEG;
}

double WrapValue(double val, double mod) {
    if (mod == 0) return val;
    return val - mod*floor(val / mod);
}

double Angle(double x1, double y1, double x2, double y2) {
    return WrapValue(DegATan2(y1 - y2, x2 - x1), 360);
}

double Distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double SquareDistance(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

double Lerp(double start, double end, double step) {
    return start + step * (end - start);
}

bool ValueInRange(double value, double min, double max) {
    return (value >= min) && (value <= max);
}

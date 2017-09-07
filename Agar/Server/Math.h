#ifndef __UTILS_MATH_H__
#define __UTILS_MATH_H__

double Log2(double x);
double DegSin(double degrees);
double DegCos(double degrees);
double DegTan(double degrees);
double DegASin(double sin);
double DegACos(double cos);
double DegATan(double tan);
double DegATan2(double y, double x);
double WrapValue(double val, double mod);
double Angle(double x1, double y1, double x2, double y2);
double SquareDistance(double x1, double y1, double x2, double y2);
double Distance(double x1, double y1, double x2, double y2);
double Lerp(double start, double end, double step);
bool   ValueInRange(double value, double min, double max);

#endif /* __UTILS_MATH_H__ */
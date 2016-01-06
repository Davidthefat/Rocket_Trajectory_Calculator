#ifndef GAUSSIAGQUAD_H
#define GAUSSIAGQUAD_H

#define GN 5
#define IN 10

class GaussianQuad
{
private:
	double w[GN];
	double x[GN];
	double a[IN];
    double b[IN];
	double c[IN];
    double d[IN];
    double h[IN];
    double l[IN];
    double m[IN];
    double z[IN];
    double al[IN];
    double xj;
    double evalInt(double);
public:
	GaussianQuad();
    void calcPolynomial(double *, double*);
	double eval(double, double);
};
#endif


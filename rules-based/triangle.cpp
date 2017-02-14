#include "triangle.h"

rules::Triangle::Triangle(double angab, double angbc, double angca,
                          double tol_radius, rules::PairsOverWholeSky& pairs) :
    ab(angab, tol_radius, pairs),
    bc(angbc, tol_radius, pairs),
    ca(angca, tol_radius, pairs)
{

}

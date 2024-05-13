/* Author: Cole Barbes
 * Last edited: 05/08/24
 * Purpose: To implement elliptic curves and Points on them
 * The curve class is basic curve which points exist on them so a point would then have a curve associated with it
 */
#include <iostream>
#include "../InfInt.h"
#include <vector>

// MOD function for infinite int
InfInt MOD(InfInt a, InfInt n);
// gcd function for inf int
InfInt GCD(InfInt a, InfInt b);
// gcd extended 
std::vector<InfInt> GCDEX(InfInt a, InfInt b);
// inverse mod
InfInt ModInv(InfInt a, InfInt n);

// Curve class to store needed data for a curve
class Curve
{
public:
    InfInt b, c, n;
    Curve();
    Curve(InfInt, InfInt, InfInt);
    Curve(InfInt, InfInt, InfInt, InfInt); // set the 
    ~Curve();
    void resetCurve(InfInt, InfInt, InfInt);    // re-run randomize of the curve
    void resetCurve(InfInt, InfInt, InfInt, InfInt); // set the value of the curve with point
    void setCurve(InfInt, InfInt, InfInt); // set the curve with b, c, n without point
};



/*
Point class handle additions, scalar multiples and doubling
*/
class Point
{
private:
    // needed vars for computing points on elliptic curves
    InfInt X;
    InfInt Y;
    InfInt factor;
    Curve curve;
    bool halt;
public:
    // constructors
    Point(InfInt, InfInt, InfInt);
    Point(const Point &);
    ~Point();
    // set values
    void setPoint(InfInt, InfInt, InfInt);
    void setCurve(InfInt, InfInt, InfInt);
    // halt functionality to halt execution of computation upon user defined exit
    void setHalt(bool);
    // double the point
    Point doubleP();
    // equals operator
    Point operator=(const Point &);
    // plus operator
    Point operator+(const Point &);
    // scalar multiplication using binary algorithm 
    Point operator*(InfInt);
    friend Point operator*(InfInt, Point &);
    // get the factor
    InfInt getFactor();
    // print the point
    void printPoint();
    std::string toString();
};


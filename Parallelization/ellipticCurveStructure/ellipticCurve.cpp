#include "ellipticCurve.h"

/*
 * MOD function to take the modulus of Infinite integer but only have positive number
 * return the result
 */
InfInt MOD(InfInt a, InfInt n)
{
    InfInt result = a;
    if (a > 0)
    {
        a = a % n;
    }
    else
    {
        a = a * -1;
        result = a % n;
        a = n - result;
    }
    return a;
}

/*
 * GCD function to find the Greatest Common Divisor of 2 numbers
 * Return Infinite integer
 */
InfInt GCD(InfInt a, InfInt b)
{
    InfInt x, y;
    if (a >= b)
    {
        x = a;
        y = b;
    }
    else
    {
        x = b;
        y = a;
    }

    while (y != 0)
    {
        InfInt temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

/*
 *	GCDEX function to find the s, t of a*s + b*t = GCD(a, b, GCD)
 *
 */
std::vector<InfInt> GCDEX(InfInt a, InfInt b)
{
    // variables
    // [0]		[1]		[2]		[3]
    // x1 = 1, y1 = 0, x2 = 0, y2 = 1
    std::vector<InfInt> variables = {1, 0, 0, 1};
    InfInt temp, quotient;

    if (a < b)
    {
        temp = b;
        b = a;
        a = temp;
    }
    while (b != 0)
    {
        quotient = a / b;
        temp = b;
        b = a % b;
        a = temp;

        temp = variables[2];
        variables[2] = variables[0] - quotient * variables[2];
        variables[0] = temp;

        temp = variables[3];
        variables[3] = variables[1] - quotient * variables[3];
        variables[1] = temp;
    }
    return {a, variables[0], variables[1]};
}

/*
 * Simple Modular inverse function
 * given a (mod n)
 * return a^-1 (mod n)
 * Meaning a*a^-1 congruent to 1 (mod n)
 */
InfInt ModInv(InfInt a, InfInt n)
{
    if (GCD(a, n) == 1)
    {
        std::vector<InfInt> exdGCD = GCDEX(a, n);
        int index = 1;
        if (a < n)
            index = 2;
        return exdGCD[index];
    }
    else
        return -1;
}

/*
 * class Constructor set all to 0
 */

Curve::Curve()
{
    b = 0;
    c = 0;
    n = 0;
}

/*
 * class Constructor for setting the x and y and the n value then finding random curve
 */

Curve::Curve(InfInt x, InfInt y, InfInt n1)
{
    n = n1;
    b = MOD(rand() * 100000 + rand(), n);
    InfInt result = MOD(x * x * x + x * b, n);
    InfInt y2 = MOD(y * y, n);
    c = MOD(y2 - result, n);
}

/*
 * Set the curve given all needed info including x and y
 */
Curve::Curve(InfInt x, InfInt y, InfInt b1, InfInt n1)
{
    b = b1;
    n = n1;
    InfInt result = MOD(x * x * x + x * b, n);
    InfInt y2 = MOD(y * y, n);
    c = MOD(y2 - result, n);
}

Curve::~Curve()
{
}

/*
 * Reset the curve with new random values given an x and y
 */
void Curve::resetCurve(InfInt x, InfInt y, InfInt n1) // re-run randomize of the Curve
{
    
    n = n1;
    b = MOD(rand() * 100000 + rand(), n);
    InfInt result = MOD(x * x * x + x * b, n);
    InfInt y2 = MOD(y * y, n);
    c = MOD(y2 - result, n);
    
}

/*
 * reset the curve given the x, y, b, n
 */
void Curve::resetCurve(InfInt x, InfInt y, InfInt b1, InfInt n1) // set the value of the Curve
{
    b = MOD(b1, n1);
    n = n1;
    InfInt result = MOD(x * x * x + x * b, n);
    InfInt y2 = MOD(y * y, n);
    c = MOD(y2 - result, n);
}

/*
 * Set the curve without the x and y, just set the curve
 */
void Curve::setCurve(InfInt b1, InfInt c1, InfInt n1) // set the value of the Curve
{
    b = MOD(b1, n1);
    c = MOD(c1, n1);
    n = n1;
}

/*
 * Set the point given x and y in mod n
 */
Point::Point(InfInt x, InfInt y, InfInt n)
{
    X = MOD(x, n);
    Y = MOD(y, n);
    curve.resetCurve(x, y, n);
    factor = 1;
    halt = false;
}

/*
 * copy constructor for the point take another point and copy it completely
 */
Point::Point(const Point &P)
{
    X = P.X;
    Y = P.Y;
    curve.setCurve(P.curve.b, P.curve.c, P.curve.n);
    factor = 1;
}

/*
 * Destructor
 */
Point::~Point()
{
}

/*
 * Set the point using x, y, n
 */
void Point::setPoint(InfInt x, InfInt y, InfInt n)
{
    X = MOD(x, n);
    Y = MOD(y, n);
    curve.resetCurve(x, y, n);

}

/*
 * set the curve using the x, y, b, n
 */
void Point::setCurve(InfInt x, InfInt y, InfInt n)
{
    X = MOD(x, n);
    Y = MOD(y, n);
    curve.resetCurve(x, y, n);
}

/*
 * equals operator to set one point equal to the other
 */
Point Point::operator=(const Point &P)
{
    X = P.X;
    Y = P.Y;
    curve.setCurve(P.curve.b, P.curve.c, P.curve.n);
    return *(this);
}

/*
 * Addition operation of a point on an elliptic curve mod n
 * P + Q
 */
Point Point::operator+(const Point &Q)
{
    if(!halt){
        // regular slope calculation
        InfInt d2 = MOD((X - Q.X), curve.n);
        InfInt d1 = MOD(Y - Q.Y, curve.n);
        InfInt result = GCD(d2, curve.n);

        if (result != 1 && result != curve.n)
        {
            factor = result;
        }
        else
        {
            InfInt m = d1 * ModInv(d2, curve.n);
            InfInt x1 = X;
            X = MOD(m * m - X - Q.X, curve.n);
            Y = MOD(m * (X - x1) - Y, curve.n);
        }

        if (factor != 1)
        {
            printf("%s + ( %s, %s ) could not be calculated\n", toString().c_str(), Q.X.toString().c_str(), Q.Y.toString().c_str());
            printf("Needed to invert %s modulo %s\n", d2.toString().c_str(), curve.n.toString().c_str());
            printf("GCD( %s, %s ) = %s\n", d2.toString().c_str(), curve.n.toString().c_str(), result.toString().c_str());
        }
    }
    return *(this);
}

/*
* double the point 
* take the tangent line of the point to find the double on the elliptic curve
*/
Point Point::doubleP()
{
    if(!halt){
        InfInt d1=0, d2=0, result=0, x1=0, m=0;
        // Using a tangent line we find the double of p
        d1 = MOD(((X * X * 3) + curve.b), curve.n);
        d2 = MOD(Y * 2, curve.n);
        // make sure the gcd is 1 before inverting
        result = GCD(d2, curve.n);
        if (result != 1 && result != curve.n)
        {
            factor = result;
            halt = true;
        }
        else
        {
            m = d1 * ModInv(d2, curve.n);
            // find the x and y points using the slope equation
            x1 = X;
            X = MOD(m * m - X - X, curve.n);
            Y = MOD(m * (x1 - X) - Y, curve.n);
        }

        if (factor != 1)
        {
            //printf("%s * ( %s, %s ) could not be calculated\n", M.toString().c_str(), X.toString().c_str(), Y.toString().c_str());
            printf("%d * ( %s, %s ) could not be calculated\n", 2, X.toString().c_str(), Y.toString().c_str());
            printf("Needed to invert %s modulo %s\n", d2.toString().c_str(), curve.n.toString().c_str());
            printf("GCD( %s, %s ) = %s\n", d2.toString().c_str(), curve.n.toString().c_str(), result.toString().c_str());
        }
    }
    return *(this);
}

/*
Scalar multiplication of a point
*/
Point Point::operator*(InfInt M)
{
    bool firstTime = true;

    InfInt k = M, d1=0, d2=0, x1=0, result=0, m=0;
    Point Total = *(this);
    
    while (k >= 1 && factor == 1)
    {
        if (firstTime)
        {
            firstTime = false;
        }
        if (k % 2 == 1 || firstTime)
        {
            Total = *this + Total;
            k--;
        }else{
            doubleP();
            k /= 2;
        }
        
    }
    return Total;
}

/*
*  left hand scalar multiplication of the point
* return the point
*/
Point operator*(InfInt lhs, Point &rhs)
{
    return rhs * lhs;
}

InfInt Point::getFactor()
{
    return factor;
}

/*
* Print the point
*/
void Point::printPoint()
{
    printf("P = ( %s, %s ), on the curve y^2 = x^3 + %sx + %s (mod %s)\n", X.toString().c_str(), Y.toString().c_str(), curve.b.toString().c_str(), curve.c.toString().c_str(), curve.n.toString().c_str());
}

/*
* turn a point to a string to show user
*/
std::string Point::toString()
{
    return "( "+X.toString()+", "+Y.toString()+" )";
}

/*
set the halt parameter to end execution or re start 
*/
void Point::setHalt(bool set)
{
   halt = set;
}

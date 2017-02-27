/*
 * Name: Rohan Mathur
 * NetID: rmathur2
 * This class defines adding, subtracting, multiplying, and dividing for real numbers, complex numbers, and rational numbers. Additionally, functions to print the specific number, get the magnitude for the number, and modify the values of the number are defined.
 */

#include <cmath>
#include "calc.h"
using namespace std;

// RealNumber, ComplexNumber and RationalNumber inherit from base Number class.

//==============NUMBER===============//
Number::Number(){}

Number::~Number(){}

double Number::magnitude(){return 0.0;}

void Number::print(){}

Number Number::operator + (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator - (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator * (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator / (const Number& arg)
{
    Number result;
    return result;
}

void Number::set_value(double rval){}

void Number::set_value(double rval, double ival){}

//=============real=====================//
//constructors for real number
RealNumber::RealNumber() {
    // set real component to zero
    realComponent = 0.0;
}

RealNumber::RealNumber(double rval) {
    // set real component to provided value
    realComponent = rval;
}

//return the magnitiude of the real number
double RealNumber::magnitude() {
    // return the absolute value of the real component
    return abs(realComponent);
}

//print real number out
void RealNumber::print() {
    // print the real number's real component out
    cout << "RealNumber: " << realComponent << "\n" << endl;
}

//real + real
RealNumber RealNumber::operator + (const RealNumber& arg) {
    // add the real components of the provided number and the current one and return it in a new real number
    RealNumber result;
    result.realComponent = realComponent + arg.realComponent;
    return result;
}

//real - real
RealNumber RealNumber::operator - (const RealNumber& arg) {
    // subtract the real components of the provided number and the current one and return it in a new real number
    RealNumber result;
    result.realComponent = realComponent - arg.realComponent;
    return result;
}

//real * real
RealNumber RealNumber::operator * (const RealNumber& arg) {
    // multiply the real components of the provided number and the current one and return it in a new real number
    RealNumber result;
    result.realComponent = realComponent * arg.realComponent;
    return result;
}

//real/real
RealNumber RealNumber::operator / (const RealNumber& arg) {
    // divide the real components of the provided number and the current one and return it in a new real number
    RealNumber result;
    result.realComponent = realComponent / arg.realComponent;
    return result;
}

//set the value for real number
void RealNumber::set_value (double rval) {
    // set the real component to the new provided value
    realComponent = rval;
}

//=============complex================//

ComplexNumber::ComplexNumber() {
    // set both the real component and the imaginary component of the number to zero
    realComponent = 0.0;
    imagComponent = 0.0;
}

ComplexNumber::ComplexNumber(double rval, double ival) {
    // set both the real component and the imaginary component of the number to the provided values
    realComponent = rval;
    imagComponent = ival;
}

//return the magnitude of the complex number
double ComplexNumber::magnitude() {
    // return the magnitude of the number by squaring the components and adding them together, then taking the square root
    return sqrt((realComponent * realComponent) + (imagComponent * imagComponent));
}
//print the complexnumber
void ComplexNumber::print() {
    // print out the ComplexNumber by pretty printing the real and imaginary components of the number with the proper denotations
    cout<<"ComplexNumber: " << realComponent << " + " << imagComponent << "i\n";
}

//imag + imag
ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg) {
    // add the current complex number and the ComplexNumber provided in the parameter by adding the two componenets and returning the newly created number
    ComplexNumber result;
    result.realComponent = realComponent + arg.realComponent;
    result.imagComponent = imagComponent + arg.imagComponent;
    return result;
}

//imag - imag
ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg) {
    // subtract the current complex number and the ComplexNumber provided in the parameter by subtracting the two componenets and returning the newly created number
    ComplexNumber result;
    result.realComponent = realComponent - arg.realComponent;
    result.imagComponent = imagComponent - arg.imagComponent;
    return result;
}

//imag * imag
ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg) {
    // multiply the current complex number and the ComplexNumber provided in the parameter by multiplying the two componenets and returning the newly created number
    ComplexNumber result;
    result.realComponent = (realComponent * arg.realComponent) - (imagComponent * arg.imagComponent);
    result.imagComponent = (realComponent * arg.imagComponent) + (imagComponent * arg.realComponent);
    return result;
}

//imag/imag
ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg) {
    // divde the current complex number and the ComplexNumber provided in the parameter by dividing the two componenets and returning the newly created number
    ComplexNumber result;
    result.realComponent = ((realComponent * arg.realComponent) + (imagComponent * arg.imagComponent)) / ((arg.realComponent * arg.realComponent) + (arg.imagComponent * arg.imagComponent));
    result.imagComponent = ((imagComponent * arg.realComponent) - (realComponent * arg.imagComponent)) / ((arg.realComponent * arg.realComponent) + (arg.imagComponent * arg.imagComponent));
    return result;
}

//set the complexnumber value
void ComplexNumber::set_value (double rval, double ival) {
    // set the real and imaginary components of the number to the provided values
    realComponent = rval;
    imagComponent = ival;
}

//=============rational================//

RationalNumber::RationalNumber() {
    // initialize the numerator to 0 and the denominator to 1 by default
    numerator = 0;
    denominator = 1;
}

RationalNumber::RationalNumber(int numer, int denom) {
    // initialize the numerator and denominator to the provided values
    RationalNumber::set_value(numer, denom);
}

//return the magnitude of the rational number
double RationalNumber::magnitude(){
    // return the magnitude of the rational number by diving the numerator by the denominator and returning it
    return numerator / denominator;
}

//print the rational number
void RationalNumber::print() {
    // pretty print the rational number by printing the numerator over the denominator
    cout << "RationalNumber: " << numerator << " / " << denominator << "\n";
}

//rational + rational
RationalNumber RationalNumber::operator + (const RationalNumber& arg) {
    // add fractions by finding the gcd of the denominators, scaling the numerator appropriately, and then adding the numerators and making the denominator the gcd from before
    RationalNumber result;
    result.denominator = gcd(denominator, arg.denominator);
    result.numerator = ((result.denominator / denominator) * numerator) + ((result.denominator / arg.denominator) * arg.numerator);

    // reduce the numerator and denominotor by dividing both numbers by the gcd of the numerator and denominator
    double newNumerator = result.numerator / gcd(result.numerator, result.denominator);
    double newDenominator = result.denominator / gcd(result.numerator, result.denominator);

    // if the two are divisible, reduce it properly
    if(fmod(newDenominator, newNumerator) == 0) {
        newDenominator = newDenominator / newNumerator;
        newNumerator = 1;
    }

    // set the numerator to carry the negative instead of the denominator if its negative
    if(newDenominator < 0) {
        newNumerator *= -1;
        newDenominator *= -1;
    }

    // apply the new numerator and denominator
    result.numerator = newNumerator;
    result.denominator = newDenominator;

    return result;
}

//rational - rational
RationalNumber RationalNumber::operator - (const RationalNumber& arg) {
    // subtract fractions by finding the gcd of the denominators, scaling the numerator appropriately, and then subtracting the numerators and making the denominator the gcd from before
    RationalNumber result;
    result.denominator = gcd(denominator, arg.denominator);
    result.numerator = ((result.denominator / denominator) * numerator) - ((result.denominator / arg.denominator) * arg.numerator);

    // reduce the numerator and denominotor by dividing both numbers by the gcd of the numerator and denominator
    double newNumerator = result.numerator / gcd(result.numerator, result.denominator);
    double newDenominator = result.denominator / gcd(result.numerator, result.denominator);

    // if the two are divisible, reduce it properly
    if(fmod(newDenominator, newNumerator) == 0) {
        newDenominator = newDenominator / newNumerator;
        newNumerator = 1;
    }

    // set the numerator to carry the negative instead of the denominator if its negative
    if(newDenominator < 0) {
        newNumerator *= -1;
        newDenominator *= -1;
    }

    // apply the new numerator and denominator
    result.numerator = newNumerator;
    result.denominator = newDenominator;

    return result;
}

//rational * rational
RationalNumber RationalNumber::operator * (const RationalNumber& arg) {
    // multiply the two fractions by mutiplying the two numerators together and the two denominators together
    RationalNumber result;
    result.numerator = numerator * arg.numerator;
    result.denominator = denominator * arg.denominator;

    // reduce the numerator and denominotor by dividing both numbers by the gcd of the numerator and denominator
    double newNumerator = result.numerator / gcd(result.numerator, result.denominator);
    double newDenominator = result.denominator / gcd(result.numerator, result.denominator);

    // if the two are divisible, reduce it properly
    if(fmod(newDenominator, newNumerator) == 0) {
        newDenominator = newDenominator / newNumerator;
        newNumerator = 1;
    }

    // set the numerator to carry the negative instead of the denominator if its negative
    if(newDenominator < 0) {
        newNumerator *= -1;
        newDenominator *= -1;
    }

    // apply the new numerator and denominator
    result.numerator = newNumerator;
    result.denominator = newDenominator;

    return result;
}

//rational/rational
RationalNumber RationalNumber::operator / (const RationalNumber& arg) {
    // divide the two fractions by multiplying one fraction by the reciprocal of the other fraction
    RationalNumber result;
    result.numerator = numerator * arg.denominator;
    result.denominator = denominator * arg.numerator;

    // reduce the numerator and denominotor by dividing both numbers by the gcd of the numerator and denominator
    double newNumerator = result.numerator / gcd(result.numerator, result.denominator);
    double newDenominator = result.denominator / gcd(result.numerator, result.denominator);

    // if the two are divisible, reduce it properly
    if(fmod(newDenominator, newNumerator) == 0) {
        newDenominator = newDenominator / newNumerator;
        newNumerator = 1;
    }

    // set the numerator to carry the negative instead of the denominator if its negative
    if(newDenominator < 0) {
        newNumerator *= -1;
        newDenominator *= -1;
    }

    // apply the new numerator and denominator
    result.numerator = newNumerator;
    result.denominator = newDenominator;

    return result;
}

//set the rational number value
void RationalNumber::set_value (int numer, int denom) {
    // set the value of the fraction to the numerator and denominator provided
    numerator = numer;
    denominator = denom;
}


// helper function
int RationalNumber::gcd(int a, int b) {
    // find the gcd of the two numbers by looping through the two until they divide with no remainder
    int c;

    while (a != 0) {
        c = a;
        a = b%a;
        b = c;
    }

    return b;
}

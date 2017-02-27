#include <iostream>
using namespace std;

class Number
{
public:
    Number();
    ~Number();
    virtual double magnitude();
    virtual void print();
    
    //operator overload
    virtual Number operator + (const Number& arg);
    virtual Number operator - (const Number& arg);
    virtual Number operator * (const Number& arg);
    virtual Number operator / (const Number& arg);
    
    //virtual set_value function for both complex and real
    virtual void set_value(double rval);
    virtual void set_value(double rval, double ival);
};

class RealNumber :public Number
{
public:
    RealNumber();
    
    RealNumber(double rval);
    
    double magnitude();
    void print();
    
    //operator overload
    RealNumber operator + (const RealNumber& arg);
    RealNumber operator - (const RealNumber& arg);
    RealNumber operator * (const RealNumber& arg);
    RealNumber operator / (const RealNumber& arg);
    
    //helper function
    using Number::set_value;
    void set_value (double rval);
    
private:
    double realComponent;
};

class ComplexNumber :public Number
{
public:
    //define your constructor
    ComplexNumber();
    ComplexNumber(double rval, double ival);
    
    double magnitude();
    void print();
    
    //operator overload
    ComplexNumber operator + (const ComplexNumber& arg);
    ComplexNumber operator - (const ComplexNumber& arg);
    ComplexNumber operator * (const ComplexNumber& arg);
    ComplexNumber operator / (const ComplexNumber& arg);
    
    //helper function
    using Number::set_value;
    void set_value (double rval, double ival);
    
private:
    double realComponent;
    double imagComponent;
};

class RationalNumber :public Number
{
public:
    //define your constructor
    RationalNumber();
    RationalNumber(int numer, int denom);
    
    double magnitude();
    double decimal_value();
    void print();
    
    //operator overload
    RationalNumber operator + (const RationalNumber& arg);
    RationalNumber operator - (const RationalNumber& arg);
    RationalNumber operator * (const RationalNumber& arg);
    RationalNumber operator / (const RationalNumber& arg);
    
    //helper function
    using Number::set_value;
    void set_value (int numer, int denom);
    
private:
    double numerator;
    double denominator;
    
    int gcd(int a, int b);
};
#include <iostream>
#include "calc.h"
#include <stdlib.h>

using namespace std;
int main ()
{
    int choice;
    double r1, r2;
    double i1, i2;
    int num1, num2, denom1, denom2;
    ComplexNumber cn1, cn2, cn3;
    RealNumber rn1, rn2, rn3;
    RationalNumber ration1, ration2, ration3;
    
    
    while(1)
    {
        choice = 0;
        cout << "-------------------------------------\n";
        cout << "Options\n";
        cout << "1)Add with real (+) \n";
        cout << "2)Subtract with real (-)\n";
        cout << "3)Multiplay with real (*)\n";
        cout << "4)Division with real (\\)\n";
        cout << "5)Add with complex (+) \n";
        cout << "6)Subtract with complex (-)\n";
        cout << "7)Multiplay with complex (*)\n";
        cout << "8)Division with complex (\\)\n";
        cout << "9)Add with rational (+) \n";
        cout << "10)Subtract with rational (-)\n";
        cout << "11)Multiplay with rational (*)\n";
        cout << "12)Division with rational (\\)\n";
        cout << "0)Exit\n";
        cout << "-------------------------------------\n";
        cout << "Enter an option:";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter a real number: ";
                cin >> r1;
                cout << "Enter another real number: ";
                cin >> r2;
                rn1.set_value(r1);
                rn2.set_value(r2);
                rn3 = rn1 + rn2;
                rn3.print();
                break;
            
            case 2:
                cout << "Enter a real number: ";
                cin >> r1;
                cout << "Enter another real number: ";
                cin >> r2;
                rn1.set_value(r1);
                rn2.set_value(r2);
                rn3 = rn1 - rn2;
                rn3.print();
                break;
                
            case 3:
                cout << "Enter a real number: ";
                cin >> r1;
                cout << "Enter another real number: ";
                cin >> r2;
                rn1.set_value(r1);
                rn2.set_value(r2);
                rn3 = rn1 * rn2;
                rn3.print();
                break;
                
            case 4:
                cout << "Enter a real number: ";
                cin >> r1;
                cout << "Enter another real number: ";
                cin >> r2;
                rn1.set_value(r1);
                rn2.set_value(r2);
                rn3 = rn1 / rn2;
                rn3.print();
                break;
        
            case 5:
                cout << "Enter the real part of a complex number: ";
                cin >> r1;
                cout << "Enter the imag part of a complex number: ";
                cin >> i1;
                cout << "Enter the real part of another complex number: ";
                cin >> r2;
                cout << "Enter the imag part of another complex number: ";
                cin >> i2;
                cn1.set_value(r1, i1);
                cn2.set_value(r2, i2);
                cn3 = cn1 + cn2;
                cn3.print();
                break;
            
            case 6:
                cout << "Enter the real part of a complex number: ";
                cin >> r1;
                cout << "Enter the imag part of a complex number: ";
                cin >> i1;
                cout << "Enter the real part of another complex number: ";
                cin >> r2;
                cout << "Enter the imag part of another complex number: ";
                cin >> i2;
                cn1.set_value(r1, i1);
                cn2.set_value(r2, i2);
                cn3 = cn1 - cn2;
                cn3.print();
                break;
            
            case 7:
                cout << "Enter the real part of a complex number: ";
                cin >> r1;
                cout << "Enter the imag part of a complex number: ";
                cin >> i1;
                cout << "Enter the real part of another complex number: ";
                cin >> r2;
                cout << "Enter the imag part of another complex number: ";
                cin >> i2;
                cn1.set_value(r1, i1);
                cn2.set_value(r2, i2);
                cn3 = cn1 * cn2;
                cn3.print();
                break;
            
            case 8:
                cout << "Enter the real part of a complex number: ";
                cin >> r1;
                cout << "Enter the imag part of a complex number: ";
                cin >> i1;
                cout << "Enter the real part of another complex number: ";
                cin >> r2;
                cout << "Enter the imag part of another complex number: ";
                cin >> i2;
                cn1.set_value(r1, i1);
                cn2.set_value(r2, i2);
                cn3 = cn1 / cn2;
                cn3.print();
                break;
                
            case 9:
                cout << "Enter the numerator of a rational number: ";
                cin >> num1;
                cout << "Enter the denominator of a rational number: ";
                cin >> denom1;
                cout << "Enter the numerator of another rational number: ";
                cin >> num2;
                cout << "Enter the denominator of another rational number: ";
                cin >> denom2;
                ration1.set_value(num1, denom1);
                ration2.set_value(num2, denom2);
                ration3 = ration1 + ration2;
                ration3.print();
                break;
                
            case 10:
                cout << "Enter the numerator of a rational number: ";
                cin >> num1;
                cout << "Enter the denominator of a rational number: ";
                cin >> denom1;
                cout << "Enter the numerator of another rational number: ";
                cin >> num2;
                cout << "Enter the denominator of another rational number: ";
                cin >> denom2;
                ration1.set_value(num1, denom1);
                ration2.set_value(num2, denom2);
                ration3 = ration1 - ration2;
                ration3.print();
                break;
                
            case 11:
                cout << "Enter the numerator of a rational number: ";
                cin >> num1;
                cout << "Enter the denominator of a rational number: ";
                cin >> denom1;
                cout << "Enter the numerator of another rational number: ";
                cin >> num2;
                cout << "Enter the denominator of another rational number: ";
                cin >> denom2;
                ration1.set_value(num1, denom1);
                ration2.set_value(num2, denom2);
                ration3 = ration1 * ration2;
                ration3.print();
                break;
                
            case 12:
                cout << "Enter the numerator of a rational number: ";
                cin >> num1;
                cout << "Enter the denominator of a rational number: ";
                cin >> denom1;
                cout << "Enter the numerator of another rational number: ";
                cin >> num2;
                cout << "Enter the denominator of another rational number: ";
                cin >> denom2;
                ration1.set_value(num1, denom1);
                ration2.set_value(num2, denom2);
                ration3 = ration1 / ration2;
                ration3.print();
                break;
        
            case 0:	
                exit(0);
                
            default:
                cout << "Invalid choice, Try again\n";
        }
    }
    
    return 0;
    
    
}

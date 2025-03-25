#include <iostream>
using namespace std;

int findGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void simplify(int &numerator, int &denominator){
    if (denominator < 0){
        numerator *= -1;
        denominator *= -1;
    }
    int gcd = findGCD(numerator, denominator);
    numerator = numerator / gcd;
    denominator = denominator / gcd;
}

bool createCharString(int characteristic, int numerator, int denominator, int len, char result[]){
    if (denominator == 0){
        return false;
    }

    int numDigits = 0;
    int temp = characteristic;
    while (temp > 0){
        temp /= 10;
        numDigits++;
    }

    //if the characteristic alone is larger than the allotted amount of characters
    if(numDigits > len){
        return false;
    }
}

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    int num1 = c1 * d1 + n1;
    int num2 = c2 * d2 + n2;
    int denominator = d1 * d2;
    int numerator = num1 * d2 + num2 * d1;
    simplify(numerator, denominator);

    int incNum = numerator;
    int charactersitic = 0;
    if(incNum < 0){
        incNum *= -1;
    }

    while (incNum >= denominator){
        incNum -= denominator;
        charactersitic++;
    }
    if(numerator < 0){
        charactersitic *= -1;
        numerator *= -1;
    }

    if(createCharString(charactersitic, numerator, denominator, len, result) == false){
        return false;
    }
    
    //if len is the amount of characters in result, then the index of len would be one after the last character
    result[len] = '\0';
    return true;
}

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    return add(c1, n1, d1, -c2, n2, d2, result, len);
}

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){

}

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){

}
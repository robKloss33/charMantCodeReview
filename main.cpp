
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 1;
    d1 = 2;

    c2 = 2;
    n2 = 2;
    d2 = 3; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
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

    //finding total number of digits
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

    //implementation if the fraction == 0
    temp = characteristic;
    if (numerator == 0){
        for (int i = len - 1; i >= 0; i--){
            result[i] = (temp % 10) + '0';
            temp /= 10;
        }
        return true;
    }

    //implentation of result if numerator != 0
    //first put the integers in result
    int index;
    temp = characteristic;
    for(index = 0; index < len - 1 || temp < 0; index++){
        result[index] = (temp % 10) + '0';
        temp /= 10;
    }

    if (index == len - 2){
        return true;
    }
    //add the decimal and increment index
    result[index++] = '.';
    index++;

    //add the decimal numbers
    for(index; index < len - 1 || numerator == 0; index++){
        numerator *= 10;
        result[index] = (numerator / denominator) + '0';
        numerator %= denominator;
    }

    return true;

}

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    int num1 = c1 * d1 + n1;
    int num2 = c2 * d2 + n2;
    int denominator = d1 * d2;
    int numerator = num1 * d2 + num2 * d1;
    simplify(numerator, denominator);

    //incNum helps finds the chacteristic to be included when calling createCharString
    int incNum = numerator;
    int charactersitic = 0;
    if(incNum < 0){
        incNum *= -1;
    }

    //finding characteristic
    while (incNum >= denominator){
        incNum -= denominator;
        charactersitic++;
    }
    if(numerator < 0){
        charactersitic *= -1;
        numerator *= -1;
    }

    bool retVal = createCharString(charactersitic, numerator, denominator, len, result);
    result[len] = '\0';
    return retVal;
    
}

bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    return add(c1, n1, d1, -c2, n2, d2, result, len);
}

bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    int num1 = c1 * d1 + n1;
    int num2 = c2 * d2 + n2;
    int numerator = num1 * num2;
    int denominator = d1 * d2;
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

    return createCharString(charactersitic, numerator, denominator, len, result);
}

bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len){
    // dividing by zero returns false
    if(c2 == 0 && n2 == 0){
        return false;
    }

    int num1 = c1 * d1 + n1;
    int num2 = c2 * d2 + n2;
    int numerator = num1 * d2;
    int denominator = num2 * d1;
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

    return createCharString(charactersitic, numerator, denominator, len, result);
}
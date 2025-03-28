#include <iostream>
using namespace std;

//parse(string numstring)
//string with name of current state
//get event tyoe function that returns an event string digit space decimal invalid c >= 0 <= 9, spaces =, these are events --- decimal, charcteristic, mantiass, trailing spac
//leading space and get a digit change state to char and return isValid true,
//unary operator, leading spaces, decimal point entered, mantissa <-- all states


//required function prototypes
int getEvent(char currentInput);
bool parse(const char numString[]);

int arraySizeFinder(const char numString[]);
int periodIndexFinder(const char numString[]);

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
    const char number[] = "-123.456";

    const char test[] = "     -123      ";
    bool valid = parse(test);
    if (valid == true)
    {
        cout << "Valid input" << endl;
    }
    else
    {
        cout << "Not Valid input" << endl;
    }
    int c, n, d;
    //cout << arraySizeFinder(number) << endl;
    //cout << periodIndexFinder(number) << endl;
   
    //if both conversions from c-string to integers can take place
    if (characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout << "c: " << c << endl;
        cout << "n: " << n << endl;
        cout << "d: " << d << endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout << "Error on input" << endl;
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
    if (add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout << "Answer: " << answer << endl;
    }
    else
    {
        //display error message
        cout << "Error on add" << endl;
    }

    if (divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout << "Answer: " << answer << endl;
    }
    else
    {
        //display error message
        cout << "Error on divide" << endl;
    }

    return 0;
}
//--

int getEvent(char currentInput)
{
    if (currentInput <= '9' && currentInput >= '0')
        return 0;
    else if (currentInput == '-' or currentInput == '+')
        return 1;
    else if (currentInput == '.')
        return 2;
    else if (currentInput == ' ')
        return 3;
    else
        return 4;

}

bool parse(const char numString[])
{
    bool isValid = false;
    int event = 4;
    int state = 0;
    //STATES vvvvvvvvvvvvvv
    //leading spaces = 0
    //unary opearator = 1
    //char = 2
    //decimal entered = 3
    //matissa = 4
    //trailing spaces = 5
    // 
    //EVENTS vvvvvvvvvvvvvv
    //digit = 0
    //unary operator = 1
    //decimal = 2
    //space = 3
    //invalid = 4;

    for (int i = 0; i < arraySizeFinder(numString) -1; i++)
    {
        event = getEvent(numString[i]);
        //testing outputs
        //cout << "State: " << state << endl;
        //cout << "Event: " << event << endl;
        //cout << endl;
        if (event == 4)
        {
            return false;
        }
        if (state == 0)
        {
            //leading spaces
            if (event == 0)
            {
                state = 2;
            }
            else if (event == 1)
            {
                state = 1;
            }
            else if (event == 2)
            {
                return isValid;
            }

        }
        else if (state == 1)
        {
            //unary operator
            if (event == 0)
            {
                state = 2;
            }
            else if (event == 1)
            {
                return false;
            }
            else if (event == 2)
            {
                return isValid;
            }
        }
        else if (state == 2)
        {
            //charasteritic
            isValid = true;
            if (event == 0)
            {
                state = 2;
            }
            else if (event == 1)
            {
                return false;
            }
            else if (event == 2)
            {
                state = 3;
            }
            else if (event == 3)
            {
                state = 5;
            }
            
        }
        else if (state == 3)
        {
            //decimal entered
            if (isValid == false)
            {
                return false;
            }
            else
            {
                if (event == 0)
                {
                    state = 4;
                }
                else if (event == 1)
                {
                    return false;
                }
                else if (event == 2)
                {
                    return false;
                }
                else if (event == 3)
                {
                    return false;
                }
            }
        }
        else if (state == 4)
        {
            //mantissa
            if (event == 0)
            {
                state = 4;
            }
            else if (event == 1)
            {
                return false;
            }
            else if (event == 2)
            {
                return false;
            }
            else if (event == 3)
            {
                state = 5;
            }
        }
        else if (state == 5)
        {
            //trailing spaces
            if (event != 3)
                return false;
        }

    }
    return isValid;
}

int periodIndexFinder(const char numString[]) {
    for(int i = 0; i < arraySizeFinder(numString);i++)
    {
        if (numString[i] == '.')
        {
            return i;
        }
    }
    return arraySizeFinder(numString);
}
int arraySizeFinder(const char numString[]) {
    int i = 0;
    while (numString[i] != '\0')
    {
        i++;
    }
    if (numString[i] == '\0')
        i++;
    return i;

};


bool characteristic(const char numString[], int& c)
{
    bool isValid = parse(numString);
    if (isValid == true)
    {
        int base = 1;
        c = 0;
        int periodIndex = periodIndexFinder(numString);
        if (periodIndex == arraySizeFinder(numString))
        {
            //prevents reading in '\0' in the case of no period
            periodIndex--;
        }
        for (int i = periodIndex - 1; i >= 0; i--)
        {
            if (numString[i] == '-')
                c *= -1;
            else
            {
                //cout << (numString[i] - 48) * base << endl;
                c += (numString[i] - 48) * base;
                base = base * 10;
            }
            
        }
    }
    else
    {
        return false;
    }
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    int base = 1;
    numerator = 0;
    int size = arraySizeFinder(numString);
    int periodIndex = periodIndexFinder(numString);
    for (int i = size-2; i > periodIndex; i--)
    {
        //cout << numString[i] << endl;
        numerator += (numString[i] - 48) * base;
        base = base * 10;
    }
    //hard coded return value to make the main() work
    //numerator = 456;
    denominator = base;
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
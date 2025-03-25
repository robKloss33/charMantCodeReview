#include <iostream>
using namespace std;

//parse(string numstring)
//string with name of current state
//get event tyoe function that returns an event string digit space decimal invalid c >= 0 <= 9, spaces =, these are events --- decimal, charcteristic, mantiass, trailing spac
//leading space and get a digit change state to char and return isValid true,
//unary operator, leading spaces, decimal point entered, mantissa <-- all states




//required function prototypes
int getEvent(char currentInput);

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
    const char number[] = "123.456";
    int c, n, d;
    //cout << arraySizeFinder(number) << endl;
    //cout << periodIndexFinder(number) << endl;
    cout << getEvent('p') << endl;
   
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

int periodIndexFinder(const char numString[]) {
    int i = 0;
    bool hasBeenFound = false;
    while (hasBeenFound == false)
    {
        if (numString[i] == '.')
        {
            hasBeenFound = true;
            return i;
        }
        i++;
    }
    return 0;
}
int arraySizeFinder(const char numString[]) {
    int i = 0;
    bool hasBeenFound = false;
    while (hasBeenFound == false)
    {
        if (numString[i] == '\0')
        {
            hasBeenFound = true;
            return i + 1;
        }
        i++;
    }
    return 0;

};


bool characteristic(const char numString[], int& c)
{
    int base = 1;
    c = 0;
    int periodIndex = periodIndexFinder(numString);
    for (int i = periodIndex - 1; i >= 0; i--)
    {
        c += (numString[i] - 48) * base;
        base = base * 10;
    }
    //hard coded return value to make the main() work
    return true;
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
        cout << numString[i] << endl;
        numerator += (numString[i] - 48) * base;
        base = base * 10;
    }
    //hard coded return value to make the main() work
    //numerator = 456;
    denominator = base;
    return true;
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to add the two numbers
    //hard coded return value to make the main() work
    result[0] = '4';
    result[1] = '.';
    result[2] = '1';
    result[3] = '6';
    result[4] = '6';
    result[5] = '6';
    result[6] = '6';
    result[7] = '6';
    result[8] = '6';
    result[9] = '\0';

    return true;
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
    return true;
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';

    return true;
}

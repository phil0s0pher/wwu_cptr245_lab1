//=======================================================
// Name: lab1.cpp
// Author: Charles Lambert and Cameron Smith
// Course: CPTR245
// Assignment: Lab 1
// Description: Function Implementations
//=======================================================

// catch documentation: https://github.com/philsquared/Catch
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <string.h>
#include <cstring>
#include <exception>
#include <locale>

using namespace std;

// Custom Exceptions
struct Float_exception : public exception {
  const char * what () const throw () {
    return "a = 0 causes Floating point exception.";
  }
};

struct Imaginary_exception : public exception {
  const char * what () const throw () {
    return "Square root evaluated to an imaginary number.";
  }
};

struct OutOfRange_exception : public exception {
  const char * what () const throw () {
    return "One of the inputs is out of the acceptable range.";
  }
};

struct Empty_String_exception : public exception {
  const char * what () const throw () {
    return "One of the input strings is empty.";
  }
};

// Factorial (example)
unsigned int factorial( unsigned int number ) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

// Quadratic equation.
double quadratic(int a, int b, int c) {

  // Throw error if the user tries to divide by zero.
  if(a == 0) {
    throw Float_exception();
  }

  // Throw error if the number under the radical is less than zero.
  double rad = (b*b) - (4 * a * c);
  if(rad < 0) {
    throw Imaginary_exception();
  }

  // Evaluate the quadratic formula.
  return ((- b) + sqrt(rad))/ (2 * a);
};


// Greatest Common Divisor (GCD).
double gcd(int number1, int number2) {

  // If one number is zero, the GCD = 0.
  if(number1 == 0 || number2 == 0)
    return 0;

  // Evaluate the GCD for two nonzero numbers.
  number1 = (number1 > 0) ? number1 : -number1;
  number2 = (number1 > 0) ? number2 : -number2;

  while(number1!=number2) {

    if(number1 > number2)
      number1 -= number2;
    else
      number2 -= number1;
  }

  return number1;
};


// Babylonian Algorithm for square root.
// Absolute C++ Ch3 PP14
double squareRoot(double value){

  // If the value is zero, the square root is zero.
  // If the value is less than zero, the square root is imaginary, so throw exception.
  if(value == 0){
    return 0;
  } else if(value < 0) {
    throw Imaginary_exception();
  }

  // Implementation of the Babylonian Algorithm after esuring value > 0.
  double guess = value / 2;
  double prev_guess;
  double r;

  do {

    r = value / guess;
    prev_guess = guess;
    guess = (guess + r) /2;

  }while((abs(guess - prev_guess) / 2) > 0.000000001);

  return r;
};

// Set of subfunctions for dayOfTheWeek.
  // Choose the value that corresponds to the correct month.
  // If leapYear = true, choose the alternate value for Jan. or Feb.
int getMonthValue(int month, bool leapYear) {
  int monthIndex[] = {0,3,3,6,1,4,6,2,5,0,3,5};

  if(leapYear && month == 1) {
    return 6;
  }
  else if(leapYear && month == 2) {
    return 2;
  }
  else {
    return monthIndex[month - 1];
  }
}

// Determine if the year input is a leap year.
bool getLeapYear(int year) {
  return (year % 400 == 0 || (year % 4 == 0 && year % 100 > 0));
}

// Get Century value based on all but the last two digits of the year input.
int getCenturyValue(int year) {
  return (3 - ((year / 100) % 4)) * 2;
}

// Get Year value based on the last two digits of the year input.
int getYearValue(int year) {
  return (year % 100) + ((year % 100) / 4);
}

// Ensure the date input does not have a high Day value than allowed.
// (For example: Feb 31 would not be allowed.)
bool dayAllowed(int day, int month, bool leapYear) {
  if(leapYear && day > 29 && month == 2) {
    return false;
  }

  int dayMonthIndex[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if(leapYear) {dayMonthIndex[1] = 29;}


  if(day > dayMonthIndex[month - 1]) {
    return false;
  }

  return true;
}

// Calculate what day of the week corresponds to the date.
// Absolute C++ Ch3 PP12
string dayOfTheWeek(int month, int day, int year) {

  // Check to make sure a legal date has been input.
  if(year < 1 || month < 1 || day < 1 || month > 12  || !dayAllowed(day, month, getLeapYear(year))) {
    throw OutOfRange_exception();
  }

  // Get values from subfunctions.
  bool leapYear = getLeapYear(year);
  int centuryValue = getCenturyValue(year);
  int yearValue = getYearValue(year);
  int monthValue = getMonthValue(month, leapYear);
  string dayIndex[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  // Add all values returned plus the number of the day and calculate the day of the week.
  return dayIndex[(day + monthValue + yearValue + centuryValue) % 7];
};


// Subfunction for parseStudentName() to remove spaces from the entered string if present.
string removeSpaces(string str)
{
  str.erase(remove(str.begin(),str.end(),' '), str.end());
  return str;
}

string stringToLower(string str)
{
  locale loc;
  for (string::size_type i = 0; i < str.length(); ++i)
    str[i] = tolower(str[i], loc);

  return str;
}

vector<string> tokenizeString(string str, char delimiter)
{
  vector<string> vec;
  string token;
  stringstream ss;

  ss << str;
  while(getline(ss, token, delimiter))
  {
    vec.push_back(token);
  }

  return vec;
}

// Find the student's Frist and Last Name and calculate the CS username.
// Username criteria:
//  - First 4 characters of Last Name
//  - If last name < 4, fill characters from first name.
//  - First 2 characters of First Name
//  - If first name < 2, fill characters from last name.
void parseStudentName(const string studentName, string& firstName, string& lastName, string& username) {

  vector<string> parsedUnameVec;
  string cstr;

  // Copy studentName to editable basic string.
  cstr.assign(studentName);

  // Force the string to be all lowercase.
  cstr = stringToLower(cstr);

  // Remove spaces if present.
  cstr = removeSpaces(cstr);

  // Spilt string into tokens.
  parsedUnameVec = tokenizeString(cstr, ',');

  // If the string is empty, throw Empty_String_exception.
  // Otherwise, calculate the appropriate username
  // based on the available data/length of given names.
  if(parsedUnameVec.size() < 2) {
    throw Empty_String_exception();
  }

  firstName = parsedUnameVec[1];
  lastName = parsedUnameVec[0];

  if((lastName.length() + firstName.length()) < 6)
  {
    username = lastName + firstName;
  }
  else if (lastName.length() < 4)
  {
    int padding = 4 - lastName.length();
    username = lastName + firstName.substr(0, 2 + padding);
  }
  else if (firstName.length() < 2)
  {
    username = lastName.substr(0, 5) + firstName;
  }
  else
  {
    username = lastName.substr(0, 4) + firstName.substr(0, 2);
  }

};

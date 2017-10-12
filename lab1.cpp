//=======================================================
// Name: lab1.cpp
// Author: ?
// Course: CPTR245
// Assignment: Lab 1
// Description: Write the test cases and math expressions.
//=======================================================

// catch documentation: https://github.com/philsquared/Catch
// This tells Catch to provide a main() - only do this in one cpp file
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <exception>

using namespace std;

// Custom Exceptions
struct Float_exception : public exception {
  const char * what () const throw () {
    return "a = 0 causes Floating point exception";
  }
};

struct Imaginary_exception : public exception {
  const char * what () const throw () {
    return "Square root evaluated to an imaginary number";
  }
};

struct OutOfRange_exception : public exception {
  const char * what () const throw () {
    return "One of the inputs is out of the acceptable range";
  }
};

struct Empty_String_exception : public exception {
  const char * what () const throw () {
    return "One of the input strings is empty";
  }
};

// Factorial
unsigned int factorial( unsigned int number ) {
    return number <= 1 ? number : factorial(number - 1) * number;
}

// Quadratic equation.
double quadratic(int a, int b, int c) {

  if(a == 0) {
    throw Float_exception();
  }

  double rad = (b*b) - (4 * a * c);
  if(rad < 0) {
    throw Imaginary_exception();
  }

  return ((- b) + sqrt(rad))/ (2 * a);
};


// Greatest Common Divisor (GCD).
double gcd(int number1, int number2){
  if(number1 == 0 || number2 == 0)
    return 0;

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
  if(value == 0){
    return 0;
  } else if(value < 0) {
    throw Imaginary_exception();
  }

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

int getMonthValue(int month, bool leapYear) {
  switch(month) {
  case 1:
    if(leapYear) {
      return 6;
        }
    else {
      return 0;
    }
    break;
  case 2:
    if(leapYear){
      return 2;
    }
    else {
      return 3;
    }
    break;
  case 3:
    return 3;
    break;
  case 4:
    return 6;
    break;
  case 5:
    return 1;
    break;
  case 6:
    return 4;
    break;
  case 7:
    return 6;
    break;
  case 8:
    return 2;
    break;
  case 9:
    return 5;
    break;
  case 10:
    return 0;
    break;
  case 11:
    return 3;
    break;
  case 12:
    return 5;
    break;
  }

  return 0;
}

bool getLeapYear(int year) {
  return (year % 400 == 0 || (year % 4 == 0 && year % 100 > 0));
}

int getCenturyValue(int year) {
  return (3 - ((year / 100) % 4)) * 2;
}

int getYearValue(int year) {
  return (year % 100) + ((year % 100) / 4);
}

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
  if(year < 1 || month < 1 || day < 1 || month > 12  || !dayAllowed(day, month, getLeapYear(year))) {
    throw OutOfRange_exception();
  }

  bool leapYear = getLeapYear(year);
  int centuryValue = getCenturyValue(year);
  int yearValue = getYearValue(year);
  int monthValue = getMonthValue(month, leapYear);
  string dayIndex[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

  return dayIndex[(day + monthValue + yearValue + centuryValue) % 7];
};


// Find the student's Frist and Last Name and calculate the CS username
// Username criteria
//  - First 4 characters of Last Name
//  - If last name < 4, fill characters from first name.
//  - First 2 characters of First Name
//  - If first name < 2, fill characters from last name.
void parseStudentName(const string studentName, string& firstName, string& lastName, string& username) {
  firstName = "hello";
  cout << firstName;

};



// Tests...
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( factorial(1) == 1 );
    REQUIRE( factorial(2) == 2 );
    REQUIRE( factorial(3) == 6 );
    REQUIRE( factorial(10) == 3628800 );
}

TEST_CASE( "Should compute quadratic", "[quadratic]" ) {
  REQUIRE( quadratic(2, 4, 2) == -1.0);
}

TEST_CASE( "When a is zero should throw floating point exception", "[quadratic]") {
  REQUIRE_THROWS_AS( quadratic(0, 20, -10), Float_exception e);
}

TEST_CASE( "If a, b, and c are specific values that create imaginary number throw imaginary_exception", "[quadratic]") {
  REQUIRE_THROWS_AS( quadratic(-1, -1, -1), Imaginary_exception e);
}

TEST_CASE( "If a or b is 0 return 0", "[gcd]") {
  REQUIRE( gcd(0, 20) == 0);
}

TEST_CASE( "It should compute the greatest common deviser", "[gcd]") {
  REQUIRE( gcd(10, 25) == 5);
}

TEST_CASE( "Should throw imaginary exception when given a negative number", "[squareRoot]") {
  REQUIRE_THROWS_AS( squareRoot(-4.00), Imaginary_exception e);
}

TEST_CASE( "Should return zero if given zero", "[squareRoot]") {
  REQUIRE( squareRoot(0.00) == 0.00);
}

TEST_CASE( "Should calculate square root of a positive double", "[squareRoot]") {
  REQUIRE( squareRoot(5) == Approx(2.2361));
}

TEST_CASE( "Should calculate leapYear", "[dayOfTheWeek]") {
  REQUIRE( getLeapYear(2017) == false);
  REQUIRE( getLeapYear(2016));
}

TEST_CASE( "Should calculate CenturyValue", "[dayOfTheWeek]") {
  REQUIRE( getCenturyValue(2016) == 6);
}

TEST_CASE( "Should calculate MonthValue", "[dayOfTheWeek]") {
  REQUIRE( getMonthValue(2, true) == 2);
  REQUIRE( getMonthValue(2, false) == 3);
  REQUIRE( getMonthValue(5, false) == 1);
}

TEST_CASE( "Should check if the day is allowed in that month", "[dayOfTheWeek]") {
  REQUIRE( dayAllowed(31, 5, true));
  REQUIRE( dayAllowed(30, 4, false));
  REQUIRE( dayAllowed(29, 2, true));
  REQUIRE( dayAllowed(28, 2, false));
}

TEST_CASE( "It should return OutOfRange_exception if year is less than 1", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS(dayOfTheWeek(12, 5, -1000), OutOfRange_exception e);
}

TEST_CASE( "It should return OutOfRange_exception if month is less than 1", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS(dayOfTheWeek(-5, 5, 1000), OutOfRange_exception e);
}

TEST_CASE( "It should return OutOfRange_exception if day is less than 1", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS(dayOfTheWeek(12, 0, 1000), OutOfRange_exception e);
}

TEST_CASE( "It should return an OutOfRange_exception if month is greater than 12", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS( dayOfTheWeek(13, 1, 2008), OutOfRange_exception e);
}

TEST_CASE( "It should calculate the day of the week given the day, month and year", "[dayOfTheWeek]") {
  REQUIRE( dayOfTheWeek(10, 9, 2017) == "Monday");
}

TEST_CASE( "It should return an OutOfRange_exception if the day does not exist in that month", "[dayOfTheWeek]") {
  REQUIRE_THROWS_AS( dayOfTheWeek(10, 32, 2017), OutOfRange_exception e);
}

TEST_CASE( "It should throw Empty_String_exception if lastname is less than 1", "[parseStudentName]") {
  const string studentName = "Smith, ";
  string firstName;
  string lastName;
  string username;
  REQUIRE_THROWS_AS( parseStudentName(studentName, firstName, lastName, username), Empty_String_exception e);
}

TEST_CASE( "It should parse the students username", "[parseStudentName]") {
  const string studentName = "Babylonian, Mike, Tj";
  string firstName;
  string lastName;
  string username;
  parseStudentName(studentName, firstName, lastName, username);
  REQUIRE( username ==  "babymi");
}

TEST_CASE( "It should pad out the username if the last name is less than 4 characters", "[parseStudentName]") {
  const string studentName = "Woo, John";
  string firstName;
  string lastName;
  string username;
  parseStudentName(studentName, firstName, lastName, username);
  REQUIRE( username ==  "woojoh");
}

TEST_CASE( "It should pad out the username if the first name is less than 2 characters", "[parseStudentName]") {
  const string studentName = "Smith, C";
  string firstName;
  string lastName;
  string username;
  parseStudentName(studentName, firstName, lastName, username);
  REQUIRE( username ==  "smithc");
}

TEST_CASE( "It should produce a username that is less than 6 characters if both last and first name together are less than 6 characters", "[parseStudentName]") {
  
}

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
    return "The values of a, b and c cause an imaginary number";
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
double squareRoot(double value);


// Calculate what day of the week corresponds to the date.
// Absolute C++ Ch3 PP12
string dayOfTheWeek(int month, int day, int year);


// Find the student's Frist and Last Name and calculate the CS username
// Username criteria
//  - First 4 characters of Last Name
//  - If last name < 4, fill characters from first name.
//  - First 2 characters of First Name
//  - If first name < 2, fill characters from last name.
void parseStudentName(const string studentName, string& firstName, string& lastName, string& username);



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

TEST_CASE( "It should compute the greatest common deviser") {
  REQUIRE( gcd(10, 25) == 5);
}

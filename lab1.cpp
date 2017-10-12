//=======================================================
// Name: lab1.cpp
// Author: Charles Lamber and Cameron Smith
// Course: CPTR245
// Assignment: Lab 1
// Description: Write the test cases and math expressions.
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


TEST_CASE( "Test for RemoveSpaces() function. It should remove all spaces and reconcatonate the strings.", "[parseStudentName]") {
  string str = "Norris, chu ck";
  string res = "Norris,chuck";
  REQUIRE(removeSpaces(str) == res);
}

TEST_CASE( "Should split the string on a delimiter, and return the parts as a vector", "[parseStudentName]") {
  string str = "howlett,james";
  vector<string> res;
  res.push_back("howlett");
  res.push_back("james");
  REQUIRE(tokenizeString(str,',') == res);
}

TEST_CASE( "Should change all characters to lowercase in string", "[parseStudentName]") {
  string str = "HeLLo WorLd";
  REQUIRE(stringToLower(str) == "hello world");
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
  REQUIRE( firstName == "mike");
  REQUIRE( lastName == "babylonian");
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
  const string studentName = "Qin, M";
  string firstName;
  string lastName;
  string username;
  parseStudentName(studentName, firstName, lastName, username);
  REQUIRE( username ==  "qinm");
}

TEST_CASE( "It should produce a username that is less than 6 characters if the last name is 1 character and the firstname is < 5", "[parseStudentName]") {
  const string studentName = "A, Thomas";
  string firstName;
  string lastName;
  string username;
  parseStudentName(studentName, firstName, lastName, username);
  REQUIRE( username ==  "athoma");
}

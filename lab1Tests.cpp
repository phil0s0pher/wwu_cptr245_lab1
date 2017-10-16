//=======================================================
// Name: lab1Tests.cpp
// Author: Charles Lambert and Cameron Smith
// Course: CPTR245
// Assignment: Lab 1
// Description: Actual tests cases.
//=======================================================

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

// Copyright 2023 CSCE 240 Programming Assignment 4
//
#include <hw4/inc/test_tax.h>


int main(int argc, char* argv[]) {
  // for test number command line arg
  const std::size_t kTestArg = 1;
  // if no arg given, run all tests
  int test = argc == 2 ? std::atoi(argv[kTestArg]) : 0;
  const std::size_t kTotalTests = 4;
  std::size_t tests_passed = 0;
  switch (test) {
    case 0:
    case 1:
    // map test 1 to TestTaxMultiplyMethod
      std::cout << "TESTING csce240::Tax::operator*" << std::endl;
      if (TestTaxMultiplyMethod(1.05, 10.0, 10.5)) {  // 1.05 is 10% of 10.5
        std::cout << "  PASSED" << std::endl;
        ++tests_passed;
        if (test)
          return 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        if (test)
          return 1;
      }
    case 2:
    // map test 2 to TestTaxMultiplyFunction
      std::cout << "TESTING csce240::operator*" << std::endl;
      if (TestTaxMultiplyFunction(1.05, 10.0, 10.5)) {  // 1.05 is 10% of 10.5
        std::cout << "  PASSED" << std::endl;
        ++tests_passed;
        if (test)
          return 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        if (test)
          return 1;
      }

    case 3: {  // need a block when declaring variables in switch-statement
    // map test 3 to TestTaxExtract
      std::cout << "TESTING csce240::operator<<" << std::endl;
      csce240::Tax extract_tax("EXT", 33.3);
      if (TestTaxExtract("EXT:33.3", extract_tax)) {
        std::cout << "  PASSED" << std::endl;
        ++tests_passed;
        if (test)
          return 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        if (test)
          return 1;
      }
    }  // end case 3 block

    case 4: {  // block needed to declare variables in switch
    // map test 4 to TestTaxInsert
      std::cout << "TESTING csce240::operator>>" << std::endl;
      csce240::Tax insert_tax("INS", 25.4);
      if (TestTaxInsert(insert_tax, "INS", 25.4)) {
        std::cout << "  PASSED" << std::endl;
        ++tests_passed;
        if (test)
          return 0;
      } else {
        std::cout << "  FAILED" << std::endl;
        if (test)
          return 1;
      }
    }  // end case 4 block

  default:
    // should only get here if test == 0
    return (!test && tests_passed == kTotalTests) ? 0 : 1;
  }

  return tests_passed == kTotalTests ? 0 : 1;
}


bool FloatingPointEquals(double lhs, double rhs) {
  double abs_diff = fabs(lhs - rhs);
  // test using percent difference and const double from header
  return abs_diff < kPercent_diff;
}


bool TestTaxMultiplyMethod(double expected, double percent, double amount) {
  csce240::Tax test_tax("TST", percent);  // instance is TST:percent

  double actual = test_tax * amount;  // get actual value

  if (FloatingPointEquals(expected, actual))
    return true;

  std::cout << std::setprecision(kPrecision)
    << std::fixed  // to display difference
    << "  Expected: " << expected << ", Actual: " << actual << std::endl
    << std::defaultfloat;  // turn off std::fixed
  return false;
}


bool TestTaxMultiplyFunction(double expected, double percent, double amount) {
  csce240::Tax test_tax("TST", percent);  // instance is TST:percent

  double actual = amount * test_tax;  // get actual value

  if (FloatingPointEquals(expected, actual))
    return true;

  std::cout << std::setprecision(kPrecision)
    << std::fixed  // to display difference
    << "  Expected: " << expected << ", Actual: " << actual << std::endl
    << std::defaultfloat;  // turn off std::fixed
  return false;
}


bool TestTaxExtract(const std::string& expected, const csce240::Tax& from) {
  std::stringstream sout;  // will function as an output stream

  sout << from;  // pass to csce240::operator<<
  if (expected == sout.str())  // std::stringstream::str returns a std::string
    return true;               //   instance

  std::cout << "  Expected: " << expected << ", Actual: " << sout.str();
  return false;
}


bool TestTaxInsert(const csce240::Tax& expected,
                   const std::string code,
                   double amount) {
  csce240::Tax actual("", 0);  // no default constructor, init empty instance
  std::stringstream sin;  // will function as input stream
  sin << code << ' ' << amount;  // add values to stream
  sin >> actual;  // pass to csce240::operator>>
  if (expected.code() == actual.code()  // compare apples to apples and...
      && expected.percent() == actual.percent()) {
    return true;
  } else {
    std::cout << "  Expected: " << expected.code() << ':' << expected.percent()
        << ",  Actual: " << actual.code() << ':' << actual.percent()
        << std::endl;
    return false;
  }
}

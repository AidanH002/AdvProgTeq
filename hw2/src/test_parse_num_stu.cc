// Copyright 2023 CSCE 240
//
#include <cstddef>
#include <iostream>
#include <string>

#include <hw2/inc/parse_grades.h>
#include <hw2/inc/parse_grades.h>


const std::string kValues[] = {  //NOLINT: guide says char** when global const
  "23SU",
  "4",
  "345",
    "E", "2", "1", "91", "2", "83",
    "Q", "1", "3.4", "Q",
  "456",
    "E", "3", "1", "77", "2", "65", "3", "84",
    "Q", "1", "3.1", "2", "2.7", "Q",
  "567",
    "E", "1", "1", "79",
    "Q", "Q",
  "890",
    "E", "0",
    "Q", "2", "3.9", "Q"
};
const std::size_t kSize = sizeof(kValues)/sizeof(std::string);
const std::string kEmptyValues[] = {  // NOLINT: see above
  "23SU",
  "0"
};
const std::size_t kEmptySize = 2;

bool TestParseNumStu();
bool TestParseNumNoStu();

int main(int argc, char* argv[]) {
  int passed = 0;

  std::cout << "Testing ParseNumStudents" << std::endl;
  if (TestParseNumStu()) {
    std::cout << "  PASSED" << std::endl;
  } else {
    std::cout << "  FAILED" << std::endl;
    passed = 1;  // exit with failure
  }

  std::cout << "Testing ParseNumStudents With Empty Array" << std::endl;
  if (TestParseNumNoStu()) {
    std::cout << "  PASSED" << std::endl;
  } else {
    std::cout << "  FAILED" << std::endl;
    passed = 1;  // exit with failure
  }

  return passed;
}


bool TestParseNumStu() {  // true when correct number of students parsed
  bool passed = true;
  const int expected = 4;
  int actual = ParseNumStudents(kValues, kSize);
  if (expected != actual) {
    std::cout << "  Expected Number of Students: " << expected << ", Actual: "
        << actual << std::endl;
    passed = false;
  }

  return passed;
}


bool TestParseNumNoStu() {  // true when return val is -1 for size is 0
  bool passed = true;
  const int expected = 0;
  ParseErrors result;

  int actual = ParseNumStudents(kEmptyValues, kEmptySize, &result);

  if (expected != actual) {
    std::cout << "  Expected Number of Students: " << expected << ", Actual: "
        << actual << std::endl;
    passed = false;
  }

  if (result != ParseErrors::kNoStudents) {
    std::cout << "  Expected ParseError: kNoStudents Actual: "
      << ::ToString(result) << std::endl;
    passed = false;
  }

  return passed;
}

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
const std::size_t kValSize = sizeof(kValues)/sizeof(std::string);
const std::string kStuIds[] = { "345", "456", "567" };
const int kExamNos[] = { 2, 3, 1 };
const std::size_t kStuIdsSize = 3;


bool TestParseNumExams();
bool TestParseNumExamsEmpty();
bool TestParseNumExamsNoId();


int main(int argc, char* argv[]) {
  int passed = 0;

  std::cout << "Testing ParseNumExams" << std::endl;
  if (TestParseNumExams()) {
    std::cout << "  PASSED" << std::endl;
  } else {
    std::cout << "  FAILED" << std::endl;
    passed = 1;  // exit with failure
  }

  std::cout << "Testing ParseNumExams With Empty Array" << std::endl;
  if (TestParseNumExamsEmpty()) {
    std::cout << "  PASSED" << std::endl;
  } else {
    std::cout << "  FAILED" << std::endl;
    passed = 1;  // exit with failure
  }

  std::cout << "Testing ParseNumExams With Missing Student" << std::endl;
  if (TestParseNumExamsNoId()) {
    std::cout << "  PASSED" << std::endl;
  } else {
    std::cout << "  FAILED" << std::endl;
    passed = 1;  // exit with failure
  }

  return passed;
}

bool TestParseNumExams() {  // true when correct number of students parsed
  bool passed = true;
  for (std::size_t i = 0; i < kStuIdsSize; ++i) {
    const int expected = kExamNos[i];
    const int actual = ParseNumExams(kStuIds[i], kValues, kValSize);
    if (expected != actual) {
      std::cout << "  " << kStuIds[i] << "-"
        << "Expected Number of Exams: " << expected
        << ", Actual: " << actual << std::endl;
      passed = false;
    }
  }

  return passed;
}


bool TestParseNumExamsEmpty() {  // true when return val is -1 for size is 0
  bool passed = true;
  ParseErrors result;
  const std::size_t expected = 0;
  const std::size_t actual = ParseNumExams("890", kValues, kValSize, &result);
  if (expected != actual) {
    std::cout << "  890-Expected Number of Exams: " << expected << ", Actual: "
        << actual << std::endl;
    passed = false;
  }

  if (result != ParseErrors::kNoExams) {
    std::cout << "  890-Expected ParseError: kNoExams Actual: "
      << ::ToString(result) << std::endl;
    passed = false;
  }

  return passed;
}


bool TestParseNumExamsNoId() {  // true when return val is -2 for missing id
  bool passed = true;
  ParseErrors result;
  ParseNumExams("000", kValues, kValSize, &result);

  if (result != ParseErrors::kMissingStudent) {
    std::cout << "  000-Expected ParseError: kMissingStudent, Actual: "
      << ::ToString(result) << std::endl;
    passed = false;
  }

  return passed;
}

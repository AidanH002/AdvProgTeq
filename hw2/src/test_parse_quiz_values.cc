// Copyright 2023 CSCE 240
//
#include <cstddef>
#include <iostream>
#include <string>

#include <hw2/inc/parse_grades.h>
#include <hw2/inc/parse_grades.h>


const std::string kValues[] = {  //NOLINT: guide says char** when global const
  "23SU",
  "3",
  "345",
    "E", "2", "1", "91", "2", "83",
    "Q", "1", "3.4", "Q",
  "456",
    "E", "3", "1", "77", "2", "65", "3", "84",
    "Q", "1", "3.1", "2", "2.7", "Q",
  "567",
    "E", "1", "1", "79",
    "Q", "Q",
};
const std::size_t kValSize = sizeof(kValues)/sizeof(std::string);
const std::string kStuIds[] = { "345", "456" };
const std::size_t kStuIdsSize = 2;
const double kQuizValues[][2] = { {3.4}, { 3.1, 2.7 } };
const std::size_t kQuizValuesSizes[] = { 1, 2 };


bool TestParseQuizValues();
bool TestParseQuizValuesEmpty();
bool TestParseQuizValuesNoId();


int main(int argc, char* argv[]) {
  int passed = 0;

  std::cout << "Testing ParseQuizValues" << std::endl;
  if (TestParseQuizValues()) {
    std::cout << "  PASSED" << std::endl;
  } else {
    std::cout << "  FAILED" << std::endl;
    passed = 1;  // exit with failure
  }

  std::cout << "Testing ParseQuizValues With Empty Array" << std::endl;
  if (TestParseQuizValuesEmpty()) {
    std::cout << "  PASSED" << std::endl;
  } else {
    std::cout << "  FAILED" << std::endl;
    passed = 1;  // exit with failure
  }

  std::cout << "Testing ParseQuizValues With Missing Student" << std::endl;
  if (TestParseQuizValuesNoId()) {
    std::cout << "  PASSED" << std::endl;
  } else {
    std::cout << "  FAILED" << std::endl;
    passed = 1;  // exit with failure
  }

  return passed;
}

bool TestParseQuizValues() {
  bool passed = true;
  const std::size_t kQuizValuesSize = 8;
  double quiz_values[kQuizValuesSize];

  for (std::size_t i = 0; i < kStuIdsSize; ++i) {
    const int expected = kQuizValuesSizes[i];
    const int actual = ParseQuizValues(kStuIds[i],
                                       kValues,
                                       kValSize,
                                       quiz_values);
    if (expected != actual) {
      std::cout << "  " << kStuIds[i] << " "
        << "Expected Number of Quiz Values: " << expected
        << ", Actual: " << actual << std::endl;
      passed = false;
    }
    for (std::size_t ii = 0; ii < kQuizValuesSizes[i]; ++ii) {
      if (kQuizValues[i][ii] != quiz_values[ii]) {
        std::cout << "  " << kStuIds[i] << " "
          << "Expected quiz_values["<< ii << "]: " << kQuizValues[i][ii]
          << ", Actual: " << quiz_values[ii] << std::endl;
        passed = false;
      }
    }
  }

  return passed;
}


bool TestParseQuizValuesEmpty() {
  bool passed = true;
  const std::size_t kQuizValuesSize = 1;
  double quiz_values[kQuizValuesSize];
  ParseErrors result;

  const int expected = 0;
  const int actual = ParseQuizValues("567",
                                     kValues,
                                     kValSize,
                                     quiz_values,
                                     &result);
  if (expected != actual) {
    std::cout << "  567 Expected Number of Quiz Values: " << expected
      << ", Actual: " << actual << std::endl;
    passed = false;
  }

  if (result != ParseErrors::kNoQuizzes) {
    std::cout << "  Expected ParseError: kNoQuizzes, Actual: "
      << ::ToString(result) << std::endl;
    passed = false;
  }

  return passed;
}


bool TestParseQuizValuesNoId() {
  bool passed = true;
  const std::size_t kQuizValuesSize = 1;
  double quiz_values[kQuizValuesSize];
  ParseErrors result;

  ParseQuizValues("000", kValues, kValSize, quiz_values, &result);

  if (result != ParseErrors::kMissingStudent) {
    std::cout << "  Expected ParseError: kMissingStudent, Actual: "
      << ::ToString(result) << std::endl;
    passed = false;
  }

  return passed;
}

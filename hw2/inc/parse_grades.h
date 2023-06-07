// copyright 2023 Aidan Hall
#ifndef HW2_INC_PARSE_GRADES_H_
#define HW2_INC_PARSE_GRADES_H_

#include <string>

enum class ParseErrors {
  kNoErrors,
  kNoStudents,
  kNoExams,
  kNoQuizzes,
  kMissingStudent,
  kMissingExam,
  kMissingQuiz
};

const std::string ToString(const ParseErrors& error);

std::size_t ParseNumStudents(const std::string values[],
  std::size_t size,
  ParseErrors* errors = nullptr);

std::size_t ParseNumExams(const std::string& stu_id,
  const std::string values[],
  std::size_t size,
  ParseErrors* errors = nullptr);

std::size_t ParseQuizValues(const std::string& stu_id,
  const std::string values[],
  std::size_t size,
  double quiz_values[],
  ParseErrors* errors = nullptr);

#endif  // HW2_INC_PARSE_GRADES_H_


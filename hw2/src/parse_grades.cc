// copyright 2023 Aidan Hall
#include <hw2/inc/parse_grades.h>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <ostream>

const std::string ToString(const ParseErrors& error) {
  switch (error) {
    case ParseErrors::kNoErrors:
      return "kNoErrors";
    case ParseErrors::kNoStudents:
      return "kNoStudents";
    case ParseErrors::kNoExams:
      return "kNoExams";
    case ParseErrors::kNoQuizzes:
      return "kNoQuizzes";
    case ParseErrors::kMissingStudent:
      return "kMissingStudent";
    case ParseErrors::kMissingExam:
      return "kMissingExam";
    case ParseErrors::kMissingQuiz:
      return "kMissingQuiz";
    default:
      return std::string();
  }
}
std::size_t ParseNumStudents(const std::string values[],
  std::size_t size, ParseErrors* errors) {
  const std::size_t kEmptyArrayValue = 0;
  if (size == 0) {
    if (errors != nullptr) {
      *errors = ParseErrors::kNoStudents;
    }
    return kEmptyArrayValue;
  }

  std::size_t numStudents = 0;
  bool parsingId = true;
  for (std::size_t i = 0; i < size; ++i) {
    if (parsingId) {
      if (values[i] == "Q") {
        parsingId = false;
      }
    } else {
      if (values[i] == "Q") {
        parsingId = true;
        ++numStudents;
      }
    }
  }

  if (errors != nullptr && numStudents == 0) {
    *errors = ParseErrors::kNoStudents;
  }

  return numStudents;
}
std::size_t ParseNumExams(const std::string& stu_id,
  const std::string values[], std::size_t size, ParseErrors* errors) {
  std::size_t numExams = 0;

  bool foundStudent = false;
  bool parsingExams = false;

  for (std::size_t i = 0; i < size; ++i) {
    if (!foundStudent) {
      if (values[i] == stu_id) {
        foundStudent = true;
      }
    } else {
      if (parsingExams) {
        if (values[i] == "Q") {
          parsingExams = false;
          break;  // Stop parsing exams when "Q" is found
        }
      } else {
        if (values[i].find("E") != std::string::npos) {
          // Check if the next value is a valid number of exams
          if (i + 1 < size) {
            try {
              numExams = std::stoi(values[i + 1]);
              parsingExams = true;
              ++i;
// Skip the next value since it has been parsed as the number of exams
            } catch (const std::invalid_argument&) {
              // Invalid number of exams
              if (errors != nullptr) {
                *errors = ParseErrors::kMissingExam;
              }
              return numExams;
// Return the parsed number of exams before the error occurred
            } catch (const std::out_of_range&) {
              // Invalid number of exams (out of range)
              if (errors != nullptr) {
                *errors = ParseErrors::kMissingExam;
              }
              return numExams;
            }
          } else {
            // Missing number of exams
            if (errors != nullptr) {
              *errors = ParseErrors::kMissingExam;
            }
            return numExams;
          }
        } else if (values[i] == "Q") {
          // Missing number of exams
          if (errors != nullptr) {
            *errors = ParseErrors::kMissingExam;
          }
          return numExams;
        }
      }
    }
  }

  if (!foundStudent) {  // Missing student
    if (errors != nullptr) {
      *errors = ParseErrors::kMissingStudent;
    }
    return numExams;
    // Return the parsed number of exams before the student was missing
  }

  if (errors != nullptr && numExams == 0) {
    *errors = ParseErrors::kNoExams;
  }

  return numExams;
}
std::size_t ParseQuizValues(const std::string& stu_id,
  const std::string values[], std::size_t size,
  double quiz_values[], ParseErrors* errors) {
  bool foundStudent = false;
  bool missingQuiz = false;
  bool finishedStudent = false;
  std::size_t index = 0;

  // Check if the array has no students or quizzes
  if (size < 2 || (size == 2 && values[1] != "E")) {
    if (errors != nullptr) {
      *errors = ParseErrors::kNoQuizzes;
    }
    return 0;
  }

  for (std::size_t i = 0; i < size; ++i) {
    if (values[i] == stu_id) {
      foundStudent = true;
      finishedStudent = false;
      continue;
    }

    if (foundStudent && !finishedStudent) {
      if (values[i] == "E") {
          // Skip over the exam values
        while (i < size && values[i] != "Q") {
          i += 2;  // Skip both exam ID and grade
        }
        i--;  // Decrement i to account for the upcoming increment in the loop
        continue;
      }

      if (values[i] == "Q") {
        if (i + 1 < size && values[i + 1] == "Q") {
          // No quiz IDs or scores between the two "Q" tokens
          finishedStudent = true;
          if (errors != nullptr) {
            *errors = ParseErrors::kNoQuizzes;
          }
          return 0;
        }

        i++;  // Move to the next value (quiz ID)

        while (i < size && values[i] != "E" && values[i] != "Q") {
          // Check if the next value is a valid quiz ID
          std::istringstream quizIdStream(values[i]);
          int quizId;
          if (!(quizIdStream >> quizId)) {
            missingQuiz = true;
            break;
          }

          i++;  // Move to the next value (quiz score)

          // Check if the next value is a valid quiz score
          if (i >= size) {
            missingQuiz = true;
            break;
          }

          std::istringstream quizScoreStream(values[i]);
          double quizScore;
          if (!(quizScoreStream >> quizScore)) {
            missingQuiz = true;
            break;
          }

          // Store the quiz score
          quiz_values[index] = quizScore;
          index++;

          i++;  // Move to the next pair of quiz ID and score
        }

        if (values[i] == "E" || values[i] == "Q") {
          i--;  // Decrement i to account for the upcoming increment in the loop
          finishedStudent = true;
        }
        continue;
      }
    }
  }

  if (!foundStudent) {
    if (errors != nullptr) {
      *errors = ParseErrors::kMissingStudent;
    }
    return 0;
  }

  if (missingQuiz) {
    if (errors != nullptr) {
      *errors = ParseErrors::kMissingQuiz;
    }
    return index;
  }

  return index;
}

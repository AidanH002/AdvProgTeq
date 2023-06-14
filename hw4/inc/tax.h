// Copyright 2023 Aidan Hall

#ifndef HW4_INC_TAX_H_
#define HW4_INC_TAX_H_

#include <iostream>
#include <string>

namespace csce240 {

class Tax {
 private:
  std::string code_;
  double percent_;

 public:
  Tax();  // Default constructor
  Tax(const std::string& code, double percent);  // Complete constructor

std::string code() const;  // Code getter
double percent() const;  // Percent getter

double operator*(double rhs) const;  // Multiply operator

std::ostream& Extract(std::ostream* output) const;  // Extract method
std::istream& Insert(std::istream* input);  // Insert method
};

double operator*(double lhs, const Tax& rhs);  // Multiply operator (global)

std::ostream& operator<<(std::ostream& output,
  const Tax& tax);  // Extract operator
std::istream& operator>>(std::istream& input, Tax& tax);  // Insert operator

}  // namespace csce240

#endif  // HW4_INC_TAX_H_

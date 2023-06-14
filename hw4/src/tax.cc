// Copyright 2023 Aidan Hall

#include <hw4/inc/tax.h>

#include <iomanip>
#include <iostream>
#include <sstream>

namespace csce240 {

Tax::Tax() : code_(""), percent_(0.0) {}

Tax::Tax(const std::string& code, double percent) :
code_(code), percent_(percent) {}

std::string Tax::code() const {
  return code_;
}

double Tax::percent() const {
  return percent_;
}

double Tax::operator*(double rhs) const {
  return rhs * (percent_ / 100.0);
}

std::ostream& Tax::Extract(std::ostream* output) const {
  if (output) {
    *output << code_ << ':' << std::fixed << std::setprecision(1) << percent_;
  }
  return *output;
}

std::istream& Tax::Insert(std::istream* input) {
  if (input) {
    *input >> code_ >> percent_;
  }
  return *input;
}

double operator*(double lhs, const Tax& rhs) {
  return lhs * (rhs.percent() / 100.0);
}

std::ostream& operator<<(std::ostream& output, const Tax& tax) {
  return tax.Extract(&output);
}

std::istream& operator>>(std::istream& input, Tax& tax) {
  return tax.Insert(&input);
}

}  // namespace csce240

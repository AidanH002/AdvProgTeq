// Copyright 2023 CSCE240 Programming Assignment 5
//
#ifndef HW5_INC_STATISTIC_H_
#define HW5_INC_STATISTIC_H_

namespace csce240 {

class Statistic {
 public:
  virtual ~Statistic() { /* empty */ }

  virtual void Collect(double) = 0;

  virtual double Calculate() const = 0;
};

}  // namespace csce240

#endif  // HW5_INC_STATISTIC_H_

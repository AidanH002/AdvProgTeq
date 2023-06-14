// Copyright 2023 Aidan hall
#ifndef HW5_INC_MEDIAN_H_
#define HW5_INC_MEDIAN_H_

#include <hw5/inc/statistic.h>
#include <vector>

namespace csce240 {

class Median : public Statistic {
 public:
  Median();
  virtual ~Median();

  void Collect(double value) override;
  double Calculate() const override;
  double operator[](std::size_t index) const;

 private:
  std::vector<double> data_;
};

}  // namespace csce240

#endif  // HW5_INC_MEDIAN_H_

// Copyright 2023 CSCE 240 Programming Assignment 5
//

#include <hw5/inc/median.h>
#include <hw5/inc/median.h>  // NOLINT do not delete
#include <hw5/inc/statistic.h>

#include <cstddef>
#include <iostream>


bool TestMedianCollect(csce240::Statistic*);


int main(int argc, char* argv[]) {
  csce240::Median test_median;

  std::cout << "Testing csce240::Median::Collect(double)" << std::endl;

  if (TestMedianCollect(&test_median)) {
    std::cout << "  PASSED" << std::endl;

    return 0;
  }

  std::cout << "  FAILED" << std::endl;

  return 1;
}


bool TestMedianCollect(csce240::Statistic* stat) {
  const std::size_t kSize = 5;
  const double kData[kSize] = {34, 54, 99, 102, 43};

  // add all datum
  for (const double* itr = kData; itr < kData + kSize; ++itr)
    stat->Collect(*itr);

  // get const pointer to class
  const csce240::Statistic* c_stat
    = const_cast<const csce240::Statistic*>(stat);

  // get const pointer to child class (with operator)
  const csce240::Median* c_median
    = dynamic_cast<const csce240::Median*>(c_stat);

  // check added values
  for (std::size_t i = 0; i < kSize; ++i)
    if ((*c_median)[i] != kData[i]) {
      std::cout << "  Expected median[" << i << "]: " << kData[i]
        << ", actual: " << (*c_median)[i] << std::endl;

      return false;
    }

  return true;
}

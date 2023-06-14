// Copyright 2023 CSCE 240 Programming Assignment 5
//

#include <hw5/inc/median.h>
#include <hw5/inc/statistic.h>
#include <iostream>


const std::size_t kSize1 = 5;
const double kData1[kSize1] = { 34, 54, 99, 102, 43 };
const double kExpected1 = 54;


const std::size_t kSize2 = 6;
const double kData2[kSize2] = { 34, 54, 99, 102, 43, 22 };
const double kExpected2 = (43.0 + 54.0) / 2.0;


void LoadMedian(const double*, std::size_t, csce240::Statistic*);
bool TestCalculateMedian(const csce240::Statistic&, double);


int main(int argc, char* argv[]) {
  // create Median
  csce240::Median test_median_1, test_median_2;
  // and address with parent's pointer
  csce240::Statistic *test_stat_1 = &test_median_1;
  csce240::Statistic *test_stat_2 = &test_median_2;

  // load Medians using parent pointer from test data above
  LoadMedian(kData1, kSize1, test_stat_1);
  LoadMedian(kData2, kSize2, test_stat_2);

  std::cout << "Testing csce240::Median::Calculate()" << std::endl;

  if (TestCalculateMedian(test_median_1, kExpected1)
    && TestCalculateMedian(test_median_2, kExpected2)) {
    std::cout << "  PASSED" << std::endl;

    return 0;
  }

  std::cout << "  FAILED" << std::endl;

  return 1;
}


void LoadMedian(const double* data,
                std::size_t size,
                csce240::Statistic* stat) {
  for (const double* itr = data; itr != data + size; ++itr)
    stat->Collect(*itr);
}


bool TestCalculateMedian(const csce240::Statistic& stat, double expected) {
  const double kActual = stat.Calculate();

  if (kActual != expected) {
    std::cout << "  Expected: " << expected << ", Actual: " << kActual
      << std::endl;

    return false;
  }

  return true;
}

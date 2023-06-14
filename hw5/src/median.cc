// Copyright 2023 Aidan Hall

#include <hw5/inc/median.h>
#include <algorithm>

namespace csce240 {

Median::Median() {
  // Constructor implementation
}

Median::~Median() {
  // Destructor implementation
}

void Median::Collect(double value) {
  data_.push_back(value);
}

double Median::Calculate() const {
  if (data_.empty()) {
    // Handle the case when the data collection is empty
    return 0.0;
  }

  // Sort the data collection
  std::vector<double> sortedData = data_;
  std::sort(sortedData.begin(), sortedData.end());

  // Calculate the median based on the sorted data
  std::size_t size = sortedData.size();
  std::size_t middle = size / 2;

  if (size % 2 == 0) {
    // If the size is even, take the average of the two middle values
    return (sortedData[middle - 1] + sortedData[middle]) / 2.0;
  } else {
    // If the size is odd, return the middle value
    return sortedData[middle];
  }
}

double Median::operator[](std::size_t index) const {
  if (index >= data_.size()) {
    // Handle the case when the index is out of range
    return 0.0;
  }

  // Return the value at the specified index
  return data_[index];
}

}  // namespace csce240

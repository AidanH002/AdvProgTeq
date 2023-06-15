// Copyright 2023 Aidan hall

#include <cstddef>
#include <iostream>
#include <ostream>

struct Point2d {
  inline explicit Point2d(double x_val, double y_val)  : x(x_val), y(y_val) {
  }
  double x, y;
};

//  these lines of code define two structs, Point2d and Vector2d,
//  with member variables representing coordinates
//  or components in two-dimensional space.

struct Vector2d {
  inline explicit Vector2d(double x_val, double y_val)  : x(x_val), y(y_val) {
  }
  double x, y;
};

inline const Point2d operator+(const Point2d& lhs, const Vector2d& rhs) {
  return Point2d(lhs.x + rhs.x, lhs.y + rhs.y);
}
// This line defines the overloaded +
// operator for adding two Point2d objects.

inline const Vector2d operator-(const Point2d& lhs, const Point2d& rhs) {
  return Vector2d(lhs.x - rhs.x, lhs.y - rhs.y);
}
//  This line defines the overloaded -
//  operator for subtracting two Point2d objects.
//  The operator returns a new Vector2d object that
//  represents the difference between the coordinates

inline std::ostream& operator<<(std::ostream& lhs, const Point2d& rhs) {
  return lhs << '(' << rhs.x << ", " << rhs.y << ')';
}
//  This line defines the overloaded output operator (<<) for Point2d objects.
//  It takes an std::ostream object (lhs) as the left-hand side operand
//  and a Point2d object (rhs) as the right-hand side operand.

int main(int argc, char* argv[]) {
  Point2d square[] = {
    Point2d(0, 0), Point2d(0, 0), Point2d(0, 0), Point2d(0, 0)
  };
  Vector2d compass[] = {
    Vector2d(0, 1), Vector2d(0, -1), Vector2d(1, 0), Vector2d(0, 0)
  };
  const Point2d* square_end = square + 4;
  // This line points to the end of the square array,
  // making the program only move up to four spaces.

  // The above lines are initializing the two arrays 'square' and 'compass'

  square[1] = square[0] + compass[2];
  square[2] = square[1] + compass[0];

  compass[3] = square[3] - square[1];

  square[3] = square[2] + compass[3];
  square[0] = square[3] + compass[1];

// these lines of code are manipulating points and vectors to
// perform translations and modifications in two-dimensional space

  for (const Point2d* itr = square; itr != square_end; ++itr) {
    std::cout << *itr;
    if (itr != square_end - 1)
      std::cout << "->";
  }

//   this code iterates over the square array,
//   printing each Point2d object to the standard output,
//   with an arrow symbol "->" between the elements except for the last one.

  return 0;
}

// Output of this program is : (0, 0)->(1, 0)->(1, 1)->(0, 1)

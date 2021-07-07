#ifndef CROSS_H
#define CROSS_H

#include "Cube.hpp"

class Cross {
public:
  static void solveCross(CubeS&);
  static int checkCross(CubeS&);
  static void solveEdge(CubeS&);
};

#endif

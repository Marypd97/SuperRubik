#ifndef PLL_H
#define PLL_H

#include "Cube.hpp"

class PLL {

public:
  static void solvePLL(CubeS &);
  static void adjustUFace(CubeS &);
  static void solveCorners(CubeS &);
  static int checkCorners(CubeS &);
  static int checkEdges(CubeS &);
  static void solveEdges(CubeS &);
};

#endif

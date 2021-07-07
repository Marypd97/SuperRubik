#ifndef EDGES_H
#define EDGES_H

#include "Cube.hpp"

class Edges {

public:
  static void solveEdges(CubeS &cube);
private:
  static void solveEdge(CubeS &cube);
  static int checkEdges(CubeS &cube);
};

#endif

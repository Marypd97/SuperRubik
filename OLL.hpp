#ifndef OLL_H
#define OLL_H

#include <iostream>
#include "Cube.hpp"
#include <iostream>

class OLL {

public:
  static void solveOLL(CubeS&);
private:
  static int findState(CubeS&); //Rotate U 4 times, check each cube state against file
  static int findEdges(CubeS&);
  static void solveCase(CubeS&, int);
  static int checkOLL(CubeS&);
  static int checkEdges(CubeS&);
};

#endif

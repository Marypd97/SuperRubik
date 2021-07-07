#ifndef CORNERS_H
#define CORNERS_H

#include "Cube.hpp"
#include "Cross.hpp"

class Corners {

public:
  static void solveCorners(CubeS&);
private:
  static int checkCorners(CubeS&);
  static int checkBottomLayer(CubeS &cube);

};

#endif

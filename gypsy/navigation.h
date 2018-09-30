#ifndef _NAVIGATION_H
#define _NAVIGATION_H

// Includes
#include "double_list.h"

// Structure for each node
typedef struct point {
  // X & Y cordinates
  float x;
  float y;
  
  // Is this a waypoint
  boolean waypoint;
} point;

// Function Prototypes
float calculate_cte(DoubleNode<point> *&, float, float);
void smooth_path(DoubleList<point> *, float, float, float);
void fill_route(DoubleList<point> *, const point *, const int);

// Constant Definitions


#endif

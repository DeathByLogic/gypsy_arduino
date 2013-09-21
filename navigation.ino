#include "navigation.h"

DoubleList<point> route;
//DoubleList<point> org_list;

// Box
point box_path[16] = {{0, 0, true}, {25, 0, false}, {50, 0, false}, {50, 25, false}, {50, 50, false}, {50, 75, false}, {50, 100, false}, {25, 100, false}, 
                      {0, 100, false}, {-25, 100, false}, {-50, 100, false}, {-50, 75, false}, {-50, 50, false}, {-50, 25, false}, {-50, 0, false}, {-25, 0, false}};

// Figure 8
point fig8_path[16] = {{0, 0, true}, {25, 0, false}, {50, 0, false}, {50, 25, false}, {50, 50, false}, {25, 50, false}, {0, 50, false}, {0, 25, false},
                       {0, 0, false}, {0, -25, false}, {0, -50, false}, {-25, -50, false}, {-50, -50, false}, {-50, -25, false}, {-50, 0, false}, {-25, 0, false}};

// Calculate the cross track error
float calculate_cte(DoubleNode<point> *&node, const float current_x, const float current_y) {
  float x1, y1, x2, y2;
  float Rx, Ry;
  float Dx, Dy;
  float u;
  float cte;
  
  // If not the last node
  if (node->next() != NULL) {  
    // Store current point and next point locations
    x1 = node->value.x;
    y1 = node->value.y;
    
    x2 = node->next()->value.x;
    y2 = node->next()->value.y;
    
    // Calculate values
    Rx = current_x - x1;
    Ry = current_y - y1;
    
    Dx = x2 - x1;
    Dy = y2 - y1;
    
    u = (Rx * Dx + Ry * Dy) / (Dx * Dx + Dy * Dy);
  
    // If past current point then move to next
    if (u > 1.0) {
      node = node->next();
    }
    
    // Calcualte cte
    cte = (Ry * Dx - Rx * Dy) / sqrt(Dx * Dx + Dy * Dy);
  } else {
    cte = 0.0;
  }
    
  return cte;
}

// Smooth the path
void smooth_path(DoubleList<point> *sth_list, float tolerance, float weight_data, float weight_smooth) {
  float change = tolerance;
  float aux_x, aux_y;
  
  // Create a temporary list
  DoubleList<point> org_list;
 
  // Pointer to current nodes
  DoubleNode<point> *sth_node;
  DoubleNode<point> *org_node;

  // Create a duplicate list
  for (DoubleNode<point> *node = sth_list->first(); node != NULL; node = node->next()) {
    org_list.addLast(node->value);
  }

  // Smooth path
  while (change >= tolerance) {
    change = 0.0;
    
    // Assign second node to pointers
    sth_node = sth_list->first();
    org_node = org_list.first();
    
    // Loop untill second to last node
    while (sth_node != NULL) {
      // Smooth current point only if not a waypoint
      if ((sth_node != sth_list->first()) && (sth_node != sth_list->last()) && (!sth_node->value.waypoint)) {
        // Save previous values
        aux_x = sth_node->value.x;
        aux_y = sth_node->value.y;
        
        // Smooth x
        sth_node->value.x += weight_data * (org_node->value.x - sth_node->value.x);
        sth_node->value.x += weight_smooth * (sth_node->prev()->value.x + sth_node->next()->value.x - (2.0 * sth_node->value.x));
        
        // Smooth y
        sth_node->value.y += weight_data * (org_node->value.y - sth_node->value.y);
        sth_node->value.y += weight_smooth * (sth_node->prev()->value.y + sth_node->next()->value.y - (2.0 * sth_node->value.y));
        
        // Calculate change
        change += abs(aux_x - sth_node->value.x);
        change += abs(aux_y - sth_node->value.y);
      }
      
      // Move to next node
      sth_node = sth_node->next();
      org_node = org_node->next();
    }
  }
}

void fill_route(DoubleList<point> *list, const point *route_points, const int length) {
  for (int i = 0; i < length; i++) {
     list->addLast(route_points[i]);
  }
}

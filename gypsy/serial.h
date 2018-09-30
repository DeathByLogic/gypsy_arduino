#ifndef _SERIAL_H
#define _SERIAL_H

// Includes
#include "double_list.h"

// Function Prototypes
void serial_init();
void serial_write_float(float);
void serial_write_location();
void serial_print_location();
void serial_print_path(DoubleList<point> *);
void serial_print_rev_path(DoubleList<point> *);
void serial_print_pointers(DoubleList<point> *);

// Constant Definitions
#define BAUD_RATE 57600

#endif

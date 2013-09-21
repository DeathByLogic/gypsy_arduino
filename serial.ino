#include "serial.h"

// Init debug serial port
void serial_init() {
  Serial.begin(BAUD_RATE);
}

// Write current location 
void serial_write_location() {
  serial_write_float(sense_x);
  serial_write_float(sense_y);
  serial_write_float(sense_theta);
  
  Serial.println("");
}

// Print location to debug window
void serial_print_location() {
  Serial.print("x: ");
  Serial.print(sense_x, DEC);
  Serial.print(" y: ");
  Serial.print(sense_y, DEC);
  Serial.print(" o: ");
  Serial.print(sense_theta, DEC);
  Serial.println("");
}

// Print path to debug
void serial_print_path(DoubleList<point> *list) {
  int i = 1;
  
  // Print Header
  serial_print_break();
  Serial.println("List Data");
  serial_print_break();
  
  for (DoubleNode<point> *node = list->first(); node != NULL; node = node->next()) {
    Serial.print(i++);Serial.print(") ");
    Serial.print("x: ");Serial.print(node->value.x);Serial.print(" ");
    Serial.print("y: ");Serial.print(node->value.y);Serial.print(" ");
    Serial.print("f: ");Serial.print(node->value.waypoint);Serial.println();
  }
}

// Print path to debug
void serial_print_rev_path(DoubleList<point> *list) {
  int i = 1;
  // Print Header
  serial_print_break();
  Serial.println("List Data (Rev)");
  serial_print_break();
  
  for (DoubleNode<point> *node = list->last(); node != NULL; node = node->prev()) {
    Serial.print(i++);Serial.print(") ");
    Serial.print("x: ");Serial.print(node->value.x);Serial.print(" ");
    Serial.print("y: ");Serial.print(node->value.y);Serial.print(" ");
    Serial.print("f: ");Serial.print(node->value.waypoint);Serial.println();
  }
}

// Print path to debug
void serial_print_pointers(DoubleList<point> *list) {
  int i = 1;
  // Print Header
  serial_print_break();
  Serial.println("List Pointers");
  serial_print_break();
  
  for (DoubleNode<point> *node = list->first(); node != NULL; node = node->next()) {
    Serial.print(i++);Serial.print(") ");
    Serial.print("p: ");Serial.print((uint16_t)node->prev(), HEX);Serial.print(" ");
    Serial.print("c: ");Serial.print((uint16_t)node, HEX);Serial.print(" ");
    Serial.print("n: ");Serial.print((uint16_t)node->next(), HEX);Serial.println();
  }
}

// Write data as binary floats to serial port
void serial_write_float(float fVal) {
  byte * bVal = (byte *) &fVal;
  
  for (int i = 0; i < 4; i++)
    Serial.write(bVal[i]);
}

void serial_print_break() {
  Serial.println("=============================="); 
}

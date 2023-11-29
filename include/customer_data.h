#ifndef CUSTOMER_DATA_H
#define CUSTOMER_DATA_H

class Customer {
public:
  unsigned int paid;
  Message *list;
};

#define scrollFlag 1
#define blinkFLag 2
#define evenOnlyFlag 4
#define oddOnlyFlag 8

class Message { //make message struct or class?
public:
  char messageText[40]; //how to handle string in avr?
  char flags;
};

#endif
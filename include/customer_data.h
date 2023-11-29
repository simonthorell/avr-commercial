#ifndef CUSTOMER_DATA_H
#define CUSTOMER_DATA_H

#define scrollFlag 1
#define blinkFLag 2
#define evenOnlyFlag 4
#define oddOnlyFlag 8

class Message { //make message struct or class?
public:
  void setMessage(char messageText[]);
  char *getMessage();

private:
  char messageText[40]; //how to handle string in avr?
  char flags;
};

class Customer {
public:
  Customer(unsigned int paid){

  }
  Message* getList();

private:
  unsigned int paid;
  Message list[5];
};

#endif
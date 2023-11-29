#include <avr/io.h>
#include "customer_data.h"
#include <string.h>

void Message::setMessage(char messageText[]){
    strcpy(this->messageText, messageText);
}
char* Message::getMessage(){
    return messageText;
}

Message* Customer::getList(){
    return list;
}
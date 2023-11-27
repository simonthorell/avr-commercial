### GROUP MEMBERS
Simon Thorell  
Robert Krantz  
Emil Kool  
Nicole Nilsson  

### BASIC OUTLINE
The main loop
```
void loop() {
  arrayMedKunder[];
  unsigned int lastShown;
  loop {
    hitta randomkund;
    dubbelkolla att den inte visades senast

        slumpa kundens medellande kolla flaggor för scroll,
        blink osv visa text + flaggor vänta 20sec
  }
}
```

Customer class
```
class customer {
public:
  unsigned int paid;
  const char *messages;
};
```

Message class
```
#define scrollFlag 1
#define blinkFLag 2
#define evenOnlyFlag 4
#define oddOnlyFlag 8

class message {
public:
  std::string messageText;
  char flags;
};
```

#include "avr_random_thingy.h"
#include "customer_data.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Create an instance of the LCD
  HD44780 lcd;
  // Initialize & clear the LCD
  lcd.Initialize();
  lcd.Clear();

  char str[] = "pFactors of 500";

  lcd.WriteText(str);
  lcd.GoTo(0, 1);

  uint16_t *factorPtrArray[2];

  factorPtrArray[0] = factorize(420, &lcd);
  factorPtrArray[1] = factorize(430, &lcd);
  lcd.Clear();
  lcd.GoTo(0, 0);
  removeCommonFactors(factorPtrArray, 2, &lcd);

  lcd.Clear();
  lcd.GoTo(0, 0);

  char buff1[10];
  for (uint8_t i = 0; i < 25; i++) {
    if (factorPtrArray[0][i] != 0) {
      sprintf(buff1, "%dx%d ", deFactorize(i), factorPtrArray[0][i]);
      lcd.WriteText(buff1);
    }
  }

  lcd.GoTo(0, 1);
  char buff2[10];
  for (uint8_t i = 0; i < 25; i++) {
    if (factorPtrArray[1][i] != 0) {
      sprintf(buff2, "%dx%d ", deFactorize(i), factorPtrArray[1][i]);
      lcd.WriteText(buff2);
    }
  }

  free(factorPtrArray[0]);
  free(factorPtrArray[1]);

  // int i = 0;
  while (1) {
    // LOOP FOR TESTING
    // Customer customer = getCustomer(i);
    //
    // if(customer.displayProperties[i] == SCROLLING) {
    //     displayScrollingText(&lcd, customer.billboards[i],
    //     sizeof(customer.billboards[i]));
    // } else if (customer.displayProperties[i] == STATIC) {
    //     displayStaticText(&lcd, customer.billboards[i]);
    // } else if (customer.displayProperties[i] == BLINKING) {
    //     displayBlinkingText(&lcd, customer.billboards[i], 5);
    // } else {
    //     continue;
    // }
    //
    // if (!(i > 1)) {i++;} else {i=0;}
  }

  return 0;
}

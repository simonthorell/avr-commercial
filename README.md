# AVR-GCC LCD Interface Project

## Introduction
This project presents a streamlined solution for programming an LCD1602 display using an Atmega328p   microcontroller with AVR-GCC. Focused on embedded programming in C/C++, it offers a cross-platform   framework suitable for a range of applications in embedded systems development.  

## Wokwi
If you want to try this project in a Wowki project follow the compilation steps and run it in this Wowki.  
`https://wokwi.com/projects/383283130065573889`

## Team Members
- Simon Thorell
- Robert Krantz
- Emil Kool
- Nicole Nilsson

## Project Overview
This project aims to program an LCD1602 display using AVR-GCC for an Atmega328p microcontroller. The   code is written in C/C++ and is designed to be cross-platform, ensuring compatibility with various  operating systems.

## Project Structure
The project is organized into several directories, each containing specific types of files:

### /include
- `avr_random_noise.h`: Header file for the noise class.
- `buttons.h`: Header file for the buttons.
- `customer_data.h`: Header file containing customer data structures.
- `lcd_display_option.h`: Header file for LCD display options.
- `set_Clock.h`: Header file for the function to set time.
- `special_functions.h`: //TODO FIX SOMETHING HERE
- `timer.h`: Header file for the internal timer.

### /libs
- `lcd.cpp`: Source file for the LCD control functions.
- `lcd.h`: Header file for the LCD control functions.

### /src
- `avr_random_noise.cpp`: Implementation of a random class listening to noise from the ADC.
- `buttons.cpp`: Implementation of the button functionality.
- `customer_data.cpp`: Implementation of customer data handling.
- `lcd_display_options.cpp`: Implementation of LCD display options.
- `main.cpp`: The main entry point for the program.
- `set_Clock.cpp`: Implementation of the ability to select the time.
- `special_functions.cpp`: Implements functions that can be triggered by buttons.
- `timer.cpp`: Implementation of the internal timer.

### Root Directory
- `Makefile`: Contains commands to compile the project.
- `README.md`: This file, providing an overview and instructions.

## How to Use
1. Ensure you have AVR-GCC installed on your system.
2. Clone the repository to your local machine.
3. Navigate to the root directory of the project.
4. Run `make` to compile the project.
5. After successful compilation, upload the binary to the Atmega328p microcontroller.
6. The LCD should display the programmed output upon successful upload.

## Cross-Platform Compatibility
This project is designed to be cross-platform. It has been tested on Windows, macOS and archLinux through WSL2, but it should work on other systems where AVR-GCC is supported.

## Contributions
For any contributions or modifications, please contact one of the team members.

## License
License what?! This is free to use!

Thank you for your interest in our AVR-GCC LCD Interface Project!

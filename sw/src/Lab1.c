// ----------------------------------------------------------------------------
// Lab1.c
#include <stdint.h>
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"

void Clock_Delay1ms(uint32_t n);
void LED_Init(void);
void LED_Out(uint32_t data);
void Switch_Init(void);
uint32_t Switch_In(void);

typedef enum {R0, R1, R2} State;

int main(void){
  PLL_Init(Bus80MHz); 
  LED_Init();
  Switch_Init();

  State currentState = R0;
  uint32_t prevSwitch = 0;
  uint32_t currentSwitch;
  uint32_t ledState = 0;

  while(1){
    currentSwitch = Switch_In();

    // Detect rising edge (button press)
    if(currentSwitch && !prevSwitch) {
      // State machine logic
      switch(currentState) {
        case R0:
          currentState = R1;
          break;
        case R1:
          currentState = R2;
          break;
        case R2:
          currentState = R0;
          ledState = !ledState;  // Toggle LED state
          LED_Out(ledState);
          break;
      }
    }

    prevSwitch = currentSwitch;
    Clock_Delay1ms(10); // Debounce delay
  }
}

void LED_Init(void){
    // Write something to initalize the GPIOs that drive the LEDs based on your EID as defined in the lab doc.
    volatile uint32_t delay;
    SYSCTL_RCGCGPIO_R |= 0x04;        // activate clock for Port C
    GPIO_PORTC_DIR_R |= 0x80;         // set PC7 direction to output
    GPIO_PORTC_DEN_R |= 0x80;         // enable PC7 digital port
}

void LED_Out(uint32_t data){
    if(data == 0){
      GPIO_PORTC_DATA_R &= ~0x80;  // Clear PC7 (set to low)
    } else {
      GPIO_PORTC_DATA_R |= 0x80;   // Set PC7 high
    }
}

void Switch_Init(void){
    volatile uint32_t delay;
    SYSCTL_RCGCGPIO_R |= 0x02;        // activate clock for Port B
    delay = SYSCTL_RCGCGPIO_R;        // allow time for clock to start
    GPIO_PORTB_DIR_R &= ~0x10;        // make PB4 input
    GPIO_PORTB_DEN_R |= 0x10;         // enable digital I/O on PB4
}

uint32_t Switch_In(void){
  // write something that reads the state of the GPIO pin as required
    return(GPIO_PORTB_DATA_R & 0x10) >> 4; // 1 if pressed, 0 if not pressed
}


void Clock_Delay(uint32_t ulCount){
  while(ulCount){
    ulCount--;
  }
}

// ------------Clock_Delay1ms------------
// Simple delay function which delays about n milliseconds.
// Inputs: n, number of msec to wait
// Outputs: none
void Clock_Delay1ms(uint32_t n){
  while(n){
    Clock_Delay(23746);  // 1 msec, tuned at 80 MHz, originally part of LCD module
    n--;
  }
}














//// ----------------------------------------------------------------------------
//// Lab1.c
//// Jonathan Valvano
//// July 8, 2024
//// Possible main program to test the lab
//// Feel free to edit this to match your specifications
//#include <stdint.h>
//#include "PLL.h"
//#include "../inc/tm4c123gh6pm.h"
//
//void Clock_Delay1ms(uint32_t n);
//void LED_Init(void);
//void LED_Out(uint32_t data);
//void Switch_Init(void);
//uint32_t Switch_In(void);
//
//int main(void){
//  PLL_Init(Bus80MHz);
//  LED_Init();
//  Switch_Init();
//  // Write something to declare required variables
//  // Write something to initalize the state of the FSM, LEDs, and variables as needed
//
//  uint32_t ledState = 0;
//  uint32_t switchState = 0;
//
//  while(1){
//      // Write something using Switch_In() and LED_Out() to implement the behavior in the lab doc
//      switchState = Switch_In();
//      LED_Out(1);
//
//      if (switchState == 1) {  // if on
//          LED_Out(1);
//      }else{                  // if off
//          LED_Out(0);
//      }
//
//      Clock_Delay1ms(1);  // delay 1ms
//  }
//}
//
//void LED_Init(void){
//    // Write something to initalize the GPIOs that drive the LEDs based on your EID as defined in the lab doc.
//
//    SYSCTL_RCGCGPIO_R |= 0x04;  // activate clock for Port E
//    GPIO_PORTE_DIR_R |= 0x00001000;         // E3 out
//    GPIO_PORTE_DEN_R |= 0x00001000;         // enable digital I/O on E3
//
//}
//void LED_Out(uint32_t data){
//    // write something that sets the state of the GPIO pin as required
//    if (data == 1) {
//        GPIO_PORTE_DATA_R |= 0x00001000;  // E3 on
//    }
//    else {
//        GPIO_PORTE_DATA_R &= ~0x00001000;  // E3 off
//    }
//}
//void Switch_Init(void){
//    // write something to initalize the GPIO that take input from the switches based on your EID as defined in the lab doc
//    SYSCTL_RCGCGPIO_R |= 0x02;  // activate clock for Port C
//    GPIO_PORTE_DIR_R |= 0x00000000;         // C5 out
//    GPIO_PORTE_DEN_R |= 0x00100000;         // enable digital I/O on C5
//
//}
//uint32_t Switch_In(void){
//  // write something that reads the state of the GPIO pin as required
//    return(GPIO_PORTC_DATA_R & 0x00100000) >> 5; // 1(pressed) or 0(not pressed)
//}
//
//void Clock_Delay(uint32_t ulCount){
//  while(ulCount){
//    ulCount--;
//  }
//}
//
//// ------------Clock_Delay1ms------------
//// Simple delay function which delays about n milliseconds.
//// Inputs: n, number of msec to wait
//// Outputs: none
//void Clock_Delay1ms(uint32_t n){
//  while(n){
//    Clock_Delay(23746);  // 1 msec, tuned at 80 MHz, originally part of LCD module
//    n--;
//  }
//}

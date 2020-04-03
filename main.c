#include <16F886.h>
#device ADC=10 *=16  

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES PUT                      //Power Up Timer
#FUSES NOMCLR                   //Master Clear pin not enabled
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NOCPD                    //No EE protection
#FUSES BROWNOUT                 //Brownout reset
#FUSES IESO                     //Internal External Switch Over mode enabled
#FUSES FCMEN                    //Fail-safe clock monitor enabled
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOWRT                    //Program memory not write protected
#FUSES BORV40                   //Brownout reset at 4.0V
#FUSES RESERVED                 //Used to set the reserved FUSE bits
#FUSES INTRC_IO 

#use delay(clock=8M)

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
#include "lcd.c"
#include <stdlib.h>

#define RESET_BUTTON    PIN_d0

int16 _atoi(char* arr, int16 digit){
   int16 ans = 0;
   for(int8 i = 0;i < digit;i++){
      ans *= (int16)10;
      ans += arr[i] - '0';
   }
   return ans;
}

int16 getInput(char* arr){
   char curr = getc();
   int16 cnt = 0;
   int16 digit = 0;
   while(curr != '.'){
      arr[cnt++] = curr;
      digit++;
      curr = getc();
   }
   return digit;
}

void main() {
   lcd_init();
   delay_ms(6);
   printf(lcd_putc,"\fPlease Enter\nrandom seed");
   printf("\fEvery time you send string please type .(dot) at the end\n");
   char seed[10];
   int16 digit = getInput(seed);
   srand(_atoi(seed, digit));
   int16 num = (int16)rand();
   int16 cnt = 0;
   //printf("\fnum : %ld\n",(long long)num);
   printf(lcd_putc,"\fEnter Number\nBtw 0 - 65535");
   char ran[10];
   while(1){
      digit = getInput(ran);
      cnt++;
      int16 input = _atoi(ran, digit);
      //printf("\fran : %ld\n",(long long)_atoi(ran, digit));
      if(input < num){
         printf("\f%ld less than answer\n", (long long)input);
         printf(lcd_putc,"\fless than answer");
      }
      else if(input > num){
         printf("\f%ld greater than answer\n", (long long)input);
         printf(lcd_putc,"\fgreater than answer");
      }
      else{
         printf(lcd_putc,"\fCORRECT\!\nanswered %ld times", (long long)cnt);
         break;
      }
   }
}

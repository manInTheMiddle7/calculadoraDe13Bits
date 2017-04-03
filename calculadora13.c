#include <18F4620.h>
#fuses INTRC_IO, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use FAST_IO(ALL)

void errorDivisor0();

void main (void){
   int16 operando1=0,operando2=0;
   int16 resultado=0;
   int8 tipoOperador=0;
/*
Se asigna al puerto a como salida
se asigna el puerto b(0,1,2,3) como salida y b(4,5,6,7) como entrada
se asigna el puerto e como salida
se asigna puerto d como entrada
puerto c como entrada
*/
   set_tris_a(0b00000000);
   set_tris_b(0b11110000);
   set_tris_e(0b00000000);
   set_tris_d(0b11111111);
// establecer el pin C7 como salida para poder mostrar leds correctamente
   set_tris_c(0b01111111);
   while(true)
   {
   //Tipo De Operacion !!
      delay_ms(20); //Antirebote por software
      if(input(PIN_B4))
      {
         tipoOperador=1;   //suma
      }
      else if(input(PIN_B5))
      {
         tipoOperador=2;   //resta
      }
      else if(input(PIN_B6))
      {
         tipoOperador=3;   //multiplicacion
      }
      else if (input(PIN_B7))
      {
         tipoOperador=4;   //division
      }
      //Obtener valores de los puertos C,D      
       operando1=input_c();
       operando2=input_d();
      
      if(tipoOperador==1)  //operador Suma
      {
            resultado=operando1+operando2;  
      }
      else if(tipoOperador==2) //operador Resta
      {         
            resultado=operando1-operando2;
      }
      else if(tipoOperador==3) //operador multiplicacion
      {
         resultado=operando1*operando2;
      }
      else if(tipoOperador==4) //operador division
      {
         if(operando2==0)  //divisor igual a 0 que es igual a operando2 igual a 0
         {
            errorDivisor0(); 
         }
         else
         {
            resultado=operando1/operando2;   
         }         
      }
/*
salida del la variable resultado por los puertos a(0,1,2,3,4,5) que se asignaron como salida
acarreo de la variable resultado para que los bits 7,8,9,10 de la variable resultado
aparezcan el los puertos b(0,1,2,3)
acarreo de la variable resultado para que los bits 11,12,13 de la variable resultado
aparezcan en el puerto e(0,1,2)
*/
         output_a(resultado);
         output_b(resultado>>6);
         output_e(resultado>>10);     
   }
}   

void errorDivisor0()
{     
   output_high(PIN_A0);
   output_high(PIN_A1);
   output_high(PIN_A2);
   output_high(PIN_A3);
   output_high(PIN_A4);
   output_high(PIN_A5);
   output_high(PIN_B0);
   output_high(PIN_B1);
   output_high(PIN_B2);
   output_high(PIN_B3);
   output_high(PIN_E0);
   output_high(PIN_E1);
   output_high(PIN_E2);
   delay_ms(200); 
   output_low(PIN_A0);
   output_low(PIN_A1);
   output_low(PIN_A2);
   output_low(PIN_A3);
   output_low(PIN_A4);
   output_low(PIN_A5);
   output_low(PIN_B0);
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   output_low(PIN_E0);
   output_low(PIN_E1);
   output_low(PIN_E2);
   delay_ms(200);   
}

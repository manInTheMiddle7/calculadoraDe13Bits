#include <18F4620.h>
#fuses INTRC_IO, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)
#use FAST_IO(ALL)
   
void main (void){
   int16 operando1=0,operando2=0;
   int16 resultado=0;
   int8 tipoOperador=0;
   
   set_tris_a(0b00000000);
   set_tris_b(0b11110000);
   set_tris_e(0b00000000);
   set_tris_d(0b11111111);
   set_tris_c(0b11111111);
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
      
      if(tipoOperador==1)
      {
            resultado=operando1+operando2;  
      }
      else if(tipoOperador==2)
      {
         
            resultado=operando1-operando2;
      }
      else if(tipoOperador==3)
      {
         resultado=operando1*operando2;
      }
      else if(tipoOperador==4)
      {
            resultado=operando1/operando2;
      }    
      
        output_a(resultado);
        output_b(resultado>>6);
        output_e(resultado>>10);     
   }
}   

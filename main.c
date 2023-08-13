#include <16f877.h>
#fuses XT,NOPROTECT,NOBROWNOUT,NOWDT,NOLVP,NOWRT,NODEBUG,NOCPD, NOPUT
#use delay(clock=1000000)
#use fast_io(b)
#use fast_io(d)

#define button1 pin_b4
#define button2 pin_b5
#define button3 pin_b6
#define button4 pin_b7

#define display1 pin_b0
#define display2 pin_b1
#define display3 pin_b2
#define display4 pin_b3

int button = 0;
int digit[] = {0b1000000,0b1111001,0b0100100,0b0110000,0b0011001,0b0010010,0b0000010,0b1111000,0b0000000,0b0010000};
int binler=0, yuzler=0, onlar=0, birler=0;

#int_rb
void rb_kesme() {
   if (input(button1)){
      button=1;
   }
   else if (input(button2)){
      button=2;
   }
   else if (input(button3)){
      button=3;
   }
   else if (input(button4)){
      button=4;
   }
   else{
      button=0;
   }
   if (button == 1) {
      birler++;
      if (birler > 9) {
         birler = 0;
         onlar++;
         if (onlar > 9) {
            onlar = 0;
            yuzler++;
            if (yuzler > 9) {
               yuzler = 0;
               binler++;
               if (binler > 9) {
                  binler = 0;
               }
            }
         }
      }
   } else if (button == 2) {
      onlar++;
      if (onlar > 9) {
         onlar = 0;
         yuzler++;
         if (yuzler > 9) {
            yuzler = 0;
            binler++;
            if (binler > 9) {
               binler = 0;
            }
         }
      }
   } else if (button == 3) {
      yuzler++;
      if (yuzler > 9) {
         yuzler = 0;
         binler++;
         if (binler > 9) {
            binler = 0;
         }
      }
   } else if (button == 4) {
      binler++;
      if (binler > 9) {
         binler = 0;
      }
   }
   clear_interrupt(INT_RB);
}


#int_timer0
void timer_kesme(){
   set_timer0(131);
   
   
   output_high(display1);
   output_d(digit[binler]);
   delay_ms(5);
   output_low(display1);

   output_high(display2);
   output_d(digit[yuzler]);
   delay_ms(5);
   output_low(display2);

   output_high(display3);
   output_d(digit[onlar]);
   delay_ms(5);
   output_low(display3);

   output_high(display4);
   output_d(digit[birler]);
   delay_ms(5);
   output_low(display4);

   clear_interrupt(INT_TIMER0);
}

void main() {
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED, 0, 1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);

   set_tris_b(0xF0);
   set_tris_d(0x00);

   output_low(display1);
   output_low(display2);
   output_low(display3);
   output_low(display4);

   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_2);
   set_timer0(131);
   
   enable_interrupts(INT_timer0);
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);

   while (1);
}


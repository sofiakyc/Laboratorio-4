#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id, thread3_id, thread4_id;

typedef struct Led
{
  uint8_t led;
  int periodo;
}Led;

void AcendeLed(void *arg)
{
  Led *instanciaLed = (Led *)arg;
  
  uint8_t state = 0;
  uint32_t tick;
  
  while(1){
    tick = osKernelGetTickCount();
    
    state ^= instanciaLed->led;
    LEDWrite(instanciaLed->led, state);
    
    osDelayUntil(instanciaLed->periodo + tick);
    //osDelay(100);
  } // while
}

void main(void){
  struct Led led1, led2, led3, led4;
  led1.led = LED1;
  led2.led = LED2;
  led3.led = LED3;
  led4.led = LED4;
  
  led1.periodo = 200;
  led2.periodo = 300;
  led3.periodo = 500;
  led4.periodo = 700;
    
  LEDInit(led1.led | led2.led | led3.led | led4.led);
  
  osKernelInitialize();

  thread1_id = osThreadNew(AcendeLed, &led1, NULL);
  thread2_id = osThreadNew(AcendeLed, &led2, NULL);
  thread3_id = osThreadNew(AcendeLed, &led3, NULL);
  thread4_id = osThreadNew(AcendeLed, &led4, NULL);

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main


/*
2.
- OS_TICK_FREQ?
	se a constante OS_TICK_FREQ não tiver sido definida, é para definir com valor 1000
– OS_THREAD_NUM?
	se a constante OS_THREAD_NUM não tiver sido definida, é para definir com valor 1
– OS_THREAD_DEF_STACK_NUM
	se a constante OS_THREAD_DEF_STACK_NUM não tiver sido definida, é para definir com valor 1
3. Baixou a frequência de tick, deixando a piscada do led mais lento.

4. thread 1: ticks para processar o job de interagir com led + 100
thread 2: 100;
*/

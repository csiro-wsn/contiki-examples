/**
 * \file
 *         A simple Contiki application showing serial interfacing
 * \author
 *         mds
 */
#include "contiki.h"
#include "dev/serial-line.h"
#include "buzzer.h"
#include <stdio.h> /* For printf() */
#include "dev/cc26xx-uart.h"

/*---------------------------------------------------------------------------*/
PROCESS(test_serial, "Serial line test process");
AUTOSTART_PROCESSES(&test_serial);
/*---------------------------------------------------------------------------*/
//Serial Interface
PROCESS_THREAD(test_serial, ev, data) {

	PROCESS_BEGIN();

	cc26xx_uart_set_input(serial_line_input_byte);	//Initalise UART in serial driver
	
   	while(1) {

     	PROCESS_YIELD();	//Let other threads run

		//Wait for event triggered by serial input
     	
		//******************************************
		//NOTE: MUST HOLD CTRL and then press ENTER 
		//at the end of typing for the serial driver 
		//to work. Serial driver expects 0x0A as
		//last character, to tigger the event.
		//******************************************
		if(ev == serial_line_event_message) {
       		printf("received line: %s\n\r", (char *)data);
			buzzer_start(1000);
     	}
	
		clock_wait(CLOCK_SECOND/10);
		buzzer_stop();
   	}
   	PROCESS_END();
}
/*---------------------------------------------------------------------------*/

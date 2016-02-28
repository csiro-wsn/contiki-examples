/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         mds
 */

#include "contiki.h"
#include <stdio.h> /* For printf() */
#include "dev/leds.h"

/*---------------------------------------------------------------------------*/
PROCESS(hello_world_process, "Hello world process");
AUTOSTART_PROCESSES(&hello_world_process);
/*---------------------------------------------------------------------------*/
//Hello World Thread
PROCESS_THREAD(hello_world_process, ev, data) {

  	PROCESS_BEGIN();	//Start of thread

	leds_off(LEDS_RED);		//Turn LED off.

	//Processing loop of thread
	while (1) {
  		printf("Hello, world\n\r");

		leds_toggle(LEDS_RED);		//Toggle Red LED
		clock_wait(CLOCK_SECOND);	//Wait for 1 second
	}

  	PROCESS_END();		//End of thread
}
/*---------------------------------------------------------------------------*/

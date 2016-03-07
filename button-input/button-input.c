/**
 * \file
 *         A very simple Contiki application showing to use the sensor tag left push button
 *         NOTE: Right push button is used to reset the sensor tag.
 * \author
 *         mds
 */

#include "contiki.h"
#include <stdio.h> /* For printf() */
#include "dev/leds.h"
#include "button-sensor.h"

/*---------------------------------------------------------------------------*/
PROCESS(button_input_process, "Button process");
AUTOSTART_PROCESSES(&button_input_process);
/*---------------------------------------------------------------------------*/
//Button INput Thread
PROCESS_THREAD(button_input_process, ev, data) {

  	PROCESS_BEGIN();	//Start of thread

	leds_off(LEDS_GREEN);		//Turn LED off.

	//Processing loop of thread
	while (1) {

        //Wait for event to occur
		PROCESS_YIELD();
  		
        //Check if sensor event has occured
		if(ev == sensors_event) {
            
            //Check if left push button event has occured
      		if(data == &button_left_sensor) {
        		printf("Left: Pin %d, press duration %d clock ticks\n", (&button_left_sensor)->value(BUTTON_SENSOR_VALUE_STATE), (&button_left_sensor)->value(BUTTON_SENSOR_VALUE_DURATION));
                
                leds_toggle(LEDS_GREEN);    //Toggle LED
			}
		}
    }

  	PROCESS_END();		//End of thread
}


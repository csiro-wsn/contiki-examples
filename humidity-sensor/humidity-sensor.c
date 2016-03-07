/**
 * \file
 *         Humidity Sensor Interface program for sensortag
 *         
 * \author
 *         mds
 */

#include "contiki.h"
#include "sys/etimer.h"
#include "sys/ctimer.h"
#include "dev/leds.h"
#include "dev/watchdog.h"
#include "random.h"
#include "board-peripherals.h"

#include "ti-lib.h"

#include <stdio.h>
#include <stdint.h>

static struct etimer et;

PROCESS(humidity_sensor_process, "humidity sensor process");
AUTOSTART_PROCESSES(&humidity_sensor_process);

static struct ctimer hdc_timer;		//Callback timer


//Intialise Humidity sensor
static void humidity_init(void *not_used) {
  SENSORS_ACTIVATE(hdc_1000_sensor);
}


PROCESS_THREAD(humidity_sensor_process, ev, data) {
	
	int humidity_temp_val;
	int humidity_val;

  	PROCESS_BEGIN();

  	etimer_set(&et, CLOCK_SECOND * 2);	//Set event timer for 20s interval.
	SENSORS_ACTIVATE(hdc_1000_sensor);	//Initialise humidity sensor

  	while(1) {

    	PROCESS_YIELD();

		//Flash Green LED every 2s.
		if(ev == PROCESS_EVENT_TIMER) {

			if(data == &et) {
				leds_toggle(LEDS_GREEN);
				etimer_set(&et, CLOCK_SECOND * 2);		//Reset event timer
			}

		//Check for sensor event
		} else if(ev == sensors_event) {

			//Check for Humidity reading
		  	if(ev == sensors_event && data == &hdc_1000_sensor) {

		    	humidity_temp_val = hdc_1000_sensor.value(HDC_1000_SENSOR_TYPE_TEMP);		//Read Humidity Temp value
				humidity_val = hdc_1000_sensor.value(HDC_1000_SENSOR_TYPE_HUMIDITY);		//Read Humidity value

				//Display values
				printf("Humidity=%d.%02d %%RH, Temp:%d.%02d C\n\r", humidity_val/100, humidity_val%100, humidity_temp_val/100, humidity_temp_val%100);

				ctimer_set(&hdc_timer, CLOCK_SECOND*5, humidity_init, NULL);	//Callback timer for humidity sensor
			}
		}
	}

  PROCESS_END();
}



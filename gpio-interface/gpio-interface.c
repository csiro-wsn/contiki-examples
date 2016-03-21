/**
 * \file
 *         A very simple Contiki application to write and read the sensortag's gpio pins (Grove2 connector)
 * \author
 *         mds
 */

#include "contiki.h"
#include <stdio.h>
#include "dev/leds.h"
#include "sensortag/board-peripherals.h"
#include "sensortag/cc2650/board.h"
#include "lib/cc26xxware/driverlib/gpio.h"
#include "ti-lib.h"

//create masks for Grove2 connector (debug devpack)
#define SENSORTAG_GROVE2_DP2	1 << BOARD_IOID_DP2
#define SENSORTAG_GROVE2_DP3	1 << BOARD_IOID_DP3

/*---------------------------------------------------------------------------*/
PROCESS(gpio_interface_process, "GPIO process");
AUTOSTART_PROCESSES(&gpio_interface_process);
/*---------------------------------------------------------------------------*/
//GPIO Interface Thread
PROCESS_THREAD(gpio_interface_process, ev, data) {

    PROCESS_BEGIN();
    
    // set pin DP2 as output, DP3 as input
    GPIODirModeSet(SENSORTAG_GROVE2_DP2, GPIO_DIR_MODE_OUT);
    GPIODirModeSet(SENSORTAG_GROVE2_DP3, GPIO_DIR_MODE_IN);

	//Set pin DP2 low
	GPIOPinWrite(SENSORTAG_GROVE2_DP2, 0);
	
	while(1) {

		// Read pin DP3 (gpio register must be masked and shifted left, to return 1 or 0.
		printf("GPIO DP3 value %X\n\r", (unsigned int)(GPIOPinRead(SENSORTAG_GROVE2_DP3) >> BOARD_IOID_DP3) & 0x01);

		// Toggle value of DP2 
        GPIOPinToggle(SENSORTAG_GROVE2_DP2);

		leds_toggle(LEDS_RED);		//Toggle Red LED
		clock_wait(CLOCK_SECOND);	//Wait for 1 second
	}

    PROCESS_END();
}


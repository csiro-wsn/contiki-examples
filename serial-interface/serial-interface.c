/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
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

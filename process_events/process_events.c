/**
 * \file
 *        An example showing events work in Contiki.
 * \author
 *         mds
 */
#include "contiki.h"
#include <stdio.h> /* For printf() */

/*---------------------------------------------------------------------------*/
PROCESS(give_process, "give process");
PROCESS(take_process, "take process");
AUTOSTART_PROCESSES(&take_process, &give_process);
/*---------------------------------------------------------------------------*/

//Take process - waits for message.
PROCESS_THREAD(take_process, ev, data) {

   	PROCESS_BEGIN();

	printf("take process\n\r");
 
   	while(1) {

		//Wait for any event to occur
		PROCESS_WAIT_EVENT();
    	printf("Take event number:%d msg %s\n\r", ev, (char *) data);
   
	}
 
   	PROCESS_END();
}

static unsigned char msg_cnt = 0;		//message count

//Give process - sends message to take process (a to z).
PROCESS_THREAD(give_process, ev, data) {

	
	PROCESS_BEGIN();

	char msg;		//message to be sent

	printf("give process\n\r");
	
   	while(1) {

		msg = (char)('a' + msg_cnt);	//create message to be sent

		printf("Give event: %c\n\r", msg);

		//give event and message		
		process_post_synch(&take_process, PROCESS_EVENT_CONTINUE, &msg);
		
		clock_wait(CLOCK_SECOND);			//Delay for 1 second
		msg_cnt = (msg_cnt + 1)%26;			//Create next message - only send a to z
	}

	PROCESS_END();
}


/**
 * \file
 *         A TCP socket echo server. Listens and replies on port 8080
 * \author
 *         mds
 */

#include "contiki-net.h"
#include "sys/cc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT 8080

static struct tcp_socket socket;

#define INPUTBUFSIZE 400
static uint8_t inputbuf[INPUTBUFSIZE];

#define OUTPUTBUFSIZE 400
static uint8_t outputbuf[OUTPUTBUFSIZE];

PROCESS(tcp_server_process, "TCP echo process");
AUTOSTART_PROCESSES(&tcp_server_process);
static uint8_t get_received;
static int bytes_to_send;

/*---------------------------------------------------------------------------*/
//Input data handler
static int input(struct tcp_socket *s, void *ptr, const uint8_t *inputptr, int inputdatalen) {

  printf("input %d bytes '%s'\n\r", inputdatalen, inputptr);

	tcp_socket_send_str(&socket, inputptr);	//Reflect byte

	//Clear buffer
	memset(inputptr, 0, inputdatalen);
    return 0; // all data consumed 
}

/*---------------------------------------------------------------------------*/
//Event handler
static void event(struct tcp_socket *s, void *ptr, tcp_socket_event_t ev) {
  printf("event %d\n", ev);
}

/*---------------------------------------------------------------------------*/
//TCP Server process
PROCESS_THREAD(tcp_server_process, ev, data) {

  	PROCESS_BEGIN();

	//Register TCP socket
  	tcp_socket_register(&socket, NULL,
               inputbuf, sizeof(inputbuf),
               outputbuf, sizeof(outputbuf),
               input, event);
  	tcp_socket_listen(&socket, SERVER_PORT);

	printf("Listening on %d\n", SERVER_PORT);
	
	while(1) {
	
		//Wait for event to occur
		PROCESS_PAUSE();
	}
	PROCESS_END();
}
/*---------------------------------------------------------------------------*/

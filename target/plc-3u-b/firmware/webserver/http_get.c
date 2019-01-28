/*----------------------------------------------------------------------------
 Copyright:      Radig Ulrich  mailto: mail@ulrichradig.de
 Author:         Radig Ulrich
 Remarks:        
 known Problems: none
 Version:        12.11.2007
 Description:    HTTP-Client (empfang einer Webseite)

 Dieses Programm ist freie Software. Sie können es unter den Bedingungen der 
 GNU General Public License, wie von der Free Software Foundation veröffentlicht, 
 weitergeben und/oder modifizieren, entweder gemäß Version 2 der Lizenz oder 
 (nach Ihrer Option) jeder späteren Version. 

 Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, 
 daß es Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, 
 sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT 
 FÜR EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License. 

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem 
 Programm erhalten haben. 
 Falls nicht, schreiben Sie an die Free Software Foundation, 
 Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA. 
------------------------------------------------------------------------------*/

#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "stack.h"
#include "usart.h"
#include "timer.h"
#include "http_get.h" 


PROGMEM const char PUT_REQUEST[] = {
    "PUT /sys/water-leaks/sensors/FF HTTP/1.1\r\n"
    "Content-Length: 2\r\n"
    "\r\n"
    "00"
};

volatile unsigned int http_get_state = 0;


void httpc_acknowledge(unsigned char index) {
/*
    for (int a = TCP_DATA_START_VAR; a < TCP_DATA_END_VAR; a++) {
        HTTPC_DEBUG("%c", eth_buffer[a]);
    }
    tcp_entry[index].time = TCP_TIME_OFF;
    tcp_entry[index].status = ACK_FLAG;
    create_new_tcp_packet(0, index);
*/
    tcp_Port_close(index);
}


void notifications__run(void) {
    unsigned long index = MAX_TCP_ENTRY;
    
    if (http_get_state < 1) {
        HTTPC_DEBUG("httpc: ARP lookup for notification server\n\r");
        unsigned int httpc__source_port = 2354;
        add_tcp_app(httpc__source_port, (void(*)(unsigned char))httpc_acknowledge);
        
        // Send ARP request
        if (arp_request(NOTIFICATIONS__SERVER_HOST)) {
            for(unsigned long a = 0;a < 2000000; a++) { asm("nop"); };
            
            tcp_port_open(NOTIFICATIONS__SERVER_HOST, HTONS(NOTIFICATIONS__SERVER_PORT), htons(httpc__source_port));
               
            unsigned char tmp_counter = 0;
            while ((index >= MAX_ARP_ENTRY) && (tcp_entry[index].app_status != 1)) {
                index = tcp_entry_search(NOTIFICATIONS__SERVER_HOST, HTONS(NOTIFICATIONS__SERVER_PORT));
                if (tmp_counter++ > 30) {
                    HTTPC_DEBUG("httpc: tcp entry not found!\r\n");
                    return;
                }
            }
             
            HTTPC_DEBUG("httpc: tcp entry found!\r\n");
            tcp_entry[index].first_ack = 1;
            ++http_get_state;
        }
        else {
            ++http_get_state;
        }
    }
    else if (http_get_state == 20000)  
    {
        HTTPC_DEBUG("httpc: sending HTTP request\r\n");
        index = tcp_entry_search(NOTIFICATIONS__SERVER_HOST, HTONS(NOTIFICATIONS__SERVER_PORT));
        memcpy_P(&eth_buffer[TCP_DATA_START], PUT_REQUEST, (sizeof(PUT_REQUEST)-1));
        tcp_entry[index].status =  ACK_FLAG | PSH_FLAG;
        create_new_tcp_packet((sizeof(PUT_REQUEST)-1), index);
        http_get_state = 20001;
    }
    else if (http_get_state < 20000) http_get_state++; // wait.. ugly
}

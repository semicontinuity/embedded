/*----------------------------------------------------------------------------
 Copyright:      Radig Ulrich  mailto: mail@ulrichradig.de
 Author:         Radig Ulrich
 Remarks:        
 known Problems: none
 Version:        24.10.2007
 Description:    Ethernet Stack

 Dieses Programm ist freie Software. Sie k�nnen es unter den Bedingungen der 
 GNU General Public License, wie von der Free Software Foundation ver�ffentlicht, 
 weitergeben und/oder modifizieren, entweder gem�� Version 2 der Lizenz oder 
 (nach Ihrer Option) jeder sp�teren Version. 

 Die Ver�ffentlichung dieses Programms erfolgt in der Hoffnung, 
 da� es Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, 
 sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT 
 F�R EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License. 

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem 
 Programm erhalten haben. 
 Falls nicht, schreiben Sie an die Free Software Foundation, 
 Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA. 
------------------------------------------------------------------------------*/

/**
 * \addtogroup ethernet Netzwerk
 *
 *	TCP/IP Protokollstapel 
 *
 *
 * @{
 */

/**
 * \addtogroup stack Protokollstapel
 *
 *
 * @{
 */

/**
 * \file
 * stack.c
 *
 * \author Ulrich Radig
 */
#include <stdio.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "networkcard/enc28j60.h"
//#include "networkcard/rtl8019.h"
#include "timer.h"
#include "usart.h"
#include "stack.h"

#if USE_DNS
#include "dns.h"
#endif

TCP_PORT_ITEM TCP_PORT_TABLE[MAX_APP_ENTRY] = //!< TCP Port-Tabelle
{
	{0,0},
	{0,0},
	{0,0} 
};

UDP_PORT_ITEM UDP_PORT_TABLE[MAX_APP_ENTRY] = //!< UDP Port-Tabelle
{
	{0,0},
	{0,0},
	{0,0} 
};

unsigned char myip[4];			//!< meine eigene IP
unsigned char netmask[4];		//!< die Netzwerk Maske
unsigned char router_ip[4];		//!< der Router/Gateway
unsigned char broadcast_ip[4];

unsigned int IP_id_counter = 0;
char eth_buffer[MTU_SIZE+1];	//!< Empfangs- und Sendepuffer f�r Netzwerk

struct arp_table arp_entry[MAX_ARP_ENTRY];	//!< die ARP Tabelle

//TCP Stack Size
//+1 damit eine Verbindung bei vollen Stack abgewiesen werden kann
struct tcp_table tcp_entry[MAX_TCP_ENTRY+1]; 	//!< Tabelle der gerade aktiven TCP Verbindungen

PING_STRUCT ping;

//----------------------------------------------------------------------------
//Converts integer variables to network Byte order
unsigned int htons(unsigned int val)
{
  return HTONS(val);
}
//----------------------------------------------------------------------------
//Converts integer variables to network Byte order
unsigned long htonl(unsigned long val)
{
  return HTONL(val);
}

//----------------------------------------------------------------------------
///Tr�gt Anwendung in Anwendungsliste ein
/**
 *	\ingroup stack
 *	Initialisierung des Netzwerks
 *
 */
void stack_init (void)
{
	//IP, NETMASK und ROUTER_IP aus EEPROM auslesen	
    (*((unsigned long*)&myip[0])) = get_eeprom_value(IP_EEPROM_STORE,MYIP);
	(*((unsigned long*)&netmask[0])) = get_eeprom_value(NETMASK_EEPROM_STORE,NETMASK);
	(*((unsigned long*)&router_ip[0])) = get_eeprom_value(ROUTER_IP_EEPROM_STORE,ROUTER_IP);
	
    #if USE_DNS
    //DNS-Server IP aus EEPROM auslesen
    (*((unsigned long*)&dns_server_ip[0])) = get_eeprom_value(DNS_IP_EEPROM_STORE,DNS_IP);
    #endif

	//MAC Adresse setzen
	mymac[0] = MYMAC1;
    mymac[1] = MYMAC2;
    mymac[2] = MYMAC3;
    mymac[3] = MYMAC4;
    mymac[4] = MYMAC5;
    mymac[5] = MYMAC6;

	printf_P(PSTR("\n\rNIC Init\n\r"));
	
	/*NIC Initialisieren*/
	DEBUG("\n\rNIC init:");
	ETH_INIT();
	DEBUG("READY!\r\n");
	printf_P(PSTR("\n\rReady\n\r"));

	
	DEBUG("My IP: %1i.%1i.%1i.%1i\r\n\r\n",myip[0],myip[1],myip[2],myip[3]);
}

//----------------------------------------------------------------------------
//
unsigned long get_eeprom_value (unsigned int eeprom_adresse,unsigned long default_value)
{
	unsigned char value[4];
	
	for (unsigned char count = 0; count<4;count++)
	{
		eeprom_busy_wait ();	
		value[count] = eeprom_read_byte((unsigned char *)(eeprom_adresse + count));
	}

	//Ist der EEPROM Inhalt leer?
	if ((*((unsigned long*)&value[0])) == 0xFFFFFFFF)
	{
		return(default_value);
	}
	return((*((unsigned long*)&value[0])));
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 *	Verwaltung des TCP Timers
 *
 */
void tcp_timer_call (void)
{
	for (unsigned char index = 0;index<MAX_TCP_ENTRY;index++)
	{
		if (tcp_entry[index].time == 0)
		{
			if (tcp_entry[index].ip != 0)
			{
				tcp_entry[index].time = TCP_MAX_ENTRY_TIME;
				if ((tcp_entry[index].error_count++) > MAX_TCP_ERRORCOUNT)
				{
					DEBUG("Eintrag wird entfernt MAX_ERROR STACK:%i\r\n",index);
					ETH_INT_DISABLE;
					tcp_entry[index].status =  RST_FLAG | ACK_FLAG;
					create_new_tcp_packet(0, index);
					ETH_INT_ENABLE;
					tcp_index_del(index);
				}
				else
				{
					DEBUG("Packet wird erneut gesendet STACK:%i\r\n",index);
					find_and_start (index);
				}
			}
		}
		else
		{
			if (tcp_entry[index].time != TCP_TIME_OFF)
			{
				tcp_entry[index].time--;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 *	Verwaltung des ARP Timers
 *
 */
void arp_timer_call (void)
{
	for (unsigned char a = 0;a<MAX_ARP_ENTRY;a++)
	{
		if (arp_entry[a].arp_t_time == 0)
		{
			for (unsigned char b = 0;b<6;b++)
			{
				arp_entry[a].arp_t_mac[b]= 0;
			}
			arp_entry[a].arp_t_ip = 0;
		}
		else
		{
			arp_entry[a].arp_t_time--;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 *	Tr�gt TCP PORT/Anwendung in Anwendungsliste ein
 *
 */
void add_tcp_app (unsigned int port, void(*fp1)(unsigned char))
{
	unsigned char port_index = 0;
	//Freien Eintrag in der Anwendungliste suchen
	while (TCP_PORT_TABLE[port_index].port)
	{ 
		port_index++;
	}
	if (port_index >= MAX_APP_ENTRY)
	{
		DEBUG("TCP Zuviele Anwendungen wurden gestartet\r\n");
		return;
	}
	DEBUG("TCP Anwendung wird in Liste eingetragen: Eintrag %i\r\n",port_index);
	TCP_PORT_TABLE[port_index].port = port;
	TCP_PORT_TABLE[port_index].fp = *fp1;
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 *	�nderung der TCP PORT/Anwendung in Anwendungsliste
 *
 */
void change_port_tcp_app (unsigned int port_old, unsigned int port_new)
{
	unsigned char port_index = 0;
	//Freien Eintrag in der Anwendungliste suchen
	while (TCP_PORT_TABLE[port_index].port && TCP_PORT_TABLE[port_index].port != port_old)
	{ 
		port_index++;
	}
	if (port_index >= MAX_APP_ENTRY)
	{
		DEBUG("(Port�nderung) Port wurde nicht gefunden\r\n");
		return;
	}
	DEBUG("TCP Anwendung Port �ndern: Eintrag %i\r\n",port_index);
	TCP_PORT_TABLE[port_index].port = port_new;
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 *	Tr�gt UDP PORT/Anwendung in Anwendungsliste ein
 *
 */
void add_udp_app (unsigned int port, void(*fp1)(unsigned char))
{
	unsigned char port_index = 0;
	//Freien Eintrag in der Anwendungliste suchen
	while (UDP_PORT_TABLE[port_index].port)
	{ 
		port_index++;
	}
	if (port_index >= MAX_APP_ENTRY)
	{
		DEBUG("Zuviele UDP Anwendungen wurden gestartet\r\n");
		return;
	}
	DEBUG("UDP Anwendung wird in Liste eingetragen: Eintrag %i\r\n",port_index);
	UDP_PORT_TABLE[port_index].port = port;
	UDP_PORT_TABLE[port_index].fp = *fp1;
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 *	L�scht UDP Anwendung aus der Anwendungsliste
 *
 */
void kill_udp_app (unsigned int port)
{
    unsigned char i;

    for (i = 0; i < MAX_APP_ENTRY; i++)
    {
        if ( UDP_PORT_TABLE[i].port == port )
        {
            UDP_PORT_TABLE[i].port = 0;
        }
    }
    return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 *	Interrupt von der Netzwerkkarte
 *
 */
ISR(ETH_INTERRUPT)
{
    eth.data_present = 1;
    time_watchdog = 0;
    ETH_INT_DISABLE;
}

//----------------------------------------------------------------------------
//ETH get data
/**
 *	\ingroup stack
 * Ethernet Datenempfang
 *
 */
void eth_get_data (void)
{ 	
	if(eth.timer)
	{
		tcp_timer_call();
		arp_timer_call();
		eth.timer = 0;
	}	
	if(eth.data_present)
	{
	#if USE_ENC28J60
		while(ETH_INT_ACTIVE)
		{	
	#endif

	#if USE_RTL8019
		if ( (ReadRTL(RTL_ISR)&(1<<OVW)) != 0)
			{
			DEBUG ("Overrun!\n");
			}

		if ( (ReadRTL(RTL_ISR) & (1<<PRX)) != 0)
		{
			unsigned char ByteH = 0;
			unsigned char ByteL = 1;
		
			while (ByteL != ByteH) //(!= bedeutet ungleich)
			{	
	#endif	
				unsigned int packet_length;
				  
				packet_length = ETH_PACKET_RECEIVE(MTU_SIZE,(uint8_t *)eth_buffer);
				if(packet_length > 0)
				{
					eth_buffer[packet_length+1] = 0;
					check_packet();
				}
			
	#if USE_RTL8019
				//auslesen des Empfangsbuffer BNRY = CURR
				ByteL = ReadRTL(BNRY); //auslesen NIC Register bnry
				WriteRTL ( CR ,(1<<STA|1<<RD2|1<<PS0));
			
				ByteH = ReadRTL(CURR); //auslesen NIC Register curr
				WriteRTL ( CR ,(1<<STA|1<<RD2));
			}
	#endif
		}
	#if USE_RTL8019
		Networkcard_INT_RES();
		Networkcard_Start();
	#endif
		eth.data_present = 0;
		ETH_INT_ENABLE;
	}
	return;
}
//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Check Packet and call Stack for TCP or UDP
 *
 */
void check_packet (void)
{
    struct Ethernet_Header *ethernet;    //Pointer auf Ethernet_Header
    struct IP_Header       *ip;          //Pointer auf IP_Header
    struct TCP_Header      *tcp;         //Pointer auf TCP_Header
    struct ICMP_Header     *icmp;        //Pointer auf ICMP_Header

    ethernet = (struct Ethernet_Header *)&eth_buffer[ETHER_OFFSET];
    ip       = (struct IP_Header       *)&eth_buffer[IP_OFFSET];
    tcp      = (struct TCP_Header      *)&eth_buffer[TCP_OFFSET];
    icmp     = (struct ICMP_Header     *)&eth_buffer[ICMP_OFFSET];
		
    if(ethernet->EnetPacketType == HTONS(0x0806) )     //ARP
	{
        arp_reply(); // check arp packet request/reply
	}
	else
	{
        if( ethernet->EnetPacketType == HTONS(0x0800) )  // if IP
		{
            if( ip->IP_Destaddr == *((unsigned long*)&myip[0]) )  // if my IP address 
            {
                arp_entry_add();  ///Refresh des ARP Eintrages
                if(ip->IP_Proto == PROT_ICMP)
                {
                    switch ( icmp->ICMP_Type )
                    {
                        case (8): //Ping reqest
                            icmp_send(ip->IP_Srcaddr,0,0,icmp->ICMP_SeqNum,icmp->ICMP_Id); 
                            break;
                            
                        case (0): //Ping reply
                            if ((*((unsigned long*)&ping.ip1[0])) == ip->IP_Srcaddr)
                            {
                                ping.result |= 0x01;
                            }
                            DEBUG("%i",    (ip->IP_Srcaddr&0x000000FF)     );
                            DEBUG(".%i",  ((ip->IP_Srcaddr&0x0000FF00)>>8 ));
                            DEBUG(".%i",  ((ip->IP_Srcaddr&0x00FF0000)>>16));
                            DEBUG(".%i :",((ip->IP_Srcaddr&0xFF000000)>>24));
                            break;
                    }
                    return;
                }
                else
                {
                    if( ip->IP_Proto == PROT_TCP ) tcp_socket_process();
                    if( ip->IP_Proto == PROT_UDP ) udp_socket_process();
                }
            }
            else
            if (ip->IP_Destaddr == (unsigned long)0xffffffff ) // if broadcast
            {
                if( ip->IP_Proto == PROT_UDP ) udp_socket_process();
            }
		}
	}
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * erzeugt einen ARP - Eintrag wenn noch nicht vorhanden 
 *
 */
void arp_entry_add (void)
{
	struct Ethernet_Header *ethernet;
	struct ARP_Header      *arp;
	struct IP_Header       *ip;

	ethernet = (struct Ethernet_Header *)&eth_buffer[ETHER_OFFSET];
	arp      = (struct ARP_Header      *)&eth_buffer[ARP_OFFSET];
	ip       = (struct IP_Header       *)&eth_buffer[IP_OFFSET];

	//Eintrag schon vorhanden?
	for (unsigned char a = 0;a<MAX_ARP_ENTRY;a++)
	{
		if( ethernet->EnetPacketType == HTONS(0x0806) ) //If ARP
		{
			if(arp_entry[a].arp_t_ip == arp->ARP_SIPAddr)
			{
			//Eintrag gefunden Time refresh
			arp_entry[a].arp_t_time = ARP_MAX_ENTRY_TIME;
			return;
			}
		} 
		if( ethernet->EnetPacketType == HTONS(0x0800) ) //If IP
		{
			if(arp_entry[a].arp_t_ip == ip->IP_Srcaddr)
			{
			//Eintrag gefunden Time refresh
			arp_entry[a].arp_t_time = ARP_MAX_ENTRY_TIME;
			return;
			}
		}
	}
	
	//Freien Eintrag finden
	for (unsigned char b = 0;b<MAX_ARP_ENTRY;b++)
	{
		if(arp_entry[b].arp_t_ip == 0)
		{
			if( ethernet->EnetPacketType == HTONS(0x0806) ) //If ARP
			{
				for(unsigned char a = 0; a < 6; a++)
				{
					arp_entry[b].arp_t_mac[a] = ethernet->EnetPacketSrc[a]; 
				}
				arp_entry[b].arp_t_ip = arp->ARP_SIPAddr;
				arp_entry[b].arp_t_time = ARP_MAX_ENTRY_TIME;
				return;
			}
			if( ethernet->EnetPacketType == HTONS(0x0800) ) //If IP
			{
				for(unsigned char a = 0; a < 6; a++)
				{
					arp_entry[b].arp_t_mac[a] = ethernet->EnetPacketSrc[a]; 
				}
				arp_entry[b].arp_t_ip = ip->IP_Srcaddr;
				arp_entry[b].arp_t_time = ARP_MAX_ENTRY_TIME;
				return;
			}
			
		DEBUG("Kein ARP oder IP Packet!\r\n");
		return;
		}
	}
	//Eintrag konnte nicht mehr aufgenommen werden
	DEBUG("ARP entry tabelle voll!\r\n");
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine such anhand der IP den ARP eintrag
 *
 */
char arp_entry_search (unsigned long dest_ip)
{
	for (unsigned char b = 0;b<MAX_ARP_ENTRY;b++)
	{
		if(arp_entry[b].arp_t_ip == dest_ip)
		{
			return(b);
		}
	}
	return (MAX_ARP_ENTRY);
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine Erzeugt ein neuen Ethernetheader
 *
 */
void new_eth_header (char *buffer,unsigned long dest_ip)
{
	unsigned char b;
	unsigned char a;
	struct Ethernet_Header *ethernet;

	ethernet = (struct Ethernet_Header *)&buffer[ETHER_OFFSET];
	
	b = arp_entry_search (dest_ip);
	if (b < MAX_ARP_ENTRY) //Eintrag gefunden wenn kleiner max. Eintrag
	{
		for(a = 0; a < 6; a++)
		{
			//MAC Destadresse wird geschrieben mit MAC Sourceadresse
			ethernet->EnetPacketDest[a] = arp_entry[b].arp_t_mac[a];
			//Meine MAC Adresse wird in Sourceadresse geschrieben
			ethernet->EnetPacketSrc[a] = mymac[a];
		}
		return;
	}

	DEBUG("ARP Eintrag nicht gefunden*\r\n");
	for(a = 0; a < 6; a++)
	{
		//MAC Destadresse wird geschrieben mit MAC Sourceadresse
		ethernet->EnetPacketDest[a] = 0xFF;
		//Meine MAC Adresse wird in Sourceadresse geschrieben
		ethernet->EnetPacketSrc[a] = mymac[a];
	}
	return;

}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine Antwortet auf ein ARP Packet
 *
 */
void arp_reply (void)
{
	unsigned char b;
	unsigned char a;
	struct Ethernet_Header *ethernet;
	struct ARP_Header      *arp;

	ethernet = (struct Ethernet_Header *)&eth_buffer[ETHER_OFFSET];
	arp      = (struct ARP_Header      *)&eth_buffer[ARP_OFFSET];


	if( arp->ARP_HWType  == HTONS(0x0001)  &&             // Hardware Typ:   Ethernet
    	arp->ARP_PRType  == HTONS(0x0800)  &&             // Protokoll Typ:  IP
    	arp->ARP_HWLen   == 0x06           &&             // L�nge der Hardwareadresse: 6
    	arp->ARP_PRLen   == 0x04           &&             // L�nge der Protokolladresse: 4 
    	arp->ARP_TIPAddr == *((unsigned long*)&myip[0]))  // F�r uns? Vergleiche ARP Target IP Adresse mit meiner IP
	{
		if (arp->ARP_Op == HTONS(0x0001))				  // ARP request?
		{
			arp_entry_add();							  // Rechner eintragen wenn noch nicht geschehen
			new_eth_header(eth_buffer, arp->ARP_SIPAddr); // Erzeugt ein neuen Ethernetheader
			ethernet->EnetPacketType = HTONS(0x0806);	  // Nutzlast 0x0800=IP Datagramm;0x0806 = ARP
			
			b = arp_entry_search (arp->ARP_SIPAddr);
			if (b < MAX_ARP_ENTRY)						  // Eintrag gefunden wenn kleiner
			{
				for(a = 0; a < 6; a++)
				{
					//ARP MAC Targetadresse wird geschrieben mit ARP Sourceadresse
					arp->ARP_THAddr[a] = arp_entry[b].arp_t_mac[a];
					//ARP MAC Sourceadresse wird geschrieben mit My MAC Adresse
					arp->ARP_SHAddr[a] = mymac[a];
				}
			}
			else
			{
				DEBUG("ARP Eintrag nicht gefunden\r\n");		// Unwarscheinlich das das jemals passiert!
			}
			
			arp->ARP_Op = HTONS(0x0002);						// ARP op=ECHO gesetzt damit es der andere merkt
			arp->ARP_TIPAddr = arp->ARP_SIPAddr;				// ARP Target IP Adresse
			arp->ARP_SIPAddr = *((unsigned long *)&myip[0]);	// ARP Source = Meine IP Adresse
			
			//Nun ist das ARP-Packet fertig zum Senden !!!
			ETH_PACKET_SEND(ARP_REPLY_LEN,(uint8_t *)eth_buffer);			// ARP Reply senden...
			return;
		}

        if ( arp->ARP_Op == HTONS(0x0002) )						// REPLY von einem anderen Client
		{
			arp_entry_add();									// Rechner eintragen wenn noch nicht geschehen
			DEBUG("ARP REPLY EMPFANGEN!\r\n");
		}
	}
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine erzeugt ein ARP Request
 *
 */
char arp_request (unsigned long dest_ip)
{
    char buffer[ARP_REQUEST_LEN];
    unsigned char index = 0;
    unsigned char index_tmp;
    unsigned char count;
    unsigned long a;
    unsigned long dest_ip_store;

    struct Ethernet_Header *ethernet;
    struct ARP_Header *arp;

    ethernet = (struct Ethernet_Header *)&buffer[ETHER_OFFSET];
    arp      = (struct ARP_Header      *)&buffer[ARP_OFFSET];

	dest_ip_store = dest_ip;

	if ((dest_ip & (*((unsigned long *)&netmask[0])))==
		((*((unsigned long *)&myip[0]))&(*((unsigned long *)&netmask[0]))))
	{
		DEBUG("MY NETWORK!\r\n");
	}
	else
	{
		DEBUG("ROUTING!\r\n");
		dest_ip = (*((unsigned long *)&router_ip[0]));
	}

    ethernet->EnetPacketType = HTONS(0x0806);          // Nutzlast 0x0800=IP Datagramm;0x0806 = ARP
  
    new_eth_header (buffer,dest_ip);
  
    arp->ARP_SIPAddr = *((unsigned long *)&myip[0]);   // MyIP = ARP Source IP
    arp->ARP_TIPAddr = dest_ip;                         // Dest IP 
	
	for(unsigned char count = 0; count < 6; count++)
	{
		  arp->ARP_SHAddr[count] = mymac[count];
		  arp->ARP_THAddr[count] = 0;
	}
	
    arp->ARP_HWType = HTONS(0x0001);
    arp->ARP_PRType = HTONS(0x0800);
    arp->ARP_HWLen  = 0x06;
    arp->ARP_PRLen  = 0x04;
    arp->ARP_Op     = HTONS(0x0001);

    ETH_PACKET_SEND(ARP_REQUEST_LEN, (uint8_t *)buffer);        //send....
	
	for(count = 0;count<20;count++)
	{
		index_tmp = arp_entry_search(dest_ip_store);
		index = arp_entry_search(dest_ip);
		if (index < MAX_ARP_ENTRY || index_tmp < MAX_ARP_ENTRY)
		{
			DEBUG("ARP EINTRAG GEFUNDEN!\r\n");
			if (index_tmp < MAX_ARP_ENTRY) return(1);//OK
			arp_entry[index].arp_t_ip = dest_ip_store;
			return(1);//OK
		}
        for(a=0;a<10000;a++)
        {
            asm("nop");
        }
		eth_get_data();
		DEBUG("**KEINEN ARP EINTRAG GEFUNDEN**\r\n");
	}
	return(0);//keine Antwort
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine erzeugt ein neues ICMP Packet
 *
 */
void icmp_send (unsigned long dest_ip, unsigned char icmp_type, 
                unsigned char icmp_code, unsigned int icmp_sn, 
                unsigned int icmp_id)
{
    unsigned int result16;  //Checksum
    struct IP_Header   *ip;
    struct ICMP_Header *icmp;

    ip   = (struct IP_Header   *)&eth_buffer[IP_OFFSET];
    icmp = (struct ICMP_Header *)&eth_buffer[ICMP_OFFSET];

    //Das ist ein Echo Reply Packet
    icmp->ICMP_Type   = icmp_type;
    icmp->ICMP_Code   = icmp_code;
    icmp->ICMP_Id     = icmp_id;
    icmp->ICMP_SeqNum = icmp_sn;
    icmp->ICMP_Cksum  = 0;
    ip->IP_Pktlen     = HTONS(0x0054);   // 0x54 = 84 
    ip->IP_Proto      = PROT_ICMP;
    make_ip_header (eth_buffer,dest_ip);

    //Berechnung der ICMP Header l�nge
    result16 = htons(ip->IP_Pktlen);
    result16 = result16 - ((ip->IP_Vers_Len & 0x0F) << 2);

    //pointer wird auf das erste Paket im ICMP Header gesetzt
    //jetzt wird die Checksumme berechnet
    result16 = checksum (&icmp->ICMP_Type, result16, 0);
  
    //schreibt Checksumme ins Packet
    icmp->ICMP_Cksum = htons(result16);
  
    //Sendet das erzeugte ICMP Packet 
    ETH_PACKET_SEND(ICMP_REPLY_LEN,(uint8_t *)eth_buffer);
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine erzeugt eine Cecksumme
 *
 */
unsigned int checksum (unsigned char *pointer,unsigned int result16,unsigned long result32)
{
	unsigned int result16_1 = 0x0000;
	unsigned char DataH;
	unsigned char DataL;
	
	//Jetzt werden alle Packete in einer While Schleife addiert
	while(result16 > 1)
	{
		//schreibt Inhalt Pointer nach DATAH danach inc Pointer
		DataH=*pointer++;

		//schreibt Inhalt Pointer nach DATAL danach inc Pointer
		DataL=*pointer++;

		//erzeugt Int aus Data L und Data H
		result16_1 = ((DataH << 8)+DataL);
		//Addiert packet mit vorherigen
		result32 = result32 + result16_1;
		//decrimiert L�nge von TCP Headerschleife um 2
		result16 -=2;
	}

	//Ist der Wert result16 ungerade ist DataL = 0
	if(result16 > 0)
	{
		//schreibt Inhalt Pointer nach DATAH danach inc Pointer
		DataH=*pointer;
		//erzeugt Int aus Data L ist 0 (ist nicht in der Berechnung) und Data H
		result16_1 = (DataH << 8);
		//Addiert packet mit vorherigen
		result32 = result32 + result16_1;
	}
	
	//Komplementbildung (addiert Long INT_H Byte mit Long INT L Byte)
	result32 = ((result32 & 0x0000FFFF)+ ((result32 & 0xFFFF0000) >> 16));
	result32 = ((result32 & 0x0000FFFF)+ ((result32 & 0xFFFF0000) >> 16));	
	result16 =~(result32 & 0x0000FFFF);
	
	return (result16);
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine erzeugt ein IP Packet
 *
 */
void make_ip_header (char *buffer,unsigned long dest_ip)
{
    unsigned int result16;  //Checksum
    struct Ethernet_Header *ethernet;
    struct IP_Header       *ip;

    ethernet = (struct Ethernet_Header *)&buffer[ETHER_OFFSET];
    ip       = (struct IP_Header       *)&buffer[IP_OFFSET];

    new_eth_header (buffer, dest_ip);         //Erzeugt einen neuen Ethernetheader
    ethernet->EnetPacketType = HTONS(0x0800); //Nutzlast 0x0800=IP

    IP_id_counter++;

    ip->IP_Frag_Offset = 0x0040;  //don't fragment
    ip->IP_ttl         = 128;      //max. hops
    ip->IP_Id          = htons(IP_id_counter);
    ip->IP_Vers_Len    = 0x45;  //4 BIT Die Versionsnummer von IP, 
    ip->IP_Tos         = 0;
    ip->IP_Destaddr     = dest_ip;
    ip->IP_Srcaddr     = *((unsigned long *)&myip[0]);
    ip->IP_Hdr_Cksum   = 0;
  
    //Berechnung der IP Header l�nge  
    result16 = (ip->IP_Vers_Len & 0x0F) << 2;

    //jetzt wird die Checksumme berechnet
    result16 = checksum (&ip->IP_Vers_Len, result16, 0);

    //schreibt Checksumme ins Packet
    ip->IP_Hdr_Cksum = htons(result16);
    return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine verwaltet TCP-Eintr�ge
 *
 */
void tcp_entry_add (char *buffer)
{
	unsigned long result32;

	struct TCP_Header *tcp;
	struct IP_Header *ip;

	tcp = (struct TCP_Header *)&buffer[TCP_OFFSET];
	ip  = (struct IP_Header  *)&buffer[IP_OFFSET];
	
	//Eintrag schon vorhanden?
	for (unsigned char index = 0;index<(MAX_TCP_ENTRY);index++)
	{
		if(	tcp_entry[index].ip == ip->IP_Srcaddr &&
			tcp_entry[index].src_port == tcp->TCP_SrcPort)
		{
		//Eintrag gefunden Time refresh
		tcp_entry[index].ack_counter = tcp->TCP_Acknum;
		tcp_entry[index].seq_counter = tcp->TCP_Seqnum;
		tcp_entry[index].status = tcp->TCP_HdrFlags;
		if (tcp_entry[index].time!=TCP_TIME_OFF)
		{
			tcp_entry[index].time = TCP_MAX_ENTRY_TIME;
		}
		result32 = htons(ip->IP_Pktlen) - IP_VERS_LEN - ((tcp->TCP_Hdrlen& 0xF0) >>2);
		result32 = result32 + htonl(tcp_entry[index].seq_counter);
		tcp_entry[index].seq_counter = htonl(result32);
		
		DEBUG("TCP Entry gefunden %i\r\n",index);
		return;
		}
	}
	
	//Freien Eintrag finden
	for (unsigned char index = 0;index<(MAX_TCP_ENTRY);index++)
	{
		if(tcp_entry[index].ip == 0)
		{
			tcp_entry[index].ip          = ip->IP_Srcaddr;
			tcp_entry[index].src_port    = tcp->TCP_SrcPort;
			tcp_entry[index].dest_port   = tcp->TCP_DestPort;
			tcp_entry[index].ack_counter = tcp->TCP_Acknum;
			tcp_entry[index].seq_counter = tcp->TCP_Seqnum;
			tcp_entry[index].status      = tcp->TCP_HdrFlags;
			tcp_entry[index].app_status  = 0;
			tcp_entry[index].time        = TCP_MAX_ENTRY_TIME;
			tcp_entry[index].error_count = 0;
			tcp_entry[index].first_ack   = 0;
			DEBUG("TCP Entry neuer Eintrag %i\r\n",index);
			return;  
		}
	}
	//Eintrag konnte nicht mehr aufgenommen werden
	DEBUG("Server Busy (NO MORE CONNECTIONS)!\r\n");
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine sucht den etntry eintrag
 *
 */
char tcp_entry_search (unsigned long dest_ip,unsigned int SrcPort)
{
	for (unsigned char index = 0;index<MAX_TCP_ENTRY;index++)
	{
		if(	tcp_entry[index].ip == dest_ip &&
			tcp_entry[index].src_port == SrcPort)
		{
			return(index);
		}
	}
	return (MAX_TCP_ENTRY);
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine verwaltet die UDP Ports
 *
 */
void udp_socket_process(void)
{
	unsigned char port_index = 0;
		
	struct UDP_Header *udp;
	udp = (struct UDP_Header *)&eth_buffer[UDP_OFFSET];

	//UDP DestPort mit Portanwendungsliste durchf�hren
	while (UDP_PORT_TABLE[port_index].port && UDP_PORT_TABLE[port_index].port!=(htons(udp->udp_DestPort)))
	{ 
		port_index++;
	}
	
	// Wenn index zu gross, dann beenden keine vorhandene Anwendung f�r den Port
	if (!UDP_PORT_TABLE[port_index].port)
	{ 
		//Keine vorhandene Anwendung eingetragen! (ENDE)
		DEBUG("UDP Keine Anwendung gefunden!\r\n");
		return;
	}

	//zugeh�rige Anwendung ausf�hren
	UDP_PORT_TABLE[port_index].fp(0); 
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine Erzeugt ein neues UDP Packet
 *
 */
void create_new_udp_packet(	unsigned int data_length,
							unsigned int src_port,
							unsigned int dest_port,
							unsigned long dest_ip)
{
	unsigned int  result16;
	unsigned long result32;

	struct UDP_Header *udp;
	struct IP_Header  *ip;

	udp = (struct UDP_Header *)&eth_buffer[UDP_OFFSET];
	ip  = (struct IP_Header  *)&eth_buffer[IP_OFFSET];

	udp->udp_SrcPort  = htons(src_port);
	udp->udp_DestPort = htons(dest_port);

	data_length     += UDP_HDR_LEN;                //UDP Packetlength
	udp->udp_Hdrlen = htons(data_length);

	data_length     += IP_VERS_LEN;                //IP Headerl�nge + UDP Headerl�nge
	ip->IP_Pktlen = htons(data_length);
	data_length += ETH_HDR_LEN;
	ip->IP_Proto = PROT_UDP;
	make_ip_header (eth_buffer,dest_ip);

	udp->udp_Chksum = 0;

	//Berechnet Headerl�nge und Addiert Pseudoheaderl�nge 2XIP = 8
	result16 = htons(ip->IP_Pktlen) + 8;
	result16 = result16 - ((ip->IP_Vers_Len & 0x0F) << 2);
	result32 = result16 + 0x09;

	//Routine berechnet die Checksumme
	result16 = checksum ((&ip->IP_Vers_Len+12), result16, result32);
	udp->udp_Chksum = htons(result16);

	ETH_PACKET_SEND(data_length,(uint8_t *)eth_buffer); //send...
	return;
}
//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine verwaltet die TCP Ports
 *
 */
void tcp_socket_process(void)
{
	unsigned char index = 0;
	unsigned char port_index = 0;
	unsigned long result32 = 0;

	struct TCP_Header *tcp;
	tcp = (struct TCP_Header *)&eth_buffer[TCP_OFFSET];

	struct IP_Header *ip;
	ip = (struct IP_Header *)&eth_buffer[IP_OFFSET];

	//TCP DestPort mit Portanwendungsliste durchf�hren
	while (TCP_PORT_TABLE[port_index].port && TCP_PORT_TABLE[port_index].port!=(htons(tcp->TCP_DestPort)))
	{ 
		port_index++;
	}
	
	// Wenn index zu gross, dann beenden keine vorhandene Anwendung f�r Port
	//Geht von einem Client was aus? Will eine Clientanwendung einen Port �ffnen?
	if (!TCP_PORT_TABLE[port_index].port)
	{ 
		//Keine vorhandene Anwendung eingetragen! (ENDE)
		DEBUG("TCP Keine Anwendung gefunden!\r\n");
		return;
	}	
	
	//Server �ffnet Port
	if((tcp->TCP_HdrFlags & SYN_FLAG) && (tcp->TCP_HdrFlags & ACK_FLAG))
	{	
		//Nimmt Eintrag auf da es eine Client - Anwendung f�r den Port gibt
		tcp_entry_add (eth_buffer);
		//War der Eintrag erfolgreich?
		index = tcp_entry_search (ip->IP_Srcaddr,tcp->TCP_SrcPort);
		if (index >= MAX_TCP_ENTRY) //Eintrag gefunden wenn ungleich
		{
			DEBUG("TCP Eintrag nicht erfolgreich!\r\n");
			return;
		}
	
		tcp_entry[index].time = MAX_TCP_PORT_OPEN_TIME;
		DEBUG("TCP Port wurde vom Server ge�ffnet STACK:%i\r\n",index);
		result32 = htonl(tcp_entry[index].seq_counter) + 1;
		tcp_entry[index].seq_counter = htonl(result32);
		tcp_entry[index].status =  ACK_FLAG;
		create_new_tcp_packet(0,index);
		//Server Port wurde ge�ffnet App. kann nun daten senden!
		tcp_entry[index].app_status = 1;
		return;
	}
	
	//Verbindungsaufbau nicht f�r Anwendung bestimmt
	if(tcp->TCP_HdrFlags == SYN_FLAG)
	{
		//Nimmt Eintrag auf da es eine Server - Anwendung f�r den Port gibt
		tcp_entry_add (eth_buffer);
		//War der Eintrag erfolgreich?
		index = tcp_entry_search (ip->IP_Srcaddr,tcp->TCP_SrcPort);
		if (index >= MAX_TCP_ENTRY) //Eintrag gefunden wenn ungleich
		{
			DEBUG("TCP Eintrag nicht erfolgreich!\r\n");
			return;
		}
	
		DEBUG("TCP New SERVER Connection! STACK:%i\r\n",index);
		
		tcp_entry[index].status =  ACK_FLAG | SYN_FLAG;
		create_new_tcp_packet(0,index);
		return;
	}

	//Packeteintrag im TCP Stack finden!
	index = tcp_entry_search (ip->IP_Srcaddr,tcp->TCP_SrcPort);
	
	if (index >= MAX_TCP_ENTRY) //Eintrag nicht gefunden
	{
		DEBUG("TCP Eintrag nicht gefunden\r\n");
		if(tcp->TCP_HdrFlags & FIN_FLAG || tcp->TCP_HdrFlags & RST_FLAG)
		{	
			tcp_entry_add (eth_buffer);//Tempor�rer Indexplatz	
			
			result32 = htonl(tcp_entry[index].seq_counter) + 1;
			tcp_entry[index].seq_counter = htonl(result32);
			
			if (tcp_entry[index].status & FIN_FLAG)
			{
				tcp_entry[index].status = ACK_FLAG;
				create_new_tcp_packet(0,index);
			}
			tcp_index_del(index);
			DEBUG("TCP-Stack Eintrag gel�scht! STACK:%i\r\n",index);
			return;
		}
		return;
	}


	//Refresh des Eintrages
	tcp_entry_add (eth_buffer);
	
	//Host will verbindung beenden!
	if(tcp_entry[index].status & FIN_FLAG || tcp_entry[index].status & RST_FLAG)
	{	
		result32 = htonl(tcp_entry[index].seq_counter) + 1;
		tcp_entry[index].seq_counter = htonl(result32);
		
		if (tcp_entry[index].status & FIN_FLAG)
		{
			// Ende der Anwendung mitteilen !
			TCP_PORT_TABLE[port_index].fp(index);

			tcp_entry[index].status = ACK_FLAG | FIN_FLAG;
			create_new_tcp_packet(0,index);
		}
		tcp_index_del(index);
		DEBUG("TCP-Stack Eintrag gel�scht! STACK:%i\r\n",index);
		return;
	}
	
	//Daten f�r Anwendung PSH-Flag gesetzt?
	if((tcp_entry[index].status & PSH_FLAG) && 
		(tcp_entry[index].status & ACK_FLAG))
	{
		//zugeh�rige Anwendung ausf�hren
		tcp_entry[index].app_status++;	
		tcp_entry[index].status =  ACK_FLAG | PSH_FLAG;
		TCP_PORT_TABLE[port_index].fp(index); 
		return;
	}
	
	//Empfangene Packet wurde best�tigt keine Daten f�r Anwendung
	//z.B. nach Verbindungsaufbau (SYN-PACKET)
	if((tcp_entry[index].status & ACK_FLAG) && (tcp_entry[index].first_ack == 0))
	{
		//keine weitere Aktion
		tcp_entry[index].first_ack = 1;
		return;
	}
	
	//Empfangsbest�tigung f�r ein von der Anwendung gesendetes Packet (ENDE)
	if((tcp_entry[index].status & ACK_FLAG) && (tcp_entry[index].first_ack == 1))
	{
		//ACK f�r Verbindungs abbau
		if(tcp_entry[index].app_status == 0xFFFF)
		{
			return;
		}

		//zugeh�rige Anwendung ausf�hren
		tcp_entry[index].status =  ACK_FLAG;
		tcp_entry[index].app_status++;
		TCP_PORT_TABLE[port_index].fp(index);
		return;
	}
	return;
}
//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Creates and sends new TCP Packet
 *
 */
void create_new_tcp_packet(unsigned int data_length, unsigned char index)
{
	unsigned int  result16;
	unsigned long result32;
	unsigned int  bufferlen;

	struct TCP_Header *tcp;
	struct IP_Header  *ip;

	tcp = (struct TCP_Header *)&eth_buffer[TCP_OFFSET];
	ip  = (struct IP_Header  *)&eth_buffer[IP_OFFSET];

	tcp->TCP_SrcPort   = tcp_entry[index].dest_port;
	tcp->TCP_DestPort  = tcp_entry[index].src_port;
	tcp->TCP_UrgentPtr = 0;
	tcp->TCP_Window    = htons(MAX_WINDOWS_SIZE);
	tcp->TCP_Hdrlen    = 0x50;

	DEBUG("TCP SrcPort %4i\r\n", htons(tcp->TCP_SrcPort));

	result32 = htonl(tcp_entry[index].seq_counter); 

	tcp->TCP_HdrFlags = tcp_entry[index].status;

	//Verbindung wird aufgebaut
	if ((tcp_entry[index].status & SYN_FLAG))
	{
	    if (!tcp_entry[index].first_ack) result32++;
	    // MSS-Option (siehe RFC 879) wil.
	    eth_buffer[TCP_DATA_START]   = 2;
	    eth_buffer[TCP_DATA_START+1] = 4;
	    eth_buffer[TCP_DATA_START+2] = (MAX_WINDOWS_SIZE >> 8) & 0xff;
	    eth_buffer[TCP_DATA_START+3] = MAX_WINDOWS_SIZE & 0xff;
	    data_length                  = 0x04;
	    tcp->TCP_Hdrlen              = 0x60;
	}

	tcp->TCP_Acknum = htonl(result32);
	tcp->TCP_Seqnum = tcp_entry[index].ack_counter;

	bufferlen = IP_VERS_LEN + TCP_HDR_LEN + data_length;    //IP Headerl�nge + TCP Headerl�nge
	ip->IP_Pktlen = htons(bufferlen);                      //Hier wird erstmal der IP Header neu erstellt
	bufferlen += ETH_HDR_LEN;
	ip->IP_Proto = PROT_TCP;
	make_ip_header (eth_buffer,tcp_entry[index].ip);

	tcp->TCP_Chksum = 0;

	//Berechnet Headerl�nge und Addiert Pseudoheaderl�nge 2XIP = 8
	result16 = htons(ip->IP_Pktlen) + 8;
	result16 = result16 - ((ip->IP_Vers_Len & 0x0F) << 2);
	result32 = result16 - 2;

	//Checksum
	result16 = checksum ((&ip->IP_Vers_Len+12), result16, result32);
	tcp->TCP_Chksum = htons(result16);

	//Send the TCP packet
	ETH_PACKET_SEND (bufferlen, (uint8_t *)eth_buffer);
	//F�r Retransmission
	tcp_entry[index].status = 0;
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine schlie�t einen offenen TCP-Port
 *
 */
void tcp_Port_close (unsigned char index)
{
	DEBUG("Port wird im TCP Stack geschlossen STACK:%i\r\n",index);
	tcp_entry[index].app_status = 0xFFFF;
	tcp_entry[index].status =  ACK_FLAG | FIN_FLAG;
	create_new_tcp_packet(0,index);
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine findet die Anwendung anhand des TCP Ports (fas find and start)
 *
 */
void find_and_start (unsigned char index)
{
	unsigned char port_index = 0;

	//Port mit Anwendung in der Liste suchen
	while ( (TCP_PORT_TABLE[port_index].port!=(htons(tcp_entry[index].dest_port))) &&
	      (port_index < MAX_APP_ENTRY)                                                 )
	{ 
	    port_index++;
	}
	if (port_index >= MAX_APP_ENTRY) return;

	//zugeh�rige Anwendung ausf�hren (Senden wiederholen)
	TCP_PORT_TABLE[port_index].fp(index);
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine �ffnet einen TCP-Port
 *
 */
void tcp_port_open (unsigned long dest_ip,unsigned int port_dst,unsigned int port_src)
{
	unsigned char index;
	ETH_INT_DISABLE;
	DEBUG("Oeffen eines Ports mit Server\r\n");
	
	//Freien Eintrag finden
	for (index = 0;index<MAX_TCP_ENTRY;index++)
	{
		if(tcp_entry[index].ip == 0)
		{
			tcp_index_del(index);
			tcp_entry[index].ip = dest_ip;
			tcp_entry[index].src_port = port_dst;
			tcp_entry[index].dest_port = port_src;
			tcp_entry[index].ack_counter = 0;
			tcp_entry[index].seq_counter = 0;
			tcp_entry[index].time = MAX_TCP_PORT_OPEN_TIME;
			DEBUG("TCP Open neuer Eintrag %i\r\n",index);
			break;
		}
	}
	if (index >= MAX_TCP_ENTRY)
	{
		//Eintrag konnte nicht mehr aufgenommen werden
		DEBUG("Busy (NO MORE CONNECTIONS)!\r\n");
	}
	
	tcp_entry[index].status =  SYN_FLAG;
	create_new_tcp_packet(0, index);
	ETH_INT_ENABLE;
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup stack
 * Diese Routine l�scht einen Eintrag
 *
 */
void tcp_index_del (unsigned char index)
{
	if (index<MAX_TCP_ENTRY + 1)
	{
		tcp_entry[index].ip = 0;
		tcp_entry[index].src_port = 0;
		tcp_entry[index].dest_port = 0;
		tcp_entry[index].ack_counter = 0;
		tcp_entry[index].seq_counter = 0;
		tcp_entry[index].status = 0;
		tcp_entry[index].app_status = 0;
		tcp_entry[index].time = 0;
		tcp_entry[index].first_ack = 0;
	}
	return;
}

/**
 * @}
 * @}
 */







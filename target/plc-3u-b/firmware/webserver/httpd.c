/*----------------------------------------------------------------------------
 Copyright:      Radig Ulrich  mailto: mail@ulrichradig.de
 Author:         Radig Ulrich
 Remarks:        
 known Problems: none
 Version:        24.10.2007
 Description:    Webserver Applikation

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

/**
 * \addtogroup webserver HTTP Webserver
 *
  *
 * @{
 */

/**
 * \file
 * httpd.c
 *
 * \author Ulrich Radig & W.Wallucks
 */

#include "config.h"
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "httpd.h"
#include "stack.h"
#include "base64.h"
//#include "analog.h"
	
#include "webpage.h"
#include "translate.h"
#if USE_MMC
#include "sdkarte/fat16.h"
#include "sdkarte/sdcard.h"
#endif

#if USE_WOL
#include "wol.h"
#endif
    
#if USE_OW
//#include "messung.h"
#include "temperature.h"

#endif

#include "usart.h"		// nur für HTTP_DEBUG
//#define HTTP_DEBUG	usart_write
#define HTTP_DEBUG(...)	

#define MAX_RESOURCE_NAME_LENGTH (12)
		
struct http_table http_entry[MAX_TCP_ENTRY];

//Hier wird das codierte Passwort aus config.h gespeichert.
unsigned char http_auth_passwort[20];

unsigned char post_in[5] = {'O','U','T','='};
unsigned char post_ready[5] = {'S','U','B','='};	// id of Submit button - marker of the end of POST request
unsigned char PORT_tmp = 0;

//----------------------------------------------------------------------------

#define HTTP_RESPONSE_200_TEXT_HTML (0)
PROGMEM const char http_response_200_text_html[]={	"HTTP/1.0 200 OK\r\n"
								"Server: AVR_Small_Webserver\r\n"
								"Content-Type: text/html\r\n\r\n"};

#define HTTP_RESPONSE_200_IMAGE_JPEG (1)
PROGMEM const char http_response_200_image_jpeg[]={	"HTTP/1.0 200 OK\r\n"
								"Server: AVR_Small_Webserver\r\n"
								"Content-Type: image/jpg\r\n\r\n"};

#define HTTP_RESPONSE_200_CSV (2)
PROGMEM const char http_csv_header[]={	"HTTP/1.1 200 OK\r\n"
									"Server: AVR_Small_Webserver\r\n"
									"Content-Disposition: attachment;filename=Datalog.csv\r\n"
									"Connection: close\r\n"
									"Content-Type: file\r\n\r\n"};
									// oder application/octet-stream

#define HTTP_RESPONSE_200_APPLICATION_OCTET_STREAM (3)
PROGMEM const char http_application_octet_stream_header[]={
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/octet-stream\r\n\r\n"
};


#define HTTP_CSV_HEADER_LEN 141

PROGMEM const char http_response_401_unauthorized[]={	"HTTP/1.0 401 Unauthorized\r\n"
								"Server: AVR_Small_Webserver\r\n"
								"WWW-Authenticate: Basic realm=\"NeedPassword\""
								"\r\nContent-Type: text/html\r\n\r\n"};


//----------------------------------------------------------------------------
//Kein Zugriff Seite bei keinem Passwort
PROGMEM const char RESPONSE_401_UNAUTHORIZED[] = {"401 Unauthorized%END"};

unsigned char rx_header_end[5] = {"\r\n\r\n\0"};

//----------------------------------------------------------------------------
/**
 *	\ingroup webserver
 *	Initialisierung des Http Servers
 *
 */
void httpd_init (void)
{
	//HTTP_AUTH_STRING 
	decode_base64((unsigned char*)HTTP_AUTH_STRING,http_auth_passwort);

	//Serverport und Anwendung eintragen
	add_tcp_app (HTTPD_PORT, (void(*)(unsigned char))httpd);
}
   
//----------------------------------------------------------------------------
/**
 * \ingroup webserver
 * the http daemon
 * registered as "TCP application", see httpd_init().
 *
 * @param[in] index in der TCP Tabelle tcp_entry
 */
void httpd (unsigned char index)
{
	if (tcp_entry[index].status & FIN_FLAG) {	// Wird Verbindungsabbau signalisiert?
		HTTP_DEBUG("\r\nHTTP %i closed.",index);
		return;
	}

	//Allererste Aufruf des Ports für diese Anwendung
	//HTTPD_Anwendungsstack löschen
	if(tcp_entry[index].app_status==1)
	{
		httpd_stack_clear(index);
	}
	
	//HTTP wurde bei dieser Verbindung zum ersten mal aufgerufen oder
	//HTML Header Retransmission!
	if (tcp_entry[index].app_status <= 2)
	{	
		httpd_header_check (index);
		return;
	}
	
	//Der Header wurde gesendet und mit ACK bestätigt (tcp_entry[index].app_status+1)
	//war das HTML Paket fertig, oder müssen weitere Daten gesendet werden, oder Retransmission?
	if (tcp_entry[index].app_status > 2 && tcp_entry[index].app_status < 0xFFFE)
	{
		httpd_data_send (index);
		return;
	}
	
	//Verbindung kann geschlossen werden! Alle HTML Daten wurden gesendet TCP Port kann
	//geschlossen werden (tcp_entry[index].app_status >= 0xFFFE)!!
	if (tcp_entry[index].app_status >= 0xFFFE)
	{
		tcp_entry[index].app_status = 0xFFFE;
		tcp_Port_close(index);
		return;
	}
	return;
}

//----------------------------------------------------------------------------
//HTTPD_STACK löschen
void httpd_stack_clear (unsigned char index)
{
	http_entry[index].http_header_type = HTTP_RESPONSE_200_TEXT_HTML;
	http_entry[index].first_switch = 0;
	http_entry[index].http_auth = HTTP_AUTH_DEFAULT;
	http_entry[index].new_page_pointer = 0;
	http_entry[index].old_page_pointer = 0;
	http_entry[index].post = 0;
	http_entry[index].auth_ptr = http_auth_passwort;
	http_entry[index].post_ptr = post_in;
	http_entry[index].post_ready_ptr = post_ready;
	http_entry[index].hdr_end_pointer = rx_header_end;
	http_entry[index].cam = 0;
#if USE_MMC
	http_entry[index].mmc = 0;
	http_entry[index].charcount = 0;
	http_entry[index].old_charcount = 0;
#endif //USE_MMC			
	HTTP_DEBUG("\r\n**** NEUE HTTP ANFORDERUNG ****\r\n\r\n");	
	return;
}

//----------------------------------------------------------------------------
/**
 *	\ingroup webserver
 *	Eintreffenden Header vom Client checken
 *
 * @param[in] index in der TCP Tabelle tcp_entry
 */
void httpd_header_check (unsigned char index)
{
	unsigned int a = 0;

    // ? Check for POST request	
    if (strcasestr_P((char*)&eth_buffer[TCP_DATA_START_VAR], PSTR("POST")) != 0)
    {
	// Was POST request
        http_entry[index].post = 1;
    }
	
	//finden der Authorization und das Ende im Header auch über mehrere Pakete hinweg!!	
	if(*http_entry[index].hdr_end_pointer != 0)
	{		
		for(a=TCP_DATA_START_VAR;a<(TCP_DATA_END_VAR);a++)
		{	
			HTTP_DEBUG("%c",eth_buffer[a]);
			
			if(!http_entry[index].http_auth) 
			{
				if (eth_buffer[a] != *http_entry[index].auth_ptr++)
				{
					http_entry[index].auth_ptr = http_auth_passwort;
				}
				if(*http_entry[index].auth_ptr == 0) 	// match
				{
					http_entry[index].http_auth = 1;
					HTTP_DEBUG("  <---LOGIN OK!--->\r\n");
				}
			}
			
			// find end of headers
			if (eth_buffer[a] != *http_entry[index].hdr_end_pointer++)
			{
				http_entry[index].hdr_end_pointer = rx_header_end;	// revert to rx_header_end
			}
			
			//Das Headerende wird mit (CR+LF+CR+LF) angezeigt!
			// hdr_end_pointer was incremented when it was checked against, and it has fully matched.
			// (hdr_end_pointer points to '\0' at the end of rx_header_end)
			if(*http_entry[index].hdr_end_pointer == 0) 
			{
				HTTP_DEBUG("<---HEADER ENDE ERREICHT!--->\r\n");
				break;
			}
		}
	}

	// ? Why start at TCP_DATA_START_VAR?
	// ? Perhaps continue?

	//Einzelnes Postpaket (z.B. bei firefox)
	if(http_entry[index].http_auth && http_entry[index].post == 1)
	{
//		PORT_tmp = PORTA;	// aktuellen Status einlesen

		for(a = TCP_DATA_START_VAR;a<(TCP_DATA_END_VAR);a++)
		{	
			//Schaltanweisung finden!
			// Compare with expected POST payload
			if (eth_buffer[a] != *http_entry[index].post_ptr++)
			{
				http_entry[index].post_ptr = post_in;	// revert
			}
			/*? else */if(*http_entry[index].post_ptr == 0) // match
			{
				switch (eth_buffer[a+1])	// ?+check overflow?
				{
				    case ('A'):
					  PORT_tmp ^= (1<<0);	// toggle
				      break;
				
				    case ('B'):
					  PORT_tmp |= (1<<1);	// setzt Ausgang
				      break;
				
				    case ('C'):
					  PORT_tmp |= (1<<2);			// setzt Ausgang
					  machineStatus.Timer1 = 20;	// und timer, der in mainloop runtergezählt wird
				      break;

                    #if USE_WOL
                    case 'W':
                        wol_enable = 1;
			break;
                    #endif //USE_WOL

					/*
					** Hier können weitere Schaltanweisungen eingefügt werden.
					**
					** Das sendende Formularfeld muss den Namen "OUT" haben und
					** ein einzelnes Zeichen als Wert, der gesetzt werden kann.
					**
					** es gibt unterschiedliche Möglichkeiten einen Port zu setzen:
					**	- Befehl setzt oder löscht den Ausgang
					**	- der Ausgang wird bei jedem Befehl umgeschaltet
					**	- der Befehl schaltet den Port, der über einen Timer wieder gelöscht wird.
					**
					** Bereits verwendete Zeichen siehe oben bei den case-Statements.
					*/

				}
				http_entry[index].post_ptr = post_in;
				//Schaltanweisung wurde gefunden
			}
		
			//Submit schließt die suche ab!
			if (eth_buffer[a] != *http_entry[index].post_ready_ptr++)
			{
				http_entry[index].post_ready_ptr = post_ready;	// reset to post_ready on mismatch
			}
			if(*http_entry[index].post_ready_ptr == 0) // reached end of post_ready => complete match
			{
				http_entry[index].post = 0;
//				PORTA = PORT_tmp;
                PORT_tmp = 0;
			break;
			//Submit gefunden
			}
		}
	}	
	



	//Welche datei wird angefordert? Wird diese in der Flashspeichertabelle gefunden?
	unsigned char page_index = 0;
	
	if (!http_entry[index].new_page_pointer
#if USE_MMC
		&& !http_entry[index].mmc	// falls Zeiger noch nicht in Dateipuffer zeigt
#endif
		)
	{
		for(a = TCP_DATA_START_VAR+5;a<(TCP_DATA_END_VAR);a++)	// process resource name after "GET /" ?
		{
			if (eth_buffer[a] == '\r')
			{
				eth_buffer[a] = '\0';	// string includes "HTTP/1.0" or "HTTP/1.1"
				break;
			}
		}
	
#if USE_MMC
		/*
		** falls SD-Karte vorhanden ist wird erst auf der Karte gesucht
		** und danach im Flash Speicher. So können einzelne Dateien
		** immer noch vom Flash benutzt werden (LEDON.GIF ...)
		*/

		// Dateinamen ab 6. Stelle extrahieren (am Anfang steht "GET /")
		// falls POST gesendet wurde eins dazuzählen (ist ein Zeichen länger)
		char *_ptmp = &eth_buffer[TCP_DATA_START_VAR + 5 + http_entry[index].post];	// points to whatever is after "GET /" or "POST /"
		unsigned char *_pfn = http_entry[index].fname;
		unsigned char *_dot = NULL;
		int8_t i = MAX_RESOURCE_NAME_LENGTH;		// max 12 Zeichen, da 8.3-Dateinamen

		// scan the resource name until ' ' (end of resource name), max
		while (*_ptmp && (*_ptmp != ' ') && i--) {
			if (*_ptmp == '.'){
				_dot = _pfn;	// memorize the locacation of the (last) dot.
			}
			*_pfn++ = *_ptmp++;	// copy resource name to http_entry[index].fname, char by char
		}
		*_pfn = 0;	// terminate with '\0'

		if (_dot != NULL) {		// dot was found
			++_dot;			// move '_dot' pointer to point to the file extension
		} else {
			_dot = _pfn;	// points to \0, i.e. empty string.
		}

		HTTP_DEBUG("\r\n%s (%s)... ",http_entry[index].fname, _dot);


		if (*(http_entry[index].fname) == '\0') { // '/' rsource -> served the same way as '/INDEX.HTM'
			strcpy_P((char *)http_entry[index].fname, PSTR("INDEX.HTM"));	// Standard setzen
			_dot = http_entry[index].fname + 6;
		
			//User Counter
			var_array[MAX_VAR_ARRAY-1]++;
		}

                if (!strcmp_P((char*)http_entry[index].fname, PSTR("sys/t"))) {
                    http_entry[index].http_header_type = HTTP_RESPONSE_200_APPLICATION_OCTET_STREAM;
                    http_entry[index].cam = 1; // cam == 1 means serve temperature data (temp. abuse)
                }
                else {

		HTTP_DEBUG("\r\nLookup %s on SD Card",http_entry[index].fname);
		File *sdfile = f16_open((char *)http_entry[index].fname,"r");
		if (sdfile) {
			HTTP_DEBUG("\r\nDatei %s auf SD-Karte gefunden.",http_entry[index].fname);

			http_entry[index].mmc = 1;	// File served from SD card

			if (strncasecmp_P((char *)_dot,PSTR("html"),4)==0) {
				http_entry[index].http_header_type = HTTP_RESPONSE_200_TEXT_HTML;
			} else if (strncasecmp_P((char *)_dot,PSTR("htm"),3)==0) {			// falls htm-Datei
				http_entry[index].http_header_type = HTTP_RESPONSE_200_TEXT_HTML;
			} else if (strncasecmp_P((char *)_dot,PSTR("csv"),3)==0) {	// falls csv-Datendatei
				http_entry[index].http_header_type = HTTP_RESPONSE_200_CSV;
			} else {
				http_entry[index].http_header_type = HTTP_RESPONSE_200_IMAGE_JPEG;	// default ist auch 1
			}

			http_entry[index].filesize = sdfile->dir_entry.file_size;

			// ersten Datenblock setzen
			http_entry[index].charcount = 0;
			http_entry[index].old_charcount = 0;
			f16_close(sdfile);
		}
		else {
#endif
#    include "httpd_render_builtin_page.inc"
#if USE_MMC
		}
                }
#endif
	}

	//Wurde das Ende vom Header nicht erreicht
	//kommen noch weitere Stücke vom Header!
	if ((*http_entry[index].hdr_end_pointer != 0) || (http_entry[index].post == 1))
	{
		//Der Empfang wird Quitiert und es wird auf weiteres Headerstück gewartet
		tcp_entry[index].status =  ACK_FLAG;
		create_new_tcp_packet(0,index);
		//Warten auf weitere Headerpackete
		tcp_entry[index].app_status = 1;
		return;
	}	
	
	//Wurde das Passwort in den ganzen Headerpacketen gefunden?
	//Wenn nicht dann ausführen und Passwort anfordern!
	if((!http_entry[index].http_auth) && tcp_entry[index].status&PSH_FLAG)
	{	
		//HTTP_AUTH_Header senden!
		http_entry[index].new_page_pointer = RESPONSE_401_UNAUTHORIZED;
		memcpy_P((char*)&eth_buffer[TCP_DATA_START_VAR],http_response_401_unauthorized,(sizeof(http_response_401_unauthorized)-1));
		tcp_entry[index].status =  ACK_FLAG | PSH_FLAG;
		create_new_tcp_packet((sizeof(http_response_401_unauthorized)-1),index);
		tcp_entry[index].app_status = 2;
		return;
	}
	
	//Standart INDEX.HTM Seite wenn keine andere gefunden wurde -- oder "404 Not Found" ??
	if (!http_entry[index].new_page_pointer
	#if USE_MMC
		&& !http_entry[index].mmc	// falls Zeiger noch nicht in Dateipuffer zeigt
	#endif
                && !http_entry[index].cam
		)
	{
		http_entry[index].new_page_pointer = Page1;
		http_entry[index].http_header_type = HTTP_RESPONSE_200_TEXT_HTML;
		//Besucher Counter
		var_array[MAX_VAR_ARRAY-1]++;
	}	
	
	tcp_entry[index].app_status = 2;
	/*
	**	Seiten Header wird gesendet
	*/
	switch (http_entry[index].http_header_type) {

		case	HTTP_RESPONSE_200_TEXT_HTML:
			a = (sizeof(http_response_200_text_html)-1);
			memcpy_P((char*)&eth_buffer[TCP_DATA_START_VAR],http_response_200_text_html,a);
			HTTP_DEBUG("\r\nsende OK für text/html");
			break;
	
		case	HTTP_RESPONSE_200_IMAGE_JPEG:
			a = (sizeof(http_response_200_image_jpeg)-1);
			memcpy_P((char*)&eth_buffer[TCP_DATA_START_VAR],http_response_200_image_jpeg,a);
			HTTP_DEBUG("\r\nsende OK für image/jpg");
			break;

		case	HTTP_RESPONSE_200_CSV:
			a = (sizeof(http_csv_header)-1);
			memcpy_P((char*)&eth_buffer[TCP_DATA_START_VAR],http_csv_header,a);
			HTTP_DEBUG("\r\nsende OK für csv-header");
			break;

		case	HTTP_RESPONSE_200_APPLICATION_OCTET_STREAM:
			a = (sizeof(http_application_octet_stream_header)-1);
			memcpy_P((char*)&eth_buffer[TCP_DATA_START_VAR], http_application_octet_stream_header, a);
			HTTP_DEBUG("\r\nSent 200 OK application/octet-stream");
			break;

	}

	HTTP_DEBUG("\r\nmit Header antworten. Index %i L:%i",index,a);
	tcp_entry[index].status =  ACK_FLAG | PSH_FLAG;
	create_new_tcp_packet(a,index);
	return;	
}

//----------------------------------------------------------------------------
/**
 *	\ingroup webserver
 *	Daten Pakete an Client schicken
 *
 * @param[in] index in der TCP Tabelle tcp_entry
 */
void httpd_data_send (unsigned char index)
{	
	//Passwort wurde im Header nicht gefunden
	if(!http_entry[index].http_auth)
	{
		http_entry[index].new_page_pointer = RESPONSE_401_UNAUTHORIZED;
	}

	if(http_entry[index].cam > 0)
	{
            memcpy(&eth_buffer[TCP_DATA_START], ow_array, MAXSENSORS << 1);

                tcp_entry[index].app_status = 0xFFFD;
		create_new_tcp_packet(MAXSENSORS << 1, index);
		return;	
	}

	//kein Paket empfangen Retransmission des alten Paketes
	if (tcp_entry[index].status == 0) 
	{
		http_entry[index].new_page_pointer = http_entry[index].old_page_pointer;
		#if USE_MMC
		if (http_entry[index].mmc) {
			 http_entry[index].charcount = http_entry[index].old_charcount;
		}
		#endif
	}


	char *ptr = &eth_buffer[TCP_DATA_START_VAR];
	uint16_t len = 0;
	char buffer[81];
	uint16_t srclen = 0;




	#if USE_MMC
	if (http_entry[index].mmc) {	// falls Datei von SD-Karte
		/*
		** alte Pointer auf Datenanfang in Datei nachziehen
		*/
		http_entry[index].old_charcount = http_entry[index].charcount;

		File *htmfile = f16_open((char *)http_entry[index].fname,"r");

		if (htmfile) {
			f16_fseek(htmfile,http_entry[index].old_charcount,FAT16_SEEK_SET);

			if (0/*http_entry[index].http_header_type == HTTP_RESPONSE_200_TEXT_HTML*/) {
				// Datei zeilenweise lesen und vorhandene Variable ersetzen
				while ( len < (MTU_SIZE-(TCP_DATA_START)-100) ) {
					if ( f16_gets(buffer, sizeof(buffer), htmfile) == 0 ) {
						tcp_entry[index].app_status = 0xFFFD;
						break;
					}
					HTTP_DEBUG("\r\n>%3i|%s|<",sizeof(buffer),buffer);

					len += translate(buffer, &ptr, &srclen);	// expand template
					http_entry[index].charcount += srclen;
				}
			}
			else {
				// keine .htm Datei -> kein translate!
				len = fat16_read_file(htmfile, (uint8_t*)ptr, MTU_SIZE-(TCP_DATA_START));
				http_entry[index].charcount += len;
				if (len < MTU_SIZE-(TCP_DATA_START)) {
					// alles gelesen
					tcp_entry[index].app_status = 0xFFFD;
				}
			}
			f16_close(htmfile);
		}
		else {
			http_entry[index].mmc = false;
		}
	}

	if ( !http_entry[index].mmc) {	// falls Datei von Flash
	#endif

		/*
		** alte Pointer auf Datenanfang in Flash nachziehen
		*/
		http_entry[index].old_page_pointer = http_entry[index].new_page_pointer;


		if (http_entry[index].http_header_type == HTTP_RESPONSE_200_TEXT_HTML) {	// falls html mit Variablen
			char *ptr2;

			while ( len < (MTU_SIZE-(TCP_DATA_START)-100) ) {
				memcpy_P(buffer, http_entry[index].new_page_pointer, sizeof(buffer)-1);
				// Datei zeilenweise lesen und vorhandene Variable ersetzen
				// CRLF suchen
				if ( (ptr2 = strstr_P(buffer,PSTR("\r\n"))) ) {
					*(ptr2+2) = 0;
					http_entry[index].new_page_pointer += (ptr2 - buffer + 2);
				}
				else {
					buffer[80] = 0;
					http_entry[index].new_page_pointer += sizeof(buffer)-1;
				}

				HTTP_DEBUG("\r\n>%i|%s|<",http_entry[index].new_page_pointer,buffer);
				// Ende-Marker vorhanden ?
				if ( (ptr2 = strstr_P(buffer,PSTR("%END"))) ) {
					HTTP_DEBUG("\r\nFlash-Dateiende.");
					tcp_entry[index].app_status = 0xFFFD;
					*ptr2 = 0;
				}
				// vorhandene Variable ersetzen
				len += translate(buffer, &ptr, &srclen);
				HTTP_DEBUG(" srclen: %3i; len: %i",srclen,len);
				if (ptr2)	// falls %END gefunden wurde -> Ende
					break;
			}
		}
		else {
			// umkopieren und auf %END suchen
			PGM_P src = http_entry[index].new_page_pointer;

			while (len < (MTU_SIZE-(TCP_DATA_START)) ) {
				*ptr = pgm_read_byte(src++);
				if (*ptr == '%' ) {
					if (strncasecmp_P("END",src,3)==0) {
						HTTP_DEBUG("\r\nFlash-Dateiende.");
						tcp_entry[index].app_status = 0xFFFD;
						// --src;	// unnötig, da sowieso Datenende
						break;
					}
				}
				++len;	// zu sendende Zeichen hochzählen
				++ptr;
			}
			http_entry[index].new_page_pointer = src;
		}
	#if USE_MMC
	}
	#endif

	//Erzeugtes Paket kann nun gesendet werden!

	//if (http_entry[index].http_header_type == HTTP_RESPONSE_200_TEXT_HTML)	// für DEBUG String terminieren
	//	*ptr = 0;
	HTTP_DEBUG("\r\n>|%s|< (length %i; new_ptr %i; old_ptr %i)",
							&eth_buffer[TCP_DATA_START_VAR],
							len,http_entry[index].new_page_pointer,buffer,
							http_entry[index].old_page_pointer);
	tcp_entry[index].status =  ACK_FLAG | PSH_FLAG;
	create_new_tcp_packet(len,index);
	return;
}


/**
 * @}
 */

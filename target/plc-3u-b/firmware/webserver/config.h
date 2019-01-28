/*----------------------------------------------------------------------------
 Copyright:      Radig Ulrich  mailto: mail@ulrichradig.de
 Author:         Radig Ulrich
 Remarks:        
 known Problems: none
 Version:        16.11.2008
 Description:    Webserver Config-File

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
 * \ingroup main	Hauptprogramm
 *
 */

/**
 * \file
 * Konfigurationsdatei
 *
 * \author Ulrich Radig & W.Wallucks
 */

// PD0	Console RX
// PD1	Console TX
// PD2	USB, Actuator
// PD3	USB, Actuator
// PD4	Ethernet INT
// PD5	Card CDI
// PD6	Card WP
// PD7	Card DAT2

// PB0	Ethernet CS
// PB1	Card DAT1
// PB2	Card CS
// PB3	MOSI
// PB4	MISO
// PB5	SCK
// PB6	XTAL1
// PB7	XTAL2

// PC0	Ethernet WOL
// PC1		(Sensor)
// PC2	Sensor
// PC3	Sensor
// PC4	Sensor
// PC5	Sensor
// PC6		(Sensor)


#ifndef _CONFIG_H_
	#define _CONFIG_H_	


/** GPIO (sensors, actuators) *************/

	#define sensors_configure() do { } while(0)

/**
 * \port
 *	- Port C - An/Aus Sensoren an Pin 0, 1, 6 und 7
 *	- Portausgang mit Schalter an PD4, PD5 und PD6
 */
#define SENS_Read			PINC	//!< Porteingang an dem die An/Aus Sensoren angeschlossen sind
#define SENS_PULLUP			PORTC	//
#define SENS_DDR			DDRC	
#define SENS_INTENA			PCIE2	// == Port C TODO
#define SENS_INTMASK		PCMSK2
#define SENS_PIN1			2		//!< Sensor an Pin 0
#define SENS_PIN2			3		//!< Sensor an Pin 1
#define SENS_PIN3			4		//!< Sensor an Pin 2
#define SENS_PIN4			5		//!< Sensor an Pin 3
#define SENS_ACTIVE_PINS	((1<<SENS_PIN1) | (1<<SENS_PIN2) | (1<<SENS_PIN3) | (1<<SENS_PIN4))
#define SENS_INT_ENABLE() 	PCICR |= (1<<SENS_INTENA)
#define SENS_INT_DISABLE() 	PCICR &= ~(1<<SENS_INTENA)

	#define sensors_pins_changed() (machineStatus.PINCchanged != 0)
	#define sensor1_pin_changed() (machineStatus.PINCchanged & 1<<SENS_PIN1)
	#define sensor2_pin_changed() (machineStatus.PINCchanged & 1<<SENS_PIN2)
	#define sensor3_pin_changed() (machineStatus.PINCchanged & 1<<SENS_PIN3)
	#define sensor4_pin_changed() (machineStatus.PINCchanged & 1<<SENS_PIN4)

	#define sensor1_pin_value() (machineStatus.PINCStatus & 1<<SENS_PIN1)
	#define sensor2_pin_value() (machineStatus.PINCStatus & 1<<SENS_PIN2)
	#define sensor3_pin_value() (machineStatus.PINCStatus & 1<<SENS_PIN3)
	#define sensor4_pin_value() (machineStatus.PINCStatus & 1<<SENS_PIN4)



#define PORT_SCHALTER1		PD1		//!< Portausgang mit Schalter
#define PORT_SCHALTER2		PD2		//!< Portausgang mit Schalter
#define PORT_SCHALTER3		PD3		//!< Portausgang mit Schalter
#define OUT_DDR			DDRD
#define OUT_PORT		PORTD


        // configure pins for actuators: PD1,PD2,PD3 are outputs (PD1 is USART TX, actually)
	#define actuators_pins_configure() do { DDRD |= ((1<<PD1)|(1<<PD2)|(1<<PD3)); } while(0)


/*
* Schalter1-3 schalten
*/
#define S1An()		OUT_PORT |= (1<<PORT_SCHALTER1)		//!< Port high schalten
#define S1Aus()		OUT_PORT &= ~(1<<PORT_SCHALTER1)	//!< Port low  schalten
#define S1Toggle()	OUT_PORT ^= (1<<PORT_SCHALTER1)		//!< Port umschalten

#define S2An()		OUT_PORT |= (1<<PORT_SCHALTER2)
#define S2Aus()		OUT_PORT &= ~(1<<PORT_SCHALTER2)
#define S2Toggle()	OUT_PORT ^= (1<<PORT_SCHALTER2)

#define S3An()		OUT_PORT |= (1<<PORT_SCHALTER3)
#define S3Aus()		OUT_PORT &= ~(1<<PORT_SCHALTER3)
#define S3Toggle()	OUT_PORT ^= (1<<PORT_SCHALTER3)



/** Ethernet *************/


/*
	- PortD Pin4 - Interrupt from ENC28j60 (PCINT2 used)
	- PortB Pin0 - Chip Select for ENC28j60
	- PortB Pin3 - MOSI
	- PortB Pin4 - MISO
	- PortB Pin5 - SCK
*/
	
	#define USE_ENC28J60	1	// ETH_M32_EX / Webmodul (www.ulrichradig.de)
	#define USE_RTL8019		0	// Holger Buss (www.mikrocontroller.com) Mega32-Board
	#define NET_IO_BOARD	0	// NET_IO_BOARD (Pollin)

	//Achtung!!!! an PORTB ist der ENC
	//nur ändern wenn man weiß was man macht!


	//! Umrechnung von IP zu unsigned long
	#define IP(a,b,c,d) ((unsigned long)(d)<<24)+((unsigned long)(c)<<16)+((unsigned long)(b)<<8)+a

	//IP des Webservers
	#define MYIP		IP(192,168,2,98)	//!< default IP des Webservers

	//Netzwerkmaske
	#define NETMASK		IP(255,255,255,0)	//!< default Netzwerkmaske
	
	//IP des Routers
	#define ROUTER_IP	IP(192,168,2,1)		//!< default IP des Routers/Gateway
	
	//IP des DNS-Servers
	#define USE_DNS		0					//!< mit/ohne DNS-Client
	#define DNS_IP		IP(192,168,2,1)		//!< IP des DNS-Servers

	//NTP Einstellen der Zeit mittels NTP
	#define USE_NTP		0 					//!< 1 = NTP Client on
	#define NTP_IP		IP(85,10,196,184)	//!< IP des NTP-Servers z.B. Server 1.de.pool.ntp.org
	#define NTP_SERVER	"1.de.pool.ntp.org"	//!< hostname des NTP-Servers, wird über DNS aufgelöst

	// don't touch! -- NTP-Server wird über DNS aufgelöst
	#if USE_NTP
	#undef	USE_DNS
	#define USE_DNS			0
	#endif


#define USE_NOTIFICATIONS          1
#define NOTIFICATIONS__SERVER_HOST IP(192,168,2,20)
#define NOTIFICATIONS__SERVER_PORT (8080)

	
	//Broadcast-Adresse für WOL
	#define USE_WOL			0 				//!< 1 = WOL on
	#define WOL_BCAST_IP	IP(192,168,2,255)
	#define WOL_MAC 		{0x00,0x1A,0xA0,0x9C,0xC6,0x0A}
	
	//! MAC Adresse des Webservers	
	#define MYMAC1	0x00
	#define MYMAC2	0x20
	#define MYMAC3	0x18
	#define MYMAC4	0xB1	
	#define MYMAC5	0x15
	#define MYMAC6	0x3F
	
	//Taktfrequenz
	//#define F_CPU 16000000UL	
	//#define F_CPU 14745600UL
	//#define F_CPU 11059200UL
	#define F_CPU 20000000UL
	
	#define TIMERBASE		25		//!< Zeitbasis für Timerinterrupt ist 25 ms

	// Timertakt intern oder extern
	// dies hat nichts mit dem Prozessortakt zu tun!
	#define EXTCLOCK 0 //0=Intern 1=Externer Uhrenquarz


	#define SPI_DDR                 (DDRB)
	#define SPI_PORT                (PORTB)
	#define SPI_SCK                 (5)
	#define SPI_MISO                (4)
	#define SPI_MOSI                (3)
	#define SPI_SS                  (2)

	#define ENC_CS                  (0)
	#define ENC_CS_DDR              (DDRB)
	#define ENC_CS_PORT             (PORTB)
	#define ENC_CS_PIN              (PINB)

	#define enc_select()            do { ENC_CS_PORT &= ~(1<<ENC_CS); } while(0)
	#define enc_deselect()          do { ENC_CS_PORT |= (1<<ENC_CS); } while(0)


	// Ethernet interrupt. Pin is input by default - no need to initialize
	#define ENC_INT                 (4)
	#define ENC_INT_PORT		(PORTD)
	#define ENC_INT_PIN             (PIND)
	#define ENC_INT_DDR             (DDRD)

	#define ETH_INTERRUPT           PCINT2_vect
	#define ETH_INT_ACTIVE          (!(ENC_INT_PIN & (1<<ENC_INT)))

// TODO
	#if defined (__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
		#define ETH_INT_ENABLE  do { PCMSK2 |= (1<<4);} while(0)
		#define ETH_INT_DISABLE do { PCMSK2 &= ~(1<<4);} while(0)
	#endif

/*
	#if defined (__AVR_ATmega32__)
		#define ETH_INT_ENABLE  GICR |= (1<<INT2)
		#define ETH_INT_DISABLE GICR &= ~(1<<INT2)
	#endif

	#if defined (__AVR_ATmega644__) || defined (__AVR_ATmega644P__)
		#define ETH_INT_ENABLE  EIMSK |= (1<<INT2)
		#define ETH_INT_DISABLE EIMSK &= ~(1<<INT2)
	#endif
*/


/** USART *************/
	#define BAUDRATE 	250000		//!< Baudrate der seriellen Schnittstelle
	#define USART_USE1		0		//!< 0 für USART0 und 1 für USART1 bei ATmega644P
									//	 Kamera ist dann an der anderen Schnittstelle
	
/** LCD ***************/
	#define USE_SER_LCD		0		//!< LCD Routinen mit einbinden
	#define USE_LCD_4Bit	0		//!< LCD im 4Bit Mode oder seriell

/** ADC ***************/
	#define USE_ADC			0		//!< AD-Wandler benutzen?
	#define MAXADCHANNEL	5		//!< max. Anzahl der verwendeten Ports für AD-Wandler (PA0 bis PAn; n = MAXADCHANNEL - 1)

/** 1-Wire ************/
	#define USE_OW			1		//!< 1-Wire bus einbinden
	#define MAXSENSORS		4		//!< max. Anzahl der 1-wire sensoren (DS18B20)
	#define OW_ONE_BUS		1		//!< nur ein fest eingestellter 1-wire bus; keine Auswahl
									//   die Ports werden in onewire.h definiert
	#define OW_EXTERN_POWERED 1		//!< falls der 1-Wire bus eine externe Versorgungsspannung hat
	#define OW_ROMCODE_SIZE 8		//!< rom-code DS18B20 size including CRC

	// hier die ausgelesenen ROM-IDs der DS18B20 eintragen
	#define OW_ID_T01		{0x28, 0x2E, 0x29, 0xA2, 0x04, 0x00, 0x00, 0x80}
	#define OW_ID_T02		{0x28, 0xA9, 0x39, 0xA3, 0x04, 0x00, 0x00, 0x1C}
	#define OW_ID_T03		{0x28, 0x68, 0x4E, 0xA2, 0x04, 0x00, 0x00, 0x07}
	#define OW_ID_T04		{0x28, 0xAE, 0xD7, 0xA2, 0x04, 0x00, 0x00, 0x6E}

        #define OW_IDS {OW_ID_T01, OW_ID_T02, OW_ID_T03, OW_ID_T04}
/** Kamera ************/
	//Kamera mit einbinden
	//Kamera arbeitet nur mit einem 14,7456Mhz Quarz!
	#define USE_CAM			0
	#define USE_SERVO		0
	//In cam.c können weitere Parameter eingestellt werde
	//z.B. Licht, Kompression usw.
	//Auflösungen
	//0 = 160x120 Pixel kürzer (zum testen OK ;-)
	//1 = 320x240 Pixel ca. 10 Sek. bei einem Mega644
	//2 = 640x480 Pixel länger (dauert zu lang!)
	#define CAM_RESOLUTION	1

/** SD-Karte **********/
	// My SD card config:
	// available:   PD5
	// locked:	PD6
	// select:      PB2


	// USE_MMC ist Voraussetzung für
	// - TCP_SERVICE	FTP ohne Dateisystem ist nicht sinnvoll ;-)
	// - E_Mail			Mailtexte werden von Karte gelesen
	// - Scheduler		Konfiguration der Schaltzeiten auf SD-Karte
	// - Logdatei		8-))
	//
	#define USE_MMC			1		//!< mit/ohne SD-Karte
	#define MAX_PATH		63		//!< maximale Pfadlänge für FAT16-Directory


	/* defines for customisation of sd/mmc port access */

	/*
	 * - PortB Pin4 Slave Select für SD-Karte (not used!)
	 */
	//#define configure_pin_ss() DDRB |= (1 << PB4)

	/**
	 * \port
	 * - PortB Pin1 Chip Select für SD-Karte
	 */
	#define configure_pin_cs() DDRB |= (1 << PB2)

	/**
	 * \port
	 * - PortA Pin6 auf Eingang und PullUp einschalten;
	 * Schalter zieht auf Masse bei gesteckter SD-Karte
	 */
	#define configure_pin_available() do { DDRD &= ~(1 << PD5); PORTD |= (1<<PD5); } while(0)

	/**
	 * \port
	 * - PortA Pin7 auf Eingang und PullUp einschalten;
	 * Schalter zieht auf Masse bei Schreibschutz für SD-Karte
	 */
	#define configure_pin_locked() do { DDRD &= ~(1 << PD6); PORTD |= (1<<PD6); } while(0)


	#define get_pin_available() ((PIND & (1<<PD5)))
	#define get_pin_locked() ((PIND & (1<<PD6)))

	#define select_card() PORTB &= ~(1 << PB2)
	#define unselect_card() PORTB |= (1 << PB2)





/** TCP-Service *******/
	#define TCP_SERVICE		0		//!< mit/ohne TCP-Service (FTP, Telnet-Cmdline)
	#define MYTCP_PORT		61234	//!< Port# für Telnet-Cmd Interpreter	
	#define DOS_LIST		1		//!< DOS style Directory-Listing
	//#define UNIX_LIST		1
	#define FTP_ANONYMOUS	1		//!< anonymen Login (ohne User/Kennwort) erlauben
	#define FTP_USER		"chef"	//!< FTP-User, falls nicht anonym
	#define FTP_PASSWORD	"123"	//!< FTP-Passwort

	// don't touch!
	#ifdef DOS_LIST
		#undef UNIX_LIST
	#endif

/** Telnet ************/
	#define USE_TELNET 0

/** Serial terminal ************/
	#define USE_TERMINAL 1


/** Passwort **********/
	#define HTTP_AUTH_DEFAULT	1	//!< Webserver mit Passwort? (0 == mit Passwort)
	
	//AUTH String "USERNAME:PASSWORT" max 14Zeichen
	//für Username:Passwort
	#define HTTP_AUTH_STRING "admin:uli1"
	
/** E-Mail ************/
    #define USE_MAIL			0			//!< sendmail verwenden
	#define MAIL_DATAFILE		"mail.ini"	//!< Datei für E-Mail Runtime-Konfiguration

	// don't touch! -- Mail benötigt DNS-Auflösung und die SD-Karte
	#if USE_MAIL
	#undef	USE_DNS
	#define USE_DNS			1
	#endif

/** Webserver abfragen **/
    //! Empfang von Wetterdaten auf der Console (über HTTP_GET)
    #define GET_WEATHER			0
    
/** Telnet -> Befehlszeile oder USART *********/
    #define CMD_TELNET      	0			//!< Kommandos und Ausgaben erfolgen über Telnet (Port 23)

/** Infrarot Fernbedienung **/
	#define USE_RC5				0
	#define	RC5_DDR				DDRC		//!< IR input port Data Direction Register
	#define	RC5_INPORT			PINC		//!< IR input port
	#define	RC5_PIN				PC5			//!< \port PC5 - IR input pin

/** Scheduler *********/
    #define USE_SCHEDULER		0			//!< Scheduler verwenden
	#define	TM_MAX_SCHALTZEITEN	16			//!< Anzahl unterschiedlicher Schaltzeiten
	#define SCHED_INIFILE		"avr.ini"	//!< Dateiname für Schaltzeiten
	#define TIME_TEMP			60			//!< jede Minute (60 sec) Temperaturen messen
	#define USE_LOGDATEI		0			//!< Logdatei schreiben

	#define MAX_VAR_ARRAY		4			//!< Anzahl Speicherplätze für Messwerte etc.

/*------------------------------------*/
	// don't touch!
	#if NET_IO_BOARD
		#undef	USE_ENC28J60		// Net_IO läuft mit ENC28J60
		#define USE_ENC28J60	1

		#undef	USE_MMC				// Net_IO hat keine SD-Karte
		#define USE_MMC			0
	#endif

	// don't touch! -- siehe oben unter SD-Karte
	#if !USE_MMC
		#undef  TCP_SERVICE
		#define TCP_SERVICE 	0

		#undef  USE_MAIL
		#define USE_MAIL 		0

		#undef  USE_SCHEDULER
		#define USE_SCHEDULER	0

		#undef  USE_LOGDATEI
		#define USE_LOGDATEI	0

		#undef	USE_DNS
		#define USE_DNS			0
	#endif

	//#if TCP_SERVICE
	//	#define _CMD_H_
	//#else
	//	#define _TCPCMD_H_
	//#endif

/*------------------------------------
*	typedefs
*/
#ifndef __STDINT_H_
	#include <stdint.h>
#endif

typedef enum { false, true } bool;

/**
 *	\ingroup main
 *	aktueller Zustand der Schalter und Zähler
 */
typedef struct
{
	volatile bool		relais1;			// Relais an/aus
	volatile bool		relais2;
	volatile bool		relais3;
	volatile uint8_t 	TReglerWert;
	volatile uint16_t 	Zaehler1;			// Zählerwerte
	volatile uint16_t 	Zaehler2;
	volatile uint16_t 	Zaehler3;
} ANLAGEN_STATUS;

/**
 *	\ingroup main
 *	Zustandsbeschreibung der angeschlossenen Schalter und Relais
 */
typedef struct
{
	volatile uint8_t	Schalter1	: 1;	// Sollzustand an/aus
	volatile uint8_t	Schalter2	: 1;
	volatile uint8_t	Schalter3	: 1;
	volatile uint8_t 	TReglerWert;
} SOLL_STATUS;

/**
 *	\ingroup schedul
 *	Schaltaktion mit Wochentag und Uhrzeit
 */
typedef struct 
{
	volatile uint8_t		Uhrzeit;		//!< Tageszeit
	volatile uint8_t 		Wochentag;		//!< pro Tag ein bit
	volatile SOLL_STATUS	Zustand;		//!< Sollzustand der Schalter
} TM_Aktion;

/**	
 * \ingroup main
 * Prototyp für Timerfunktion
 */
typedef void(*timercmd_fp)(void);


/**
 *	\ingroup main
 *	Prozessstatus und aktuelle Werte für die Endlosschleife in main()
 */
typedef struct
{
	volatile uint8_t		timeChanged;	//!< Zeitmessung geändert
	volatile bool 			initialisieren;	//!< Maschine muss initialisiert werden
	volatile bool 			Tlesen;			//!< Temperaturen müssen gelesen werden
	volatile bool 			regeln;			//!< Werte einstellen
	volatile bool 			LogInit;		//!< SD-Karte mit Logdatei neu initialisieren
	volatile bool 			LogSchreiben;	//!< Werte müssen geloggt werden
	volatile bool			ADCgemessen;	//!< analoger Wert am ADC wurde gemessen
#if USE_MAIL
	volatile uint8_t		sendmail;		//!< # der zu sendenden E-Mail
#endif
	volatile unsigned char	PINCchanged;	//!< Eingang wurde geändert
#ifdef PINA
	volatile unsigned char	PINAStatus;		//!< letzter Wert für PINA
#endif
	volatile unsigned char	PINCStatus;		//!< letzter Wert für PINC
	volatile unsigned char	PINDStatus;		//!< letzter Wert für PIND
	volatile uint8_t 		Timer1;			//!< Countdown Timer #1
	volatile uint8_t 		Timer2;			//!< Countdown Timer #2
	timercmd_fp				Timer2_func;
	volatile uint8_t 		Timer3;			//!< Countdown Timer #3
	volatile bool			Time3Elapsed;	
	timercmd_fp				Timer3_func;
#if USE_RC5
	volatile uint16_t 		lastRC5data;	//!< letzter gültiger RC5 Code
	int8_t					disp_index;		//!< aktueller angezeigter Wert im LCD
#endif
} PROZESS_STATUS;



#if USE_MMC

#include "sdkarte/fat16.h"	// Definitionen für Dateisystem-Strukturen

/**
 *	\ingroup sdkarte
 *	FAT Dateistruktur
 */
typedef struct fat16_file_struct
{
    struct fat16_fs_struct* fs;					//!<
    struct fat16_dir_entry_struct dir_entry;	//!<
    uint32_t pos;								//!< aktuelle Schreib-/Lese-Position in Datei
    uint16_t pos_cluster;						//!< aktueller Datei cluster im Puffer
	char	mode;								//!< file open mode
} File;

/**
 *	\ingroup main
 *	Status der Logdatei
 */
typedef struct
{
	const char			log_datei[13];	//!< aktueller Dateiname der Logdatei
	File 				*logfile;		//!< Zeiger auf FILE-Struktur der offenen Logdatei
	volatile uint8_t	logTag;			//!< Tag der Logdatei
	volatile uint8_t	logMonat;		//!< Monat der Logdatei
	volatile uint8_t	logJahr;		//!< Jahr der Logdatei
} LOG_STATUS;

#endif


/*------------------------------------
*	globale Variable
*/
	extern volatile ANLAGEN_STATUS	anlagenStatus;
	extern volatile PROZESS_STATUS 	machineStatus;
#if USE_MMC
	extern 			LOG_STATUS		logStatus;
#endif
	extern volatile SOLL_STATUS 	anlagenSollStatus;
	extern unsigned int var_array[MAX_VAR_ARRAY];

#endif //_CONFIG_H


/*
 */

/*----------------------------------------------------------------------------
 Copyright:      Radig Ulrich  mailto: mail@ulrichradig.de
 Author:         Radig Ulrich
 Remarks:        
 known Problems: none
 Version:        09.11.2007
 Description:    Html Seiten

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
 * \addtogroup webserver
 *
 *
 * @{
 */

/**
 * \file
 * webpage.h
 *
 *	Javascript und grafische Schaltbuttons von Andy
 *
 * \author Ulrich Radig & W.Wallucks & Andy
 */

#ifndef _WEBPAGE_H
	#define _WEBPAGE_H

#include <avr/pgmspace.h>

//****************************************************************************
//Dateien und Webseiten am ende dieser Seite in Tabelle eintragen !!!!!!!
//****************************************************************************


//----------------------------------------------------------------------------
//Dazustellende Webseite
const char name_Page1[] PROGMEM = "index.htm";
const char Page1[] PROGMEM = {"Page1%END"};

//----------------------------------------------------------------------------
//Status Seite
const char name_Page4[] PROGMEM = "Status.htm";
const char Page4[] PROGMEM = {"Page4%END"};
//----------------------------------------------------------------------------
//Das GIF Bild f�r LED on
const char name_led_on[] PROGMEM = "ledon.gif";
const char led_on[] PROGMEM = 
	{'%','E','N','D'};
	
//----------------------------------------------------------------------------
//Das GIF Bild f�r den LED off
const char name_led_off[] PROGMEM = "ledoff.gif";
const char led_off[] PROGMEM =
	{'%','E','N','D'};
	
//----------------------------------------------------------------------------
//Das GIF Bild f�r den Balken
const char name_bild_balken[] PROGMEM = "balke.gif";
const char bild_balken[] PROGMEM = 
	{'%','E','N','D'};

//----------------------------------------------------------------------------
//Das GIF Bild f�r die Rakete
const char name_bild_rakete[] PROGMEM = "raket.gif";
const char bild_rakete[] PROGMEM = 
	{'%','E','N','D'};

//Nur Dateiname und Pointer eintragen	
const WEBPAGE_ITEM WEBPAGE_TABLE[] PROGMEM = // Befehls-Tabelle
{
	{name_Page1,Page1},
	{name_Page4,Page4},
	{name_bild_rakete,bild_rakete},
	{name_bild_balken,bild_balken},
	{name_led_on,led_on},
	{name_led_off,led_off},
	{NULL,NULL} 
};

#endif //_WEBPAGE_H


/**
 * @}
 */







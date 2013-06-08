/*----------------------------------------------------------------------------
 Copyright:      W.Wallucks
 Remarks:        
 known Problems: none
 Version:        04.05.2008
 Description:    messen und regeln mit dem Webmodul

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
 * \addtogroup messen Datenaufnahme und Logging
 *
 * @{
  */

/**
 * \file
 * Messung.h
 * Definitionen der Ports für angeschlossene Relais und Schalter
 *
 * \author W.Wallucks
 */

/**
 * @}
 */
#ifndef _MESSUNG_H_
	#define _MESSUNG_H_

#if USE_OW
extern volatile int16_t ow_array[MAXSENSORS];	// Speicherplatz für 1-wire Sensorwerte
#endif

//----------------------------------------------------------------------------
// Prototypen
void messung_init(void);
uint8_t start_OW(void);
void lese_Temperatur(void);
void set_SensorResolution(void);
int16_t initSchaltzeiten(char *);
void regelAnlage(SOLL_STATUS *);
void log_init(void);
void log_status(void);

#endif

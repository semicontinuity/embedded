/*----------------------------------------------------------------------------
 Copyright:      W.Wallucks
 Remarks:        
 known Problems: none
 Version:        04.05.2008
 Description:    messen und regeln mit dem Webmodul

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
 * \addtogroup messen Datenaufnahme und Logging
 *
 * @{
  */

/**
 * \file
 * Messung.h
 * Definitionen der Ports f�r angeschlossene Relais und Schalter
 *
 * \author W.Wallucks
 */

/**
 * @}
 */
#ifndef _MESSUNG_H_
	#define _MESSUNG_H_

#if USE_OW
extern volatile int16_t ow_array[MAXSENSORS];	// Speicherplatz f�r 1-wire Sensorwerte
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

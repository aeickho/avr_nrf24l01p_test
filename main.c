/************************************************************************/
/*                                                                      */
/*                      UART test program                               */
/*                                                                      */
/*              Author: Peter Dannegger                                 */
/*                                                                      */
/************************************************************************/
#include "main.h"
#include "uart0.h"
#include "funk/nrf24l01p.h"
#include "funk/mega48.h"
#include "funk/openbeacon.h"

#include <string.h>
uint8_t buf[16];

void
delay_1ms (u16 i)
{
  do
    {
      _delay_ms (1);
    }
  while (--i);
}


int
main (void)
{
struct NRF_CFG config;
    uint8_t buf[16];
    
 
  init_uart0 ((u16) (XTAL / BAUD / 16 - 0.5));
  sei ();
  delay_1ms (300);
  uputs0 ("\n\r");
  uputs0 ("nRF\n\r");
  cli ();
  sei ();

  uputs0 ("nrf_init, ");
  nrf_init(); 
  uputs0 ("done\n\r");

  uputs0 ("sendConfig, "); //activate Interrupts
  config.nrmacs=1;
  config.maclen[0] = 16;
  config.channel = 81;
  memcpy(config.mac0, "\x01\x02\x03\x02\x01", 5);
  nrf_config_set(&config);
                        
  uputs0 ("done\n\r");

  uputs0 ("read:\n\r");  
  do
    {
//     uputs0 ("w:");
     
      if (nrf_rcv_pkt_time (64, sizeof (buf), buf) == 16)
	{
//	uputs0 ("r\n\r");
	  buf[14] = 0;
	  if (buf[1] == 0x23 || buf[1] == 0x24)
	    {
               uputs0 ((char *) (buf + 6));
 	      uputs0 ("\n\r");
	    }
	}
//    uputs0 ("\n\r");
    }
  while (1);


}

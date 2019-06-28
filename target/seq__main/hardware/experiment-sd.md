## MidiBox SEQ V4 LCD connections

|                 |      | Conflict         |
|-----------------|------|------------------|
| SI (SPI1 MISO)  | PA6  | DIS3_E           |
| SO (SPI1 MOSI)  | PA7  | ETH_RMII_CRS_DV  |
| SC (SPI1 SCK)   | PA5  | not 5V tolerant  |
| RC2             | PD11 | DIS0_D3          |
| RC1             | PB2  | DIS1_D2          |

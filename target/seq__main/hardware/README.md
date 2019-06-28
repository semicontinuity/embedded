## General information

Pins that are not 5V tolerant:

- PA4
- PA5

Pins than can only sink 3mA max:

- PC13
- PC14
- PC15


## SPI pin-out

|                 |      | Conflict         |
|-----------------|------|------------------|
| SPI1_NSS        | PA4  |                  |
| SPI3_NSS        | PA4  |                  |
| SPI1_SCK        | PA5  |                  |
| SPI1_MISO       | PA6  |                  |
| SPI1_MOSI       | PA7  | ETH_RMII_CRS_DV  |
| SPI1_NSS        | PA15 |                  |
| SPI3_NSS        | PA15 |                  |
| SPI1_SCK        | PB3  | DIS1_D3          |
| SPI3_SCK        | PB3  | DIS1_D3          |
| SPI1_MISO       | PB4  | DIS1_D4          |
| SPI3_MISO       | PB4  | DIS1_D4          |
| SPI1_MOSI       | PB5  | DIS1_D5          |
| SPI3_MOSI       | PB5  | DIS1_D5          |
| SPI2_NSS        | PB9  | I2C1_SDA         |
| SPI2_SCK        | PB10 |                  |
| SPI2_NSS        | PB12 | ETH_RMII_TXD0    |
| SPI2_SCK        | PB13 | ETH_RMII_TXD1    |
| SPI2_MISO       | PB14 |                  |
| SPI2_MOSI       | PB15 |                  |
| SPI2_MISO       | PC2  |                  |
| SPI2_MOSI       | PC3  |                  |
| SPI3_SCK        | PC10 | SDIO_D2          |
| SPI3_MISO       | PC11 | SDIO_D3          |
| SPI3_MOSI       | PC12 | SDIO_CK          |


## I2C pin-out

|                 |      | Conflict         |
|-----------------|------|------------------|
| I2C3_SCL        | PA8  |                  |
| I2C3_SMBA       | PA9  |                  |
| I2C1_SMBA       | PB5  |                  |
| I2C1_SCL        | PB6  |                  |
| I2C1_SDA        | PB7  |                  |
| I2C1_SCL        | PB8  |                  |
| I2C1_SDA        | PB9  |                  |
| I2C2_SCL        | PB10 |                  |
| I2C2_SDA        | PB11 | ETH_RMII_TX_EN   | 
| I2C2_SMBA       | PB12 | ETH_RMII_TXD0    |
| I2C3_SDA        | PC9  | SDIO_D1          |

## USART pin-out

|                 |      | Conflict         |
|-----------------|------|------------------|
| UART4_TX        | PA0  |                  |
| UART4_RX        | PA1  | ETH_RMII_REF_CLK |
| USART2_TX       | PA2  | ETH_MDIO         |
| USART2_RX       | PA3  |                  |
| USART1_TX       | PA9  | DIS0_D1          |
| USART1_RX       | PA10 | DIS0_D2          |
| USART1_TX       | PB6  | DIS1_D6          |
| USART1_RX       | PB7  | DIS1_D7          |
| USART3_TX       | PB10 |                  |
| USART3_RX       | PB11 | ETH_RMII_TX_EN   |
| USART3_TX       | PC10 | SDIO_D2          |
| USART3_RX       | PC11 | SDIO_D3          |
| UART4_TX        | PC10 | SDIO_D2          |
| UART4_RX        | PC11 | SDIO_D3          |
| UART5_TX        | PC12 | SDIO_CK          |
| UART5_RX        | PD2  | SDIO_CMD         |
| USART2_TX       | PD5  | +                |
| USART2_RX       | PD6  | +                |
| USART3_TX       | PD8  | N/A              |
| USART3_RX       | PD9  | N/A              |

## SD Card slot pin-out (9; 1-8)

|    |         |
|----|---------|
|  1 | CD/DAT3 |
|  2 | CMD     |
|  3 | Vss1    |
|  4 | Vdd     |
|  5 | CLK     |
|  6 | Vss2    |
|  7 | DAT0    |
|  8 | DAT1    |
|  9 | DAT2    |

## SD Card connections

|    |        |
|----|--------|
|PC8 |SDIO_D0 |
|PC9 |SDIO_D1 |
|PC10|SDIO_D2 |
|PC11|SDIO_D3 |
|PC12|SDIO_CK |
|PD2 |SDIO_CMD|


## Ethernet PHY connections

|                 |      |
|-----------------|------|
|ETH_RMII_REF_CLK | PA1  |
|ETH_MDIO         | PA2  |
|ETH_RMII_CRS_DV  | PA7  |
|ETH_MDC          | PC1  |
|ETH_RMII_RXD0    | PC4  |
|ETH_RMII_RXD1    | PC5  |
|ETH_RMII_TX_EN   | PB11 |
|ETH_RMII_TXD0    | PB12 |
|ETH_RMII_TXD1    | PB13 |
|ETH_RST_PIN (OPT)| PE2  |


## USB OTG FS connections

|                 |      |
|-----------------|------|
|OTG_FS_SOF       | PA8  |
|OTG_FS_VBUS      | PA9  |
|OTG_FS_ID        | PA10 |
|OTG_FS_DM        | PA11 |
|OTG_FS_DP        | PA12 |


## CAN connections

|                 |      |
|-----------------|------|
|CAN1_RX          | PA11 |
|CAN1_TX          | PA12 |
|CAN2_RX          | PB5  |
|CAN2_TX          | PB6  |
|CAN1_RX          | PB8  |
|CAN1_TX          | PB9  |
|CAN2_RX          | PB12 |
|CAN2_TX          | PB13 |
|CAN1_RX          | PD0  |
|CAN1_TX          | PD1  |


## DIY More board pin-out (bottom view, outdated)

|            |    |    |            |    |    |    |    |    |    |    |    |    |    |    |    |            |    |    |            |
|------------|----|----|------------|----|----|----|----|----|----|----|----|----|----|----|----|------------|----|----|------------|
|            |    |    |            |    |DIS3|DIS3|ETH |ETH |    |    |    |    |    |    |SDIO|            |    |    |            |
|            |    |    |            |    |D5  |D7  |RMII|RMII|    |    |    |    |    |    |D0  |            |    |    |            |
|            |    |    |            |    |    |    |TXEN|TXD0|    |    |    |    |    |    |    |            |    |    |            |
|------------|----|----|------------|----|----|----|----|----|----|----|----|----|----|----|----|------------|----|----|------------|
|            |    |    |            |PE11|PE13|PE15|PB11|PB12|PB14|PD8 |PD10|PD12|PD14|PC6 |PC8 |            |    |    |            |
|            |    |    |            |PE12|PE14|PB10|GND |3.3V|PB13|PB15|PD9 |PD11|PD13|PD15|PC7 |            |    |    |            |
|------------|----|----|------------|----|----|----|----|----|----|----|----|----|----|----|----|------------|----|----|------------|
|            |    |    |            |DIS3|DIS3|    |    |    |ETH |    |    |    |    |    |    |            |    |    |            |
|            |    |    |            |D4  |D6  |    |    |    |RMII|    |    |    |    |    |    |            |    |    |            |
|            |    |    |            |    |    |    |    |    |TXD1|    |    |    |    |    |    |            |    |    |            |
|------------|----|----|------------|----|----|----|----|----|----|----|----|----|----|----|----|------------|----|----|------------|
|            |GND |BT1 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |    |    |            |
|            |GND |BT0 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |    |    |            |
|            |PB2 |PE10|DIS3_D2     |    |    |    |    |    |    |    |    |    |    |    |    |            |VCC |GND |            |
|DIS3_D1     |PE9 |PE8 |DIS3_D0     |    |    |    |    |    |    |    |    |    |    |    |    |SDIO_D1     |PC9 |PA8 |            |
|            |PE7 |PE1 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |PA9 |PA10|            |
|            |PB9 |PB8 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |PA11|PA12|            |
|            |PB1 |PB0 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |PA13|PA14|            |
|ETR1        |PC5 |PC4 |ETR0        |    |    |    |    |    |    |    |    |    |    |    |    |            |PA15|PC10|SDIO_D2     |
|ETDV        |PA7 |PA6 |            |    |    |    |    |    |    |    |    |    |    |    |    |SDIO_D3     |PC11|PC12|SDIO_CK     |
|            |PA5 |PA4 |            | -- | -- |    |    |    |    |    |    |    |    |    |    |            |PD0 |PD1 |            |
|            |PA3 |PC3 |            |    |    |    |    |    |    |    |    |    |    |    |    |SDIO_CMD    |PD2 |PD3 |            |
|ETMI        |PA2 |PA1 |ETH_REF_CLK |    |    |    |    |    |    |    |    |    |    |    |    |            |PD4 |PD5 |            |
|            |PA0 |PC2 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |PD6 |PD7 |            |
|ETMC        |PC1 |PC0 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |PB3 |PB4 |            |
|            |GND |3.3V|            |    |    |    |    |    |    |    |    |    |    |    |    |            |PB5 |PB6 |            |
|            |PC13|PE6 |            | -- |    |    |    |    |    |    |    |    |    |    |    |            |PB7 |PE0 |DIS2_D0     |
|            |PE5 |PE4 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |3.3V|GND |            |
|            |PE3 |PE2 |            |    |    |    |    |    |    |    |    |    |    |    |    |            |VCC |GND |            |


## DIY More board pin-out (top view)

|            |    |    |            |    |    |    |    |    |    |    |    |    |    |    |    |            |    |    |            |
|------------|----|----|------------|----|----|----|----|----|----|----|----|----|----|----|----|------------|----|----|------------|
|            |    |    |            |SDIO|?SPI|DIS0|DIS0|DIS0|DIS0|?SPI|ETH |ETH |DIS3|DIS3|DIS3|            |    |    |            |
|            |    |    |            |D0  |CS1 |D6  |D4  |D2  |D0  |MISO|TXD0|TX  |D7  |D5  |D3  |            |    |    |            |
|            |    |    |            |    |    |    |    |    |    |    |&   |EN  |    |    |    |            |    |    |            |
|------------|----|----|------------|----|----|----|----|----|----|----|----|----|----|----|----|------------|----|----|------------|
|            |    |    |            |PC8 |PC6 |PD14|PD12|PD10|PD8 |PB14|PB12|PB11|PE15|PE13|PE11|            |    |    |            |
|            |    |    |            |PC7 |PD15|PD13|PD11|PD9 |PB15|PB13|3.3V|GND |PB10|PE14|PE12|            |    |    |            |
|------------|----|----|------------|----|----|----|----|----|----|----|----|----|----|----|----|------------|----|----|------------|
|            |    |    |            |?SPI|DIS0|DIS0|DIS0|DIS0|?SPI|ETH |3.3V|GND |?SPI|DIS3|DIS3|            |    |    |            |
|            |    |    |            |CS2 |D7  |D5  |D3  |D1  |MOSI|TXD1|    |    |SCK |D6  |D4  |            |    |    |            |
|            |    |    |            |    |    |    |    |    |    |&   |    |    |    |    |    |            |    |    |            |
|------------|----|----|------------|----|----|----|----|----|----|----|----|----|----|----|----|------------|----|----|------------|
|            |    |    |            |    |    |    |    |    |    |    |    |    |    |    |    |BOOT1       |BT1 |GND |GND         |
|            |    |    |            |    |    |    |    |    |    |    |    |    |    |    |    |BOOT0       |BT0 |GND |GND         |
|GND         |GND |VCC |VCC         |    |    |    |    |    |    |    |    |    |    |    |    |DIS3_D2     |PE10|PB2 |DIS1_D2     |
|OTG_FS_SOF  |PA8 |PC9 |SDIO_D1     |    |    |    |    |    |    |    |    |    |    |    |    |DIS3_D0     |PE8 |PE9 |DIS3_D1     |
|OTG_FS_ID   |PA10|PA9 |OTG_FS_VBUS |    |    |    |    |    |    |    |    |    |    |    |    |DIS2_D1     |PE1 |PE7 |DIS2_D7     |
|OTF_FS_DP   |PA12|PA11|OTG_FS_DM   |    |    |    |    |    |    |    |    |    |    |    |    |I2C1_SCL  & |PB8 |PB9 |I2C1_SDA  & |
|DIS1_RW     |PA14|PA13|DIS1_RS     |    |    |    |    |    |    |    |    |    |    |    |    |DIS1_D0     |PB0 |PB1 |DIS1_D1     |
|SDIO_D2     |PC10|PA15|DIS1_E      |    |    |    |    |    |    |    |    |    |    |    |    |ETH_RXD0    |PC4 |PC5 |ETH_RXD1    |
|SDIO_CK     |PC12|PC11|SDIO_D3     |    |    |    |    |    |    |    |    |    |    |    |    |DIS3_E      |PA6 |PA7 |ETH_CRS_DV  |
|CAN1_TX?  & |PD1 |PD0 |CAN1_RX?  & |    |    |    |    |    |    |    |    |    |    | -- | -- |INT1?       |PA4 |PA5 |INT2?       |
|DIS0_E      |PD3 |PD2 |SDIO_CMD    |    |    |    |    |    |    |    |    |    |    |    |    |DIS2_E      |PC3 |PA3 |DIS3_RW     |
|USART2_TX   |PD5 |PD4 |DIS0_RS     |    |    |    |    |    |    |    |    |    |    |    |    |ETH_REF_CLK |PA1 |PA2 |ETH_MDIO    |
|DIS0_RW     |PD7 |PD6 |USART2_RX   |    |    |    |    |    |    |    |    |    |    |    |    |DIS2_RW     |PC2 |PA0 |PWM?        |
|DIS1_D4     |PB4 |PB3 |DIS1_D3     |    |    |    |    |    |    |    |    |    |    |    |    |DIS2_RS     |PC0 |PC1 |ETH_MDC     |
|DIS1_D6   & |PB6 |PB5 |DIS1_D5   & |    |    |    |    |    |    |    |    |    |    |    |    |3.3V        |3.3V|GND |GND         |
|DIS2_D0     |PE0 |PB7 |DIS1_D7     |    |    |    |    |    |    |    |    |    |    |    | -- |DIS2_D6     |PE6 |PC13|DIS3_RS     |
|GND         |GND |3.3V|3.3V        |    |    |    |    |    |    |    |    |    |    |    |    |DIS2_D4     |PE4 |PE5 |DIS2_D5     |
|GND         |GND |VCC |VCC         |    |    |    |    |    |    |    |    |    |    |    |    |DIS2_D2     |PE2 |PE3 |DIS2_D3     |

## Pin-outs by port

|    |                             |
|----|-----------------------------|
|PA0 | PWM?                        |
|PA1 | ETH_REF_CLK                 |
|PA2 | ETH_MDI                     |
|PA4 | (not 5V tolerant)           |
|PA5 | (not 5V tolerant)           |
|PA6 | DIS3_E                      |
|PA7 | ETH_RMII_CRS_DV             |
|PA8 | OTG_FS_SOF                  |
|PA9 | OTG_FS_VBUS                 |
|PA10| OTG_FS_ID                   |
|PA11| OTF_FS_DM                   |
|PA12| OTG_FS_DP                   |
|PA13| DIS1_RS (+ SWD)             |
|PA14| DIS1_RW (+ SWD)             |
|PA15| DIS1_E                      |
|PB0 | DIS1_D0                     |
|PB1 | DIS1_D1                     |
|PB2 | DIS1_D2                     |
|PB3 | DIS1_D3 (+ SWO)             |
|PB4 | DIS1_D4                     |
|PB5 | DIS1_D5                     |
|PB6 | DIS1_D6                     |
|PB7 | DIS1_D7                     |
|PB8 | I2C1_SCL                    |
|PB9 | I2C1_SDA                    |
|PB10| SPI2_SCK (no NSS)?          |
|PB11| ETH_RMII_TX_EN              |
|PB12| ETH_RMII_TXD0               |
|PB13| ETH_RMII_TXD1               |
|PB14| SPI2_MISO (no NSS)?         |
|PB15| SPI2_MOSI (no NSS)?         |
|PC0 | DIS2_RS                     |
|PC1 | ETH_MDC                     |
|PC2 | DIS2_RW                     |
|PC3 | DIS2_E                      |
|PC4 | ETH_RMII_RXD0               |
|PC5 | ETH_RMII_RXD1               |
|PC6 | SPI CS1?                    |
|PC7 | SPI CS2?                    |
|PC8 | SDIO_D0                     |
|PC9 | SDIO_D1                     |
|PC10| SDIO_D2                     |
|PC11| SDIO_D3                     |
|PC12| SDIO_CK                     |
|PC13| DIS3_RS (sink 3mA max)      |
|PC14| (sink 3mA max, not fitted)  |
|PC15| (sink 3mA max, not fitted)  |
|PD0 | CAN1_RX                     |
|PD1 | CAN1_TX                     |
|PD2 | SDIO_CMD                    |
|PD3 | DIS0_E                      |
|PD4 | DIS0_RS                     |
|PD5 | USART2_TX                   |
|PD6 | USART2_RX                   |
|PD7 | DIS0_RW                     |
|PD8 | DIS0_D0                     |
|PD9 | DIS0_D1                     |
|PD10| DIS0_D2                     |
|PD11| DIS0_D3                     |
|PD12| DIS0_D4                     |
|PD13| DIS0_D5                     |
|PD14| DIS0_D6                     |
|PD15| DIS0_D7                     |
|PE0 | DIS2_D0                     |
|PE1 | DIS2_D1                     |
|PE2 | DIS2_D2                     |
|PE3 | DIS2_D3                     |
|PE4 | DIS2_D4                     |
|PE5 | DIS2_D5                     |
|PE6 | DIS2_D6                     |
|PE7 | DIS2_D7                     |
|PE8 | DIS3_D0                     |
|PE9 | DIS3_D1                     |
|PE10| DIS3_D2                     |
|PE11| DIS3_D3                     |
|PE12| DIS3_D4                     |
|PE13| DIS3_D5                     |
|PE14| DIS3_D6                     |
|PE15| DIS3_D7                     |

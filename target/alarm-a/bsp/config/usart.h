#define USART_BAUD_RATE (19200UL)

// Uart
#define SIG_TXD_PORT (PORTD)
#define SIG_TXD_DIR  (DDRD)
#define SIG_TXD_PIN  (1)

#define SIG_RXD_PORT (PORTD)
#define SIG_RXD_DIR  (DDRD)
#define SIG_RXD_PIN  (0)

// 1. txd is output
// 2. rxd is input (default), int. pull up.
#define usart__pins_init() do {\
    set_bit_in_reg (SIG_TXD_DIR,SIG_TXD_PIN);\
    set_bit_in_reg (SIG_RXD_PORT,SIG_RXD_PIN);\
} while(0)

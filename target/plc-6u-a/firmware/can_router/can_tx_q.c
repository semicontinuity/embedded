#include "can_tx_q.h"

uint8_t can_tx_q[CAN_TX_Q_SIZE] __attribute__((section(".can_tx_q")));

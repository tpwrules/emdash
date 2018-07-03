#ifndef BOOTLOAD_H
#define BOOTLOAD_H

// CAN message processing functions
// called after a message was received
void CAN_rx(uint8_t msg_obj_num);

// called after a message was transmitted
void CAN_tx(uint8_t msg_obj_num);

// called when a bus error happened
void CAN_error(uint32_t error_info);

// main bootloader function
void bootload(void);

#endif
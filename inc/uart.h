
int init_uart();

short read_uart(int uart0_filestream, char type, void *p_out);

void write_uart(unsigned char *tx_buffer, int size, int uart_filestream);
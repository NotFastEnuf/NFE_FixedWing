

void rx_init(void);
void checkrx( void);
#if defined(RX_DSMX_2048) || defined(RX_DSM2_1024)
void rx_spektrum_bind(void);
#endif
void apply_rates(void);
void apply_stick_travel_check(void);



































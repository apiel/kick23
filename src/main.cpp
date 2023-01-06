#ifdef BOARD_ESP32C3
#include "./boards/esp32c3_main.h"
#else
#ifdef BOARD_SAMD51_TRELLIS
#include "./boards/samd51_trellis_main.h"
#else
#include "./boards/samd51_main.h"
#endif
#endif

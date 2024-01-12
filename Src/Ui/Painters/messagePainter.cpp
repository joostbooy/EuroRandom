#include "messagePainter.h"

uint16_t MessagePainter::x = 0;
uint16_t MessagePainter::y = 16;
uint16_t MessagePainter::w = 0;
uint16_t MessagePainter::h = 32;


bool MessagePainter::is_error;
bool MessagePainter::is_visible;
uint16_t MessagePainter::duration_ms = 0;
uint16_t MessagePainter::interval_;
StringBuilderBase<32> MessagePainter::str;

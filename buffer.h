#ifndef BUFFER_H
#define BUFFER_H
#include <stdint.h>

class Buffer
{
public:
	Buffer();
	static uint8_t getUInt8(const uint8_t *buffer, int32_t *index);
	static int16_t getInt16(const uint8_t *buffer, int32_t *index);
	static uint16_t getUInt16(const uint8_t *buffer, int32_t *index);
	static int32_t getInt32(const uint8_t *buffer, int32_t *index);
};

#endif // BUFFER_H

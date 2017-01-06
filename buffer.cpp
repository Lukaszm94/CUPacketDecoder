#include "buffer.h"

Buffer::Buffer()
{

}

uint8_t Buffer::getUInt8(const uint8_t *buffer, int32_t *index)
{
	uint8_t res = buffer[*index];
	*index += 1;
	return res;
}

int16_t Buffer::getInt16(const uint8_t *buffer, int32_t *index)
{
	int16_t res = ((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}

uint16_t Buffer::getUInt16(const uint8_t *buffer, int32_t *index)
{
	uint16_t res = ((uint16_t) buffer[*index]) << 8 |
					((uint16_t) buffer[*index + 1]);
	*index += 2;
	return res;
}

int32_t Buffer::getInt32(const uint8_t *buffer, int32_t *index)
{
	int32_t res = ((uint32_t) buffer[*index]) << 24 |
					((uint32_t) buffer[*index + 1]) << 16 |
					((uint32_t) buffer[*index + 2]) << 8 |
					((uint32_t) buffer[*index + 3]);
	*index += 4;
	return res;
}

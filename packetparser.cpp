#include "packetparser.h"
#include "buffer.h"
#include <QDebug>

#define CURRENT_PACKET_HEADER 'a'
#define CURRENT_PACKET_DATA_SIZE 4
#define TEMPERATURE_PACKET_HEADER 'b'
#define TEMPERATURE_PACKET_DATA_SIZE 8
#define BATTERY_PACKET_HEADER 'c'
#define BATTERY_PACKET_DATA_SIZE (2*6 + 9)
#define SPEED_PACKET_HEADER 'd'
#define SPEED_PACKET_DATA_SIZE 2
#define ERROR_PACKET_HEADER 'e'

#define PACKET_END_CHAR ';'
#define PACKET_OVERHEAD_SIZE 2

#define MAX_BUFFER_SIZE 32

PacketParser::PacketParser(QObject *parent) : QObject(parent)
{

}

void PacketParser::appendBytes(QByteArray data)
{
	buffer += data;
}

void PacketParser::parse()
{
	if(buffer.isEmpty()) {
		return;
	}
	char firstChar = buffer.at(0);
	int bufferSize = buffer.size();
	if(firstChar == CURRENT_PACKET_HEADER) {
		//qDebug() << "firstChar == CURRENT_PACKET_HEADER";
		if(bufferSize > (CURRENT_PACKET_DATA_SIZE + PACKET_OVERHEAD_SIZE - 1)) {
			if(buffer.at(CURRENT_PACKET_DATA_SIZE + PACKET_OVERHEAD_SIZE - 1) != PACKET_END_CHAR) {
				removeDataFromBufferUntil(PACKET_END_CHAR);
				return;
			}
			// extract data from packet
			CurrentPacket packet = extractCurrentPacketFromBuffer();
			removeDataFromBufferUntil(PACKET_END_CHAR);
			emit newCurrentPacket(packet);
			return;
		}
		// wait for more data
		return;
	} else if(firstChar == TEMPERATURE_PACKET_HEADER) {
		//qDebug() << "firstChar == TEMPERATURE_PACKET_HEADER";
		if(bufferSize > (TEMPERATURE_PACKET_DATA_SIZE + PACKET_OVERHEAD_SIZE - 1)) {
			if(buffer.at(TEMPERATURE_PACKET_DATA_SIZE + PACKET_OVERHEAD_SIZE - 1) != PACKET_END_CHAR) {
				removeDataFromBufferUntil(PACKET_END_CHAR);
				return;
			}
			// extract data from packet
			TemperaturePacket packet = extractTemperaturePacketFromBuffer();
			removeDataFromBufferUntil(PACKET_END_CHAR);
			emit newTemperaturePacket(packet);
			return;
		}
		// wait for more data
		return;
	} else if(firstChar == BATTERY_PACKET_HEADER) {
		if(bufferSize > (BATTERY_PACKET_DATA_SIZE + PACKET_OVERHEAD_SIZE - 1)) {
			if(buffer.at(BATTERY_PACKET_DATA_SIZE + PACKET_OVERHEAD_SIZE - 1) != PACKET_END_CHAR) {
				removeDataFromBufferUntil(PACKET_END_CHAR);
				return;
			}
			// extract data from packet
			BatteryPacket packet = extractBatteryPacketFromBuffer();
			removeDataFromBufferUntil(PACKET_END_CHAR);
			emit newBatteryPacket(packet);
			return;
		}
		// wait for more data
		return;
	} else if(firstChar == SPEED_PACKET_HEADER) {
		if(bufferSize > (SPEED_PACKET_DATA_SIZE + PACKET_OVERHEAD_SIZE - 1)) {
			if(buffer.at(SPEED_PACKET_DATA_SIZE + PACKET_OVERHEAD_SIZE - 1) != PACKET_END_CHAR) {
				removeDataFromBufferUntil(PACKET_END_CHAR);
				return;
			}
			// extract data from packet
			SpeedPacket packet = extractSpeedPacketFromBuffer();
			removeDataFromBufferUntil(PACKET_END_CHAR);
			emit newSpeedPacket(packet);
			return;
		}
		// wait for more data
		return;
	} else {
		// unknown first char
		qDebug() << "unknown first char= " << firstChar;
		removeDataFromBufferUntil(PACKET_END_CHAR);
	}
	if(bufferSize > MAX_BUFFER_SIZE) {
		buffer.clear();
	}
}

CurrentPacket PacketParser::extractCurrentPacketFromBuffer()
{
	CurrentPacket packet;
	uint8_t* data = (uint8_t*)buffer.data();
	int32_t index = 1;
	packet.VESC1Current = Buffer::getInt16(data, &index);
	packet.VESC2Current = Buffer::getInt16(data, &index);
	return packet;
}

TemperaturePacket PacketParser::extractTemperaturePacketFromBuffer()
{
	TemperaturePacket packet;
	uint8_t* data = (uint8_t*)buffer.data();
	int32_t index = 1;
	packet.VESC1Temperature = Buffer::getInt16(data, &index);
	packet.VESC2Temperature = Buffer::getInt16(data, &index);
	packet.powerSwitchTemperature= Buffer::getInt16(data, &index);
	packet.driversUnitCaseTemperature= Buffer::getInt16(data, &index);
	return packet;
}

BatteryPacket PacketParser::extractBatteryPacketFromBuffer()
{
	BatteryPacket packet;
	uint8_t* data = (uint8_t*)buffer.data();
	int32_t index = 1;

	for(int i = 0; i < BM_BATTERY_CELLS_COUNT; i++) {
		packet.cellsVoltage[i] = Buffer::getUInt16(data, &index);
	}
	packet.CUBatteryVoltage = Buffer::getUInt16(data, &index);
	packet.VESCBatteryVoltage = Buffer::getUInt16(data, &index);
	packet.ampHoursDrawn = Buffer::getUInt16(data, &index);
	packet.ampHoursCharged = Buffer::getUInt16(data, &index);
	packet.batteryCharge = Buffer::getUInt8(data, &index);
	return packet;
}

SpeedPacket PacketParser::extractSpeedPacketFromBuffer()
{
	SpeedPacket packet;
	uint8_t* data = (uint8_t*)buffer.data();
	int32_t index = 1;
	packet.speed = Buffer::getUInt16(data, &index);
	return packet;
}

void PacketParser::removeDataFromBufferUntil(char c)
{
	int index = buffer.indexOf(c);
	if(index < 0) { // char not found
		buffer.clear();
		return;
	}
	if(index == (buffer.size() - 1)) { // c is last char in the buffer
		buffer.clear();
		return;
	}
	buffer.remove(0, index + 1);
}

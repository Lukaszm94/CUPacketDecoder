#ifndef PACKETPARSER_H
#define PACKETPARSER_H

#include <QObject>
#include <QByteArray>
#include "datatypes.h"

class PacketParser : public QObject
{
	Q_OBJECT
public:
	explicit PacketParser(QObject *parent = 0);
	void appendBytes(QByteArray data);
	void parse();

signals:
	void newCurrentPacket(CurrentPacket packet);
	void newBatteryPacket(BatteryPacket packet);
	void newTemperaturePacket(TemperaturePacket packet);
	void newSpeedPacket(SpeedPacket packet);

private:
	CurrentPacket extractCurrentPacketFromBuffer();
	TemperaturePacket extractTemperaturePacketFromBuffer();
	BatteryPacket extractBatteryPacketFromBuffer();
	SpeedPacket extractSpeedPacketFromBuffer();
	void removeDataFromBufferUntil(char c);

	QByteArray buffer;
};

#endif // PACKETPARSER_H

#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QtSerialPort>
#include "packetparser.h"

class SerialManager : public QObject
{
	Q_OBJECT
public:
	explicit SerialManager(QObject *parent = 0);
	void setParser(PacketParser* p);
	bool connectToPort(QString portName);
	void sendLightsPacket(LightsPacket packet);

private slots:
	void onNewSerialData();

private:
	PacketParser* parser;
	QSerialPort* serialPort;
};

#endif // SERIALMANAGER_H

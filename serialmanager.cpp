#include "serialmanager.h"

#define LIGHTS_PACKET_HEADER 'l'
#define PACKET_END_CHAR ';'
#define LIGHTS_PACKET_SIZE (3+2)

SerialManager::SerialManager(QObject *parent) : QObject(parent)
{
	serialPort = new QSerialPort(this);

	if(connectToPort("COM22")) {
		qDebug() << "Serial port opened";
		serialPort->clear();
	} else {
		qDebug() << "Serial port NOT opened";
	}

	connect(serialPort, SIGNAL(readyRead()), this, SLOT(onNewSerialData()));
}

void SerialManager::setParser(PacketParser *p)
{
	parser = p;
}

bool SerialManager::connectToPort(QString portName)
{
	if(serialPort->isOpen()) {
		qDebug() << "SerialManager: serial port already open!";
		return false;
	}
	if(portName.isEmpty()) {
		qDebug() << "SerialManager: portName empty";
		return false;
	}
	bool ok = false;
	serialPort->setPortName(portName);
	if(serialPort->open(QSerialPort::ReadWrite)) {
		bool settingsOk = true;
		settingsOk = serialPort->setBaudRate(QSerialPort::Baud38400);
		settingsOk = serialPort->setDataBits(QSerialPort::Data8);
		settingsOk = serialPort->setFlowControl(QSerialPort::NoFlowControl);
		settingsOk = serialPort->setParity(QSerialPort::NoParity);
		settingsOk = serialPort->setStopBits(QSerialPort::OneStop);
		if(!settingsOk) {
			qDebug() << "SerialManager::openSerialPort(): unable to set one (or more) of the serial port settings";
		} else {
			qDebug() << "SerialManager::openSerialPort(): settings set OK";
			ok = true;
		}
	}
	return ok;
}

void SerialManager::sendLightsPacket(LightsPacket packet)
{
	QByteArray data = QByteArray(LIGHTS_PACKET_SIZE, 'x');
	data[0] = LIGHTS_PACKET_HEADER;
	data[1] = packet.brightness;
	data[2] = packet.reactToBraking;
	data[3] = packet.blinkingMode;
	data[4] = PACKET_END_CHAR;
	int bytesSent = serialPort->write(data);
	if(bytesSent != data.size()) {
		qDebug() << "sendLightsPacket: wrong number of bytes sent: " << bytesSent;
	}
	qDebug() << "Sent: " << data;
}

void SerialManager::onNewSerialData()
{
	QByteArray array(serialPort->readAll());
	parser->appendBytes(array);
	//qDebug() << "Received: " << array;
	for(int i = 0; i < 5; i++) {
		parser->parse();
	}
}

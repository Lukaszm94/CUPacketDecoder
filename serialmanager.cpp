#include "serialmanager.h"

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

void SerialManager::onNewSerialData()
{
	QByteArray array(serialPort->readAll());
	parser->appendBytes(array);
	//qDebug() << "Received: " << array;
	for(int i = 0; i < 5; i++) {
		parser->parse();
	}
}

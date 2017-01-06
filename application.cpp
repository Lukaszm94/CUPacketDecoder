#include "application.h"
#include "datatypes.h"
#include <QDebug>

Application::Application(int argc, char *argv[]) : QApplication(argc, argv)
{
	qRegisterMetaType<BatteryPacket>("BatteryPacket");
	qRegisterMetaType<CurrentPacket>("CurrentPacket");
	qRegisterMetaType<TemperaturePacket>("TemperaturePacket");
	qRegisterMetaType<SpeedPacket>("SpeedPacket");

	dataManager = new DataManager;
	serialManager = new SerialManager(this);
	packetParser = new PacketParser(this);
	gui = new GUI;

	serialManager->setParser(packetParser);

	connect(packetParser, SIGNAL(newBatteryPacket(BatteryPacket)), this, SLOT(onNewBatteryPacket(BatteryPacket)));
	connect(packetParser, SIGNAL(newCurrentPacket(CurrentPacket)), this, SLOT(onNewCurrentPacket(CurrentPacket)));
	connect(packetParser, SIGNAL(newTemperaturePacket(TemperaturePacket)), this, SLOT(onNewTemperaturePacket(TemperaturePacket)));
	connect(packetParser, SIGNAL(newSpeedPacket(SpeedPacket)), this, SLOT(onNewSpeedPacket(SpeedPacket)));
	connect(dataManager, SIGNAL(newLogEntry(QString)), this, SLOT(onNewDataManagerLogEntry(QString)));
	connect(gui->mainWindow, SIGNAL(clearLogButtonClicked()), this, SLOT(onClearDataManagerLogClicked()));
	connect(gui->mainWindow, SIGNAL(saveLogButtonClicked(QString)), this, SLOT(onSaveDataManagerLog(QString)));
}

void Application::onNewCurrentPacket(CurrentPacket packet)
{
	dataManager->updateCurrent(packet);
	gui->mainWindow->updateCurrentData(packet);
	/*qDebug() << "CURRENT PACKET:";
	qDebug() << "VESC1: " << packet.VESC1Current / 10.0;
	qDebug() << "VESC2: " << packet.VESC2Current / 10.0;*/
}

void Application::onNewBatteryPacket(BatteryPacket packet)
{
	dataManager->updateBattery(packet);
	gui->mainWindow->updateBatteryData(packet);
	/*qDebug() << "BATTERY PACKET:";
	for(int i = 0; i < BM_BATTERY_CELLS_COUNT; i++) {
		qDebug() << "Cell " << i <<": " << (double)packet.cellsVoltage[i] / 100.0;
	}
	qDebug() << "CU Voltage: " << packet.CUBatteryVoltage / 100.0;
	qDebug() << "VESC Voltage: " << packet.VESCBatteryVoltage / 100.0;
	qDebug() << "Amp hours drawn: " << packet.ampHoursDrawn / 1000.0;
	qDebug() << "Amp hours charged: " << packet.ampHoursCharged / 1000.0;*/
}

void Application::onNewTemperaturePacket(TemperaturePacket packet)
{
	dataManager->updateTemperature(packet);
	gui->mainWindow->updateTemperatureData(packet);
	/*qDebug() << "TEMPERATURE PACKET";
	qDebug() << "VESC1: " << packet.VESC1Temperature;
	qDebug() << "VESC2: " << packet.VESC2Temperature;
	qDebug() << "PowerSwitch: " << packet.powerSwitchTemperature;
	qDebug() << "DriversUnitCase: " << packet.driversUnitCaseTemperature;*/
}

void Application::onNewSpeedPacket(SpeedPacket packet)
{
	dataManager->updateSpeed(packet);
	gui->mainWindow->updateSpeedData(packet);
	/*qDebug() << "SPEED PACKET";
	qDebug() << "Speed: " << packet.speed / 100.0;*/
}

void Application::onNewDataManagerLogEntry(QString str)
{
	gui->mainWindow->appendLog(str);
}

void Application::onClearDataManagerLogClicked()
{
	dataManager->clearBuffer();
	gui->mainWindow->clearLog();
}

void Application::onSaveDataManagerLog(QString path)
{
	if(dataManager->saveDataToFile(path)) {
		qDebug() << "Save ok";
	} else {
		qDebug() << "Save failed";
	}
}

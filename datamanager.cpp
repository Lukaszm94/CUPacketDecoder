#include "datamanager.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define DATA_MANAGER_LOG_PERIOD 200
#define AUTOSAVE_TIMER_PERIOD_S 10

DataManager::DataManager(QObject *parent) : QObject(parent)
{
	timer = new QTimer;
	autosaveTimer = new QTimer;

	connect(timer, SIGNAL(timeout()), this, SLOT(onTimerTimeout()));
	connect(autosaveTimer, SIGNAL(timeout()), this, SLOT(onAutosaveTimerTimeout()));

	timer->start(DATA_MANAGER_LOG_PERIOD);
	autosaveTimer->start(AUTOSAVE_TIMER_PERIOD_S * 1000);
	timeOffset.start();
}

void DataManager::updateCurrent(CurrentPacket packet)
{
	newData.current = packet;
}

void DataManager::updateBattery(BatteryPacket packet)
{
	newData.battery = packet;
}

void DataManager::updateTemperature(TemperaturePacket packet)
{
	newData.temperature = packet;
}

void DataManager::updateSpeed(SpeedPacket packet)
{
	newData.speed = packet;
}

void DataManager::clearBuffer()
{
	timeOffset.restart();
	dataBuffer.clear();
}

bool DataManager::saveDataToFile(QString filePath)
{
	QFile csvFile(filePath);
	if(!csvFile.open(QFile::WriteOnly)) {
		return false;
	}
	QTextStream stream(&csvFile);
	for(BoardData data : dataBuffer) {
		stream << dataToString(data) + "\n";
	}
	csvFile.close();
	return true;
}

void DataManager::onTimerTimeout()
{
	newData.timestamp = timeOffset.elapsed();
	dataBuffer.append(newData);
	emit newLogEntry(dataToString(newData));
}

void DataManager::onAutosaveTimerTimeout()
{
	QString fileName = "autosave_" + QTime::currentTime().toString() + ".csv";
	fileName.replace(':', '_');
	if(saveDataToFile(fileName)) {
		qDebug() << "autosave ok";
	} else {
		qDebug() << "autosave fail";
	}
}

//timestamp, VESC1Current, VESC2Current, cellsVoltages, CUVoltage, VESCVoltage, ampHoursDrawn, ampHoursCharged, VESC1Temp, VESC2Temp, PSTemp, DUCTemp, speed
QString DataManager::dataToString(BoardData data)
{
	QString str = QString::number(data.timestamp) + "," + QString::number((double)(data.current.VESC1Current / 10.0), 'f', 1) + "," + QString::number((double)(data.current.VESC2Current / 10.0), 'f', 1);
	for(int i = 0; i < BM_BATTERY_CELLS_COUNT; i++) {
		str += "," + QString::number((double)(data.battery.cellsVoltage[i] / 100.0), 'f', 2);
	}
	str += "," + QString::number((double)(data.battery.CUBatteryVoltage / 100.0), 'f', 1) + "," + QString::number((double)(data.battery.VESCBatteryVoltage / 100.0), 'f', 1);
	str += "," + QString::number((double)(data.battery.ampHoursDrawn / 1000.0), 'f', 3) + "," + QString::number((double)(data.battery.ampHoursCharged/ 1000.0), 'f', 3);
	str += "," + QString::number((double)(data.temperature.VESC1Temperature / 100.0), 'f', 1) + "," + QString::number((double)(data.temperature.VESC2Temperature / 100.0), 'f', 1);
	str += "," + QString::number((double)(data.temperature.powerSwitchTemperature / 100.0), 'f', 1) + "," + QString::number((double)(data.temperature.driversUnitCaseTemperature / 100.0), 'f', 1);
	str += "," + QString::number((double)(data.speed.speed / 100.0), 'f', 1);
	return str;
}

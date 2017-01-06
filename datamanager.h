#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QTime>
#include "datatypes.h"

struct BoardData {
	int timestamp;
	CurrentPacket current;
	BatteryPacket battery;
	TemperaturePacket temperature;
	SpeedPacket speed;
};

class DataManager : public QObject
{
	Q_OBJECT
public:
	explicit DataManager(QObject *parent = 0);
	void updateCurrent(CurrentPacket packet);
	void updateBattery(BatteryPacket packet);
	void updateTemperature(TemperaturePacket packet);
	void updateSpeed(SpeedPacket packet);
	void clearBuffer();
	bool saveDataToFile(QString filePath);

signals:
	void newLogEntry(QString str);

private slots:
	void onTimerTimeout();
	void onAutosaveTimerTimeout();

private:
	QString dataToString(BoardData data);

	BoardData newData;
	QVector<BoardData> dataBuffer;
	QTimer* timer;
	QTimer* autosaveTimer;
	QTime timeOffset;
};

#endif // DATAMANAGER_H

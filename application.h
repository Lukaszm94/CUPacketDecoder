#ifndef APPLICATION_H
#define APPLICATION_H
#include <QApplication>
#include <QString>
#include "serialmanager.h"
#include "packetparser.h"
#include "gui.h"
#include "datamanager.h"

class Application : public QApplication
{
	Q_OBJECT
public:
	Application(int argc, char* argv[]);

private slots:
	void onNewCurrentPacket(CurrentPacket packet);
	void onNewBatteryPacket(BatteryPacket packet);
	void onNewTemperaturePacket(TemperaturePacket packet);
	void onNewSpeedPacket(SpeedPacket packet);
	void onNewDataManagerLogEntry(QString str);
	void onClearDataManagerLogClicked();
	void onSaveDataManagerLog(QString path);

private:
	DataManager* dataManager;
	SerialManager* serialManager;
	PacketParser* packetParser;
	GUI* gui;
};

#endif // APPLICATION_H

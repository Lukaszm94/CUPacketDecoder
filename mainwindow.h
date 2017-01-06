#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QVector>
#include "datatypes.h"
#include "logwidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void updateCurrentData(CurrentPacket packet);
	void updateBatteryData(BatteryPacket packet);
	void updateTemperatureData(TemperaturePacket packet);
	void updateSpeedData(SpeedPacket packet);
	void clearLog();
	void appendLog(QString str);

signals:
	void clearLogButtonClicked();
	void saveLogButtonClicked(QString path);

private slots:
	void onClearLogButtonClicked();
	void onSaveLogButtonClicked();

private:
	QTabWidget* tabWidget;

	//current
	QLabel* VESC1CurrentLabel;
	QLabel* VESC2CurrentLabel;
	//battery
	QVector<QLabel*> cellsVoltageLabels;
	QLabel* CUBatteryVoltageLabel;
	QLabel* VESCBatteryVoltageLabel;
	QLabel* ampHoursDrawnLabel;
	QLabel* ampHoursChargedLabel;
	//temperature
	QLabel* VESC1TemperatureLabel;
	QLabel* VESC2TemperatureLabel;
	QLabel* powerSwitchTemperatureLabel;
	QLabel* driversUnitTemperatureLabel;
	//speed
	QLabel* speedLabel;

	//data log
	LogWidget* logWidget;
};

#endif // MAINWINDOW_H

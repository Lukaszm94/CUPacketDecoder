#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	tabWidget = new QTabWidget;

	VESC1CurrentLabel = new QLabel;
	VESC2CurrentLabel = new QLabel;

	for(int i = 0; i < BM_BATTERY_CELLS_COUNT; i++) {
		cellsVoltageLabels.append(new QLabel);
	}
	CUBatteryVoltageLabel = new QLabel;
	VESCBatteryVoltageLabel = new QLabel;
	ampHoursDrawnLabel = new QLabel;
	ampHoursChargedLabel = new QLabel;

	VESC1TemperatureLabel = new QLabel;
	VESC2TemperatureLabel = new QLabel;
	powerSwitchTemperatureLabel = new QLabel;
	driversUnitTemperatureLabel = new QLabel;

	speedLabel = new QLabel;

	logWidget = new LogWidget;

	//layout
	QVBoxLayout* currentLayout = new QVBoxLayout;
	currentLayout->addWidget(VESC1CurrentLabel);
	currentLayout->addWidget(VESC2CurrentLabel);

	QVBoxLayout* batteryLayout = new QVBoxLayout;
	for(int i = 0; i < BM_BATTERY_CELLS_COUNT; i++) {
		batteryLayout->addWidget(cellsVoltageLabels.at(i));
	}
	batteryLayout->addWidget(CUBatteryVoltageLabel);
	batteryLayout->addWidget(VESCBatteryVoltageLabel);
	batteryLayout->addWidget(ampHoursDrawnLabel);
	batteryLayout->addWidget(ampHoursChargedLabel);

	QVBoxLayout* temperatureLayout = new QVBoxLayout;
	temperatureLayout->addWidget(VESC1TemperatureLabel);
	temperatureLayout->addWidget(VESC2TemperatureLabel);
	temperatureLayout->addWidget(powerSwitchTemperatureLabel);
	temperatureLayout->addWidget(driversUnitTemperatureLabel);

	QVBoxLayout* speedLayout = new QVBoxLayout;
	speedLayout->addWidget(speedLabel);

	QGroupBox* currentGroupBox = new QGroupBox("Current");
	currentGroupBox->setLayout(currentLayout);

	QGroupBox* batteryGroupBox = new QGroupBox("Battery");
	batteryGroupBox->setLayout(batteryLayout);

	QGroupBox* temperatureGroupBox = new QGroupBox("Temperature");
	temperatureGroupBox->setLayout(temperatureLayout);

	QGroupBox* speedGroupBox = new QGroupBox("Speed");
	speedGroupBox->setLayout(speedLayout);

	QVBoxLayout* leftColumn = new QVBoxLayout;
	leftColumn->addWidget(currentGroupBox);
	leftColumn->addWidget(speedGroupBox);
	leftColumn->addWidget(temperatureGroupBox);

	QVBoxLayout* rightColumn = new QVBoxLayout;
	rightColumn->addWidget(batteryGroupBox);

	QHBoxLayout* dataLayout = new QHBoxLayout;
	dataLayout->addLayout(leftColumn);
	dataLayout->addLayout(rightColumn);
	QWidget* dataWidget = new QWidget;
	dataWidget->setLayout(dataLayout);

	tabWidget->addTab(dataWidget, "Data");
	tabWidget->addTab(logWidget, "Log");
	this->setCentralWidget(tabWidget);

	connect(logWidget->saveButton, SIGNAL(clicked(bool)), this, SLOT(onSaveLogButtonClicked()));
	connect(logWidget->clearButton, SIGNAL(clicked(bool)), this, SLOT(onClearLogButtonClicked()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateCurrentData(CurrentPacket packet)
{
	QString str = "VESC1: <b>" + QString::number((double)(packet.VESC1Current / 10.0), 'f', 1) + "</b>A";
	VESC1CurrentLabel->setText(str);
	str = "VESC2: <b>" + QString::number((double)(packet.VESC2Current / 10.0), 'f', 1) + "</b>A";
	VESC2CurrentLabel->setText(str);
}

void MainWindow::updateBatteryData(BatteryPacket packet)
{
	QString str;
	for(int i = 0; i < BM_BATTERY_CELLS_COUNT; i++) {
		str = "Cell " + QString::number(i) + ": <b>" + QString::number((double)(packet.cellsVoltage[i] / 100.0), 'f', 2) + "</b>V";
		cellsVoltageLabels.at(i)->setText(str);
	}
	str = "VESC: <b>" + QString::number((double)(packet.VESCBatteryVoltage / 100.0), 'f', 1) + "</b>V";
	VESCBatteryVoltageLabel->setText(str);
	str = "CU: <b>" + QString::number((double)(packet.CUBatteryVoltage / 100.0), 'f', 1) + "</b>V";
	CUBatteryVoltageLabel->setText(str);
	str = "Ah drawn: <b>" + QString::number((double)(packet.ampHoursDrawn / 1000.0), 'f', 3) + "</b>Ah";
	ampHoursDrawnLabel->setText(str);
	str = "Ah charged: <b>" + QString::number((double)(packet.ampHoursCharged/ 1000.0), 'f', 3) + "</b>Ah";
	ampHoursChargedLabel->setText(str);
}

void MainWindow::updateTemperatureData(TemperaturePacket packet)
{
	QString str = "VESC1: <b>" + QString::number((double)(packet.VESC1Temperature / 100.0), 'f', 1) + "</b>C";
	VESC1TemperatureLabel->setText(str);
	str = "VESC2: <b>" + QString::number((double)(packet.VESC2Temperature / 100.0), 'f', 1) + "</b>C";
	VESC2TemperatureLabel->setText(str);
	str = "PowerSwitch: <b>" + QString::number((double)(packet.powerSwitchTemperature / 100.0), 'f', 1) + "</b>C";
	powerSwitchTemperatureLabel->setText(str);
	str = "DriversUnitCase: <b>" + QString::number((double)(packet.driversUnitCaseTemperature / 100.0), 'f', 1) + "</b>C";
	driversUnitTemperatureLabel->setText(str);
}

void MainWindow::updateSpeedData(SpeedPacket packet)
{
	QString str = "Speed: <b>" + QString::number((double)(packet.speed / 100.0), 'f', 1) + "</b>m/s";
	speedLabel->setText(str);
}

void MainWindow::clearLog()
{
	logWidget->logTextEdit->clear();
}

void MainWindow::appendLog(QString str)
{
	logWidget->logTextEdit->append(str);
}

void MainWindow::onClearLogButtonClicked()
{
	emit clearLogButtonClicked();
}

void MainWindow::onSaveLogButtonClicked()
{
	QString path = QFileDialog::getSaveFileName(this, "Save logged data", QString(), "CSV data (*.csv)");
	if(path.isEmpty()) {
		return;
	}
	emit saveLogButtonClicked(path);
}

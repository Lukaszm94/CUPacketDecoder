#include "gui.h"

GUI::GUI(QObject *parent) : QObject(parent)
{
	mainWindow = new MainWindow;

	mainWindow->show();
}

#ifndef GUI_H
#define GUI_H

#include <QObject>
#include "mainwindow.h"

class GUI : public QObject
{
	Q_OBJECT
	friend class Application;
public:
	explicit GUI(QObject *parent = 0);

signals:

private:
	MainWindow* mainWindow;
};

#endif // GUI_H

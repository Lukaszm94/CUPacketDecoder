#ifndef LIGHTSWIDGET_H
#define LIGHTSWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QVector>

class LightsWidget : public QWidget
{
	Q_OBJECT
	friend class MainWindow;
public:
	explicit LightsWidget(QWidget *parent = 0);

signals:

public slots:

private:
	QPushButton* sendButton;
	QSlider* brightnessSlider;
	QCheckBox* reactToBrakingCheckBox;
	QVector<QRadioButton*> blinkingModeRadioButtons;
};

#endif // LIGHTSWIDGET_H

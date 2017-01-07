#include "lightswidget.h"

#define BLINKING_MODES_COUNT 3

LightsWidget::LightsWidget(QWidget *parent) : QWidget(parent)
{
	sendButton = new QPushButton("Send");
	brightnessSlider = new QSlider;
	reactToBrakingCheckBox = new QCheckBox("React to braking");
	blinkingModeRadioButtons.append(new QRadioButton("Solid"));
	blinkingModeRadioButtons.append(new QRadioButton("Blink 1"));
	blinkingModeRadioButtons.append(new QRadioButton("Blink 2"));

	QGroupBox* blinkingModeGroupBox = new QGroupBox("Blinking mode");
	QVBoxLayout* blinkingModeRadioButtonsLayout = new QVBoxLayout;
	for(auto button : blinkingModeRadioButtons) {
		blinkingModeRadioButtonsLayout->addWidget(button);
	}
	blinkingModeGroupBox->setLayout(blinkingModeRadioButtonsLayout);

	QHBoxLayout* middleLayout = new QHBoxLayout;
	middleLayout->addWidget(blinkingModeGroupBox);
	middleLayout->addWidget(reactToBrakingCheckBox);

	QHBoxLayout* bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(sendButton);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(brightnessSlider);
	mainLayout->addLayout(middleLayout);
	mainLayout->addLayout(bottomLayout);
	this->setLayout(mainLayout);

	blinkingModeRadioButtons.at(0)->setChecked(true);
	brightnessSlider->setOrientation(Qt::Horizontal);
}

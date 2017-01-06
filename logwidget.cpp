#include "logwidget.h"

LogWidget::LogWidget(QWidget *parent) : QWidget(parent)
{
	logTextEdit = new QTextEdit;
	filePathLineEdit = new QLineEdit;
	clearButton = new QPushButton("Clear");
	saveButton = new QPushButton("Save");

	QHBoxLayout* topLayout = new QHBoxLayout;
	topLayout->addWidget(filePathLineEdit);
	topLayout->addWidget(saveButton);
	topLayout->addStretch();
	topLayout->addWidget(clearButton);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(logTextEdit);
	this->setLayout(mainLayout);

	filePathLineEdit->setFixedWidth(200);
	filePathLineEdit->setReadOnly(true);
}

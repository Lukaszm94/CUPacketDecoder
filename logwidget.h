#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QtWidgets>

class LogWidget : public QWidget
{
	Q_OBJECT
	friend class MainWindow;
public:
	explicit LogWidget(QWidget *parent = 0);

signals:
	void clearButtonClicked();
	void saveButtonClicked();

private:
	QTextEdit* logTextEdit;
	QLineEdit* filePathLineEdit;
	QPushButton* clearButton;
	QPushButton* saveButton;
};

#endif // LOGWIDGET_H

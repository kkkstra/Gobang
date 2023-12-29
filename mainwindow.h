#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private slots:
	void OnLocalGameButtonClicked();
	void OnAiGameButtonClicked();

private:
	Ui::MainWindow* ui;
	Controller* controller;
};
#endif // MAINWINDOW_H

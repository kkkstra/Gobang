#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include "ui_style.h"

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

protected:
	virtual void mousePressEvent(QMouseEvent* event);

private slots:
	void OnLocalGameButtonClicked();
	void OnAiGameButtonClicked();

private:
	Ui::MainWindow* ui;
	Controller* controller;
	UIPushbutton titleButton[TITLE_BUTTON_N];
};
#endif // MAINWINDOW_H

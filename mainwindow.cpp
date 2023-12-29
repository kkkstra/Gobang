#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setFixedSize(500, 600);

	controller = new Controller;

	connect(ui->localGameButton, &QPushButton::clicked, this, &MainWindow::OnLocalGameButtonClicked);
	connect(controller, &Controller::ReturnToMainWindow, this, [=]() {
		controller->close();
		this->show();
		}, Qt::QueuedConnection);
	connect(ui->aiGameButton, &QPushButton::clicked, this, &MainWindow::OnAiGameButtonClicked);
}

void MainWindow::OnLocalGameButtonClicked() {
	hide();
	controller->InitGame(LOCAL_MODE);
	controller->show();
}

void MainWindow::OnAiGameButtonClicked() {
	hide();
	controller->InitGame(AI_MODE);
	controller->show();
}

MainWindow::~MainWindow()
{
	delete ui;
}

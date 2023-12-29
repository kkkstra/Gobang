#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEvent>
#include <qt_windows.h>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setFixedSize(500, 500);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);

	for (int i = 0; i < TITLE_BUTTON_N; i++) {
		titleButton[i].setParent(this);
		titleButton[i].setGeometry(TITLE_BUTTON_L + i * TITLE_BUTTON_ITV, TITLE_BUTTON_U + i * TITLE_BUTTON_ITV / 16,
			TITLE_BUTTON_W, TITLE_BUTTON_H);
		titleButton[i].setStyleSheet(TITLE_BUTTON_STYLE[i]);
	}

	titleButton[MINI_BUTTON].setText("_");
	titleButton[CLOSE_BUTTON].setText("x");

	ui->aiGameButton->setStyleSheet(CTRL_BUTTON_STYLE);
	ui->localGameButton->setStyleSheet(CTRL_BUTTON_STYLE);

	ui->label_2->setPixmap(QPixmap(":/img/blackpiece.png").scaled(50, 50));
	ui->label_2->setAlignment(Qt::AlignCenter);

	connect(titleButton + MINI_BUTTON, &UIPushbutton::clicked, this, &MainWindow::showMinimized);
	connect(titleButton + CLOSE_BUTTON, &UIPushbutton::clicked, this, &MainWindow::close);

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

void MainWindow::mousePressEvent(QMouseEvent* event) {
	if (ReleaseCapture() && event->y() <= TITLE_BUTTON_D)
	{
		QWidget* pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

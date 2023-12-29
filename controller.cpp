#include "controller.h"
#include "ui_controller.h"
#include <QDebug>

Controller::Controller(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::Controller)
{
	ui->setupUi(this);

	ai = new GobangAi();

	ConfigureUi();
	InitController();
}

void Controller::ConfigureUi() {
	setFixedSize(1000, 750);
	ui->blackImage->setPixmap(QPixmap(":/img/blackpiece.png").scaled(50, 50));
	ui->blackImage->setAlignment(Qt::AlignCenter);
	ui->whiteImage->setPixmap(QPixmap(":/img/whitepiece.png").scaled(50, 50));
	ui->whiteImage->setAlignment(Qt::AlignCenter);
}

void Controller::InitController() {
	BlackTimer = new QTimer(this);
	WhiteTimer = new QTimer(this);

	connect(BlackTimer, &QTimer::timeout, this, &Controller::UpdateBlackTimer);
	connect(WhiteTimer, &QTimer::timeout, this, &Controller::UpdateWhiteTimer);
	connect(this, &Controller::GameOver, this, &Controller::EndGame);
	connect(ui->chessboard, &Board::GameOver, this, &Controller::EndGame);
	connect(ui->chessboard, &Board::PlayerSwitch, this, &Controller::SwitchTimer);
	connect(ui->chessboard, &Board::PlayerSwitch, this, &Controller::AiSwitchPiece);
	connect(ui->chessboard, &Board::SetAiPiece, this, &Controller::SetAiPiece);
	connect(ui->chessboard, &Board::TakeAiPiece, this, &Controller::TakeAiPiece);
	connect(ui->chessboard, &Board::DecreaseRound, this, [=]() { ai->DecreaseRound(); });
	connect(ui->returnButton, &QPushButton::clicked, this, &Controller::ReturnToMain);
	connect(ui->undoButton, &QPushButton::clicked, this, &Controller::Undo);
	connect(ai, &GobangAi::AiDropPiece, this, &Controller::SetBoardPiece);
}

void Controller::InitGame(GameMode mode) {
	BlackCountdown = INITIAL_COUNTDOWN;
	WhiteCountdown = INITIAL_COUNTDOWN;
	WhiteTimer->stop();
	BlackTimer->stop();
	ui->blackTimer->display("10:00");
	ui->whiteTimer->display("10:00");

	SetGameMode(mode);
	ai->InitGobangAi();
	ui->chessboard->StartGame();
}

void Controller::SwitchTimer(Player player) {
	BlackCountdown = INITIAL_COUNTDOWN;
	WhiteCountdown = INITIAL_COUNTDOWN;
	ui->blackTimer->display("10:00");
	ui->whiteTimer->display("10:00");
	BlackTimer->stop();
	WhiteTimer->stop();
	if (player == BLACK_PLAYER) {
		BlackTimer->start(1000);
	}
	else {
		WhiteTimer->start(1000);
	}
}

void Controller::UpdateBlackTimer() {
	QString timeString = QString("%1:%2").arg(BlackCountdown / 60, 2, 10, QChar('0')).arg(BlackCountdown % 60, 2, 10, QChar('0'));
	ui->blackTimer->display(timeString);
	if (!BlackCountdown) {
		BlackCountdown = INITIAL_COUNTDOWN;    // 初始化倒计时时间
		WhiteCountdown = INITIAL_COUNTDOWN;
		emit GameOver(WHITE_WIN);
	}
	else {
		BlackCountdown--;
	}
}

void Controller::UpdateWhiteTimer() {
	QString timeString = QString("%1:%2").arg(WhiteCountdown / 60, 2, 10, QChar('0')).arg(WhiteCountdown % 60, 2, 10, QChar('0'));
	ui->whiteTimer->display(timeString);
	if (!WhiteCountdown) {
		BlackCountdown = INITIAL_COUNTDOWN;    // 初始化倒计时时间
		WhiteCountdown = INITIAL_COUNTDOWN;
		emit GameOver(BLACK_WIN);
	}
	else {
		WhiteCountdown--;
	}
}

void Controller::EndGame(GameStatus gameStatus) {
	// qDebug() << "End game! ";
	if (gameStatus == DRAW) {
		QMessageBox::information(this, "游戏结束", "和棋", QMessageBox::Ok);
	}
	else {
		QString player = (gameStatus == BLACK_WIN) ? "黑方" : "白方";
		QMessageBox::information(this, "游戏结束", tr("%1获胜").arg(player), QMessageBox::Ok);
	}
	emit ReturnToMainWindow();
}

void Controller::Undo() {
	ui->chessboard->Undo();
}

void Controller::SetGameMode(GameMode mode) {
	QSet<Player> players;
	if (mode == AI_MODE) {
		QMessageBox msgBox;
		msgBox.setWindowIcon(QIcon(":/img/blackpiece.png"));
		msgBox.setWindowTitle(tr("选择执方"));
		msgBox.setText("请选择你的执方");
		QPushButton* blackButton = msgBox.addButton(tr("黑方"), QMessageBox::YesRole);
		QPushButton* whiteButton = msgBox.addButton(tr("白方"), QMessageBox::NoRole);

		msgBox.exec();

		if (msgBox.clickedButton() == blackButton) {
			players << BLACK_PLAYER;
			ai->SetPlayer(WHITE_PLAYER);
		}
		else if (msgBox.clickedButton() == whiteButton) {
			players << WHITE_PLAYER;
			ai->SetPlayer(BLACK_PLAYER);
		}
		setWindowTitle(tr("AI 五子棋 - 人机游戏"));
	}
	else {
		players << BLACK_PLAYER << WHITE_PLAYER;
		setWindowTitle(tr("AI 五子棋 - 本地游戏"));
	}
	ui->chessboard->InitBoard(mode, players);
}

void Controller::AiSwitchPiece(Player player) {
	auto players = ui->chessboard->GetPlayers();
	if (ui->chessboard->GetGameMode() == AI_MODE) {
		if (!players.contains(player)) {
			if (player == BLACK_PLAYER) {
				ui->blackLable2->setText("努力思考中(>_<)");
			}
			else {
				ui->whiteLable2->setText("努力思考中(>_<)");
			}
			ai->start();
		} else {
			if (player == BLACK_PLAYER) {
				ui->whiteLable2->setText("");
			}
			else {
				ui->blackLable2->setText("");
			}
		}
	}
}

void Controller::SetBoardPiece(int x, int y) {
	ui->chessboard->DropPiece(x, y);
}

void Controller::SetAiPiece(int x, int y, BoardPiece piece) {
	ai->DropPiece(x, y, piece);
}

void Controller::TakeAiPiece(int x, int y) {
	ai->TakePiece(x, y);
}

void Controller::ReturnToMain() {
	emit ReturnToMainWindow();
}

Controller::~Controller()
{
	delete ui;
}

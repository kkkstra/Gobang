#include "board.h"
#include "ui_board.h"
#include <QDebug>

const QSize Board::BOARD_SIZE(750, 750);
const QSize Board::LATT_SIZE(50, 50);
const QPoint Board::START_POS(25, 25);

Board::Board(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::Board)
{
	ui->setupUi(this);
	setMouseTracking(true);
	setFixedSize(750, 750);

	QSet<Player> defaultPlayers;
	defaultPlayers << BLACK_PLAYER << WHITE_PLAYER;
	InitBoard(LOCAL_MODE, defaultPlayers);
	StartGame();
}

void Board::InitBoard(GameMode mode, QSet<Player> selectedPlayers) {
	gameMode = mode;
	players = selectedPlayers;
}

void Board::StartGame() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			board[i][j] = NO_PIECE;
		}
	}
	currentPlayer = BLACK_PLAYER;
	gameStatus = PLAYING;
	update();
	emit PlayerSwitch(currentPlayer);
}

void Board::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	QBrush  brush;
	brush.setColor(QColor("#EEEEEE"));
	brush.setStyle(Qt::SolidPattern);
	painter.setBrush(brush);

	painter.drawRect(QRect(QPoint(START_POS.x() - 5, START_POS.y() - 5), LATT_SIZE * 14 + QSize(10, 10)));
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			painter.drawRect(QRect(START_POS + QPoint(i * LATT_SIZE.width(), j * LATT_SIZE.height()), LATT_SIZE));
		}
	}

	// 绘制"天元"与"星"
	brush.setColor(Qt::black);
	painter.setBrush(brush);
	QPair<int, int> pointers[5] = {
		qMakePair(3, 3),
		qMakePair(3, 11),
		qMakePair(7, 7),
		qMakePair(11, 3),
		qMakePair(11, 11)
	};
	for (auto p : pointers) {
		painter.drawRect(QRect(START_POS + QPoint(p.first * LATT_SIZE.width() - 5, p.second * LATT_SIZE.height() - 5), QSize(10, 10)));
	}

	// 选框
	QColor color = currentPlayer == WHITE_PLAYER ? QColor("#EEEEEE") : QColor("#333333");
	brush.setColor(color);
	painter.setBrush(brush);
	painter.setPen(QPen(QColor("#333333"), 2));
	painter.drawRect(QRect(mousePos - QPoint(8, 8), QSize(16, 16)));

	// 绘制棋子
	painter.setPen(Qt::NoPen);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (board[i][j] != NO_PIECE) {
				QColor color = (board[i][j] == WHITE_PIECE) ? QColor("#EEEEEE") : QColor("#333333");
				painter.setBrush(QBrush(color));
				painter.setPen(QPen(QColor("#333333"), 3));
				painter.drawEllipse(START_POS.x() - (LATT_SIZE.width() - 5) / 2 + i * LATT_SIZE.width(),
					START_POS.y() - (LATT_SIZE.width() - 5) / 2 + j * LATT_SIZE.height(),
					LATT_SIZE.width() - 5, LATT_SIZE.height() - 5);
			}
		}
	}

	if (!piecesRecord.empty()) {
		QPoint last = piecesRecord.top();
		int lx = last.x(), ly = last.y();
		color = (board[lx][ly] == WHITE_PIECE) ? QColor("#333333") : QColor("#EEEEEE");
		painter.setBrush(QBrush(color));
		painter.setPen(QPen(color, 3));
		painter.drawEllipse(START_POS.x() - 6 / 2 + last.x() * LATT_SIZE.width(),
			START_POS.y() - 6 / 2 + last.y() * LATT_SIZE.height(),
			6, 6);
	}
}

void Board::mouseMoveEvent(QMouseEvent* event) {
	if (players.contains(currentPlayer)) {
		QPoint absPos = event->pos();
		QPoint relPos = absPos - (START_POS - QPoint(LATT_SIZE.width() / 2, LATT_SIZE.height() / 2));
		int x = relPos.x();
		int y = relPos.y();

		if (x < 0 || x >= LATT_SIZE.width() * 15 || y < 0 || y >= LATT_SIZE.height() * 15)
			return;

		int X = x / LATT_SIZE.width();
		int Y = y / LATT_SIZE.height();

		// 更新鼠标位置
		mousePos = START_POS + QPoint(X * LATT_SIZE.width(), Y * LATT_SIZE.height());
		update();
	}
}

void Board::mouseReleaseEvent(QMouseEvent* event) {
	if (players.contains(currentPlayer)) {
		QPoint absPos = event->pos();
		QPoint relPos = absPos - (START_POS - QPoint(LATT_SIZE.width() / 2, LATT_SIZE.height() / 2));
		int x = relPos.x();
		int y = relPos.y();

		if (x < 0 || x >= LATT_SIZE.width() * 15 || y < 0 || y >= LATT_SIZE.height() * 15)
			return;

		int X = x / LATT_SIZE.width();
		int Y = y / LATT_SIZE.height();

		if (board[X][Y] == NO_PIECE) {
			DropPiece(X, Y);
		}
	}
}

void Board::DropPiece(int X, int Y) {
	BoardPiece piece = currentPlayer == BLACK_PLAYER ? BLACK_PIECE : WHITE_PIECE;
	board[X][Y] = piece;
	update();
	piecesRecord.push(QPoint(X, Y));
	CheckWinner();
	emit SetAiPiece(X, Y, piece);
	if (gameStatus == PLAYING) {
		Player player = currentPlayer == BLACK_PLAYER ? WHITE_PLAYER : BLACK_PLAYER;
		SwitchPlayer(player);
	}
}

void Board::SwitchPlayer(Player player) {
	update();
	currentPlayer = player;
	emit PlayerSwitch(currentPlayer);
}

void Board::CheckWinner() {
	bool full = true;
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			if (board[i][j] == NO_PIECE) {
				full = false;
			}
			if (board[i][j] != NO_PIECE && CheckFivePieces(i, j)) {
				gameStatus = (board[i][j] == BLACK_PIECE) ? BLACK_WIN : WHITE_WIN;
				emit GameOver(gameStatus);
			}
		}
	}
	if (full) {
		gameStatus = DRAW;
		emit GameOver(gameStatus);    // 和棋
	}
}

bool Board::CheckFivePieces(int x, int y) {
	const int direction[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };
	int cur = board[x][y];
	bool win = false;
	for (int k = 0; k < 4; k++) {
		int tx = x, ty = y;
		bool equal = true;
		for (int i = 0; i < 4; i++) {
			tx += direction[k][0];
			ty += direction[k][1];
			if (tx < 0 || tx >= 15 || ty < 0 || ty >= 15 || board[tx][ty] != cur) {
				equal = false;
				break;
			}
		}
		if (equal) {
			win = true;
			break;
		}
	}
	return win;
}

void Board::Undo() {
	if (gameStatus == PLAYING) {
		if (gameMode == LOCAL_MODE) {
			QPoint pos = piecesRecord.pop();
			board[pos.x()][pos.y()] = NO_PIECE;
			emit TakeAiPiece(pos.x(), pos.y());
			update();
			Player player = currentPlayer == BLACK_PLAYER ? WHITE_PLAYER : BLACK_PLAYER;
			SwitchPlayer(player);
		} else {
			QPoint pos = piecesRecord.pop();
			board[pos.x()][pos.y()] = NO_PIECE;
			emit TakeAiPiece(pos.x(), pos.y());
			pos = piecesRecord.pop();
			board[pos.x()][pos.y()] = NO_PIECE;
			emit TakeAiPiece(pos.x(), pos.y());
			emit DecreaseRound();
			update();
			SwitchPlayer(currentPlayer);
		}
	}
}

GameMode Board::GetGameMode() { return gameMode; }

const QSet<Player>& Board::GetPlayers() { return players; }

Player Board::GetCurrentPlayer() { return currentPlayer; }

Board::~Board()
{
	delete ui;
}

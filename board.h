#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QSet>
#include <QPainter>
#include <QVector>
#include <QPair>
#include <QMouseEvent>
#include <QStack>
#include <QPoint>

enum Player {
	BLACK_PLAYER,
	WHITE_PLAYER
};

enum BoardPiece {
	NO_PIECE,
	BLACK_PIECE,
	WHITE_PIECE
};

enum GameStatus {
	PLAYING,
	DRAW,
	BLACK_WIN,
	WHITE_WIN,
};

enum GameMode {
	LOCAL_MODE,
	AI_MODE
};

namespace Ui {
	class Board;
}

class Board : public QWidget
{
	Q_OBJECT

public:
	explicit Board(QWidget* parent = nullptr);
	~Board();

	void paintEvent(QPaintEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);

	void InitBoard(GameMode mode, QSet<Player> selectedPlayers);
	void StartGame();
	void Undo();
	GameMode GetGameMode();
	const QSet<Player>& GetPlayers();
	Player GetCurrentPlayer();
	void DropPiece(int X, int Y);

public:
	static const QSize BOARD_SIZE; // 棋盘大小
	static const QSize LATT_SIZE; // 棋子大小
	static const QPoint START_POS; // 棋盘中单元格起始位置

signals:
	void GameOver(GameStatus gameStatus);
	void PlayerSwitch(Player player);
	void ReturnToMainWindow();
	void SetAiPiece(int X, int Y, BoardPiece piece);
	void TakeAiPiece(int x, int y);
	void DecreaseRound();

private:
	Ui::Board* ui;
	QSet<Player> players;
	BoardPiece board[15][15];
	QPoint mousePos;
	Player currentPlayer;
	GameStatus gameStatus;
	GameMode gameMode;
	QStack<QPoint> piecesRecord;

	void SwitchPlayer(Player player);
	void CheckWinner();
	bool CheckFivePieces(int x, int y);
};

#endif // BOARD_H

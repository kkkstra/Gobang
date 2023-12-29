#ifndef GOBANGAI_H
#define GOBANGAI_H

#include <QThread>
#include <QTime>
#include <QDebug>
#include <QPoint>
#include "board.h"
#include "gobangai_macro.h"

struct PointScore {
	QPoint pos;
	int score;
	PointScore(int x, int y, int score = -INF)
		: pos(x, y) {}
};

class GobangAi : public QThread {
	Q_OBJECT
private:
	int round;
	int board[15][15];
	QPoint nextDrop;
	Player aiPlayer;
	Player humanPlayer;

	int typeTable[4][4][4][4][4][4]; // 棋形映射

public:
	GobangAi();

	void InitGobangAi();
	void run() override;
	void SetPlayer(Player player);
	void DropPiece(int x, int y, BoardPiece piece);
	void TakePiece(int x, int y);
	void DecreaseRound();

signals:
	void AiDropPiece(int x, int y);

private:
	void InitTypeTable();
	void SetNextDrop(int x, int y);
	int MinMaxSearch(const Player player, const int depth, int alpha, int beta);
	void PlayRound0(); // 第一局
	int SeekPoints(QPoint* points, int chessid, int limit);
	int Evaluate(int &res, int record[17]);
	int EvaluatePosWorth(int x, int y, int chessid);
	int CalculatePosScore(int black, int white, int chessid);
	QPoint getXY(int row, int col, int dir, int rel);
	bool CheckBound(int x, int y);
	bool KillSearch(const Player player, int depth);
	int SeekKillPoints(QPoint* points);
};

#endif // GOBANGAI_H

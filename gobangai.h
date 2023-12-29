#ifndef GOBANGAI_H
#define GOBANGAI_H

#include <QThread>
#include <QTime>
#include <QDebug>
#include <QPoint>
#include "board.h"
#include "gobangai_macro.h"

class GobangAi : public QThread {
	Q_OBJECT
private:
	int round;
	BoardPiece board[15][15];
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
	void PlayRound1(); // 第一局
	int SeekPoints(QPoint* points, Player player);
	int Evaluate();
};

#endif // GOBANGAI_H

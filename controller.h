#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "board.h"
#include "gobangai.h"
#include "ui_style.h"
#include <QWidget>
#include <QTimer>
#include <QMessageBox>

const int INITIAL_COUNTDOWN = 599;

namespace Ui {
	class Controller;
}

class Controller : public QWidget
{
	Q_OBJECT

public:
	explicit Controller(QWidget* parent = nullptr);
	~Controller();

	void InitController();
	void InitGame(GameMode);

public slots:
	void UpdateBlackTimer();
	void UpdateWhiteTimer();
	void SwitchTimer(Player);
	void EndGame(GameStatus);
	void ReturnToMain();
	void AiSwitchPiece(Player player);
	void SetAiPiece(int x, int y, BoardPiece piece);
	void TakeAiPiece(int x, int y);
	void SetBoardPiece(int x, int y);

protected:
	virtual void mousePressEvent(QMouseEvent* event);

signals:
	void GameOver(GameStatus);
	void ReturnToMainWindow();

private:
	Ui::Controller* ui;
	GobangAi* ai;
	UIPushbutton titleButton[TITLE_BUTTON_N];

	QTimer* BlackTimer;
	QTimer* WhiteTimer;
	int BlackCountdown, WhiteCountdown;

	void ConfigureUi();
	void Undo();
	void SetGameMode(GameMode);
};

#endif // CONTROLLER_H

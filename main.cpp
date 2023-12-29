#include "mainwindow.h"
#include "controller.h"

#include <QApplication>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);

	qRegisterMetaType<GameStatus>("GameStatus");
	qRegisterMetaType<Player>("Player");
	qRegisterMetaType<BoardPiece>("BoardPiece");

	MainWindow w;
	w.show();
	return a.exec();
}

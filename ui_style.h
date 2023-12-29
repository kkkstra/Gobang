#ifndef UI_STYLE_H
#define UI_STYLE_H

#include <QString>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QEvent>

enum TITLE_BUTTON_INDEX {
	MINI_BUTTON,
	CLOSE_BUTTON,
	TITLE_BUTTON_N
};

enum TITLE_BUTTON_SIZE_PARAM
{
	TITLE_BUTTON_W = 30,
	TITLE_BUTTON_H = 30,
	TITLE_BUTTON_ITV = 32,
	TITLE_BUTTON_L = 500 - TITLE_BUTTON_N * (int)(TITLE_BUTTON_ITV * 1.15),
	TITLE_BUTTON_U = TITLE_BUTTON_H / 4,
	TITLE_BUTTON_D = TITLE_BUTTON_H + TITLE_BUTTON_H / 4
};

class UIPushbutton : public QPushButton
{
public:
	UIPushbutton(QWidget* parent = Q_NULLPTR);
	virtual void closeEvent(QEvent* event);
	void test();
};

const QString CTRL_BUTTON_STYLE =
// 操作按钮风格（扁平，圆角，黑白）
"QPushButton"
"{"
"background-color:rgba(244,244,244,200);"	// 背景色（也可以设置图片）
"border-style:outset;"				// 边框样式（inset/outset）
"border-width:2px;"				// 边框宽度像素
"border-radius:18px;"				// 边框圆角半径像素
"border-color:rgba(68,68,68,220);"		// 边框颜色
"font:bold 20px;"				// 字体，字体大小
"color:rgba(58,58,58,230);"			// 字体颜色
"padding:4px;"					// 填衬
"}"
//鼠标按下样式
"QPushButton:pressed"
"{"
"background-color:rgba(42,42,42,255);"
"border-width:4px;"				// 边框宽度像素
"border-color:rgba(234,234,234,255);"
"border-style:inset;"
"color:rgba(200,200,200,255);"
"}"
//鼠标悬停样式
"QPushButton:hover"
"{"
"background-color:rgba(48,48,48,230);"
"border-color:rgba(250,250,250,250);"
"color:rgba(250,250,250,250);"
"}";

const QString BUBBLE_BUTTON_STYLE =
// 气泡按钮风格（方块，扁平，黑白）
"QPushButton"
"{"
"background-color:rgba(250,250,250,230);"	// 背景色（也可以设置图片）
"border-style:outset;"				// 边框样式（inset/outset）
"border-width:2px;"				// 边框宽度像素
"border-radius:15px;"				// 边框圆角半径像素
"border-color:rgba(68,68,68,220);"		// 边框颜色
"padding:6px;"					// 填衬
"}";

const QString TITLE_BUTTON_STYLE[] = {
	// 标题栏按钮风格（扁平，圆角，黑白）
	"QPushButton"
	"{"
		"background-color:rgba(68,68,68,0);"		// 背景色（也可以设置图片）
		"border-style:outset;"				// 边框样式（inset/outset）
		"border-width:2px;"				// 边框宽度像素
		"border-radius:15px;"				// 边框圆角半径像素
		"border-color:rgba(68,68,68,0);"		// 边框颜色
		"font:bold 16px;"				// 字体，字体大小
		"color:rgba(68,68,68,240);"			// 字体颜色
	"}"
	//鼠标按下样式
	"QPushButton:pressed"
	"{"
		"font:bold12px;"
	"}",

	"QPushButton"
	"{"
		"background-color:rgba(68,68,68,0);"
		"border-style:outset;"
		"border-width:2px;"
		"border-radius:15px;"
		"border-color:rgba(68,68,68,0);"
		"font:bold 24px;"
		"color:rgba(68,68,68,240);"
	"}"
	//鼠标按下样式
	"QPushButton:pressed"
	"{"
		"font:bold 20px;"
	"}"
	//鼠标悬停样式（无）
};


#endif // UI_STYLE_H

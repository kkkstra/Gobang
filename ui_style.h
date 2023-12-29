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
// ������ť��񣨱�ƽ��Բ�ǣ��ڰף�
"QPushButton"
"{"
"background-color:rgba(244,244,244,200);"	// ����ɫ��Ҳ��������ͼƬ��
"border-style:outset;"				// �߿���ʽ��inset/outset��
"border-width:2px;"				// �߿�������
"border-radius:18px;"				// �߿�Բ�ǰ뾶����
"border-color:rgba(68,68,68,220);"		// �߿���ɫ
"font:bold 20px;"				// ���壬�����С
"color:rgba(58,58,58,230);"			// ������ɫ
"padding:4px;"					// ���
"}"
//��갴����ʽ
"QPushButton:pressed"
"{"
"background-color:rgba(42,42,42,255);"
"border-width:4px;"				// �߿�������
"border-color:rgba(234,234,234,255);"
"border-style:inset;"
"color:rgba(200,200,200,255);"
"}"
//�����ͣ��ʽ
"QPushButton:hover"
"{"
"background-color:rgba(48,48,48,230);"
"border-color:rgba(250,250,250,250);"
"color:rgba(250,250,250,250);"
"}";

const QString BUBBLE_BUTTON_STYLE =
// ���ݰ�ť��񣨷��飬��ƽ���ڰף�
"QPushButton"
"{"
"background-color:rgba(250,250,250,230);"	// ����ɫ��Ҳ��������ͼƬ��
"border-style:outset;"				// �߿���ʽ��inset/outset��
"border-width:2px;"				// �߿�������
"border-radius:15px;"				// �߿�Բ�ǰ뾶����
"border-color:rgba(68,68,68,220);"		// �߿���ɫ
"padding:6px;"					// ���
"}";

const QString TITLE_BUTTON_STYLE[] = {
	// ��������ť��񣨱�ƽ��Բ�ǣ��ڰף�
	"QPushButton"
	"{"
		"background-color:rgba(68,68,68,0);"		// ����ɫ��Ҳ��������ͼƬ��
		"border-style:outset;"				// �߿���ʽ��inset/outset��
		"border-width:2px;"				// �߿�������
		"border-radius:15px;"				// �߿�Բ�ǰ뾶����
		"border-color:rgba(68,68,68,0);"		// �߿���ɫ
		"font:bold 16px;"				// ���壬�����С
		"color:rgba(68,68,68,240);"			// ������ɫ
	"}"
	//��갴����ʽ
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
	//��갴����ʽ
	"QPushButton:pressed"
	"{"
		"font:bold 20px;"
	"}"
	//�����ͣ��ʽ���ޣ�
};


#endif // UI_STYLE_H

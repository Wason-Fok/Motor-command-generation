#pragma once
// -----------------------------
// 用于显示常用命令列表
// -----------------------------

#include <QWidget>
#include "ui_ComandList.h"

class ComandList : public QWidget
{
	Q_OBJECT

public:
	ComandList(QWidget *parent = Q_NULLPTR);
	~ComandList();

private:
	Ui::ComandList ui;
};

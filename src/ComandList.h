#pragma once
// -----------------------------
// ������ʾ���������б�
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

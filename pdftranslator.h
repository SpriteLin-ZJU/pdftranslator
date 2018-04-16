#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_pdftranslator.h"

class pdftranslator : public QMainWindow
{
	Q_OBJECT

public:
	pdftranslator(QWidget *parent = Q_NULLPTR);

private:
	Ui::pdftranslatorClass ui;
};

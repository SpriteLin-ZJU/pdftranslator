#pragma once

#include <QMainWindow>
#include <QTextEdit>
#include "trans.h"


class PdfTranslator : public QMainWindow
{
	Q_OBJECT

public:
	PdfTranslator(QWidget *parent = 0);
	~PdfTranslator();
private:
	void open();
	QAction *openAction;
	void save();
	QAction *saveAction;
	void deleteEnter();
	QAction *brushAction;
	void translate();
	QAction *translateAction;

	QTextEdit *textEdit;

	Trans *trans;

};

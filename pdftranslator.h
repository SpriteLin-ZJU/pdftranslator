#pragma once

#include <QMainWindow>
#include <QTextEdit>

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

	QTextEdit *textEdit;
};

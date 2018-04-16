#include "pdftranslator.h"
#include <QApplication>
#include <stdio.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PdfTranslator w;
	w.resize(700, 400);
	w.show();

	return a.exec();
}

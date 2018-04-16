#include "pdftranslator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	pdftranslator w;
	w.show();
	return a.exec();
}

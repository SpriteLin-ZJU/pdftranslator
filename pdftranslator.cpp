#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QFontDatabase>
#include "pdftranslator.h"


PdfTranslator::PdfTranslator(QWidget *parent)
	: QMainWindow(parent),
	trans(0)
{
	setWindowTitle(tr("PDF Translator"));
	//open按钮
	openAction = new QAction(QIcon(":/images/Resources/images/doc-open.png"), tr("&Open..."), this);
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing file"));
	connect(openAction, &QAction::triggered, this, &PdfTranslator::open);
	//save按钮
	saveAction = new QAction(QIcon(":/images/Resources/images/save.png"), tr("&Save..."), this);
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save file"));
	connect(saveAction, &QAction::triggered, this, &PdfTranslator::save);
	//格式调整按钮
	brushAction = new QAction(QIcon(":/images/Resources/images/paintbrush.png"), tr("&DeleteEnter..."), this);
	brushAction->setStatusTip(tr("Delete line break"));
	connect(brushAction, &QAction::triggered, this, &PdfTranslator::deleteEnter);
	//翻译按钮
	translateAction = new QAction(QIcon(":/images/Resources/images/translate.png"), tr("&Translate..."), this);
	translateAction->setStatusTip(tr("Translate text"));
	connect(translateAction, &QAction::triggered, this, &PdfTranslator::translate);

	QMenu *file = menuBar()->addMenu(tr("&File"));
	file->addAction(openAction);
	file->addAction(saveAction);

	QMenu *tool = menuBar()->addMenu(tr("&Tool"));

	QToolBar *toolBar = addToolBar(tr("&File"));
	toolBar->addAction(openAction);
	toolBar->addAction(saveAction);
	toolBar->addAction(brushAction);
	toolBar->addAction(translateAction);

	textEdit = new QTextEdit(this);
	setCentralWidget(textEdit);
	textEdit->setFont(QFont("Arial, Microsoft YaHei UI",12));

	statusBar();

	trans = new Trans;

}

PdfTranslator::~PdfTranslator()
{
	delete trans;
}

void PdfTranslator::open()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Read File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream in(&file);
		textEdit->setText(in.readAll());
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"),
			tr("You did not select any file."));
	}
}

void PdfTranslator::save()
{
	QString path = QFileDialog::getSaveFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
	if (!path.isEmpty()) {
		QFile file(path);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QMessageBox::warning(this, tr("Write File"),
				tr("Cannot open file:\n%1").arg(path));
			return;
		}
		QTextStream out(&file);
		out << textEdit->toPlainText();
		file.close();
	}
	else {
		QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
	}
}

void PdfTranslator::deleteEnter()
{
	QString text = textEdit->toPlainText();
	text.replace("\n", " ");
	textEdit->setText(text);

}

void PdfTranslator::translate()
{
	QString text = textEdit->toPlainText();
	if (!text.isEmpty()) {
		auto res = trans->translate(text, QString("zh"), QString("en"));
		if (res.first)
			textEdit->setText(res.second);
		else
			statusBar()->showMessage("Error", 3000);
	}
}


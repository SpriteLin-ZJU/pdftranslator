#ifndef TRANS_H
#define TRANS_H

#include <QObject>
#include <QPair>
class Parser;
class Trans : public QObject
{
    Q_OBJECT
public:
    explicit Trans(QObject *parent = 0);

private:
    Parser *parser;
public slots:
    QPair <bool, QString> translate(const QString & string, const QString & to = "auto", const QString & from = "auto");

};

#endif // TRANS_H

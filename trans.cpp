#include "trans.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QCryptographicHash>
#include <QEventLoop>
#include <time.h>
#include <QDebug>

QString toMd5(QString str)
{
    QString md5;
    QByteArray array;
    array = QCryptographicHash::hash(str.toUtf8(), QCryptographicHash::Md5);
    md5 = array.toHex();
    return md5;
}
QString signCreate(QString appid, QString q, int salt, QString key)
{
    QString ret = QString("%1%2%3%4").arg(appid).arg(q).arg(salt).arg(key);
    return toMd5(ret);
}

class Parser: public QObject
{
    Q_OBJECT
public:
    bool init()
    {
        qsrand(time(0));
        url = "http://api.fanyi.baidu.com/api/trans/vip/translate";
        appid = "20180416000147193";
        key = "IpGYAVJ3NZvEWXM_5Ujw";
        return true;
    }

    QPair <bool , QString> trans(const QString & string, const QString & to , const QString & from)
    {
        QEventLoop event;
        salt = qrand() % INT_MAX;
        //create postStr
        sign = signCreate(appid, string, salt, key);
        QString format = QString("q=%1&appid=%4&salt=%5&from=%2&to=%3&sign=%6")
                .arg(string)
                .arg(from)
                .arg(to)
                .arg(appid)
                .arg(salt)
                .arg(sign);
        qDebug() << format;
        QString postStr = QString("%7?q=%1&appid=%4&salt=%5&from=%2&to=%3&sign=%6")
                .arg(string)
                .arg(from)
                .arg(to)
                .arg(appid)
                .arg(salt)
                .arg(sign)
                .arg(url);
        QByteArray buf;
        QNetworkRequest request = QNetworkRequest(QUrl(postStr));
        request.setRawHeader("Content-Type", "application");

        QNetworkReply *replay = NULL;
        auto c1 = connect(&himma, &QNetworkAccessManager::finished, [&](){
            if (replay) {
                buf = replay->readAll();
               event.exit(1);
            }
        });
//        const QByteArray array = format.toUtf8();
        replay = himma.get(request);
//        replay =  himma.post(request, format.toUtf8());
        event.exec();

        disconnect(c1);

        if (buf.isEmpty()) {
            qDebug() << "empty";
            return {false, string};
        } else {
            QString jaso = buf;
            qDebug() << jaso;
        }

        QJsonObject data(QJsonDocument::fromJson(buf).object());
        if(!data.contains("trans_result")
             || data["trans_result"].toArray().isEmpty()
             || !data["trans_result"].toArray()[0].toObject().contains("dst")) {
            qDebug() << "no result";

            return { false, QString() };
        }

        return { true, data["trans_result"].toArray()[0].toObject()["dst"].toString() };
    }

private:
    QString url;
    QString q;
    QString from;
    QString to;
    QString appid;
    int salt;
    QString key;
    QString sign;

    QNetworkAccessManager himma;
};
Trans::Trans( QObject *parent) : QObject(parent)
{
    parser = new Parser;
    parser->init();
}
QPair <bool, QString> Trans::translate(const QString & string, const QString & to , const QString & from )
{
    QByteArray a = string.toUtf8();

    QString str = a;
    return parser->trans(str, to, from);
}

#include "trans.moc"
//


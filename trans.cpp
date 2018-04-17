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
        url = "https://translation.googleapis.com/language/translate/v2";
        appid = "20180416000147193";
        key = "AIzaSyBcntEMjw6fXJPmP0KqGOkg_edcNoskEJY";
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
        QString postStr = QString("%5?key=%4&source=%2&target=%3&q=%1")
                .arg(string)
                .arg(from)
                .arg(to)
                .arg(key)
                .arg(url);
		qDebug() << postStr;
		qDebug() << key;

        QByteArray buf;
        QNetworkRequest request = QNetworkRequest(QUrl(postStr));
        request.setRawHeader("Content-Type", "application");		//请求头

        QNetworkReply *reply = NULL;
        auto c1 = connect(&himma, &QNetworkAccessManager::finished, [&](){
            if (reply) {
                buf = reply->readAll();
               event.exit(1);
            }
        });
//        const QByteArray array = format.toUtf8();
        reply = himma.get(request);
//        replay =  himma.post(request, format.toUtf8());
        event.exec();

        disconnect(c1);

        if (buf.isEmpty()) {
            qDebug() << "empty";
            return {false, string};
        } else {
            QString jason = buf;
            qDebug() << jason;
        }

        QJsonObject data(QJsonDocument::fromJson(buf).object());
		QJsonObject jason = data["data"].toArray()[0].toObject();
        if(!jason.contains("translations")
             || jason["translations"].toArray().isEmpty()
             || !jason["translations"].toArray()[0].toObject().contains("translatedText")) {
            qDebug() << "no result";

            return { false, QString() };
        }

        return { true, jason["translations"].toArray()[0].toObject()["translatedText"].toString() };
		//返回格式{"from":"en","to":"zh","trans_result":[{"src":"apple","dst":"\u82f9\u679c"}]}
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


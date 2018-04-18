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



class Parser: public QObject
{
    Q_OBJECT
public:
    bool init()
    {
        url = "https://translation.googleapis.com/language/translate/v2";
        key = "";
        return true;
    }

    QPair <bool , QString> trans(const QString & string, const QString & to , const QString & from)
    {
        QEventLoop event;

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
        request.setRawHeader("Content-Type", "application");		//ÇëÇóÍ·

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
		QJsonObject jason = data["data"].toObject();
        if(!jason.contains("translations")
             || jason["translations"].toArray().isEmpty()
             || !jason["translations"].toArray()[0].toObject().contains("translatedText")) {
            qDebug() << "no result";

            return { false, QString() };
        }

        return { true, jason["translations"].toArray()[0].toObject()["translatedText"].toString() };
		/*{
			"data": {
				"translations": [
				{
					"translatedText": "Mi nombre es Steve",
						"detectedSourceLanguage" : "en"
				}
				]
			}
		}*/

		delete reply;
	}

private:
    QString url;
    QString q;
    QString from;
    QString to;
    QString key;

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


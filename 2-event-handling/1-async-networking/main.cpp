#include <QtCore/QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

void printHtml(const QString &html)
{
  qDebug() << "Done!";
  qDebug() << html;
}

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  QString html;
  qDebug() << "Starting...";

  QNetworkAccessManager manager;
  QNetworkRequest request(QUrl("http://www.dustyfeet.com"));
  QNetworkReply *reply = manager.get(request);

  QObject::connect(reply, &QNetworkReply::readyRead, [reply, &html]
                   { html += reply->readAll(); });

  QObject::connect(reply, &QNetworkReply::downloadProgress, [](qint64 bytesReceived, qint64 bytesTotal)
                   { qDebug() << "Progress " << bytesReceived << " of " << bytesTotal; });

  QObject::connect(reply, &QNetworkReply::finished, [&html]
                   { printHtml(html); });

  return app.exec();
}

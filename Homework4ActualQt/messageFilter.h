#ifndef MESSAGEFILTER_H
#define MESSAGEFILTER_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class MessageFilter : public QObject
{
    public: 
      MessageFilter();

      bool filterMessage(QString message);
    private: 
      QNetworkAccessManager manager;
      QString apiKey;
      QUrl url;
};

#endif

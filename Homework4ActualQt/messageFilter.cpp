#include "messageFilter.h"
#include <string>
#include <QDebug>
#include <iostream>
#include <QEventLoop>

MessageFilter::MessageFilter()
{
  url = QUrl("https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent");
  apiKey = "AIzaSyDUUKwYDyav0IoQoqAMcmdsgVt6pNzzO-Y";
}

bool MessageFilter::filterMessage(QString message)
{
  QNetworkRequest request(url);
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  request.setRawHeader("x-goog-api-key", apiKey.toUtf8());

  //Prompt for api
  QString prompt = QStringLiteral(
  R"(You will act as a message moderation systme assistant.
  Analyze the user message below, and respond with exactly one word: true if the message is
  appropriate and false if not.

  If the message contains hateful speech, racism, harrasment, sexual content, threats of violence,
  obscence language or excessive profanity, respond with false. Otherwise, respond with true.
    If there are reference to commiting self-harm, or self violence, respond with false.

  Here is the user message to analyze:
  )") + message;

  /*
    {
      "contents": [
        {
          "role": "user",
          "parts": [
            {"text": "Explain the required JSON structure for the Gemini API."}
          ]
        }
      ],
    }

    This is requred format of a prompt sent to gemini, so I have to manually construct in(C++ doesnt allow you to pass
    JSON object as string literal)
   */

  QJsonObject geminiPrompt;
  geminiPrompt["text"] = prompt;

  QJsonArray parts;
  parts.append(geminiPrompt);

  QJsonObject body;
  body["parts"] = parts;
  body["role"] = "user";

  QJsonArray contentArr;
  contentArr.append(body);

  QJsonObject finalObj;
  finalObj["contents"] = contentArr;

  QJsonDocument doc(finalObj);
  QByteArray data = doc.toJson();

    //Send the actual request to the gemini api
  QNetworkReply* reply = manager.post(request, data);

  //Do not execute furthur until response is received(reply is asynchronous)
  QEventLoop loop;
  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  //Following code is to parse teh response code from gemini api
  /*
      Response is formatted like:
      {
        "candidates": [
          {
            "content": {
              "parts": [
                {
                  "text": "true" or "false"
                }
              ]
            }
          }
        ]
      }
  */
  QByteArray responseData = reply->readAll();

  qDebug() << "Raw gemini code: " << responseData;

  QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

  QJsonObject responseObj = jsonResponse.object();

  QJsonArray responses = responseObj["candidates"].toArray();

  QJsonObject firstResponse = responses[0].toObject();

  QJsonObject responseParts = firstResponse["content"].toObject();

  QJsonArray partsPart = responseParts["parts"].toArray();

  QJsonObject textPart = partsPart[0].toObject();

  QString moderationResult = textPart["text"].toString().trimmed().toLower();

  //Get the moderation result and returen eitehr true or false based on that
  if (moderationResult.toStdString() == "false")
  {
      return false;
  }
  else
  {
      return true;
  }

}

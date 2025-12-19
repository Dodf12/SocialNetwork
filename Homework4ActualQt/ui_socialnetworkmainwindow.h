/********************************************************************************
** Form generated from reading UI file 'socialnetworkmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKMAINWINDOW_H
#define UI_SOCIALNETWORKMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkMainWindow
{
public:
    QWidget *centralwidget;
    QLabel *loginPageLabel;
    QPushButton *loginButton;
    QTextEdit *usernameEntry;
    QTableWidget *friendsList;
    QLabel *Post3;
    QLabel *Post4;
    QLabel *Post2;
    QLabel *label_5;
    QTextEdit *addPost;
    QPushButton *submitNewPost;
    QTableWidget *suggestedFriends;
    QPushButton *pushButton;
    QPushButton *AddFriend;
    QComboBox *privacyLevelBox;
    QTextEdit *userBio;
    QPushButton *saveUserBio;
    QComboBox *bioComboBox;
    QPushButton *likePost2;
    QPushButton *likePost3;
    QPushButton *likePost4;
    QPushButton *likePost5;
    QLabel *FriendsLabel;
    QLabel *SuggestedFriendsLabel;
    QPushButton *likePost1;
    QLabel *Post1;
    QPushButton *backToLoginButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkMainWindow)
    {
        if (SocialNetworkMainWindow->objectName().isEmpty())
            SocialNetworkMainWindow->setObjectName("SocialNetworkMainWindow");
        SocialNetworkMainWindow->resize(1100, 792);
        centralwidget = new QWidget(SocialNetworkMainWindow);
        centralwidget->setObjectName("centralwidget");
        loginPageLabel = new QLabel(centralwidget);
        loginPageLabel->setObjectName("loginPageLabel");
        loginPageLabel->setGeometry(QRect(240, -10, 561, 81));
        loginPageLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(450, 310, 100, 32));
        usernameEntry = new QTextEdit(centralwidget);
        usernameEntry->setObjectName("usernameEntry");
        usernameEntry->setGeometry(QRect(410, 270, 201, 31));
        friendsList = new QTableWidget(centralwidget);
        friendsList->setObjectName("friendsList");
        friendsList->setGeometry(QRect(0, 230, 231, 191));
        Post3 = new QLabel(centralwidget);
        Post3->setObjectName("Post3");
        Post3->setGeometry(QRect(250, 270, 591, 101));
        Post4 = new QLabel(centralwidget);
        Post4->setObjectName("Post4");
        Post4->setGeometry(QRect(250, 420, 631, 101));
        Post2 = new QLabel(centralwidget);
        Post2->setObjectName("Post2");
        Post2->setGeometry(QRect(260, 170, 571, 101));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(240, 530, 581, 101));
        addPost = new QTextEdit(centralwidget);
        addPost->setObjectName("addPost");
        addPost->setGeometry(QRect(400, 600, 141, 91));
        submitNewPost = new QPushButton(centralwidget);
        submitNewPost->setObjectName("submitNewPost");
        submitNewPost->setGeometry(QRect(730, 630, 100, 32));
        suggestedFriends = new QTableWidget(centralwidget);
        suggestedFriends->setObjectName("suggestedFriends");
        suggestedFriends->setGeometry(QRect(10, 490, 221, 192));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(960, 10, 101, 32));
        AddFriend = new QPushButton(centralwidget);
        AddFriend->setObjectName("AddFriend");
        AddFriend->setGeometry(QRect(840, 10, 101, 32));
        privacyLevelBox = new QComboBox(centralwidget);
        privacyLevelBox->setObjectName("privacyLevelBox");
        privacyLevelBox->setGeometry(QRect(600, 630, 103, 32));
        userBio = new QTextEdit(centralwidget);
        userBio->setObjectName("userBio");
        userBio->setGeometry(QRect(0, 20, 221, 91));
        saveUserBio = new QPushButton(centralwidget);
        saveUserBio->setObjectName("saveUserBio");
        saveUserBio->setGeometry(QRect(120, 130, 82, 32));
        bioComboBox = new QComboBox(centralwidget);
        bioComboBox->setObjectName("bioComboBox");
        bioComboBox->setGeometry(QRect(0, 120, 103, 32));
        likePost2 = new QPushButton(centralwidget);
        likePost2->setObjectName("likePost2");
        likePost2->setGeometry(QRect(940, 220, 100, 32));
        likePost3 = new QPushButton(centralwidget);
        likePost3->setObjectName("likePost3");
        likePost3->setGeometry(QRect(940, 310, 100, 32));
        likePost4 = new QPushButton(centralwidget);
        likePost4->setObjectName("likePost4");
        likePost4->setGeometry(QRect(940, 440, 100, 32));
        likePost5 = new QPushButton(centralwidget);
        likePost5->setObjectName("likePost5");
        likePost5->setGeometry(QRect(940, 530, 100, 32));
        FriendsLabel = new QLabel(centralwidget);
        FriendsLabel->setObjectName("FriendsLabel");
        FriendsLabel->setGeometry(QRect(50, 180, 111, 31));
        SuggestedFriendsLabel = new QLabel(centralwidget);
        SuggestedFriendsLabel->setObjectName("SuggestedFriendsLabel");
        SuggestedFriendsLabel->setGeometry(QRect(40, 440, 151, 41));
        likePost1 = new QPushButton(centralwidget);
        likePost1->setObjectName("likePost1");
        likePost1->setGeometry(QRect(940, 130, 91, 32));
        Post1 = new QLabel(centralwidget);
        Post1->setObjectName("Post1");
        Post1->setGeometry(QRect(260, 110, 599, 79));
        backToLoginButton = new QPushButton(centralwidget);
        backToLoginButton->setObjectName("backToLoginButton");
        backToLoginButton->setGeometry(QRect(910, 10, 100, 32));
        SocialNetworkMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1100, 33));
        SocialNetworkMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkMainWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkMainWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkMainWindow);

        QMetaObject::connectSlotsByName(SocialNetworkMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkMainWindow)
    {
        SocialNetworkMainWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkMainWindow", "SocialNetworkMainWindow", nullptr));
        loginPageLabel->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Login Page", nullptr));
        loginButton->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Login", nullptr));
        usernameEntry->setHtml(QCoreApplication::translate("SocialNetworkMainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Enter your Username Here:</p></body></html>", nullptr));
        Post3->setText(QCoreApplication::translate("SocialNetworkMainWindow", "TextLabel", nullptr));
        Post4->setText(QCoreApplication::translate("SocialNetworkMainWindow", "TextLabel", nullptr));
        Post2->setText(QCoreApplication::translate("SocialNetworkMainWindow", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("SocialNetworkMainWindow", "TextLabel", nullptr));
        addPost->setHtml(QCoreApplication::translate("SocialNetworkMainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'.AppleSystemUIFont'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Add Post</p></body></html>", nullptr));
        submitNewPost->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Submit", nullptr));
        pushButton->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Back To Profile", nullptr));
        AddFriend->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Add Friend", nullptr));
        privacyLevelBox->setProperty("Private", QVariant(QString()));
        saveUserBio->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Save Bio", nullptr));
        likePost2->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Like Post 2", nullptr));
        likePost3->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Like Post 3", nullptr));
        likePost4->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Like Post 4", nullptr));
        likePost5->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Like Post 5", nullptr));
        FriendsLabel->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Friends", nullptr));
        SuggestedFriendsLabel->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Suggested Friends", nullptr));
        likePost1->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Like Post 1", nullptr));
        Post1->setText(QCoreApplication::translate("SocialNetworkMainWindow", "TextLabel", nullptr));
        backToLoginButton->setText(QCoreApplication::translate("SocialNetworkMainWindow", "Back to Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkMainWindow: public Ui_SocialNetworkMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKMAINWINDOW_H

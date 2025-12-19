#include "socialnetworkmainwindow.h"
#include "ui_socialnetworkmainwindow.h"
#include "network.h"
#include "user.h"
#include "bio.h"
#include "messageFilter.h"
#include <vector>
#include <QDebug>
#include <QLinearGradient>
#include <QBrush>
// DO I NEED PRE AND POST COMMENTS ON MY SHIT?

SocialNetworkMainWindow::SocialNetworkMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SocialNetworkMainWindow)
{
    ui->setupUi(this);

    // Set Starting Page
    currPage = "Login";
    display();

    // Set up Friends Table

    ui->friendsList->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->friendsList, &QTableWidget::itemClicked, this, &SocialNetworkMainWindow::navigateOtherUser);

    // Set up Suggested Friends Table

    ui->suggestedFriends->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->suggestedFriends, &QTableWidget::itemClicked, this, &SocialNetworkMainWindow::navigateOtherUser);

    // Connect Back to Profile Button
    connect(ui->pushButton, &QPushButton::clicked, this, &SocialNetworkMainWindow::backToProfile);

    //Connect back to profile
    connect(ui->backToLoginButton, &QPushButton::clicked, this, &SocialNetworkMainWindow::backToLogin);

    // Connect add Friend
    connect(ui->AddFriend, &QPushButton::clicked, this, &SocialNetworkMainWindow::addFriendButton);

    // Connect like buttons to toggleLikes function
    connect(ui->likePost1, &QPushButton::clicked, this, &SocialNetworkMainWindow::toggleLikes);
    connect(ui->likePost2, &QPushButton::clicked, this, &SocialNetworkMainWindow::toggleLikes);
    connect(ui->likePost3, &QPushButton::clicked, this, &SocialNetworkMainWindow::toggleLikes);
    connect(ui->likePost4, &QPushButton::clicked, this, &SocialNetworkMainWindow::toggleLikes);
    connect(ui->likePost5, &QPushButton::clicked, this, &SocialNetworkMainWindow::toggleLikes);

    // Login Page Button Connect
    connect(ui->loginButton, &QPushButton::clicked, this,
            &SocialNetworkMainWindow::onLoginClicked);

    // Adding post button
    connect(ui->submitNewPost, &QPushButton::clicked, this,
            &SocialNetworkMainWindow::addPostFunc);

    connect(ui->saveUserBio, &QPushButton::clicked, this, &SocialNetworkMainWindow::updateBios);

    socialNetwork.readUsers("users.txt");
    socialNetwork.readPosts("posts.txt");
    socialNetwork.readBios("bios.txt");

    // Set up Combo Box
    ui->privacyLevelBox->clear();
    ui->privacyLevelBox->addItem("PUBLIC");
    ui->privacyLevelBox->addItem("FRIENDS");
    ui->privacyLevelBox->addItem("PRIVATE");

    ui->privacyLevelBox->setCurrentIndex(0);

    // Set up Bio Combo Box
    ui->bioComboBox->addItem("Public");
    ui->bioComboBox->addItem("Friends");
    ui->privacyLevelBox->setCurrentIndex(0);

    applyUI();
}

/*This function essentially saves user data an posts.
 Is called when user friends are updated, or posts are added
 */
void SocialNetworkMainWindow::saveUsersAndFiles()
{
    socialNetwork.writeUsers("users.txt");
    socialNetwork.writePosts("posts.txt");
    socialNetwork.writeBios("bios.txt");
}

/* Takes user from login page to their profile
 provided they wrote their name correctly
 */
void SocialNetworkMainWindow::onLoginClicked()
{
    QString name = ui->usernameEntry->toPlainText();
    if (name.isEmpty())
    {
        ui->usernameEntry->setText("No Username Typed. Please Enter a valid Username");
    }

    int userId = socialNetwork.getId(name.toStdString());
    // int userId = 1;

    if (userId == -1)
    {
        ui->usernameEntry->setText("Not a Valid Username. Please enter it again");
    }
    else
    {
        currentLoggedInUser = socialNetwork.getUser(userId);
        currentUserProfile = currentLoggedInUser;
        currPage = "Profile";
        display();
    }
}

/*
 Button takes user back to the profile oth elogged in user
 */

void SocialNetworkMainWindow::backToProfile()
{
    currPage = "Profile";
    currentUserProfile = currentLoggedInUser;
    display();
}

/*
Populates the friends table with the current user profile friends
*/
void SocialNetworkMainWindow::displayFriends()
{

    ui->friendsList->setColumnCount(1);
    ui->friendsList->clearContents();

    auto friendsList = currentUserProfile->getFriends();
    ui->friendsList->clearContents();
    ui->friendsList->setRowCount(friendsList.size());

    int rowNumber = 0;
    for (int id : friendsList)
    {
        if (id != currentUserProfile->getId())
        {
            std::string name = socialNetwork.getUser(id)->getName();
            QString qname = QString::fromStdString(name);

            QTableWidgetItem *item = new QTableWidgetItem(qname);

            item->setData(Qt::UserRole, id);
            ui->friendsList->setItem(rowNumber, 0, item);
            rowNumber++;
        }
    }
}

/*
Populates the logged in user table with friends that are suggested
*/

void SocialNetworkMainWindow::displaySuggestedFriends()
{
    ui->suggestedFriends->setColumnCount(1);
    ui->suggestedFriends->clear();

    int score = -1;
    auto sugFrndList = socialNetwork.suggestFriends(currentLoggedInUser->getId(), score);

    ui->suggestedFriends->setRowCount(sugFrndList.size());
    int rowNumber = 0;
    for (int id : sugFrndList)
    {
        std::string name = socialNetwork.getUser(id)->getName();
        QString qname = QString::fromStdString(name);

        QTableWidgetItem *item = new QTableWidgetItem(qname);

        item->setData(Qt::UserRole, id);
        ui->suggestedFriends->setItem(rowNumber, 0, item);
        rowNumber++;
    }
}

/*
Gets all the posts that the current user profile being display has on their profile
*/

void SocialNetworkMainWindow::displayPosts()
{
    int labelNumber = 1;

    ui->Post1->clear();
    ui->Post2->clear();
    ui->Post3->clear();
    ui->Post4->clear();
    ui->label_5->clear();

    std::vector<QLabel *> labelList = {ui->Post1, ui->Post2, ui->Post3, ui->Post4, ui->label_5};

    auto userPosts = socialNetwork.getPosts(currentUserProfile->getId());

    int numOfPosts = 0;

    // Id of profile we are currently viewing
    int viewId = currentUserProfile->getId();

    // Id of the user who is logged in
    int ownId = currentLoggedInUser->getId();

    for (int i = userPosts.size() - 1; i >= 0 && numOfPosts < 5; i--)
    {
        Post *temp = userPosts[i];

        std::string postPriv = temp->getPrivacy();

        std::string tempStr = "";

        for (char c : postPriv)
        {
            if (c != ' ')
            {
                tempStr += c;
            }
        }

        postPriv = tempStr;

        if (postPriv[0] == '\t')
        {
            postPriv.erase(0, 1);
        }

        // Bool that checks whether the current post is viewable by them(in accordance to privacy)
        bool viewerCanSee = false;

        bool eq = (postPriv == "PUBLIC");

        // Author id of current post we are viewing
        int authId = temp->getAuthorId();

        // Current profile that the post is on
        int profileId = temp->getProfileId();

        // If its public, anyone can see
        if (postPriv == "PUBLIC")
        {
            viewerCanSee = true;
        }

        // Only let person see if the post profile id and the owner are the same, or if the authorid is the same
        else if (postPriv == "PRIVATE")
        {

            // Viewer can only see if they are the owner of the profile, or they are teh author of the post
            viewerCanSee = (ownId == profileId) || (ownId == authId);
        }
        else if (postPriv == "FRIENDS")
        {
            User *own = socialNetwork.getUser(ownId);

            // Check if viewer is same as profile owner or profile owner is same as author or if viewer id is from of owner
            if (viewId == ownId || ownId == authId || own->isFriend(viewId))
            {
                viewerCanSee = true;
            }
        }

        if (viewerCanSee)
        {
            currPosts[numOfPosts] = temp;
            QString str = QString::fromStdString(socialNetwork.postDisplayString(temp));
            labelList[numOfPosts]->setText(str);
            numOfPosts++;
        }
    }
}

/*
Lets users add posts and updates the top 5 posts to show the one they entered
*/

void SocialNetworkMainWindow::addPostFunc()
{
    QString post = ui->addPost->toPlainText();

    if (messageFilter.filterMessage(post) == false)
    {
        ui->addPost->setPlainText("We detected innaprorpate content in your post. Modify it before submitting.");
        return;
    }

    std::string postStr = post.toStdString();

    QString privacyQtStr = ui->privacyLevelBox->currentText();
    std::string postPrivacy = privacyQtStr.toStdString();

    Post *newPost = new Post(currentUserProfile->getId(), currentLoggedInUser->getId(), postStr, 0, {}, postPrivacy);
    socialNetwork.addPost(newPost);

    ui->addPost->clear();
    displayPosts();

    saveUsersAndFiles();
}

/*
 Navigates to and displays another users profile when they are clicked on
*/
void SocialNetworkMainWindow::navigateOtherUser(QTableWidgetItem *item)
{
    QString user = item->text();

    // Gets the clicked user profile
    currentUserProfile = socialNetwork.getUser(socialNetwork.getId(user.toStdString()));

    currPage = "OtherUser";
    display();
};

/*
 Function simply adds a selected user as a friend
*/
void SocialNetworkMainWindow::addFriendButton()
{
    if (!currentLoggedInUser->isFriend(currentUserProfile->getId()))
    {
        socialNetwork.addConnection(currentLoggedInUser->getName(), currentUserProfile->getName());
    }
    saveUsersAndFiles();
    display();
}

void SocialNetworkMainWindow::toggleLikes()
{
    // Since all 5 like buttons use this function as slot, need to know which button triggered(which post)
    QObject *origButton = sender();

    if (origButton == ui->likePost1)
    {
        Post *p = currPosts[0];
        if (p != nullptr)
        {
            p->addLike(currentLoggedInUser->getId());
            saveUsersAndFiles();
            displayPosts();
        }
    }
    else if (origButton == ui->likePost2)
    {
        Post *p = currPosts[1];
        if (p != nullptr)
        {
            p->addLike(currentLoggedInUser->getId());
            saveUsersAndFiles();
            displayPosts();
        }
    }
    else if (origButton == ui->likePost3)
    {
        Post *p = currPosts[2];
        if (p != nullptr)
        {
            p->addLike(currentLoggedInUser->getId());
            saveUsersAndFiles();
            displayPosts();
        }
    }
    else if (origButton == ui->likePost4)
    {
        Post *p = currPosts[3];
        if (p != nullptr)
        {
            p->addLike(currentLoggedInUser->getId());
            saveUsersAndFiles();
            displayPosts();
        }
    }
    else if (origButton == ui->likePost5)
    {
        Post *p = currPosts[4];
        if (p != nullptr)
        {
            p->addLike(currentLoggedInUser->getId());
            saveUsersAndFiles();
            displayPosts();
        }
    }
}

void SocialNetworkMainWindow::updateBios()
{
    QString qBio = ui->userBio->toPlainText();
    std::string newBio = qBio.toStdString();

    if (messageFilter.filterMessage(qBio) == false)
    {
        ui->userBio->setPlainText("We detected innaprorpate content in your bio. Modify it before submitting.");
        return;
    }

    std::string privacy = ui->bioComboBox->currentText().toStdString();

    auto t = socialNetwork.getBios();
    Bio *temp = t[currentUserProfile->getId()];

    if (privacy == "Public")
    {
        temp->setPublicBio(newBio);
    }
    else if (privacy == "Friends")
    {
        temp->setFriendsBio(newBio);
    }

    saveUsersAndFiles();
    displayBios();
    display();
}


void SocialNetworkMainWindow::displayBios()
{
    int viewerId = currentLoggedInUser->getId();
    int profileId = currentUserProfile->getId();

    std::string bioStr = socialNetwork.getVisibleBio(viewerId, profileId);

    auto bios = socialNetwork.getBios();

    for (int i = 0; i < bios.size(); i++)
    {
        Bio *b = bios[i];
    }

    ui->userBio->setPlainText(QString::fromStdString(bioStr));

    ui->userBio->setReadOnly(viewerId != profileId);
    ui->userBio->setEnabled(true);
}

/* Function controls everything in temrs of display. Based on what type of page is shown, the
 display function hides/shows different widgets
 */
void SocialNetworkMainWindow::display()
{
    if (currPage == "Profile")
    {
        QString text = "My Profile";

        ui->pushButton->hide();
        ui->usernameEntry->hide();
        ui->loginButton->hide();
        ui->loginPageLabel->setText(text);

        ui->friendsList->show();

        ui->Post1->show();
        ui->Post2->show();
        ui->Post3->show();
        ui->Post4->show();
        ui->label_5->show();

        // For Adding Post
        ui->addPost->show();
        ui->submitNewPost->show();

        // Suggest Friends
        ui->suggestedFriends->show();

        displayFriends();
        displayPosts();
        displaySuggestedFriends();
        displayBios();

        ui->AddFriend->hide();

        ui->privacyLevelBox->show();

        ui->userBio->show();

        ui->bioComboBox->show();
        ui->saveUserBio->show();

        ui->likePost1->show();
        ui->likePost2->show();
        ui->likePost3->show();
        ui->likePost4->show();
        ui->likePost5->show();

        ui->FriendsLabel->show();
        ui->SuggestedFriendsLabel->show();

        ui->backToLoginButton->show();
    }
    else if (currPage == "Login")
    {
        ui->pushButton->hide();
        ui->AddFriend->hide();
        ui->friendsList->hide();
        ui->Post1->hide();
        ui->Post2->hide();
        ui->Post3->hide();
        ui->Post4->hide();
        ui->label_5->hide();

        ui->addPost->hide();
        ui->submitNewPost->hide();

        ui->privacyLevelBox->hide();

        ui->bioComboBox->hide();
        ui->saveUserBio->hide();

        // Suggest Friends
        ui->suggestedFriends->hide();

        ui->userBio->hide();
        ui->saveUserBio->hide();

        ui->likePost1->hide();
        ui->likePost2->hide();
        ui->likePost3->hide();
        ui->likePost4->hide();
        ui->likePost5->hide();

        ui->FriendsLabel->hide();
        ui->SuggestedFriendsLabel->hide();

        ui->backToLoginButton->hide();

        ui->usernameEntry->show();
        ui->loginButton->show();
        ui->loginPageLabel->show();
    }
    else if (currPage == "OtherUser")
    {
        ui->pushButton->show();
        ui->suggestedFriends->hide();
        // QString otherUser = currentUserProfile->getName();
        displayFriends();
        displayPosts();
        displaySuggestedFriends();
        displayBios();

        QString name = QString::fromStdString(currentUserProfile->getName());
        QString text = name + "'s Profile";
        ui->loginPageLabel->setText(text);
        ui->AddFriend->show();

        // ui->privacyLevelBox->show();

        ui->userBio->show();

        ui->bioComboBox->show();
        ui->saveUserBio->hide();

        ui->likePost1->show();
        ui->likePost2->show();
        ui->likePost3->show();
        ui->likePost4->show();
        ui->likePost5->show();

        ui->FriendsLabel->show();

        ui->backToLoginButton->hide();
    }
}

void SocialNetworkMainWindow::applyUI()
{
    // Part to style login page
    ui->loginButton->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );

    // Login Page Stuff is here

    // Title font
    QFont titleFont = ui->loginPageLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    ui->loginPageLabel->setFont(titleFont);

    titleFont = ui->FriendsLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    ui->FriendsLabel->setFont(titleFont);

    titleFont = ui->SuggestedFriendsLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    ui->SuggestedFriendsLabel->setFont(titleFont);


    //Following functiosn are to set colos and styles for all UI components in the social network
    ui->centralwidget->setStyleSheet(
        "background-color: #0E0014"
    );

    ui->usernameEntry->setStyleSheet(
        "border: 2px solid orange;"
        "background-color: #32273f;"
        "border-radius: 10px;"
        "color: white;"
    );

    ui->friendsList->setStyleSheet(
        "background-color: #32273f;"
        "border: 2px solid orange;"
        "border-radius: 5px;"
        "color: white;"
    );

    ui->userBio->setStyleSheet(
        "background-color: #32273f;"
        "border: 2px solid orange;"
        "border-radius: 5px;"
        "color: white;"
    );

    ui->addPost->setStyleSheet(
        "background-color: #32273f;"
        "border: 2px solid orange;"
        "border-radius: 5px;"
        "color: white;"
    );

    ui->submitNewPost->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );

    ui->saveUserBio->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );

    ui->AddFriend->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );

    ui->saveUserBio->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );

    ui->pushButton->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );

    //Deal with all table stuff here
    ui->friendsList->horizontalHeader()->setVisible(false);

    ui->friendsList->setStyleSheet(
        "QTableWidget::item:selected {"
        "background-color: #662D01;"
        "color: gray;"
        "}"

        "QTableWidget {"
        "gridline-color: transparent;"
        "background-color: #32273f;"
        "border: 2px solid orange;"
        "border-radius: 5px;"
        "color: white;"
        "}"

        "QTableWidget::verticalHeader {"
            "background-color: orange;"
            "color: gray;"
        "}"

    );


    ui->backToLoginButton->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );

    ui->suggestedFriends->horizontalHeader()->setVisible(false);
    
    ui->suggestedFriends->setStyleSheet(
        "QTableWidget::item:selected {"
        "background-color: #662D01;"
        "color: gray;"
        "}"

        "QTableWidget {"
        "gridline-color: transparent;"
        "background-color: #32273f;"
        "border: 2px solid orange;"
        "border-radius: 5px;"
        "color: white;"
        "}"

        "QTableWidget::verticalHeader {"
            "background-color: orange;"
            "color: gray;"
        "}"
    );

    ui->privacyLevelBox->setStyleSheet(
        "QComboBox {"
        "background-color: #2772ff;"
        "color: white;"
        "border: 2px solid orange;"
        "border-radius: 5px;"
        "padding: 4px 8px;"
        "}"

        "QComboBox QAbstractItemView {"
        "background-color: #003fb5;"
        "color: white;"
        "selection-background-color: #662D01;"
        "border: 1px solid orange;"
        "border-radius: 5px;"
        "border-color: orange;"
        "}"
    );

    ui->bioComboBox->setStyleSheet(
        "QComboBox {"
        "background-color: #2772ff;"
        "color: white;"
        "border: 2px solid orange;"
        "border-radius: 5px;"
        "padding: 4px 8px;"
        "}"

        "QComboBox QAbstractItemView {"
        "background-color: #003fb5;"
        "color: white;"
        "selection-background-color: #662D01;"
        "border: 1px solid orange;"
        "border-radius: 5px;"
        "border-color: orange;"
        "}"
    );

    ui->likePost1->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );
    ui->likePost2->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );
    ui->likePost3->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );
    ui->likePost4->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );
    ui->likePost5->setStyleSheet(
        "color: white;"
        "background-color: orange;"
        "selection-background-color: #662D01;"
        "border-radius: 5px;"
    );

    ui->usernameEntry->setCursorWidth(1);
    ui->userBio->setCursorWidth(1);
}

void SocialNetworkMainWindow::backToLogin()
{
    currPage = "Login";
    currentLoggedInUser = nullptr;
    currentUserProfile = nullptr;
    display();
}

SocialNetworkMainWindow::~SocialNetworkMainWindow()
{
    delete ui;
}

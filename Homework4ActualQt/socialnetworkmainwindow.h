#ifndef SOCIALNETWORKMAINWINDOW_H
#define SOCIALNETWORKMAINWINDOW_H

#include <QMainWindow>
#include "network.h"
#include "user.h"
#include "messageFilter.h"
#include "post.h"
#include <QTableWidget>
#include <vector>

//DO I NEED
QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkMainWindow;
}
QT_END_NAMESPACE

class SocialNetworkMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkMainWindow(QWidget *parent = nullptr);
    ~SocialNetworkMainWindow();


    //Functions on Login Page

    //PRE:  Username in the login field must not be empty
    //POST: If login username is valid, sets currentLoggedInUser and displays the profile
    void onLoginClicked();

    //Functions on Profile Page

    //PRE: CurrentUserProfile cannot be nullptr and there must be a friends list in the network
    //POST: The table is filled in with all the currentUsers friends
    void displayFriends();

    //PRE:Make sure that the currentUserProfile is not nullptr
    /*POST: Posts section has all the user posts, and 5 most recent posts are displayed, and
    if posts are updated, it will add that to the most recent */
    void displayPosts();

    //Function for add new post
    //PRE: The text box for addign posts should not be empty
    //POST: A new post is added to the user current posts and displayed on their profile
    void addPostFunc();

    //Suggest Friends
    //PRE: SOcial network must be initialized and the score value must be set to -1
    //POST: Suggest friend table is now populated with all the suggested friends
    void displaySuggestedFriends();

    //When Table Item Clicked
    //PRE: Clicked table needs to have a valid user and a valid user id
    //POST: The currentUserProfile is updated to the user that has been selected, and loads up their profile
    void navigateOtherUser(QTableWidgetItem *item);

    //PRE: function to display bio of user profile
    //POST: Display bio of current user based on viewer permissions
    void displayBios();

    //PRE: Bio text box should not be empty
    //POST: updates bio of current user profile using the test given
    void updateBios();

    //PRE: None
    //POST: Toggles likes on posts when like button is clicked
    void toggleLikes();

    //PRE: The current logged in user cannot be nullptr
    //POST: Displays the logged in user's profile
    void backToProfile();

    //PRE: None
    //POST: Returns to the login page from any other page
    void backToLogin();

    //PRE: The logged in user and the current user profile are not already friends
    //POST: Two users are now friends, and the UI updates them as friends for both profiles
    void addFriendButton();

    //Functions Concerning All Pages

    //PRE: currPage must be set to a valid string, either "Login "Profile" or "OtherUser"
    //POST: Shows the only the .ui widgets of current page
    void display();

    //Add Users and posts to file

    //PRE: Social network must have a output file that it writes to
    //POST: All users and posts are written to output files for storage
    void saveUsersAndFiles();

    //PRE: None
    //POST: Applies all UI settings in the beggining of th eprogram
    void applyUI();


private:
    Ui::SocialNetworkMainWindow *ui; //Main ui page
    Network socialNetwork; //Social network that has been instantiated

    User* currentLoggedInUser = nullptr; //Current LoggedInUser(user on the login page)
    User* currentUserProfile = nullptr; //Current User Profile(who the user is viewing)

    std::string currPage; //String indivated which page they are on currently

    MessageFilter messageFilter; // Message filter for filtering posts

    //Array stores the current 5 displayed posts
    std::vector<Post*> currPosts = std::vector<Post*>(5, nullptr);
};
#endif // SOCIALNETWORKMAINWINDOW_H

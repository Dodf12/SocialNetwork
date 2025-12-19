#ifndef NETWORK_H
#define NETWORK_H


#include "user.h"
#include "post.h"
#include "bio.h"
#include <vector>
#include <string>


class Network
{
  public:
    //Constructors

    //Default constructor
    Network() {};


    //GETTERS

    //OVERVIEW: Takes in user id and returns a pointer to the dynamically allocated user
    /* DESCRIPTION:
    Takes the id, and loops through the vector of user pointers.
    Retrievs the id of the user using the getId() function of the
    User class, and compares with parameter. 
    Returns user if found, otherwise returns nullptr.
    */
    User* getUser(int id);

    //OVERVIEW: Returns id of the user based on name provided
    /*DESCRIPTION:
    Lops through the vector of the users, retrieves name of current
    user, and compares
    with name provided(the parameter). If found, it returns the
    user id. If not found, it returns -1
    */
    int getId(std::string name);

    //Returns the total number of users in the network
    int numUsers() const { return users_.size(); }  

    std::vector<Bio*> getBios(){ return bios_; }

    //FUNCTIONS


    //Adds a new user to the network
    void addUser(User* user);

    //OVERVIEW:Adds a friend connection between two users by taking both their names
    /*DESCRIPTION
    Function takes two strings as parameters, which are names of user.
    First checks if both users exist, and if not, returns -1;
    Takes the names of both users, and then retrieves their ids.
    Checks to make sure ids are valid, and if not, returns -1.
    Then, uses id's to both the user objects and uses
    addFriend() function to add each other as friends.
    */
    int addConnection(std::string s1, std::string s2);

    //OVERVIEW:Removes a friend connection between two users by taking both their names
    /*DESCRIPTION
    Function takes two strings as parameters, which are names of user.
    First checks if both users exist, and if not, returns -1;
    Takes the names of both users, and then retrieves their ids.
    Checks to make sure ids are valid, and if not, returns -1.
    Then, uses id's to both the user objects and uses
    deleteFriend() function to remove each other as friends.
    */
    int deleteConnection(std::string s1, std::string s2);

    //FILE IO


    //OVERVIEW: Reads in users from a file that are stored in a specific format
    /*DESCRIPTION:
    Reads in a file that is formatted in this manner.
    2
    0
      John Doe
      1990
      95050
      1
    1
      Abhi Pala
      1999
      95051
      0

    The very first line is the number of users in the file. 
    Then, for each user, there are 5 liens that correspond.
    First line is the id of the user.
    Second line is the name of the users.
    Third line is the birth year of the user.
    Fourth line is the zip code of the user.
    Fifth line is the list of friend id's of the user, separated by spaces.

    THe function reads teh file by line and retrieves each value, and stores it 
    in temporary variables. After reading in all 5 user inputs, a new user
    object is dynamically created and added to the network.
    */
    void readUsers(const char* fname);
    
    //OVERVIEW: Takes in an outuput file and write all users in the network into the file
    /*DESCRIPTION: Loops through all the users in the network, and for each user,
    writes the information to the file in the same format as describe in the readUsers function.
    The very first line is number of users.
    For each user, 5 lines are written for id, year, zip, and friends.
    The friends set is looped through and each id is writtend, seperate by a space.
    */
    void writeUsers(const char* fname);


    //GRAPHS

    //PRE: Index from starting place and index of ending place
    /*POST: Returns a vector of user ids that is the shortest path from start to end. IT returns all intermediate nodes as well.
    If no path exists, it return an empty array.*/
    std::vector<int> shortestPath(int from, int to);

    //PRE: Index of from variable, which is empty and is update when the function runs and index of ending place. Also requires the length of the path
    /*POST: Returns the shortest path to that user stipulated by the distance/length of path provided. If
    no path exists with that distance, it returns an empty array and sets the to variable to -1.*/
    std::vector<int> distanceUser(int from, int& to, int distance);

    /*PRE: Index of the user to suggest friends for and a refernece to an int variable score, 
    which is to calculate the score of those who have most mutual friends with the user,
    but are not friends with the user*/
    /*POST: Returns a vector of user ids that are suggested friends for the user. They are
    friends who have the most mutual friends with the user*/
    std::vector<int> suggestFriends(int who, int& score);

    /*PRE: None*/
    /*POST: Returns a vector of groups, where each member in a group is friends with all the other members in a group.*/
    std::vector< std::vector<int> > groups();


    //POST FUNCTIONS

    //PRE: Function that takes in pointer a Post Object and adds it to the Post Vector of Network
    //POST: Does not reurn anything, but adds the post to network
    void addPost(Post* post);

    //PRE: Function takes in user id and returns a vector of Post pointers corresponding to posts
    //POST: Returns a vector of Post Pointers 
    std::vector<Post*> getPosts(int id);

    //PRE: Function takes a Post pointer and returns a nice formatted string representatino of the post
    //POST: THis returns a string representation of thsi specific post
    std::string postDisplayString(Post* post);

    //PRE: need profile id of a user and number of posts to retrieve
    //POST: Returns a string having the most recent 'howMany' posts for the user
    std::string getPostsString(int profileId, int howMany);


    //FILE IO FOR POSTS

    //PRE: File name to read posts
    //POST: Returns 0 if successful, and -1 if fails to open file
    int readPosts(char* fname);

    //PRE: It is a file name for output file
    //POST: REtunrs a number 0 if successful, and -1 if the file fails to open
    int writePosts(char* fname);


    //FIL IO FOR BIO

    int readBios(char* fname);

    int writeBios(char* fname);


    //FOR USER BIO
    std::string getVisibleBio(int viewerId, int profileId);
  private:
  //User attributes
  //Vector containing pointers to dynamically allocating user objects
    std::vector<User*> users_;

    //Private Helper function for DFS traversal
    void DFS_Helper(std::vector<bool>& visited, User* user, std::vector<int>& ans);

    //Array where post attributes are stored
    std::vector<std::vector<Post*> > posts_;

    //Array where bios are stored
    std::vector<Bio*> bios_;

};

#endif

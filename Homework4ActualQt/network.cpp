#include "network.h"
#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>
#include <algorithm>

//Helper function that compares two Post pointers based on their message ids
bool postComparePost(Post *p1, Post *p2)
{
    return p1->getMessageId() < p2->getMessageId();
}

// OVERVIEW: Takes in user id and returns a pointer to the dynamically allocated user
/* DESCRIPTION:
Takes the id, and loops through the vector of user pointers.
Retrievs the id of the user using the getId() function of the
User class, and compares with parameter.
Returns user if found, otherwise returns nullptr.
*/
User *Network::getUser(int id)
{
  /*Loops through all users in the network and if finds one
  with matching id, returns it.*/
  for (auto u : users_)
  {
    if (u->getId() == id)
    {
      return u;
    }
  }

  return nullptr;
}

// OVERVIEW: Returns id of the user based on name provided
/*DESCRIPTION:
Lops through the vector of the users, retrieves name of current
user, and compares
with name provided(the parameter). If found, it returns the
user id. If not found, it returns -1
*/
int Network::getId(std::string name)
{
  /*Loops through all users, and if find matching name,
  returns their id.*/
  for (auto u : users_)
  {
    if (u->getName() == name)
    {
      return u->getId();
    }
  }

  return -1;
}

// OVERVIEW:Adds a friend connection between two users by taking both their names
/*DESCRIPTION
Function takes two strings as parameters, which are names of user.
First checks if both users exist, and if not, returns -1;
Takes the names of both users, and then retrieves their ids.
Checks to make sure ids are valid, and if not, returns -1.
Then, uses id's to both the user objects and uses
addFriend() function to add each other as friends.
*/

int Network::addConnection(std::string s1, std::string s2)
{
  // Checks if both users dont exist, and if so, returns -1
  if (getId(s1) == -1 || getId(s2) == -1)
  {
    return -1;
  }

  // Storing ids in temp variable
  int id1 = getId(s1);
  int id2 = getId(s2);

  // checks if either user pointer is null, and if so, returns -1
  if (getUser(id1) == nullptr || getUser(id2) == nullptr)
  {
    return -1;
  }

  // Retrieves the users
  User *u1 = getUser(id1);
  User *u2 = getUser(id2);

  // Adds each other as friends
  u2->addFriend(id1);
  u1->addFriend(id2);

  return 0;
}

// OVERVIEW:Removes a friend connection between two users by taking both their names
/*DESCRIPTION
Function takes two strings as parameters, which are names of user.
First checks if both users exist, and if not, returns -1;
Takes the names of both users, and then retrieves their ids.
Checks to make sure ids are valid, and if not, returns -1.
Then, uses id's to both the user objects and uses
deleteFriend() function to remove each other as friends.
*/
// NOTE: Same code as addConnection, except uses deleteFriend instead of addFriend
int Network::deleteConnection(std::string s1, std::string s2)
{
  if (getId(s1) == -1 || getId(s2) == -1)
  {
    return -1;
  }

  // Storing ids in temp variable
  int id1 = getId(s1);
  int id2 = getId(s2);

  // checks if either user pointer is null, and if so, returns -1
  if (getUser(id1) == nullptr || getUser(id2) == nullptr)
  {
    return -1;
  }

  // Retrieves the users
  User *u1 = getUser(id1);
  User *u2 = getUser(id2);

  // Delete each other as friends
  u2->deleteFriend(id1);
  u1->deleteFriend(id2);

  return 0;
}

void Network::addUser(User *user)
{
  users_.push_back(user);
  
  if (user ->getId() >= posts_.size())
  {
    posts_.resize(user -> getId() + 1);
  }
}

// OVERVIEW: Reads in users from a file that are stored in a specific format
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

void Network::readUsers(const char *fname)
{

  // Creat input file stream obj and open file
  std::ifstream input;
  input.open(fname);

  // CHecks to make sure that file is opened correctly
  if (!input.is_open())
  {
    std::cerr << "Fail to open file" << std::endl;
  }

  /*Following 3 lines read in the very first line of files, which is an int of number of users
  and stores it in numOfUsers variable*/
  std::string temp;
  getline(input, temp);

  int numOfUsers = std::stoi(temp);

  // Variable that stores every line read in from teh file temporarily before extracting values
  std::string line;

  /*Following 5 variables are temporary variables to store teh 5 different user attributes
  before creating a new user obj*/
  int id;
  std::string name;
  int year;
  int zip;
  std::set<int> friends;

  // Loops same number of times as number of users in file
  for (int i = 0; i < numOfUsers; i++)
  {
    // Reads in each line and stores in the temp variables, and later creates the user input
    getline(input, line);
    id = std::stoi(line); // Getting user id

    getline(input, name);
    name = name.substr(1); // Getting the user name, and removing white space at start

    getline(input, line);
    year = std::stoi(line); // Getting user birth year

    getline(input, line);
    zip = std::stoi(line); // Getting user zip code

    // Following 5 lines(of code) are for getting the set of friend ids
    getline(input, line);
    friends.clear(); // Clears the set of friends before adding current users friends

    std::stringstream temp(line); // create a string stream with extracted line so that its easier to extract values
    int friendID;

    while (temp >> friendID)
    {
      friends.insert(friendID);
    } 

    // Creates a new user objecct dynamically and adds to the network
    addUser(new User(id, name, year, zip, friends));
  }
}

// OVERVIEW: Takes in an outuput file and write all users in the network into the file
/*DESCRIPTION: Loops through all the users in the network, and for each user,
writes the information to the file in the same format as describe in the readUsers function.
The very first line is number of users.
For each user, 5 lines are written for id, year, zip, and friends.
The friends set is looped through and each id is writtend, seperate by a space.
*/
void Network::writeUsers(const char *fname)
{
  // Creates output file stream obj and opens file
  std::ofstream output;
  output.open(fname);

  if (!output.is_open())
  {
    std::cerr << "Fail to open file" << std::endl;
  }

  // First adds number of users in the network
  output << users_.size() << std::endl;

  // Loops through all users and writes their info to the file
  for (auto u : users_)
  {
    // The \t and \n are to maintaing the same proper formatting as described in readUsers function
    output << u->getId() << "\n";
    output << "\t" << u->getName() << "\n";
    output << "\t" << u->getYear() << "\n";
    output << "\t" << u->getZip() << "\n";
    output << "\t"; // First tabbing space before friends are written down
    for (auto num : u->getFriends())
    {
      output << num << " ";
    }
    output << "\n";
  }
}

// PRE: Index from starting place and index of ending place
/*POST: Returns a vector of user ids that is the shortest path from start to end. IT returns all intermediate nodes as well.
 If no path exists, it return an empty array.*/
std::vector<int> Network::shortestPath(int from, int to)
{

  // Standard BFS/shortest path algorithm
  std::queue<int> nextNodes;                       // The queue to do BFS
  std::vector<bool> visited(users_.size(), false); // Track nodes that have been visited

  std::vector<int> previous(users_.size(), -1); // Seeing closest node

  previous[from] = -1;

  nextNodes.push(from);
  visited[from] = true;

  // Standard BFS while loop
  while (!nextNodes.empty())
  {
    int currUserId = nextNodes.front();
    nextNodes.pop();
    for (int friendsId : getUser(currUserId)->getFriends())
    {
      if (!visited[friendsId])
      {
        visited[friendsId] = true;
        nextNodes.push(friendsId);
        previous[friendsId] = currUserId;
      }
    }
  }

  // vector to stor answer
  std::vector<int> ans;

  // If the to node was never visited, because the graph is not fully connected, then returns an empty vector
  if (!visited[to])
  {
    return ans;
  }

  ans.push_back(to);

  // Backtracks from the node to the first node
  int prevNode = previous[to];
  while (prevNode != -1)
  {
    ans.push_back(prevNode);
    prevNode = previous[prevNode];
  }

  // Reverse and returns in vector
  std::reverse(ans.begin(), ans.end());

  return ans;
}

// PRE: Index of from variable, which is empty and is update when the function runs and index of ending place. Also requires the length of the path
/*POST: Returns the shortest path to that user stipulated by the distance/length of path provided. If
no path exists with that distance, it returns an empty array and sets the to variable to -1.*/
std::vector<int> Network::distanceUser(int from, int &to, int distance)
{
  for (auto &user : users_)
  {
    std::vector<int> path = shortestPath(from, user->getId()); // Call shortest path function to get path from each user to find one with correct distance

    // Sets to to user id and returns path if it matches the distance
    if (path.size() == distance + 1)
    {
      to = user->getId();
      return path;
    }
  }

  // if no user found with that distance, returns empty array and sets variable to -1
  to = -1;
  std::vector<int> empty;
  return empty;
}

/*PRE: Index of the user to suggest friends for and a refernece to an int variable score,
which is to calculate the score of those who have most mutual friends with the user,
but are not friends with the user*/
/*POST: Returns a vector of user ids that are suggested friends for the user. They are
friends who have the most mutual friends with the user*/
std::vector<int> Network::suggestFriends(int who, int &score)
{
  std::vector<int> ans;

  // Loop through all users
  for (auto &user : users_)
  {
    int temp = user->getId();

    // Make sure user is not suggest to themselves and not already a friend
    if (temp != who && shortestPath(who, temp).size() == 3)
    {
      int sum = 0; // Num of mutual friends
      for (int friendsId : user->getFriends())
      {
        // Finding mutual friends
        if (getUser(who)->isFriend(friendsId) && who != friendsId)
        {
          sum++;
        }
      }

      // If new max score found, it clears ans and add this and all other users with the same score
      if (sum > score)
      {
        ans.clear();
        ans.push_back(user->getId());
        score = sum;
      }

      else if (sum == score)
      {
        ans.push_back(user->getId());
      } // If same score, just add to ans
    }
  }

  // Make sure to set 0 if no suggested friends
  if (ans.size() == 0)
  {
    score = 0;
  }
  return ans;
}

/*PRE: None*/
/*POST: Returns a vector of groups, where each member in a group is friends with all the other members in a group.*/
std::vector< std::vector<int> > Network::groups()
{
  std::vector<bool> visited(users_.size(), false);

  std::vector< std::vector<int> > finalAns;

  // Run DFS for each unvisited node and count how many times DFS is done(number of groups)
  std::vector<int> ans;
  int count = 0;
  for (auto &user : users_)
  {
    // Does DFS if user not visited
    if (!visited[user->getId()])
    {
      ans.push_back(user->getId());
      count++; // Counts number of groups
      visited[user->getId()] = true;
      DFS_Helper(visited, user, ans);
    }

    // If group was found, adds to final ans
    if (count > 0)
    {
      finalAns.push_back(ans);
      ans.clear();
    }

    count = 0;
  }

  return finalAns;
}

// PRE:NONE
/*POST: Helper function for DFS traversal*/
void Network::DFS_Helper(std::vector<bool> &visited, User *user, std::vector<int> &ans)
{
  for (auto &id : user->getFriends())
  {
    if (!visited[id])
    {
      ans.push_back(id);
      visited[id] = true;
      DFS_Helper(visited, getUser(id), ans);
    }
  }
}

// POST FUNCTIONS

/* Function takes a poost object in,
finds the message id by counting total number of
posts in network before, and then adds post to the
posts_ array
*/
void Network::addPost(Post* post)
{
  int profileId = post -> getProfileId();

  int total = 0;
  for (auto& p : posts_)
  {
    total += p.size();
  }

  post -> setMessageId(total);
  posts_[profileId].push_back(post);
}

/*
Function takes in a user id and returns a vector of posts pointers,
which are posts for that user
*/
std::vector<Post*> Network::getPosts(int id)
{
  return posts_[id];
}

/*
Function takes in post pointer, and returns a nicely formatted string which
details the author name and what they wrote in their message
*/
std::string Network::postDisplayString(Post *post)
{
  std::string authorName = getUser(post->getAuthorId())->getName();
  std::string text = post->toString();
  return authorName + " wrote: " + text;
}

/*
Function gets the profileId, and how many posts to retrieve.
Loops through, makilng sure not to go out of bounds(if request
over the limit of posts, it stops them). It appends
each post's display string to the answer string.
*/
std::string Network::getPostsString(int profileId, int howMany)
{
  std::string ans = "";

  //Check to make sure that howMany is not more than total posts
  for (int i = posts_[profileId].size() - 1; i >= 0 && howMany > 0; i--)
  {
    ans += postDisplayString(posts_[profileId][i]) + "\n\n";
    howMany--;
  }

  return ans;
}

// FILE IO FOR POSTS

/*
Same function as readUsers, except for posts.
Follows same format and code, except creates Post or LinkPost objects
*/
int Network::readPosts(char *fname)
{
  // Create input file stream obj and open file
  std::ifstream input;
  input.open(fname);

  /*Following 3 lines read in the very first line of files, which is an int of number of users
and stores it in numOfUsers variable*/
  std::string temp;
  getline(input, temp);
  int numOfUsers = std::stoi(temp);

  // Variable that stores every line read in from teh file temporarily before extracting values
  std::string line;

  /*Following 5 variables are temporary variables to store teh 5 different user attributes
  before creating a new user obj*/
  int id;
  std::string message;
  int profileId;
  int authorId;
  int likes;
  std::set<int> likedBy;
  std::string privacy;
  std::string url;

  // Loops same number of times as number of users in file
  for (int i = 0; i < numOfUsers; i++)
  {
    // Reads in each line and stores in the temp variables, and later creates the user input
    getline(input, line);
    id = std::stoi(line); // Getting user id

    //Get User Message
    getline(input, message);
    message = message.substr(1);

    //Get Profile Id
    getline(input, line);
    profileId = std::stoi(line);

    //Get Author Id
    getline(input, line);
    authorId = std::stoi(line);

    //Get likes
    getline(input, line);
    int likes = std::stoi(line);

    //Get prviacy
    getline(input, privacy);
    privacy = privacy.substr(1);

    //Get likedBy array
    getline(input, line);
    likedBy.clear(); // Clears the set of friends before adding current users friends
    std::stringstream temp(line);
    int likedById;
    while (temp >> likedById)
    {
        likedBy.insert(likedById);
    }


    //Get url
    getline(input, url);



    //If url is blank, create Post object, else create LinkePost
    if (url == "")
    {
      addPost(new Post(profileId, authorId, message, likes, likedBy, privacy));
    }
    else
    {
      url = url.substr(1);
      addPost(new LinkPost(profileId, authorId, message, likes, url, likedBy, privacy));
    }
  }

  return 0;
}


/*
Function takes in a file name for the output file,
and basically first adds all posts in the network.
Then sorts the array based on message, and then
writes it to the file via the specified format
*/
/*NOTES: Uses a helper function which is not apart of the class. 
The helper function compares the message id's sicne cannot compare
Post pointers*/
int Network::writePosts(char *fname)
{
  std::map<int, Post*> postMap;
    // Creates output file stream obj and opens file
  std::ofstream output;
  output.open(fname);

  if (!output.is_open())
  {
    std::cerr << "Fail to open file" << std::endl;
  }


  std::vector<Post*> allPosts;

  int total = 0;
  for (auto postVec : posts_)
  {
    for (auto post : postVec)
    {
      allPosts.push_back(post);
      total++;
    }
  }

  std::sort(allPosts.begin(), allPosts.end(), postComparePost);

  // First adds number of posts in the network
  output << total << "\n";

  // Loops through all users and writes their info to the file
  for (auto u : allPosts)
  {
    // The \t and \n are to maintaing the same proper formatting as described in readUsers function
    output << u->getMessageId() << "\n";
    output << "\t" << u->getMessage() << "\n";
    output <<  "\t" << u->getProfileId() << "\n";
    output << "\t" << u->getAuthorId()<< "\n";
    output << "\t" << u->getLikes() << "\n";

    output << "\t" << u->getPrivacy() << "\n";

    for (int i : u->getLikedBy())
    {
      output << i << " ";
    }
    output << "\n";

    if (u->getURL() != "")
    {
      output << "\t" << u->getURL() << "\n";
    }
    else
    {
      output << "\n";
    }
  }

  return 0;
}

int Network::readBios(char* fname)
{
    std::ifstream fin(fname);


    int numOfBios;
    std::string temp;

    getline(fin, temp);

    numOfBios = stoi(temp);

    int id;
    std::string publicBio;
    std::string friendsBio;

    bios_.resize(numOfBios, nullptr);

    for(int i = 0; i < numOfBios; i++)
    {
        //Read in Id
        getline(fin, temp);
        id = stoi(temp);

        getline(fin, publicBio);

        getline(fin, friendsBio);

        bios_[id] = new Bio(friendsBio, publicBio);
    }
    return 0;
}

int Network::writeBios(char* fname)
{
    std::ofstream fout(fname);

    fout << bios_.size() << std::endl;

    for(int i = 0; i < bios_.size(); i++)
    {
        Bio* bioObj = bios_[i];
        fout << i << std::endl;
        fout << "\t" << bioObj -> getPublicBio() << std::endl;
        fout << "\t" << bioObj -> getFriendsBio() << std::endl;
    }

    fout.close();
    return 0;
}


std::string Network::getVisibleBio(int viewerId, int profileId)
{
    if(profileId < 0 || profileId >= bios_.size())
    {
        return "";
    }
    User *profileUser = getUser(profileId);

    if (viewerId == profileId || profileUser->isFriend(viewerId))
    {
        Bio* bioObj = bios_[profileId];
        return bioObj->getFriendsBio();
    }
    else
    {
        Bio* bioObj = bios_[profileId];
        return bioObj->getPublicBio();
    }
}


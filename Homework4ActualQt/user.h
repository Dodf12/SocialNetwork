#ifndef USER_H
#define USER_H

/*NOTE ABOUT MY FORMATTING:
I divde my code in .h files based on sectiosn like constructors, getters, functions etc.
Between each section, I leave two blank lines so that it's more readable.
*/

// Libraries I am using
#include <string>
#include <set>
#include <iostream> //For debugging
#include "bio.h"

/*
The user class is to reperesent a user in my social network.
The user has aattributes like name, id, year and their zip code in order to
have as many distinguishable traits as possible.
*/
class User
{
public:
  // CONSTRUCTORS(section title)

  // Default constructor
  User() {};

  // Constructor with parameters
  User(int id, std::string name, int year, int zip, std::set<int> friends) : id_(id), name_(name), year_(year), zip_(zip), friends(friends) {}

  // GETTERS

  // Get id by return id var
  int getId() const { return id_; }

  // Gets Name
  std::string getName() const { return name_; }

  // Gets Year
  int getYear() const { return year_; }

  // Gets Zip code
  int getZip() const { return zip_; }

  // Returns a REFERENCE to the set of friends
  std::set<int> &getFriends() { return friends; }

  // Get bio
  Bio getBio() { return bio_; }

  // FUNCTIONS

  // OVERVIEW: Add friend function(takes user id as parameter)
  /*DESCRIPTION:Adds id to the set of the user's friends*/
  void addFriend(int id);

  // OVERVIEW:Delete friend function(takes user id as parameter)
  /*DESCRIPTION:
  Removes id from the set of the user's friend ONLY IF IT EXISTS
  */
  void deleteFriend(int id);

  // Things I am adding

  int getFriendCount() const { return friends.size(); }

  // ASK DR. LI ABOUT THIS
  bool isFriend(int id) { return friends.count(id) == 1; }

private:
  // USER ATTRIBUTES

  // Unique identfying integer for id
  int id_;

  // First and last name of the user(all in one string)
  std::string name_;

  // Year user was born
  int year_;

  // Zip code of the user
  int zip_;

  // Set of friend IDs
  std::set<int> friends;

  // Things I have added for future updates(presently not implemented)

  // Lists whether user profile is private or not. If private, user cannot be added as a friend
  bool isPrivate_ = false;

  // User status message(not implement, and is for future updates)
  std::string status_;

  // User bio object
  Bio bio_;
};

#endif
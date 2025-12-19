#ifndef POST_H
#define POST_H

#include <string>
#include <set>

class Post
{
public:
  // Constructors

  // PRE: None
  /*POST: Default constructor for post object*/
  Post();

  /*PRE: profileId, authorId, message string, and number of likes.
  Creates a Post object, and profileId is the user
  WHO RECEIVES the post, while AuthorID is the one who makes
  the post. Message, string and lieks are standard*/
  /*POST: Returns nothing*/
  Post(int profileId, int authorId, std::string message, int likes, std::set<int> likedBy, std::string plevel);

  // SETTERS

  // PRE: integer for message id
  /*POST: Sets the message id to provided integer*/
  void setMessageId(int id) { messageId_ = id; }

  void setPrivacy(std::string &pLevel) { privacyLevel_ = pLevel; }

  // GETTERS

  // PRE: None
  /*POST: Returns the message id*/
  int getMessageId() { return messageId_; }

  // PRE: None
  /*POST: Returns the profile id*/
  int getProfileId() { return profileId_; }

  // PRE: None
  /*POST: Returns id of post writer/author*/
  int getAuthorId() { return authorId_; }

  // PRE: None
  /*POST: Returns the message string that the users types*/
  std::string getMessage() { return message_; }

  // PRE: Nane
  /*POST: Return number of likes */
  int getLikes() { return likes_; }

  //PRE: None
  /*POST: Returns the privacy level of the post*/
  std::string getPrivacy() {return privacyLevel_;}

  //PRE: None
  /*POST: returns set of user ids who have like the post*/
  std::set<int> getLikedBy() { return likedBy_; }


  //OTHER FUNCTIONS
  void addLike(int userId);

  // PRE: None
  /*POST: Returns URL string from the LinkPOST object(it is blank for the Post object)*/
  virtual std::string getURL() { return ""; }

  // PRE: None
  /*POST: REturns a string representation of the post, and is virtual, so adds link for LinkPost
  in this format:  ”[message_] ([likes_] likes)”*/
  virtual std::string toString();

  bool isLikedBy(int userId);
private:
  int messageId_;       // Unique identifier for message
  int profileId_;       // Id of user who Receives post
  int authorId_;        // Id of user who creats post
  std::string message_; // Content of post
  int likes_;           // Number of likes the post has

  // New thing
  std::string privacyLevel_;

  //Stores who liked the post
  std::set<int> likedBy_;
};

class LinkPost : public Post
{
public:
  // Constructors

  // PRE: None, is a default Constructor
  // POST: Creates a default LinkPost Object
  LinkPost();

  // PRE: Profile id, author id, the string message, number of likes, and URL string
  LinkPost(int profileId, int authorIds, std::string message, int likes, std::string url, std::set<int> likedBy,std::string plevel);

  // GETTERS

  // PRE: None
  /*POST: Returns the URL string from the object*/
  std::string getURL() { return url_; }

  // PRE: None
  /*POST: Returns the string representation of the LinkPost object formatted like this: ”[message_] (url: [url_]) ([likes_] likes)”*/
  std::string toString();

private:
  std::string url_;
};

#endif

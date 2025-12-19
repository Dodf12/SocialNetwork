#include "post.h"

/* Default Constructor initialized with all the basic values*/
Post::Post() : messageId_(-1), profileId_(0), authorId_(0), message_(""), likes_(0), likedBy_({}), privacyLevel_("Public") {}

/* Pramaterized constructor, and initailizes all values to what is specified,
except for message id*/
Post::Post(int profileId, int authorId, std::string message, int likes, std::set<int> likedBy, std::string plevel)
    : messageId_(-1), profileId_(profileId), authorId_(authorId), message_(message), likes_(likes), privacyLevel_(plevel) {}


    void Post::addLike(int userId)
    {
      if(likedBy_.count(userId) == 0)
      {
        likes_++;
        likedBy_.insert(userId);
      }
      else
      {
          likes_--;
          likedBy_.erase(userId);
      }
    }
/*
Function returns a neatly formatted string represnetaion of the Post OBject
*/
std::string Post::toString()
{
  return message_ + " " + "(" + std::to_string(likes_) + " likes)";
}

/* LinkPost class function definitions below, and calls Post Constructor*/
LinkPost::LinkPost() : Post(), url_("") {}

/*Calls post constructor and also initizalizes the URL*/
LinkPost::LinkPost(int profileId, int authorId, std::string message, int likes, std::string url, std::set<int> likedBy, std::string plevel)
    : Post(profileId, authorId, message, likes, likedBy, plevel), url_(url) {}

/*Function retruns neatly formatted string representation of the LinkPost object*/
std::string LinkPost::toString()
{
  return getMessage() + " (url: " + getURL() + ") (" + std::to_string(getLikes()) + " likes)";
}

bool Post::isLikedBy(int userId)
{
  return likedBy_.count(userId) > 0;
}

#ifndef BIO_H
#define BIO_H

#include <string>

class Bio
{
  private:
    std::string friendsBio_;
    std::string publicBio_;

  public:

    //Constructor
    Bio() : friendsBio_("This is the friends-only bio."), publicBio_("This is the public bio.") {}
    Bio(std::string friendsBio, std::string publicBio) : friendsBio_(friendsBio), publicBio_(publicBio) {}  

    
    //Setters
    void setFriendsBio(std::string bio) { friendsBio_ = bio; }
    void setPublicBio(std::string bio) { publicBio_ = bio; }

    //Getters
    std::string getFriendsBio() { return friendsBio_; }
    std::string getPublicBio() { return publicBio_; }


};

#endif


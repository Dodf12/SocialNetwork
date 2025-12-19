#include "user.h"
#include <iostream>

//OVERVIEW: Add friend function(takes user id as parameter)
/*
Adds id to the set of the user's friends
*/
void User::addFriend(int id)
{
	//Adds friend id to the set of friends
	friends.insert(id);
}


//OVERVIEW:Delete friend function(takes user id as parameter)
/*DESCRIPTION:
Removes id from the set of the user's friend ONLY IF IT EXISTS
*/
void User::deleteFriend(int id)
{
    //Checks how many people with that id are in the set, and it's 1, they are removed
	if(friends.count(id) == 1)
	{
		friends.erase(id);
	}
}

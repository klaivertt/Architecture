#include "Helper.h"
#include "Common.h"
#include "User.h"
#include "Media.h"

//-------------------------------------------------------------------------
int main()
{
	// Create initial stuff
	std::vector<User> users = std::vector<User>(5);
	srand(time(NULL));
	for (auto user : users)
	{
		//user.SetMedia(media);
		user.Print();
	}

	// Update loop
	while(true)
	{ 
		// Do update

		for (auto user : users)
		{

		}

		// Wait for user input
		system("pause");
	}
}
#include "Application.h"

int main() 
{
    CJ::Application application;
   
    if (application.Initialize("Creajeux Engine", sf::VideoMode(1280, 720), 60))
    {
        application.Run();
    }
    
    return 0;
}

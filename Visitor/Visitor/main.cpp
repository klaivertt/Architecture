#include "dictionary.h"
#include "visitor.h"

int main()
{
    Directory* root = new Directory("User");
    Directory* alex = new Directory("Alex");
    Files* poulio = new Files("Poulio.png");
    Files* password = new Files("password_ne_pas_suprimmer.txt", 256u);

    root->Add(alex);
    alex->Add(poulio);
    alex->Add(password);
    PrintVisitor v(root);
    ComputeSizeVisitor vS(root);

    system("pause");

    delete root;

    return EXIT_SUCCESS;
}

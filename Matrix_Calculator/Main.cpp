#include <iostream>
#include "ui.h"
#include "matrix.h"
#include "vector.h"
using namespace std;


int main()
{
    SubMenu* mainMenu = new SubMenu("Main Menu");

    ActionItem* action1 = new ActionItem("Matrix Calculator", actionOne_Matrix);
    ActionItem* action2 = new ActionItem("Vector Calculator", actionTwo_Vector);


    mainMenu->addItem(action1);
    mainMenu->addItem(action2);

    mainMenu->execute();

    delete mainMenu;
    return 0;
}

#include <iostream>
#include "ui.h"
#include "matrix.h"
#include "vector.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include "smatrix.h"


ActionItem::ActionItem(const string& name, void(*action)())
{
    this->name = name;
    this->action = action;
}

void ActionItem::execute()
{
    action();
}

SubMenu::SubMenu(const string& name)
{
    this->name = name;
}

void SubMenu::addItem(MenuItem* item)
{
    items.push_back(item);
}

void SubMenu::execute()
{
    int choice = 0;
    while (true) {
        std::cout << "\n--- " << name << " ---\n";
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i]->name << "\n";
        }
        std::cout << items.size() + 1 << ". Exit the program. \n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice < 1 || choice > items.size() + 1) {
            std::cout << "Invalid choice. Try again.\n";
        }
        else if (choice == items.size() + 1) {
            break; // Exit submenu
        }
        else {
            items[choice - 1]->execute();
        }
    }
}

SubMenu::~SubMenu()
{
    for (auto item : items)
    {
        delete item;
    }
}



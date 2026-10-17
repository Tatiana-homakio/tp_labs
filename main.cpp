#include "Keeper.h"
#include "Furniture.h"
#include "Worker.h"
#include "Machine.h"
#include <iostream>
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void addObjectMenu(Keeper& keeper) {
    std::cout << "\nObject type: 1. Furniture  2. Worker  3. Machine\nYour choice: ";
    int choice; std::cin >> choice;
    if (std::cin.fail()) { clearInput(); std::cout << "Input error!\n"; return; }

    std::cout << "ID: "; int id; std::cin >> id;
    if (std::cin.fail()) { clearInput(); std::cout << "ID input error!\n"; return; }

    try {
        if (choice == 1) {
            auto* f = new Furniture(); f->setId(id); f->read(std::cin); keeper.add(f);
        } else if (choice == 2) {
            auto* w = new Worker(); w->setId(id); w->read(std::cin); keeper.add(w);
        } else if (choice == 3) {
            auto* m = new Machine(); m->setId(id); m->read(std::cin); keeper.add(m);
        } else {
            std::cout << "Wrong type.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void deleteObjectMenu(Keeper& keeper) {
    if (keeper.getSize() == 0) { std::cout << "Container is empty.\n"; return; }
    keeper.printAll();
    std::cout << "Index to delete: "; int idx; std::cin >> idx;
    if (std::cin.fail()) { clearInput(); std::cout << "Input error!\n"; return; }
    try { keeper.removeAt(idx); std::cout << "Deleted.\n"; }
    catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
}

void editObjectMenu(Keeper& keeper) {
    if (keeper.getSize() == 0) { std::cout << "Container is empty.\n"; return; }
    keeper.printAll();
    std::cout << "Index to edit: "; int idx; std::cin >> idx;
    if (std::cin.fail()) { clearInput(); std::cout << "Input error!\n"; return; }
    try {
        Base* obj = keeper[idx];
        obj->print(std::cout);
        std::cout << "\nNew data:\n";
        obj->read(std::cin);
    } catch (const std::exception& e) { std::cout << "Error: " << e.what() << "\n"; }
}

int main() {
    Keeper keeper;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n========== MENU ==========\n"
                  << "1. Add object\n"
                  << "2. Show all objects\n"
                  << "3. Show object by index\n"
                  << "4. Delete object by index\n"
                  << "5. Edit object by index\n"
                  << "6. Clear container\n"
                  << "7. Show container size\n"
                  << "0. Exit\n"
                  << "Your choice: ";
        std::cin >> choice;
        if (std::cin.fail()) { clearInput(); std::cout << "Input error!\n"; continue; }

        try {
            switch (choice) {
            case 1: addObjectMenu(keeper); break;
            case 2: keeper.printAll(); break;
            case 3: {
                std::cout << "Index: "; int i; std::cin >> i;
                if (std::cin.fail()) { clearInput(); std::cout << "Input error!\n"; break; }
                keeper.printByIndex(i);
                break;
            }
            case 4: deleteObjectMenu(keeper); break;
            case 5: editObjectMenu(keeper); break;
            case 6: keeper.clear(); std::cout << "Cleared.\n"; break;
            case 7: std::cout << "Size: " << keeper.getSize()
                             << ", capacity: " << keeper.getCapacity() << "\n"; break;
            case 0: std::cout << "Exit.\n"; break;
            default: std::cout << "Wrong menu item.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << "\n";
        }
    }
    return 0;
}
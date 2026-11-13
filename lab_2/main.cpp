#include "OrderArray.h"
#include "TextProcessor.h"
#include <iostream>
#include <string>
#include <limits>

// ============================================================
//  Печать меню
// ============================================================
void printMenu() {
    std::cout << "\n========== MENU ==========\n"
              << " 1. Add Order\n"
              << " 2. Remove Order by index\n"
              << " 3. Edit Order by index\n"
              << " 4. Show all Orders\n"
              << " 5. Sort by payer account\n"
              << " 6. Total amount by payer account\n"
              << " 7. File/string streams (process text file)\n"
              << " 0. Exit\n"
              << "==========================\n"
              << "Choice: ";
}

// ============================================================
//  Аккуратный ввод целого числа
// ============================================================
int readInt(const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) {
            std::cin.ignore(10000, '\n');
            return v;
        }
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Error: please enter a number.\n";
    }
}

// ============================================================
//  main
// ============================================================
int main() {
    OrderArray arr;
    std::cout << "Lab 2, variant 20 (ORDER)\n";

    while (true) {
        printMenu();
        int choice = readInt("");

        try {
            switch (choice) {

            // ---------- 1. Добавить ----------
            case 1: {
                Order o;
                std::cin >> o;
                int pos = readInt("Position (-1 = append): ");
                arr.add(o, pos);
                break;
            }

            // ---------- 2. Удалить ----------
            case 2: {
                int idx = readInt("Index to remove: ");
                arr.remove(idx);
                break;
            }

            // ---------- 3. Редактировать ----------
            case 3: {
                int idx = readInt("Index to edit: ");
                Order o;
                std::cin >> o;
                arr.edit(idx, o);
                break;
            }

            // ---------- 4. Показать все ----------
            case 4:
                std::cout << "Total: " << arr.getSize() << "\n";
                arr.printAll();
                break;

            // ---------- 5. Сортировка ----------
            case 5:
                arr.sortByPayerAccount();
                break;

            // ---------- 6. Сумма по счёту плательщика ----------
            case 6: {
                std::string payer;
                std::cout << "Payer account: ";
                std::getline(std::cin, payer);

                if (!arr.hasPayer(payer)) {
                    std::cout << "Account '" << payer << "' not found.\n";
                } else {
                    std::cout << "Total for account '" << payer << "': "
                              << arr.totalByPayer(payer) << " RUB\n";
                }
                break;
            }

            // ---------- 7. Файловые/строковые потоки ----------
            case 7: {
                std::string fname;
                std::cout << "File path: ";
                std::getline(std::cin, fname);
                TextProcessor::processFile(fname);
                break;
            }

            // ---------- 0. Выход ----------
            case 0:
                std::cout << "Exit.\n";
                return 0;

            default:
                std::cout << "Invalid menu item.\n";
            }
        }
        catch (const InvalidAccountException& e) {
            std::cout << "Account error: " << e.what() << "\n";
        }
        catch (const EmptyArrayException& e) {
            std::cout << "Array error: " << e.what() << "\n";
        }
        catch (const IndexOutOfRangeException& e) {
            std::cout << "Index error: " << e.what() << "\n";
        }
        catch (const FileOpenException& e) {
            std::cout << "File error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
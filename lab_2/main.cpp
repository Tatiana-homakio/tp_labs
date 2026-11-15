#include "OrderArray.h"
#include "TextProcessor.h"
#include <iostream>
#include <string>

using namespace std;   

// Печатает главное меню программы
void printMenu() {
    cout << "\n========== MENU ==========\n"
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

// Читает целое число с клавиатуры; при ошибке просит повторить
int readInt(const string& prompt) {
    int v;
    while (true) {
        cout << prompt;                            // выводим подсказку
        if (cin >> v) {                            // пытаемся прочитать число
            cin.ignore(10000, '\n');               // очищаем буфер до конца строки
            return v;
        }
        cin.clear();                               // сбрасываем флаг ошибки потока
        cin.ignore(10000, '\n');                   // выбрасываем некорректный ввод
        cout << "Error: please enter a number.\n";
    }
}

int main() {
    OrderArray arr;                                // создаём массив заказов
    cout << "Lab 2, variant 20 (ORDER)\n";

    while (true) {
        printMenu();
        int choice = readInt("");                  // получаем пункт меню

        try {
            switch (choice) {
            case 1: {                              // добавить заказ
                Order o;
                cin >> o;                          // ввод полей заказа
                int pos = readInt("Position (-1 = append): ");
                arr.add(o, pos);
                break;
            }
            case 2: {                              // удалить по индексу
                int idx = readInt("Index to remove: ");
                arr.remove(idx);
                break;
            }
            case 3: {                              // редактировать по индексу
                int idx = readInt("Index to edit: ");
                Order o;
                cin >> o;
                arr.edit(idx, o);
                break;
            }
            case 4:                                // показать все
                cout << "Total: " << arr.getSize() << "\n";
                arr.printAll();
                break;
            case 5:                                // сортировка
                arr.sortByPayerAccount();
                break;
            case 6: {                              // сумма по счёту
                string payer;
                cout << "Payer account: ";
                getline(cin, payer);               // читаем строку целиком
                if (!arr.hasPayer(payer)) {        // проверяем, есть ли такой счёт
                    cout << "Account '" << payer << "' not found.\n";
                } else {
                    cout << "Total for account '" << payer << "': "
                         << arr.totalByPayer(payer) << " RUB\n";
                }
                break;
            }
            case 7: {                              // обработка текстового файла
                string fname;
                cout << "File path: ";
                getline(cin, fname);
                TextProcessor::processFile(fname);
                break;
            }
            case 0:                                // выход
                cout << "Exit.\n";
                return 0;
            default:
                cout << "Invalid menu item.\n";
            }
        }
        catch (const InvalidAccountException& e) { // ошибки данных заказа
            cout << "Account error: " << e.what() << "\n";
        }
        catch (const EmptyArrayException& e) {     // массив пуст
            cout << "Array error: " << e.what() << "\n";
        }
        catch (const IndexOutOfRangeException& e) { // неверный индекс
            cout << "Index error: " << e.what() << "\n";
        }
        catch (const FileOpenException& e) {       // файл не открылся
            cout << "File error: " << e.what() << "\n";
        }
        catch (const exception& e) {               // прочие std-исключения
            cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}
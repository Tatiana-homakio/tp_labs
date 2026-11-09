#include "Order.h"
#include <iostream>

// ============================================================
//  День 1: временная заглушка — просто проверяем класс Order
// ============================================================
int main() {
    std::cout << "=== Order class test (Day 1) ===\n\n";

    try {
        // 1. Конструктор по умолчанию
        Order o1;

        // 2. Конструктор с параметрами
        Order o2("40817810000000000001",
                 "40817810000000000002",
                 1500.0);

        // 3. operator<<
        std::cout << "o2 = " << o2 << "\n";

        // 4. Конструктор копирования
        Order o3 = o2;
        std::cout << "o3 = " << o3 << "\n";

        // 5. operator=
        o1 = o2;
        std::cout << "o1 (after =) = " << o1 << "\n";

        // 6. set/get
        o1.setAmount(2000.0);
        std::cout << "o1 amount after setAmount = " << o1.getAmount() << "\n";

        // 7. Проверка исключения
        std::cout << "\nTrying to create Order with negative amount...\n";
        Order bad("A", "B", -100);   // бросит исключение
        std::cout << "This line should not be reached\n";
    }
    catch (const InvalidAccountException& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "Other exception: " << e.what() << "\n";
    }

    std::cout << "\n=== End of test ===\n";
    return 0;
}
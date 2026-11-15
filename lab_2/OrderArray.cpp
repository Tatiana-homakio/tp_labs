#include "OrderArray.h"
#include <iostream>

using namespace std;   

// Конструктор: массив пуст, память не выделена
OrderArray::OrderArray()
    : data(nullptr), size(0), capacity(0) {
    cout << "[OrderArray] Constructor called\n";
}

// Деструктор: освобождает динамическую память
OrderArray::~OrderArray() {
    cout << "[OrderArray] Destructor called\n";
    delete[] data;                                 // освобождаем массив
}

// Расширяет массив до newCap, копируя старые элементы
void OrderArray::resize(int newCap) {
    Order* newData = new Order[newCap];            // новый блок памяти
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];                      // копируем старые элементы
    delete[] data;                                 // старую память освобождаем
    data     = newData;                            // подменяем указатель
    capacity = newCap;
}

// Добавляет заказ в позицию position (или в конец, если position вне диапазона)
void OrderArray::add(const Order& o, int position) {
    if (size == capacity)                          // нет места — расширяем
        resize(capacity == 0 ? 4 : capacity * 2);  // старт с 4, потом удваиваем

    if (position < 0 || position > size)
        position = size;                           // позиция по умолчанию — конец

    for (int i = size; i > position; --i)          // сдвигаем элементы вправо
        data[i] = data[i - 1];

    data[position] = o;                            // вставляем новый элемент
    ++size;
    cout << "Order added at position " << position << "\n";
}

// Удаляет элемент по индексу и сдвигает оставшиеся влево
void OrderArray::remove(int index) {
    if (size == 0)                                 // пустой массив
        throw EmptyArrayException("Array is empty — nothing to delete");
    if (index < 0 || index >= size)                // индекс вне диапазона
        throw IndexOutOfRangeException("Invalid index for removal");

    for (int i = index; i < size - 1; ++i)         // сдвигаем влево
        data[i] = data[i + 1];

    --size;
    cout << "Element #" << index << " removed\n";
}

// Заменяет элемент по индексу новым заказом
void OrderArray::edit(int index, const Order& o) {
    if (index < 0 || index >= size)                // проверка индекса
        throw IndexOutOfRangeException("Invalid index for editing");
    data[index] = o;                               // копируем через operator=
    cout << "Element #" << index << " edited\n";
}

// Возвращает ссылку на элемент с проверкой индекса
Order& OrderArray::at(int index) {
    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Invalid index (at)");
    return data[index];
}

const Order& OrderArray::at(int index) const {
    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Invalid index (at const)");
    return data[index];
}

// Сортировка вставками по счёту плательщика (по возрастанию строки)
void OrderArray::sortByPayerAccount() {
    for (int i = 1; i < size; ++i) {               // идём со второго элемента
        Order key = data[i];                       // запоминаем текущий
        int j = i - 1;
        while (j >= 0 && data[j].getPayerAccount() > key.getPayerAccount()) {
            data[j + 1] = data[j];                 // сдвигаем вправо
            --j;
        }
        data[j + 1] = key;                         // ставим key на место
    }
    cout << "Sorted by payer account\n";
}

// Сумма всех сумм заказов с указанным счётом плательщика
double OrderArray::totalByPayer(const string& payer) const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
        if (data[i].getPayerAccount() == payer)    // совпадение счёта
            sum += data[i].getAmount();
    return sum;
}

// Проверяет, есть ли заказ с таким счётом плательщика
bool OrderArray::hasPayer(const string& payer) const {
    for (int i = 0; i < size; ++i)
        if (data[i].getPayerAccount() == payer)    // нашли — true
            return true;
    return false;
}

// Печатает все заказы с индексами
void OrderArray::printAll() const {
    if (size == 0) {
        cout << "  (empty)\n";
        return;
    }
    for (int i = 0; i < size; ++i)
        cout << "  [" << i << "] " << data[i] << "\n"; // использует operator<<
}
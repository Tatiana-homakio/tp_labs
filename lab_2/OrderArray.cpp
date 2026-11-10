#include "OrderArray.h"
#include <iostream>

// ============================================================
//  Конструктор / деструктор
// ============================================================
OrderArray::OrderArray()
    : data(nullptr), size(0), capacity(0) {
    std::cout << "[OrderArray] Constructor called\n";
}

OrderArray::~OrderArray() {
    std::cout << "[OrderArray] Destructor called\n";
    delete[] data;
}

// ============================================================
//  Расширение массива (динамическое выделение памяти)
// ============================================================
void OrderArray::resize(int newCap) {
    Order* newData = new Order[newCap];
    for (int i = 0; i < size; ++i)
        newData[i] = data[i];
    delete[] data;
    data     = newData;
    capacity = newCap;
}

// ============================================================
//  Добавление элемента
// ============================================================
void OrderArray::add(const Order& o, int position) {
    if (size == capacity)
        resize(capacity == 0 ? 4 : capacity * 2);

    if (position < 0 || position > size)
        position = size;

    for (int i = size; i > position; --i)
        data[i] = data[i - 1];

    data[position] = o;
    ++size;
    std::cout << "Order added at position " << position << "\n";
}

// ============================================================
//  Удаление элемента
// ============================================================
void OrderArray::remove(int index) {
    if (size == 0)
        throw EmptyArrayException("Array is empty — nothing to delete");
    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Invalid index for removal");

    for (int i = index; i < size - 1; ++i)
        data[i] = data[i + 1];

    --size;
    std::cout << "Element #" << index << " removed\n";
}

// ============================================================
//  Редактирование элемента
// ============================================================
void OrderArray::edit(int index, const Order& o) {
    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Invalid index for editing");
    data[index] = o;
    std::cout << "Element #" << index << " edited\n";
}

// ============================================================
//  Доступ по индексу
// ============================================================
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

// ============================================================
//  Сортировка вставками по счёту плательщика
//  (без std::sort — свой алгоритм)
// ============================================================
void OrderArray::sortByPayerAccount() {
    for (int i = 1; i < size; ++i) {
        Order key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j].getPayerAccount() > key.getPayerAccount()) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = key;
    }
    std::cout << "Sorted by payer account\n";
}

// ============================================================
//  Сумма по счёту плательщика
// ============================================================
double OrderArray::totalByPayer(const std::string& payer) const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
        if (data[i].getPayerAccount() == payer)
            sum += data[i].getAmount();
    return sum;
}

// ============================================================
//  Есть ли такой счёт?
// ============================================================
bool OrderArray::hasPayer(const std::string& payer) const {
    for (int i = 0; i < size; ++i)
        if (data[i].getPayerAccount() == payer)
            return true;
    return false;
}

// ============================================================
//  Печать всех
// ============================================================
void OrderArray::printAll() const {
    if (size == 0) {
        std::cout << "  (empty)\n";
        return;
    }
    for (int i = 0; i < size; ++i)
        std::cout << "  [" << i << "] " << data[i] << "\n";
}
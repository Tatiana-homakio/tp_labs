#ifndef ORDERARRAY_H
#define ORDERARRAY_H

#include "Order.h"
#include <stdexcept>

// ============================================================
//  Исключение: массив пуст
// ============================================================
class EmptyArrayException : public std::runtime_error {
public:
    explicit EmptyArrayException(const std::string& m) : std::runtime_error(m) {}
};

// ============================================================
//  Исключение: неверный индекс
// ============================================================
class IndexOutOfRangeException : public std::runtime_error {
public:
    explicit IndexOutOfRangeException(const std::string& m) : std::runtime_error(m) {}
};

// ============================================================
//  OrderArray — динамический массив объектов Order
//  (свой, без std::vector)
// ============================================================
class OrderArray {
private:
    Order* data;      // динамический массив
    int    size;      // сколько элементов сейчас
    int    capacity;  // сколько выделено

    void resize(int newCap);  // расширение массива

public:
    // ---------- Конструктор / деструктор ----------
    OrderArray();
    ~OrderArray();

    // Запрет копирования (массив владеет памятью)
    OrderArray(const OrderArray&) = delete;
    OrderArray& operator=(const OrderArray&) = delete;

    // ---------- get ----------
    int getSize() const     { return size; }
    int getCapacity() const { return capacity; }

    // ---------- Основные операции ----------
    void add(const Order& o, int position = -1);  // -1 => в конец
    void remove(int index);
    void edit(int index, const Order& o);

    Order&       at(int index);
    const Order& at(int index) const;

    // ---------- Сортировка и поиск ----------
    void   sortByPayerAccount();
    double totalByPayer(const std::string& payer) const;
    bool   hasPayer(const std::string& payer) const;

    // ---------- Вывод ----------
    void printAll() const;
};

#endif // ORDERARRAY_H
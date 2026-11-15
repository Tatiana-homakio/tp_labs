#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <stdexcept>

// Исключение для некорректных данных о счёте или сумме
class InvalidAccountException : public std::runtime_error {
public:
    explicit InvalidAccountException(const std::string& msg)
        : std::runtime_error(msg) {}                // передаём текст в базовый класс
};

// Класс Order — перевод денег: счёт плательщика, счёт получателя, сумма
class Order {
private:
    std::string payerAccount;                       // счёт плательщика
    std::string receiverAccount;                    // счёт получателя
    double amount;                                  // сумма в рублях

public:
    Order();                                        // конструктор по умолчанию
    Order(const std::string& payer,
          const std::string& receiver,
          double amount);                           // конструктор с параметрами
    Order(const Order& other);                      // конструктор копирования
    ~Order();                                       // деструктор

    Order& operator=(const Order& other);           // оператор присваивания

    friend std::ostream& operator<<(std::ostream& os, const Order& o); // вывод
    friend std::istream& operator>>(std::istream& is, Order& o);       // ввод

    void setPayerAccount(const std::string& v);
    void setReceiverAccount(const std::string& v);
    void setAmount(double v);

    const std::string& getPayerAccount() const;
    const std::string& getReceiverAccount() const;
    double getAmount() const;

    bool isValid() const;                           // проверка заполненности
};

#endif
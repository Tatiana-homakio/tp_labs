#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <stdexcept>

// ============================================================
//  Исключение для некорректных данных о счёте/сумме
// ============================================================
class InvalidAccountException : public std::runtime_error {
public:
    explicit InvalidAccountException(const std::string& msg)
        : std::runtime_error(msg) {}
};

// ============================================================
//  Класс Order — «перевод денег»
//  Поля: расчетный счет плательщика, расчетный счет получателя,
//        перечисляемая сумма в рублях
// ============================================================
class Order {
private:
    std::string payerAccount;     // расчетный счет плательщика
    std::string receiverAccount;  // расчетный счет получателя
    double amount;                // сумма в рублях

public:
    // ---------- Конструкторы / деструктор ----------
    Order();                                                    // по умолчанию
    Order(const std::string& payer,
          const std::string& receiver,
          double amount);                                       // с параметрами
    Order(const Order& other);                                  // копирования
    ~Order();                                                   // деструктор

    // ---------- Оператор присваивания ----------
    Order& operator=(const Order& other);

    // ---------- Перегруженные операции вставки/извлечения ----------
    friend std::ostream& operator<<(std::ostream& os, const Order& o);
    friend std::istream& operator>>(std::istream& is, Order& o);

    // ---------- set ----------
    void setPayerAccount(const std::string& v);
    void setReceiverAccount(const std::string& v);
    void setAmount(double v);

    // ---------- get ----------
    const std::string& getPayerAccount() const;
    const std::string& getReceiverAccount() const;
    double getAmount() const;

    // ---------- Вспомогательный метод ----------
    bool isValid() const;
};

#endif // ORDER_H
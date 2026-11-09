#include "Order.h"

// ============================================================
//  Конструктор по умолчанию
// ============================================================
Order::Order()
    : payerAccount(""), receiverAccount(""), amount(0.0) {
    std::cout << "[Order] Default constructor called\n";
}

// ============================================================
//  Конструктор с параметрами
// ============================================================
Order::Order(const std::string& payer,
             const std::string& receiver,
             double amount)
    : payerAccount(payer), receiverAccount(receiver), amount(amount) {
    std::cout << "[Order] Parameterized constructor called\n";
    if (amount < 0)
        throw InvalidAccountException("Amount cannot be negative");
}

// ============================================================
//  Конструктор копирования
// ============================================================
Order::Order(const Order& other)
    : payerAccount(other.payerAccount),
      receiverAccount(other.receiverAccount),
      amount(other.amount) {
    std::cout << "[Order] Copy constructor called\n";
}

// ============================================================
//  Деструктор
// ============================================================
Order::~Order() {
    std::cout << "[Order] Destructor called (payer=" << payerAccount << ")\n";
}

// ============================================================
//  Оператор присваивания
// ============================================================
Order& Order::operator=(const Order& other) {
    std::cout << "[Order] operator= called\n";
    if (this != &other) {
        payerAccount    = other.payerAccount;
        receiverAccount = other.receiverAccount;
        amount          = other.amount;
    }
    return *this;
}

// ============================================================
//  operator<<  — вывод объекта в поток
// ============================================================
std::ostream& operator<<(std::ostream& os, const Order& o) {
    os << "Payer: " << o.payerAccount
       << " | Receiver: " << o.receiverAccount
       << " | Amount: " << o.amount << " RUB";
    return os;
}

// ============================================================
//  operator>>  — ввод объекта из потока
// ============================================================
std::istream& operator>>(std::istream& is, Order& o) {
    std::string p, r;
    double a;

    std::cout << "  Payer account: ";
    std::getline(is, p);

    std::cout << "  Receiver account: ";
    std::getline(is, r);

    std::cout << "  Amount (RUB): ";
    is >> a;
    is.ignore(10000, '\n');

    if (a < 0)
        throw InvalidAccountException("Amount cannot be negative");

    o.payerAccount    = p;
    o.receiverAccount = r;
    o.amount          = a;
    return is;
}

// ============================================================
//  set-функции
// ============================================================
void Order::setPayerAccount(const std::string& v)    { payerAccount = v; }
void Order::setReceiverAccount(const std::string& v) { receiverAccount = v; }

void Order::setAmount(double v) {
    if (v < 0)
        throw InvalidAccountException("Amount cannot be negative");
    amount = v;
}

// ============================================================
//  get-функции
// ============================================================
const std::string& Order::getPayerAccount() const    { return payerAccount; }
const std::string& Order::getReceiverAccount() const { return receiverAccount; }
double Order::getAmount() const                      { return amount; }

// ============================================================
//  Проверка корректности
// ============================================================
bool Order::isValid() const {
    return !payerAccount.empty() && !receiverAccount.empty();
}
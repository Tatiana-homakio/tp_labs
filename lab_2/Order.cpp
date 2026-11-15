#include "Order.h"

using namespace std;   

// Конструктор по умолчанию: пустые счета и нулевая сумма
Order::Order()
    : payerAccount(""), receiverAccount(""), amount(0.0) {
    cout << "[Order] Default constructor called\n";
}

// Конструктор с параметрами: проверяет, что сумма не отрицательная
Order::Order(const string& payer,
             const string& receiver,
             double amount)
    : payerAccount(payer), receiverAccount(receiver), amount(amount) {
    cout << "[Order] Parameterized constructor called\n";
    if (amount < 0)                                // отрицательная сумма — ошибка
        throw InvalidAccountException("Amount cannot be negative");
}

// Конструктор копирования: поэлементно копирует поля
Order::Order(const Order& other)
    : payerAccount(other.payerAccount),
      receiverAccount(other.receiverAccount),
      amount(other.amount) {
    cout << "[Order] Copy constructor called\n";
}

// Деструктор: выводит сообщение об уничтожении объекта
Order::~Order() {
    cout << "[Order] Destructor called (payer=" << payerAccount << ")\n";
}

// Оператор присваивания: копирует поля, защищается от самоприсваивания
Order& Order::operator=(const Order& other) {
    cout << "[Order] operator= called\n";
    if (this != &other) {                          // проверка на самоприсваивание
        payerAccount    = other.payerAccount;
        receiverAccount = other.receiverAccount;
        amount          = other.amount;
    }
    return *this;
}

// Вывод заказа в поток в одну строку
ostream& operator<<(ostream& os, const Order& o) {
    os << "Payer: " << o.payerAccount
       << " | Receiver: " << o.receiverAccount
       << " | Amount: " << o.amount << " RUB";
    return os;
}

// Ввод заказа с клавиатуры; сумма проверяется на отрицательность
istream& operator>>(istream& is, Order& o) {
    string p, r;
    double a;

    cout << "  Payer account: ";
    getline(is, p);                                // читаем строку до '\n'

    cout << "  Receiver account: ";
    getline(is, r);

    cout << "  Amount (RUB): ";
    is >> a;                                       // читаем число
    is.ignore(10000, '\n');                        // убираем остаток строки

    if (a < 0)                                     // отрицательная сумма — ошибка
        throw InvalidAccountException("Amount cannot be negative");

    o.payerAccount    = p;
    o.receiverAccount = r;
    o.amount          = a;
    return is;
}

void Order::setPayerAccount(const string& v)    { payerAccount = v; }
void Order::setReceiverAccount(const string& v) { receiverAccount = v; }

// Сеттер суммы с проверкой
void Order::setAmount(double v) {
    if (v < 0)                                     // отрицательная сумма запрещена
        throw InvalidAccountException("Amount cannot be negative");
    amount = v;
}

const string& Order::getPayerAccount() const    { return payerAccount; }
const string& Order::getReceiverAccount() const { return receiverAccount; }
double Order::getAmount() const                 { return amount; }

// Объект считается корректным, если оба счёта непустые
bool Order::isValid() const {
    return !payerAccount.empty() && !receiverAccount.empty();
}
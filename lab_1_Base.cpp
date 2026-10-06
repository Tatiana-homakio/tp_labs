#include "lab_1_Base.h"

Base::Base() : id(0) {
    std::cout << "[Base] Конструктор по умолчанию\n";
}

Base::Base(int id) : id(id) {
    std::cout << "[Base] Конструктор с параметрами (id=" << id << ")\n";
}

Base::Base(const Base& other) : id(other.id) {
    std::cout << "[Base] Конструктор копирования (id=" << id << ")\n";
}

Base::~Base() {
    std::cout << "[Base] Деструктор (id=" << id << ")\n";
}

int Base::getId() const { return id; }
void Base::setId(int id) { this->id = id; }

std::ostream& operator<<(std::ostream& os, const Base& obj) {
    obj.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Base& obj) {
    obj.read(is);
    return is;
}

bool Base::operator==(const Base& other) const {
    return this->id == other.id;
}

bool Base::operator!=(const Base& other) const {
    return !(*this == other);
}
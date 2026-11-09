#include "Base.h"

Base::Base() : id(0) {
    std::cout << "[Base] Default constructor\n";
}

Base::Base(int id) : id(id) {
    std::cout << "[Base] Param constructor (id=" << id << ")\n";
}

Base::Base(const Base& other) : id(other.id) {
    std::cout << "[Base] Copy constructor (id=" << id << ")\n";
}

Base::~Base() {
    std::cout << "[Base] Destructor (id=" << id << ")\n";
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
#include "Keeper.h"
#include "Furniture.h"
#include "Worker.h"
#include "Machine.h"

Keeper::Keeper() : items(nullptr), size(0), capacity(0) {
    std::cout << "[Keeper] Default constructor\n";
}

Keeper::Keeper(const Keeper& other) : items(nullptr), size(other.size), capacity(other.capacity) {
    std::cout << "[Keeper] Copy constructor\n";
    if (capacity > 0) {
        items = new Base*[capacity];
        for (int i = 0; i < size; ++i) items[i] = other.items[i]->clone();
    }
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Destructor\n";
    clear();
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        clear();
        size = other.size;
        capacity = other.capacity;
        if (capacity > 0) {
            items = new Base*[capacity];
            for (int i = 0; i < size; ++i) items[i] = other.items[i]->clone();
        }
    }
    return *this;
}

void Keeper::reserve(int newCapacity) {
    if (newCapacity <= capacity) return;
    Base** newItems = new Base*[newCapacity];
    for (int i = 0; i < size; ++i) newItems[i] = items[i];
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}

void Keeper::add(Base* item) {
    if (item == nullptr)
        throw KeeperException("Cannot add null pointer");
    if (size >= capacity) reserve(capacity == 0 ? 4 : capacity * 2);
    items[size++] = item;
}

void Keeper::removeAt(int index) {
    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Index " + std::to_string(index) +
            " out of range [0, " + std::to_string(size - 1) + "]");
    delete items[index];
    for (int i = index; i < size - 1; ++i) items[i] = items[i + 1];
    --size;
}

int Keeper::getSize() const { return size; }
int Keeper::getCapacity() const { return capacity; }

Base* Keeper::operator[](int index) {
    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Index " + std::to_string(index) + " out of range");
    return items[index];
}

const Base* Keeper::operator[](int index) const {
    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Index " + std::to_string(index) + " out of range");
    return items[index];
}

void Keeper::printAll(std::ostream& os) const {
    if (size == 0) { os << "Container is empty.\n"; return; }
    for (int i = 0; i < size; ++i) {
        os << "[" << i << "] ";
        items[i]->print(os);
        os << "------------------------\n";
    }
}

void Keeper::printByIndex(int index, std::ostream& os) const {
    if (index < 0 || index >= size)
        throw IndexOutOfRangeException("Index " + std::to_string(index) + " out of range");
    items[index]->print(os);
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open())
        throw FileException("Cannot open file for writing: " + filename);
    ofs << size << "\n";
    for (int i = 0; i < size; ++i) items[i]->save(ofs);
    ofs.close();
    std::cout << "Saved objects: " << size << " to " << filename << "\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open())
        throw FileException("Cannot open file for reading: " + filename);
    clear();
    int count;
    ifs >> count;
    for (int i = 0; i < count; ++i) {
        std::string type;
        ifs >> type;
        Base* obj = nullptr;
        if (type == "FURNITURE") obj = new Furniture();
        else if (type == "WORKER") obj = new Worker();
        else if (type == "MACHINE") obj = new Machine();
        else throw FileException("Unknown object type: " + type);
        obj->load(ifs);
        add(obj);
    }
    ifs.close();
    std::cout << "Loaded objects: " << size << " from " << filename << "\n";
}

void Keeper::clear() {
    for (int i = 0; i < size; ++i) delete items[i];
    delete[] items;
    items = nullptr;
    size = 0;
    capacity = 0;
}

std::ostream& operator<<(std::ostream& os, const Keeper& k) {
    k.printAll(os);
    return os;
}
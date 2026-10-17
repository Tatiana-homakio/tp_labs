#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <stdexcept>

class KeeperException : public std::runtime_error {
public:
    explicit KeeperException(const std::string& msg) : std::runtime_error(msg) {}
};

class IndexOutOfRangeException : public KeeperException {
public:
    explicit IndexOutOfRangeException(const std::string& msg) : KeeperException(msg) {}
};

class FileException : public KeeperException {
public:
    explicit FileException(const std::string& msg) : KeeperException(msg) {}
};

class Keeper {
private:
    Base** items;
    int size;
    int capacity;

    void reserve(int newCapacity);

public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);

    Base* operator[](int index);
    const Base* operator[](int index) const;

    void add(Base* item);
    void removeAt(int index);
    int getSize() const;
    int getCapacity() const;

    void printAll(std::ostream& os = std::cout) const;
    void printByIndex(int index, std::ostream& os = std::cout) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    void clear();

    friend std::ostream& operator<<(std::ostream& os, const Keeper& k);
};

#endif
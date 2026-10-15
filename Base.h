#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>
#include <fstream>

class Base {
protected:
    int id;

public:
    Base();
    Base(int id);
    Base(const Base& other);
    virtual ~Base();

    int getId() const;
    void setId(int id);

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual void save(std::ofstream& ofs) const = 0;
    virtual void load(std::ifstream& ifs) = 0;
    virtual std::string getType() const = 0;
    virtual Base* clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Base& obj);
    friend std::istream& operator>>(std::istream& is, Base& obj);
    bool operator==(const Base& other) const;
    bool operator!=(const Base& other) const;
};

#endif
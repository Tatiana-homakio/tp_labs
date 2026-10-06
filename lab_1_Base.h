#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>

class Base {
protected:
    int id;

public:
    Base();
    Base(int id);
    virtual ~Base();

    int getId() const;
    void setId(int id);

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual std::string getType() const = 0;
};

#endif
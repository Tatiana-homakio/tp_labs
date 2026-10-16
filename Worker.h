#ifndef WORKER_H
#define WORKER_H

#include "Base.h"

class Worker : public Base {
private:
    std::string fullName;
    std::string position;
    double salary;
    std::string address;
    std::string phone;

public:
    Worker();
    Worker(int id, const std::string& fio, const std::string& pos,
           double salary, const std::string& addr, const std::string& phone);
    Worker(const Worker& other);
    ~Worker() override;

    std::string getFullName() const;
    std::string getPosition() const;
    double getSalary() const;
    std::string getAddress() const;
    std::string getPhone() const;

    void setFullName(const std::string& f);
    void setPosition(const std::string& p);
    void setSalary(double s);
    void setAddress(const std::string& a);
    void setPhone(const std::string& p);

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    void save(std::ofstream& ofs) const override;
    void load(std::ifstream& ifs) override;
    std::string getType() const override;
    Base* clone() const override;
};

#endif
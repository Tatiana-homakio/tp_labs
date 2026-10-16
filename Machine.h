#ifndef MACHINE_H
#define MACHINE_H

#include "Base.h"

class Machine : public Base {
private:
    std::string brand;
    std::string model;
    std::string plate;

public:
    Machine();
    Machine(int id, const std::string& brand, const std::string& model, const std::string& plate);
    Machine(const Machine& other);
    ~Machine() override;

    std::string getBrand() const;
    std::string getModel() const;
    std::string getPlate() const;

    void setBrand(const std::string& b);
    void setModel(const std::string& m);
    void setPlate(const std::string& p);

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    void save(std::ofstream& ofs) const override;
    void load(std::ifstream& ifs) override;
    std::string getType() const override;
    Base* clone() const override;
};

#endif
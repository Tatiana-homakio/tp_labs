#ifndef FURNITURE_H
#define FURNITURE_H

#include "Base.h"

class Furniture : public Base {
private:
    std::string type;
    double height;
    double width;
    double depth;
    std::string color;
    std::string material;
    double price;

public:
    Furniture();
    Furniture(int id, const std::string& type, double h, double w, double d,
              const std::string& color, const std::string& material, double price);
    Furniture(const Furniture& other);
    ~Furniture() override;

    std::string getFurnitureType() const;
    double getHeight() const;
    double getWidth() const;
    double getDepth() const;
    std::string getColor() const;
    std::string getMaterial() const;
    double getPrice() const;

    void setFurnitureType(const std::string& t);
    void setHeight(double h);
    void setWidth(double w);
    void setDepth(double d);
    void setColor(const std::string& c);
    void setMaterial(const std::string& m);
    void setPrice(double p);

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    void save(std::ofstream& ofs) const override;
    void load(std::ifstream& ifs) override;
    std::string getType() const override;
    Base* clone() const override;
};

#endif
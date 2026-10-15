#include "Furniture.h"

Furniture::Furniture() : Base(), type(""), height(0), width(0), depth(0),
                          color(""), material(""), price(0) {
    std::cout << "[Furniture] Default constructor\n";
}

Furniture::Furniture(int id, const std::string& type, double h, double w, double d,
                     const std::string& color, const std::string& material, double price)
    : Base(id), type(type), height(h), width(w), depth(d),
      color(color), material(material), price(price) {
    std::cout << "[Furniture] Param constructor (id=" << id << ")\n";
}

Furniture::Furniture(const Furniture& other)
    : Base(other), type(other.type), height(other.height), width(other.width),
      depth(other.depth), color(other.color), material(other.material), price(other.price) {
    std::cout << "[Furniture] Copy constructor (id=" << id << ")\n";
}

Furniture::~Furniture() {
    std::cout << "[Furniture] Destructor (id=" << id << ")\n";
}

std::string Furniture::getFurnitureType() const { return type; }
double Furniture::getHeight() const { return height; }
double Furniture::getWidth() const { return width; }
double Furniture::getDepth() const { return depth; }
std::string Furniture::getColor() const { return color; }
std::string Furniture::getMaterial() const { return material; }
double Furniture::getPrice() const { return price; }

void Furniture::setFurnitureType(const std::string& t) { type = t; }
void Furniture::setHeight(double h) { height = h; }
void Furniture::setWidth(double w) { width = w; }
void Furniture::setDepth(double d) { depth = d; }
void Furniture::setColor(const std::string& c) { color = c; }
void Furniture::setMaterial(const std::string& m) { material = m; }
void Furniture::setPrice(double p) { price = p; }

void Furniture::print(std::ostream& os) const {
    os << "=== Furniture ===\n"
       << "ID: " << id << "\n"
       << "Type: " << type << "\n"
       << "Size (HxWxD): " << height << " x " << width << " x " << depth << "\n"
       << "Color: " << color << "\n"
       << "Material: " << material << "\n"
       << "Price: " << price << "\n";
}

void Furniture::read(std::istream& is) {
    std::cout << "Type: "; is >> type;
    std::cout << "Height: "; is >> height;
    std::cout << "Width: "; is >> width;
    std::cout << "Depth: "; is >> depth;
    std::cout << "Color: "; is >> color;
    std::cout << "Material: "; is >> material;
    std::cout << "Price: "; is >> price;
}

void Furniture::save(std::ofstream& ofs) const {
    ofs << "FURNITURE\n";
    ofs << id << "\n" << type << "\n" << height << " " << width << " " << depth << "\n"
        << color << "\n" << material << "\n" << price << "\n";
}

void Furniture::load(std::ifstream& ifs) {
    ifs >> id >> type >> height >> width >> depth >> color >> material >> price;
}

std::string Furniture::getType() const { return "Furniture"; }

Base* Furniture::clone() const { return new Furniture(*this); }
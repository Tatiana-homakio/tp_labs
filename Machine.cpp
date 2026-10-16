#include "Machine.h"

Machine::Machine() : Base(), brand(""), model(""), plate("") {
    std::cout << "[Machine] Default constructor\n";
}

Machine::Machine(int id, const std::string& brand, const std::string& model, const std::string& plate)
    : Base(id), brand(brand), model(model), plate(plate) {
    std::cout << "[Machine] Param constructor (id=" << id << ")\n";
}

Machine::Machine(const Machine& other)
    : Base(other), brand(other.brand), model(other.model), plate(other.plate) {
    std::cout << "[Machine] Copy constructor (id=" << id << ")\n";
}

Machine::~Machine() {
    std::cout << "[Machine] Destructor (id=" << id << ")\n";
}

std::string Machine::getBrand() const { return brand; }
std::string Machine::getModel() const { return model; }
std::string Machine::getPlate() const { return plate; }

void Machine::setBrand(const std::string& b) { brand = b; }
void Machine::setModel(const std::string& m) { model = m; }
void Machine::setPlate(const std::string& p) { plate = p; }

void Machine::print(std::ostream& os) const {
    os << "=== Machine ===\n"
       << "ID: " << id << "\n"
       << "Brand: " << brand << "\n"
       << "Model: " << model << "\n"
       << "Plate: " << plate << "\n";
}

void Machine::read(std::istream& is) {
    std::cout << "Brand: "; is >> brand;
    std::cout << "Model: "; is >> model;
    std::cout << "Plate: "; is >> plate;
}

void Machine::save(std::ofstream& ofs) const {
    ofs << "MACHINE\n";
    ofs << id << "\n" << brand << "\n" << model << "\n" << plate << "\n";
}

void Machine::load(std::ifstream& ifs) {
    ifs >> id >> brand >> model >> plate;
}

std::string Machine::getType() const { return "Machine"; }

Base* Machine::clone() const { return new Machine(*this); }
#include "Worker.h"

Worker::Worker() : Base(), fullName(""), position(""), salary(0), address(""), phone("") {
    std::cout << "[Worker] Default constructor\n";
}

Worker::Worker(int id, const std::string& fio, const std::string& pos,
               double salary, const std::string& addr, const std::string& phone)
    : Base(id), fullName(fio), position(pos), salary(salary), address(addr), phone(phone) {
    std::cout << "[Worker] Param constructor (id=" << id << ")\n";
}

Worker::Worker(const Worker& other)
    : Base(other), fullName(other.fullName), position(other.position),
      salary(other.salary), address(other.address), phone(other.phone) {
    std::cout << "[Worker] Copy constructor (id=" << id << ")\n";
}

Worker::~Worker() {
    std::cout << "[Worker] Destructor (id=" << id << ")\n";
}

std::string Worker::getFullName() const { return fullName; }
std::string Worker::getPosition() const { return position; }
double Worker::getSalary() const { return salary; }
std::string Worker::getAddress() const { return address; }
std::string Worker::getPhone() const { return phone; }

void Worker::setFullName(const std::string& f) { fullName = f; }
void Worker::setPosition(const std::string& p) { position = p; }
void Worker::setSalary(double s) { salary = s; }
void Worker::setAddress(const std::string& a) { address = a; }
void Worker::setPhone(const std::string& p) { phone = p; }

void Worker::print(std::ostream& os) const {
    os << "=== Worker ===\n"
       << "ID: " << id << "\n"
       << "Full name: " << fullName << "\n"
       << "Position: " << position << "\n"
       << "Salary: " << salary << "\n"
       << "Address: " << address << "\n"
       << "Phone: " << phone << "\n";
}

void Worker::read(std::istream& is) {
    std::cout << "Full name: "; is >> fullName;
    std::cout << "Position: "; is >> position;
    std::cout << "Salary: "; is >> salary;
    std::cout << "Address: "; is >> address;
    std::cout << "Phone: "; is >> phone;
}

void Worker::save(std::ofstream& ofs) const {
    ofs << "WORKER\n";
    ofs << id << "\n" << fullName << "\n" << position << "\n" << salary << "\n"
        << address << "\n" << phone << "\n";
}

void Worker::load(std::ifstream& ifs) {
    ifs >> id >> fullName >> position >> salary >> address >> phone;
}

std::string Worker::getType() const { return "Worker"; }

Base* Worker::clone() const { return new Worker(*this); }
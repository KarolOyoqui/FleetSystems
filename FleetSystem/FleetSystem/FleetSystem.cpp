#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Maneuver {};

class FuelTank {
public:
    FuelTank() { cout << "FuelTank created\n"; }
    ~FuelTank() { cout << "FuelTank destroyed\n"; }
};

class Telemetry {
public:
    Telemetry() { cout << "Telemetry created\n"; }
    ~Telemetry() { cout << "Telemetry destroyed\n"; }
};

class Entity {
public:
    Entity() { cout << "Entity created\n"; }
    virtual ~Entity() { cout << "Entity destroyed\n"; }
};

class Module {
protected:
    string name;
    int power;
public:
    Module(string n, int p) : name(n), power(p) { cout << "Module created\n"; }
    virtual ~Module() { cout << "Module destroyed\n"; }
    virtual void activate() { cout << "Module activated\n"; }
};

class Engine final : public Module {
public:
    Engine(string n, int p) : Module(n, p) { cout << "Engine created\n"; }
    ~Engine() override { cout << "Engine destroyed\n"; }
    void activate() override { cout << "Engine " << name << " turned on!\n"; }
};

class Shield final : public Module {
public:
    Shield(string n, int p) : Module(n, p) { cout << "Shield created\n"; }
    ~Shield() override { cout << "Shield destroyed\n"; }
    void activate() override { cout << "Shield " << name << " turned on!\n"; }
};

class Spacecraft : public Entity {
private:
    FuelTank tank;
    Telemetry telemetry;
    Module* module;

public:
    Spacecraft() : Entity(), module(nullptr) { cout << "Spacecraft created\n"; }
    ~Spacecraft() override { cout << "Spacecraft destroyed\n"; }

    void mountModule(Module* m) { module = m; }
    void executeManeuver(const Maneuver& m) {}

    void tick() {
        if (module) module->activate();
    }
};

// Rule of 5
class CargoHold {
private:
    int* cargo;
    int size;

public:
    CargoHold(int s) : size(s) {
        cargo = new int[size];
        for (int i = 0; i < size; ++i) {
            cargo[i] = 0;
        }
    }

    ~CargoHold() {
        delete[] cargo;
    }

    CargoHold(const CargoHold& other) : size(other.size) {
        cargo = new int[size];
        for (int i = 0; i < size; ++i) {
            cargo[i] = other.cargo[i];
        }
    }

    CargoHold& operator=(const CargoHold& other) {
        if (this == &other) return *this;
        delete[] cargo;
        size = other.size;
        cargo = new int[size];
        for (int i = 0; i < size; ++i) {
            cargo[i] = other.cargo[i];
        }
        return *this;
    }

    CargoHold(CargoHold&& other) noexcept
        : cargo(other.cargo), size(other.size) {
        other.cargo = nullptr;
        other.size = 0;
    }

    CargoHold& operator=(CargoHold&& other) noexcept {
        if (this == &other) return *this;

        delete[] cargo;
        cargo = other.cargo;
        size = other.size;
        other.cargo = nullptr;
        other.size = 0;
        return *this;
    }
};

// Rule of zero
class ModernCargoHold {
private:
    std::vector<int> cargo_;

public:
    ModernCargoHold() = default;

    void addCargo(const int& p) { cargo_.push_back(p); }
    int getSize() const { return static_cast<int>(cargo_.size()); }
    const int& getCargo(int i) const { return cargo_.at(i); }
};

class Fleet {
private:
    std::vector<std::unique_ptr<Spacecraft>> ships_;

public:
    void addShip(std::unique_ptr<Spacecraft> ship) {
        ships_.push_back(std::move(ship));
    }
};

// Exception Safety and RAII
class DockingException : public std::runtime_error {
public:
    DockingException(const string& msg) : std::runtime_error(msg) {}
};


int main() {
    return 0;
}
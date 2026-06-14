#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

using namespace std;

class Maneuver {};

class DockingException : public std::runtime_error {
public:
    DockingException(const string& msg) : std::runtime_error(msg) {}
};

class FuelTank {
private:
    int fuelLevel;
public:
    FuelTank() : fuelLevel(0) { cout << "FuelTank created\n"; }
    ~FuelTank() { cout << "FuelTank destroyed\n"; }
    int getFuel() const { return fuelLevel; }
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

    void dock() {
        if (tank.getFuel() < 10) {
            throw DockingException("Docking failed: Insufficient fuel!");
        }
        cout << "Docking successful!\n";
    }
};

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

    void destroyOneShip() {
        if (!ships_.empty()) {
            cout << "\nDestroying one ship from Fleet\n";
            ships_.pop_back();
        }
    }
};

int main() {
    cout << "--- Starting Simulation ---" << endl;

    Fleet myFleet;

    myFleet.addShip(make_unique<Spacecraft>());
    myFleet.addShip(make_unique<Spacecraft>());

    try {
        cout << "Creating a temporary ship..." << endl;
        unique_ptr<Spacecraft> temporaryShip = make_unique<Spacecraft>();

        cout << "Creating a plasma engine..." << endl;
        unique_ptr<Engine> plasmaEngine = make_unique<Engine>("Plasma", 100);

        temporaryShip->mountModule(plasmaEngine.get());

        Maneuver basicManeuver;
        temporaryShip->executeManeuver(basicManeuver);

        temporaryShip->tick();

        cout << "Trying to dock the ship..." << endl;
        temporaryShip->dock();

    }
    catch (const DockingException& error) {
        cout << "An error happened: " << error.what() << endl;
    }

    myFleet.destroyOneShip();

    cout << "--- End of Simulation ---" << endl;
    return 0;
}
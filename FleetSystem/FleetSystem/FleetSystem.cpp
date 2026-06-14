#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Maneuver {};

class FuelTank {
public:
    FuelTank() { cout << "FuelTank creado\n"; }
    ~FuelTank() { cout << "FuelTank destruido\n"; }
};

class Telemetry {
public:
    Telemetry() { cout << "Telemetry creado\n"; }
    ~Telemetry() { cout << "Telemetry destruido\n"; }
};

class Entity {
public:
    Entity() { cout << "Entity creado\n"; }
    virtual ~Entity() { cout << "Entity destruido\n"; }
};

class Module {
protected:
    string name;
    int power;
public:
    Module(string n, int p) : name(n), power(p) { cout << "Module creado\n"; }
    virtual ~Module() { cout << "Module destruido\n"; }
    virtual void activate() { cout << "Modulo activado\n"; }
};

class Engine final : public Module {
public:
    Engine(string n, int p) : Module(n, p) { cout << "Engine creado\n"; }
    ~Engine() override { cout << "Engine destruido\n"; }
    void activate() override { cout << "Motor " << name << " encendido!\n"; }
};

class Shield final : public Module {
public:
    Shield(string n, int p) : Module(n, p) { cout << "Shield creado\n"; }
    ~Shield() override { cout << "Shield destruido\n"; }
    void activate() override { cout << "Escudo " << name << " encendido!\n"; }
};

class Spacecraft : public Entity {
private:
    FuelTank tank;
    Telemetry telemetry;
    Module* module;

public:
    Spacecraft() : Entity(), module(nullptr) { cout << "Spacecraft creado\n"; }
    ~Spacecraft() override { cout << "Spacecraft destruido\n"; }

    void mountModule(Module* m) { module = m; }
    void executeManeuver(const Maneuver& m) {}

    void tick() {
        if (module) module->activate();
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

int main() {
    return 0;
}
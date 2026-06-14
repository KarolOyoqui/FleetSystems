# SpaceFleet-cpp

# Project Description
This is an assignment to practice the concepts from my Object-Oriented Programming class. It involves completing each of the quizzes done in class to reinforce the concepts.
# System Operation
* **Safety Protocols:** The program verifies fuel levels and engine status before allowing any flight maneuvers.
* **User-friendly:** Spacecrafts and modules can be registered, tracked, and modified easily using a clean console interface.
* **Component Docking:** The system validates module compatibility and throws exceptions if safety criteria aren't met during docking.

# OOP concepts
For this project, I applied what we learned in class like this:

* **Inheritance and Abstraction:** My Entity class is the parent class, and Spacecraft is the child. Also, Module is a base class from which Engine and Shield inherit their properties to recycle code.
* **Polymorphism:** I use it when activating ship upgrades. I mount components using pointers of the parent class (Module*) and call activate() so each one executes its own unique systems.
* **OOP Relationships (Composition, Aggregation, and Dependency):** I applied all types of connections between classes:
  1. **Composition:** Inside Spacecraft, the FuelTank and Telemetry are normal objects. If the ship is destroyed, they die with it.
  2. **Aggregation:** The ship holds a Module* pointer.The module belongs to the ship, but if the ship dies, the module can still exist on its own.
  3. **Dependency:** The ship uses a Maneuver object only as a temporary parameter inside a function to run a quick calculation and then drops it.
* **Rule of 5 (Manual Memory):** In CargoHold, I managed raw pointers (int*) and dynamic arrays with new and delete[]. I implemented the destructor, copy, and move constructors/assignments to avoid leaks.
* **Exceptions:** I created an error called DockingException. If a spacecraft attempts a dangerous docking maneuver without fuel, it throws this exception and the try...catch prevents the program from crashing.

# Memory Management (Rule of Zero & RAII)
To handle the core simulation memory, I decided to use the **Rule of Zero** and modern C++ smart pointers:
1. **std::vector** for storing lists of ships and cargo items.
2. **std::unique_ptr** inside the Fleet class to handle individual Spacecraft objects safely.
3. **std::string** for textual data like module names.
  
# UML Class Diagram
<img width="840" height="712" alt="image" src="https://github.com/user-attachments/assets/abee98be-36ea-4ba5-a848-729cf25aac1a" />


# Project Structure

**Main.cpp**
It is the main file that handles everything. It initializes the fleet hangar, registers the spaceships, mounts their modules, and runs the main loop simulation.

**Entity.h & Spacecraft.h** Here the ships are defined using inheritance. Entity acts as the base, and Spacecraft adds the internal fuel tank, telemetry tools, and module slots.

**Module.h (Engine.h / Shield.h)**
Here the data for the upgrades is stored. Module is the base class, while Engine and Shield act as specific components that change how the ship behaves.

**Fleet.h**
It acts as the main manager holding all active ships securely using smart containers (unique_ptr).

**CargoHold.h & ModernCargoHold.h**
* CargoHold demonstrates traditional manual memory tracking (Rule of 5).
* ModernCargoHold achieves the same goal but uses modern std::vector automation (Rule of Zero).

# Build and Compilation Instructions
To ensure the program compiles correctly, use the following command in your terminal:

```bash
g++ -std=c++14 -Wall Main.cpp -o fleet_simulation

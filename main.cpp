#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <random>
#include <string>
#include <algorithm>

// Singleton Pattern: Meadow Class
class Meadow {
private:
    static Meadow* instance;
    std::map<int, std::string> colonies; // Colony ID and Species
    std::map<int, std::map<std::string, int>> resources; // Colony resources
    std::map<int, std::map<std::string, int>> colonyStats; // Colony statistics: workers, warriors, ant kills, colony kills, ticks alive
    std::map<int, std::map<int, std::string>> colonyKills; // Colony ID and killed colony mapping
    Meadow() {}

public:
    static Meadow* getInstance() {
        if (!instance) {
            instance = new Meadow();
        }
        return instance;
    }

    int spawnColony(int x, int y, const std::string& species) {
        int id = colonies.size() + 1;
        colonies[id] = species;
        resources[id] = {}; // Initialize empty resources
        colonyStats[id] = {{"workers", 0}, {"warriors", 0}, {"antKills", 0}, {"colonyKills", 0}, {"ticksAlive", 0}};
        colonyKills[id] = {}; // Initialize empty colony kills
        std::cout << "Colony " << id << " of species " << species << " spawned at (" << x << ", " << y << ").\n";
        return id;
    }

    void giveResources(int id, const std::string& resource, int amount) {
        if (colonies.find(id) != colonies.end()) {
            resources[id][resource] += amount;
            if (resource == "worker") {
                colonyStats[id]["workers"] += amount;
            } else if (resource == "warrior") {
                colonyStats[id]["warriors"] += amount;
            }
            std::cout << "Gave " << amount << " of " << resource << " to colony " << id << ".\n";
        } else {
            std::cout << "Colony " << id << " does not exist.\n";
        }
    }

    void recordKill(int killerId, int killedId, const std::string& killedSpecies) {
        if (colonies.find(killerId) != colonies.end() && colonies.find(killedId) != colonies.end()) {
            colonyStats[killerId]["colonyKills"] += 1;
            colonyKills[killerId][killedId] = killedSpecies;
            std::cout << "Colony " << killerId << " killed colony " << killedId << ".\n";
        } else {
            std::cout << "Invalid colony ID for kill operation.\n";
        }
    }

    void recordAntKill(int id) {
        if (colonies.find(id) != colonies.end()) {
            colonyStats[id]["antKills"] += 1;
            std::cout << "Colony " << id << " killed an ant.\n";
        } else {
            std::cout << "Colony " << id << " does not exist.\n";
        }
    }

    void displayColonySummary(int id) {
        if (colonies.find(id) != colonies.end()) {
            std::cout << "Colony ID: " << id << "\n";
            std::cout << "Species: " << colonies[id] << "\n";
            std::cout << "Workers: " << colonyStats[id]["workers"] << "\n";
            std::cout << "Warriors: " << colonyStats[id]["warriors"] << "\n";
            std::cout << "Ant Kills: " << colonyStats[id]["antKills"] << "\n";
            std::cout << "Colony Kills: " << colonyStats[id]["colonyKills"] << " (";
            for (const auto& [killedId, killedSpecies] : colonyKills[id]) {
                std::cout << killedId << ":" << killedSpecies << " ";
            }
            std::cout << ")\n";
            std::cout << "Ticks alive: " << colonyStats[id]["ticksAlive"] << "\n";
            std::cout << "Status: Alive\n";
        } else {
            std::cout << "Colony " << id << " does not exist.\n";
        }
    }

    void incrementTick(int id) {
        if (colonyStats.find(id) != colonyStats.end()) {
            colonyStats[id]["ticksAlive"] += 1;
        }
    }

    const std::map<int, std::string>& getColonies() const {
        return colonies;
    }
};

Meadow* Meadow::instance = nullptr;

// Builder Pattern: AntFarm Class
class AntFarm {
public:
    class Builder {
    private:
        int rooms;
        int restingCapacity;

    public:
        Builder& setRooms(int numRooms) {
            rooms = numRooms;
            return *this;
        }

        Builder& setRestingCapacity(int capacity) {
            restingCapacity = capacity;
            return *this;
        }

        AntFarm build() {
            return AntFarm(rooms, restingCapacity);
        }
    };

    void display() {
        std::cout << "AntFarm with " << rooms << " rooms and resting capacity " << restingCapacity << ".\n";
    }

private:
    int rooms;
    int restingCapacity;
    AntFarm(int rooms, int capacity) : rooms(rooms), restingCapacity(capacity) {}
};

// Factory Pattern: Ant and Ant Types
class Ant {
public:
    virtual void performAction() = 0;
    virtual ~Ant() {}
};

class Drone : public Ant {
public:
    void performAction() override {
        std::cout << "Drone is foraging for food.\n";
    }
};

class Warrior : public Ant {
public:
    void performAction() override {
        std::cout << "Warrior is battling enemies.\n";
    }
};

class Queen : public Ant {
public:
    void performAction() override {
        std::cout << "Queen is spawning eggs.\n";
    }
};

class AntFactory {
public:
    std::unique_ptr<Ant> createAnt(const std::string& type) {
        if (type == "Drone") {
            return std::make_unique<Drone>();
        } else if (type == "Warrior") {
            return std::make_unique<Warrior>();
        } else if (type == "Queen") {
            return std::make_unique<Queen>();
        } else {
            return nullptr;
        }
    }
};

// Decorator Pattern: Attributes
class AntAttributes {
public:
    virtual void describe() = 0;
    virtual ~AntAttributes() {}
};

class BaseAttributes : public AntAttributes {
public:
    void describe() override {
        std::cout << "Basic ant attributes.\n";
    }
};

class SpeedDecorator : public AntAttributes {
private:
    std::shared_ptr<AntAttributes> base;

public:
    SpeedDecorator(std::shared_ptr<AntAttributes> baseAttr) : base(baseAttr) {}

    void describe() override {
        base->describe();
        std::cout << "Faster speed attribute added.\n";
    }
};

class StrengthDecorator : public AntAttributes {
private:
    std::shared_ptr<AntAttributes> base;

public:
    StrengthDecorator(std::shared_ptr<AntAttributes> baseAttr) : base(baseAttr) {}

    void describe() override {
        base->describe();
        std::cout << "Increased strength attribute added.\n";
    }
};

// Mediator Pattern: Tick Simulation
class Mediator {
public:
    void performTick(std::vector<std::shared_ptr<Ant>>& ants) {
        std::shuffle(ants.begin(), ants.end(), std::mt19937{std::random_device{}()});
        for (auto& ant : ants) {
            ant->performAction();
        }
    }
};

// CLI Interface
void handleCLI() {
    Meadow* meadow = Meadow::getInstance();
    AntFactory factory;
    Mediator mediator;
    std::vector<std::shared_ptr<Ant>> ants;

    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        if (command.find("spawn") == 0) {
            int x, y;
            std::string species;
            char speciesBuff[50];
            std::sscanf(command.c_str(), "spawn %d %d %s", &x, &y, speciesBuff);
            species = speciesBuff;
            int id = meadow->spawnColony(x, y, species);
            ants.push_back(factory.createAnt("Queen"));
        } else if (command.find("give") == 0) {
            int id, amount;
            char resource[50];
            std::sscanf(command.c_str(), "give %d %s %d", &id, resource, &amount);
            meadow->giveResources(id, resource, amount);
        } else if (command.find("recordAntKill") == 0) {
            int id;
            std::sscanf(command.c_str(), "recordAntKill %d", &id);
            meadow->recordAntKill(id);
        } else if (command.find("recordKill") == 0) {
            int killerId, killedId;
            char killedSpecies[50];
            std::sscanf(command.c_str(), "recordKill %d %d %s", &killerId, &killedId, killedSpecies);
           meadow->recordKill(killerId, killedId, killedSpecies);
        } else if (command.find("summary") == 0) {
            int id;
            std::sscanf(command.c_str(), "summary %d", &id);
            meadow->displayColonySummary(id);
        } else if (command.find("tick") == 0) {
            int ticks = 1;
            std::sscanf(command.c_str(), "tick %d", &ticks);
            for (int t = 0; t < ticks; ++t) {
                for (const auto& [id, species] : meadow->getColonies()) {
                    meadow->incrementTick(id); // Update ticks alive for each colony
                }
                mediator.performTick(ants);
            }
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command.\n";
        }
    }
}


int main() {
    handleCLI();
    return 0;
}


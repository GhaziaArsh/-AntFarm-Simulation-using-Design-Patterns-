# -AntFarm-Simulation-using-Design-Patterns-
The AntFarm Simulation System models ant colony behaviors using C++ and various design patterns, including Singleton, Factory, Builder, Decorator, and Mediator. It simulates activities such as foraging, building, and defending. The command-line interface (CLI) allows for interactive user engagement, creating an immersive simulation experience.
# Ant Farm Simulation System

## Overview
The Ant Farm Simulation System simulates the behavior and management of ants in a colony. The system incorporates several design patterns to model activities such as foraging, building, and defending the colony.

## Design Patterns Used
1. **Singleton Pattern**:
   - **Class**: `Meadow`
   - **Purpose**: Ensures there is only one instance of the `Meadow` class, which manages all ant colonies.

2. **Builder Pattern**:
   - **Class**: `AntFarm`
   - **Purpose**: Provides a flexible way to construct complex `AntFarm` objects with various configurations.

3. **Factory Pattern**:
   - **Class**: `AntFactory`
   - **Purpose**: Creates different types of ants (`Drone`, `Warrior`, `Queen`).

4. **Decorator Pattern**:
   - **Class**: `AntAttributes` and its decorators (`SpeedDecorator`, `StrengthDecorator`)
   - **Purpose**: Dynamically adds attributes to ants, such as increased speed or strength.

5. **Mediator Pattern**:
   - **Class**: `Mediator`
   - **Purpose**: Manages interactions and communications between different ants during each tick of the simulation.

## Class Descriptions

### Meadow Class
- **Pattern**: Singleton
- **Description**: Manages the creation and statistics of ant colonies.
- **Key Methods**:
  - `getInstance()`: Returns the singleton instance of the `Meadow`.
  - `spawnColony(int x, int y, const std::string& species)`: Spawns a new colony at specified coordinates.
  - `giveResources(int id, const std::string& resource, int amount)`: Allocates resources to a specific colony.
  - `recordKill(int killerId, int killedId, const std::string& killedSpecies)`: Records a colony kill.
  - `recordAntKill(int id)`: Records an ant kill.
  - `displayColonySummary(int id)`: Displays a detailed summary of a specific colony.
  - `incrementTick(int id)`: Increments the tick count for a specific colony.

### AntFarm Class
- **Pattern**: Builder
- **Description**: Constructs and configures ant farms.
- **Key Methods**:
  - `Builder& setRooms(int numRooms)`: Sets the number of rooms in the ant farm.
  - `Builder& setRestingCapacity(int capacity)`: Sets the resting capacity of the ant farm.
  - `build()`: Constructs the ant farm with the specified configuration.
  - `display()`: Displays the configuration of the ant farm.

### Ant Class and Subclasses
- **Pattern**: Factory
- **Description**: Represents different types of ants and their actions.
- **Subclasses**: `Drone`, `Warrior`, `Queen`
- **Key Methods**:
  - `performAction()`: Defines specific actions for each type of ant.

### AntFactory Class
- **Pattern**: Factory
- **Description**: Creates different types of ants based on the given type.
- **Key Methods**:
  - `createAnt(const std::string& type)`: Creates and returns an ant of the specified type.

### AntAttributes Class and Decorators
- **Pattern**: Decorator
- **Description**: Adds attributes to ants dynamically.
- **Key Methods**:
  - `describe()`: Describes the attributes of an ant.

### Mediator Class
- **Pattern**: Mediator
- **Description**: Manages the actions of all ants during each tick in the simulation.
- **Key Methods**:
  - `performTick(std::vector<std::shared_ptr<Ant>>& ants)`: Shuffles and performs actions for all ants.

## Command-Line Interface (CLI)
The CLI allows users to interact with the Ant Farm Simulation System using various commands.

- **Commands**:
  - `spawn X Y T`: Spawns a new colony at position (X, Y) of species T.
  - `give I R A`: Gives the colony identified by I resource R of amount A.
  - `recordAntKill I`: Records an ant kill for colony I.
  - `recordKill I J S`: Records that colony I killed colony J of species S.
  - `summary I`: Displays a summary of colony I.
  - `tick T`: Performs T tick operations (or one tick if T is not specified).
  - `exit`: Exits the CLI.

## Example Usage and Output
```plaintext
Enter command: spawn 14 -32 Killer
Colony 1 of species Killer spawned at (14, -32).

Enter command: spawn 15 -30 Pansy
Colony 2 of species Pansy spawned at (15, -30).

Enter command: give 2 worker 4
Gave 4 of worker to colony 2.

Enter command: tick 25
(Executing tick operations...)

Enter command: recordAntKill 2
Colony 2 killed an ant.

Enter command: recordKill 1 2 Pansy
Colony 1 killed colony 2.

Enter command: summary 1
Colony ID: 1
Species: Killer
Workers: 14
Warriors: 10
Ant Kills: 18
Colony Kills: 2 (2:Pansy 4:Gatherer)
Ticks alive: 143
Status: Alive

Enter command: summary 2
Colony ID: 2
Species: Pansy
Workers: 4
Warriors: 0
Ant Kills: 2
Colony Kills: 0
Ticks alive: 25
Status: Killed by 1:Killer

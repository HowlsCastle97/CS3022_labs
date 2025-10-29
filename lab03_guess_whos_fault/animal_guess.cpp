#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

class AnimalUtil {
public:
    enum Animal { DOG = 1, CAT, BIRD, FISH };

    static const char* toStr(Animal a) {
        switch (a) {
            case DOG:  return "Dog";
            case CAT:  return "Cat";
            case BIRD: return "Bird";
            case FISH: return "Fish";
            default:   return "Unknown";
        }
    }
};

const std::string staticWelcomeMessage = "Welcome to the Animal Guesser!";

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << staticWelcomeMessage << "\n";
    std::cout << "Guess the Animal! (1: Dog, 2: Cat, 3: Bird, 4: Fish)\n";
    std::cout << "Enter 0 to quit.\n";

    std::cout << "[DEBUG] staticWelcomeMessage address: "
          << static_cast<const void*>(staticWelcomeMessage.c_str()) << "\n";

    // ERROR #1: pointer must be initialized (removed bad deref)
    AnimalUtil::Animal* mysteryAnimal = nullptr;
    // ERROR #2: removed nullptr dereference

    while (true) {
        // ERROR #3: delete old allocation before new one (no leak)
        delete mysteryAnimal;
        mysteryAnimal =
            new AnimalUtil::Animal(static_cast<AnimalUtil::Animal>(1 + std::rand() % 4));

        std::cout << "\nYour guess: ";

        int guess = -1;
        if (!(std::cin >> guess)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; please enter 1, 2, 3, 4, or 0.\n";
            continue;
        }

        if (guess == 0) {
            std::cout << "Bye!\n";
            break;
        }

        if (guess < 1 || guess > 4) {
            std::cout << "Please enter 1, 2, 3, 4, or 0.\n";
            continue;
        }

        // ----- Q3 TEMP DEBUG -----
        std::cout << "[DEBUG] &mysteryAnimal (address of pointer var on stack): "
                  << &mysteryAnimal << "\n";
        std::cout << "[DEBUG] mysteryAnimal (heap address stored in pointer): "
                  << mysteryAnimal << "\n";
        std::cout << "[DEBUG] *mysteryAnimal (enum value at heap address): "
                  << static_cast<int>(*mysteryAnimal) << " -> "
                  << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        // -------------------------

        if (*mysteryAnimal == static_cast<AnimalUtil::Animal>(guess)) {
            std::cout << "Correct! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        } else {
            std::cout << "Wrong! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        }
    }

    delete mysteryAnimal;
    return 0;
}

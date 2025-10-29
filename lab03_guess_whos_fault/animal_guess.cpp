#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

// Toggle this to 0 to silence the debug/diagram prints for your final run
#define SHOW_DIAGNOSTICS 1

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

#if SHOW_DIAGNOSTICS
    // Q4: Print where the static storage lives (address of first char in the string)
    std::cout << "[diag] &staticWelcomeMessage[0]: "
              << static_cast<const void*>(&staticWelcomeMessage[0]) << "\n";
#endif

    // Error #1 fix: initialize pointer; comment out the bad deref
    AnimalUtil::Animal* mysteryAnimal = nullptr;
    /*
    std::cout << "The animal is initialized to: "
              << AnimalUtil::toStr(*mysteryAnimal) << "\n";
    */

    // Error #2 fix: comment out the null deref
    mysteryAnimal = nullptr;
    /*
    std::cout << "The animal should initally be nothing: "
              << AnimalUtil::toStr(*mysteryAnimal) << "\n";
    */

    while (true) {
        // Error #3 fix: prevent leak before creating a new animal each round
        delete mysteryAnimal;
        mysteryAnimal =
            new AnimalUtil::Animal(static_cast<AnimalUtil::Animal>(1 + std::rand() % 4));

#if SHOW_DIAGNOSTICS
        // Q3 diagnostics: show the three memory items each round
        std::cout << "[diag] &mysteryAnimal (address of pointer var on stack): "
                  << static_cast<const void*>(&mysteryAnimal) << "\n";
        std::cout << "[diag] mysteryAnimal (address pointer points to on heap): "
                  << static_cast<const void*>(mysteryAnimal) << "\n";
        std::cout << "[diag] *mysteryAnimal (enum value at that heap address): "
                  << static_cast<int>(*mysteryAnimal) << " -> "
                  << AnimalUtil::toStr(*mysteryAnimal) << "\n";
#endif

        std::cout << "\nYour guess: ";

        int guess = -1;
        if (!(std::cin >> guess)) {
            // input type validation
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; try again.\n";
            continue;
        }

        if (guess == 0) {
            std::cout << "Bye!\n";
            break;
        }

        // Range validation: only 1,2,3,4 allowed (or 0 to quit)
        if (guess < 1 || guess > 4) {
            std::cout << "Please enter 1, 2, 3, or 4 (or 0 to quit).\n";
            continue;
        }

        if (*mysteryAnimal == static_cast<AnimalUtil::Animal>(guess)) {
            std::cout << "Correct! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        } else {
            std::cout << "Wrong! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        }
    }

    delete mysteryAnimal;  // free last allocation
    return 0;
}

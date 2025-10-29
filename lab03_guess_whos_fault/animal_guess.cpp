#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

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

    // Error #1 fix: initialize pointer; comment out the bad deref
    AnimalUtil::Animal* mysteryAnimal = nullptr;
    // std::cout << "The animal is initialized to: "
    //           << AnimalUtil::toStr(*mysteryAnimal) << "\n";

    // Error #2 fix: comment out the null deref
    mysteryAnimal = nullptr;
    // std::cout << "The animal should initally be nothing: "
    //           << AnimalUtil::toStr(*mysteryAnimal) << "\n";

    while (true) {
        // Error #3 fix: prevent leak before creating a new animal each round
        delete mysteryAnimal;
        mysteryAnimal =
            new AnimalUtil::Animal(static_cast<AnimalUtil::Animal>(1 + std::rand() % 4));

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

        // Validation, no other entries than 0,1,2,3,4 allowed!
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

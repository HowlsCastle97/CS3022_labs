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

    // ERROR #1: pointer must be initialized (removed bad deref)
    AnimalUtil::Animal* mysteryAnimal = nullptr;

    // ERROR #2: removed nullptr dereference that printed *mysteryAnimal

    while (true) {
        // ERROR #3: delete old allocation before new one (no leak)
        delete mysteryAnimal;
        mysteryAnimal =
            new AnimalUtil::Animal(static_cast<AnimalUtil::Animal>(1 + std::rand() % 4));

        std::cout << "\nYour guess: ";

        int guess = -1;
        // non-numeric input
        if (!(std::cin >> guess)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; please enter 1, 2, 3, 4, or 0.\n";
            continue;
        }

        // exit
        if (guess == 0) {
            std::cout << "Bye!\n";
            break;
        }

        // range check
        if (guess < 1 || guess > 4) {
            std::cout << "Please enter 1, 2, 3, 4, or 0.\n";
            continue;
        }

        // compare only for valid guesses
        if (*mysteryAnimal == static_cast<AnimalUtil::Animal>(guess)) {
            std::cout << "Correct! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        } else {
            std::cout << "Wrong! It was " << AnimalUtil::toStr(*mysteryAnimal) << "\n";
        }
    }

    delete mysteryAnimal;
    return 0;
}

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

    // Pointer starts safe (keeps the lab’s pointer semantics)
    AnimalUtil::Animal* mysteryAnimal = nullptr;

    while (true) {
        // Fix for error #3: free old before new (no leak)
        delete mysteryAnimal;
        mysteryAnimal =
            new AnimalUtil::Animal(static_cast<AnimalUtil::Animal>(1 + std::rand() % 4));

        std::cout << "\nYour guess: ";

        int guess = -1;
        if (!(std::cin >> guess)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input; try again.\n";
            continue;
        }

        if (guess == 0) {
            std::cout << "Bye!\n";
            break;
        }

        // Only allow 1–4 (or 0 to quit)
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

    delete mysteryAnimal;
    return 0;
}

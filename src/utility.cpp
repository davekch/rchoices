#include "utility.hpp"

Chooser::Chooser() {
    std::random_device device;
    std::mt19937 gen(device());
    generator = gen;
}

int Chooser::random_uniform_choice(std::vector<int> *choices) {
    // return a randomly selected element from choices or 0 if choices is empty
    if (choices->size() == 0) {
     return 0;
    }
    std::uniform_int_distribution<int> dist(0, choices->size()-1);
    return choices->at(dist(generator));
}

int Chooser::random_gaussian(float mean, float spread) {
    std::normal_distribution<float> dist(mean, spread);
    return (int) round(dist(generator));
}

float gauss(float x, float mean, float sigma) {
    // something proportional to a gauss distribution
    return 0.8 * exp(-pow((x - mean), 2) / (2 * pow(sigma, 2)));
}

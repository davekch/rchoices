#pragma once
#include<vector>
#include<random>

class Chooser {
private:
 std::mt19937 generator;
public:
 Chooser();
 int random_uniform_choice(std::vector<int> *choices);
 int random_gaussian(float mean, float spread);
};

float gauss(float x, float mean, float sigma);

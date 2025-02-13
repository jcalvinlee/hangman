#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include <set>
#include <algorithm>

static void print(std::vector<char>, std::vector<bool>);

int main()
{
    std::ifstream file("words.txt");
    std::string word;
    std::vector<std::string> words;

    if (file.is_open())
    {
        while (file >> word)
        {
            words.push_back(word);
        }
        file.close();
    } 
    else
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    if (words.empty())
    {
        std::cerr << "No words found in file" << std::endl;
        return 1;
    }

    // Create random engine and distribution
    std::random_device rd;  // Obtain a random seed from hardware
    std::mt19937 gen(rd()); // Initialize the generator with the seed
    std::uniform_int_distribution<> distrib(0, words.size() - 1);

    // Get a random index
    int randomIndex = distrib(gen);

    std::string answer{ words[randomIndex] };
    std::vector<char> answer_vector(answer.begin(), answer.end());
    std::vector<bool> answer_map(answer_vector.size(), false);
    std::set<char> used{};

    int lives{ 5 };

    while (lives > 0 && !std::all_of(answer_map.begin(), answer_map.end(), [](bool flag) { return flag; }))
    {
        print(answer_vector, answer_map);
        std::cout << "Enter a character: ";
        char choice{};
        std::cin >> choice;

        if (used.count(choice))
        {
            std::cout << choice << " was already used!" << std::endl;
            continue;
        }

        used.insert(choice);

        int64_t count{ std::count(answer_vector.begin(), answer_vector.end(), choice) };
        if (count == 0)
        {
            --lives;
            std::cout << "The word does not contain: " << choice << ", " << lives << " lives left." << std::endl;
        }
        else
        {
            for (size_t i = 0; i < answer_vector.size(); ++i)
            {
                if (answer_vector[i] == choice)
                {
                    answer_map[i] = true;
                }
            }
        }
    }

    if (lives == 0)
    {
        std::cout << "You lose! The word was: " << answer << std::endl;
    }
    else
    {
        std::cout << "You won!" << std::endl;
    }

    return 0;
}

static void print(std::vector<char> answer_vector, std::vector<bool> answer_map)
{
    for (size_t i = 0; i < answer_vector.size(); ++i)
    {
        if (answer_map[i])
        {
            std::cout << answer_vector[i] << ' ';
        }
        else
        {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
}


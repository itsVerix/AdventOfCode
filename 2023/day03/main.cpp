#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <set>
#include <map>

bool is_symbol(char c)
{
    return (c != '.' && !std::isdigit(c));
}

void gear_of_number(std::set<std::pair<int, int>>& gears, int i, int j, std::vector<std::string> input)
{
    for (int a = i - 1; a <= i + 1; ++a) {
        for (int b = j - 1; b <= j + 1; ++b) {
            if (input[a][b] == '*')
                gears.insert({a, b});
        }
    }
}

int part1(std::vector<std::string> input)
{
    int row_size = input[0].size();
    int sum = 0;

    input.insert(input.begin(), std::string(row_size, '.'));
    input.emplace_back(row_size, '.');

    for(int i = 0; i < input.size(); ++i)
    {
        input[i].insert(input[i].begin(), '.');
    }

    for(int i = 0; i < input.size(); ++i)
    {
        input[i].push_back('.');
    }

    for(int i = 1; i < input.size() - 1; ++i)
    {
        std::string number;
        bool is_part_number = false;

        for(int j = 1; j < input[i].size() - 1; ++j)
        {
            char character = input[i][j];

            bool top_left = is_symbol(input[i - 1][j - 1]);
            bool top_center = is_symbol(input[i - 1][j]);
            bool top_right = is_symbol(input[i - 1][j + 1]);
            bool middle_left = is_symbol(input[i][j - 1]);
            bool middle_right = is_symbol(input[i][j + 1]);
            bool bottom_left = is_symbol(input[i + 1][j - 1]);
            bool bottom_center = is_symbol(input[i + 1][j]);
            bool bottom_right = is_symbol(input[i + 1][j + 1]);

            if(std::isdigit(character))
            {
                number += character;

                if(top_left || top_center || top_right || middle_left || middle_right || bottom_left || bottom_center || bottom_right)
                    is_part_number = true;
            }
            if(!std::isdigit(character) || j == row_size )
            {
                if(is_part_number && !number.empty() )
                {
                    sum += std::stoi(number);
                }
                number.clear();
                is_part_number = false;
            }
        }
    }
    return sum;
}

int part2(std::vector<std::string> input)
{
    int row_size = input[0].size();
    int sum = 0;

    input.insert(input.begin(), std::string(row_size, '.'));
    input.push_back(std::string(row_size, '.'));

    for(int i = 0; i < input.size(); ++i)
    {
        input[i].insert(input[i].begin(), '.');
    }

    for(int i = 0; i < input.size(); ++i)
    {
        input[i].push_back('.');
    }
    std::set<std::pair<int, int>> gears;

    std::map<std::pair<int, int>, std::vector<int>> gear_to_number;
    for(int i = 1; i < input.size() - 1; ++i)
    {
        std::string number;

        for(int j = 1; j < input[i].size() - 1; ++j)
        {
            char character = input[i][j];
            if(std::isdigit(character))
            {
                number += character;
                gear_of_number(gears, i, j, input);
            }

            if(!std::isdigit(character) || j == row_size )
            {
                if (!number.empty() && !gears.empty())
                {
                    for(auto p : gears)
                    {
                        gear_to_number[p].push_back(std::stoi(number));
                    }
                }
                gears.clear();
                number.clear();
            }
        }
    }

    for(const auto& p : gear_to_number)
    {
        if(!p.second.empty())
        {
            if(p.second.size() >= 2)
            {
                int multiple = 1;

                for(auto i : p.second)
                {
                    multiple *= i;
                }
                sum += multiple;
            }
        }
    }
    return sum;
}

int main()
{
    std::ifstream input("input.txt", std::ifstream::in);
    if (!input) {
        std::cerr << "Can't open 'input.txt' file!\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (input >> line) {
        lines.emplace_back(line);
    }
    input.close();

    std::cout << "The solution for part 1 is: " << part1(lines) <<'\n';
    std::cout << "The solution for part 2 is: " << part2(lines) <<'\n';
}

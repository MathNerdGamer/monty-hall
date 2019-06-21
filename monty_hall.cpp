/*
MIT License

Copyright (c) 2019 Math Nerd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <iostream>
#include <random>
#include <sstream>
#include <vector>

namespace math_nerd
{
    struct prize
    {
        enum
        {
            goat,
            car
        };
    };
}

using namespace std;
using namespace math_nerd;

int main(int argc, char **argv)
{
    int total_sims{ 1000 };
    constexpr int doors{ 3 };

    {   // Scope for stringstream.
        stringstream buf;

        switch( argc )
        {
            case 2:
            {
                buf << argv[1];
                buf >> total_sims;
                
                if( total_sims > 1000000000 )
                {
                    total_sims = 1000000000;
                }
                else if( total_sims < 10000 )
                {
                    total_sims = 10000;
                }

                break;
            }

            default:
            {
                // BLANK
            }
        }
    }   // End of scope for stringstream.

    random_device seed{};

    mt19937 rng{ seed() };

    uniform_int_distribution<int> select_door(0, 2);

    int successes{ 0 };

    long double win_pct{ 0.0 };

    for( auto sim{ 0 }; sim < total_sims; ++sim )
    {
        // Set up prizes
        vector<int> door(doors, 0);
        for( auto it{ 0 }; it < doors; ++it )
        {
            door[it] = prize::goat;
        }
        door[select_door(rng)] = prize::car;

        // Contestant selects a door
        auto contestant = select_door(rng);

        // Here, Monty Hall opens all doors besides the door the contestant chose and one other.
        // This other door must be the car if the contestant's selection was a goat. Therefore,
        if( door[contestant] == prize::goat )
        {
            ++successes;
        }
    }

    win_pct = static_cast<long double>(successes) / total_sims;

    std::cout << "Result: " << successes << " / " << total_sims << '\n';

    std::cout << "Using the optimal strategy, to swap after a goat is revealed, one wins the car " << 100*win_pct << "% of the time.\n";

    return EXIT_SUCCESS;
}

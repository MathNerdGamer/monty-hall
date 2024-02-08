#include <iostream>
#include <random>
#include <sstream>
#include <vector>

enum class prize
{
    goat,
    car
};

using namespace std;

int main( int argc, char **argv )
{
    int total_sims{ 1000 };
    constexpr int doors{ 3 };

    {   // Scope for stringstream.
        stringstream buf;

        switch ( argc )
        {
            case 2:
            {
                buf << argv[1];
                buf >> total_sims;

                if ( total_sims > 1000000000 )
                {
                    total_sims = 1000000000;
                }
                else if ( total_sims < 10000 )
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

    uniform_int_distribution<int> select_door( 0, 2 );

    int successes{ 0 };

    long double win_pct{ 0.0 };

    for ( auto sim{ 0 }; sim < total_sims; ++sim )
    {
        // Set up prizes - 2 with goats, 1 with car. The car door is picked at random.
        vector<prize> door( doors, prize::goat );
        door[select_door( rng )] = prize::car;

        // Contestant selects a door at random.
        auto contestant = select_door( rng );

        // Here, Monty Hall opens all doors besides the door the contestant chose and one other.
        // This other door must be the car if the contestant's selection was a goat. Therefore,
        if ( door[contestant] == prize::goat )
        {
            ++successes;
        }
    }

    win_pct = static_cast<long double>(successes) / total_sims;

    std::cout << "Result: " << successes << " / " << total_sims << '\n';

    std::cout << "Using the optimal strategy, to swap after a goat is revealed, one wins the car " << 100 * win_pct << "% of the time.\n";

    return EXIT_SUCCESS;
}

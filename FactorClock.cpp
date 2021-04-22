// FactorClock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Currently generating primes

#include <iostream>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now())
    {
    }

    void reset()
    {
        m_beg = clock_t::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
    }
};

int main()
{
    /*
    //defines if file is just 1 million or all 10 million
    //false == just 1 million
    //true == all 10 million

    bool primeFile{ false };

    //name of the prime file to use
    std::string primeFileName{};

    if (primeFile)
    {
        //primes up to 10 million
        primeFileName = "primes1.txt";

    }
    else
    {
        //primes up to 1 million
        primeFileName = "primes2.txt";
    }

    std::string line;
    std::ifstream myfile(primeFileName);
        while (getline(myfile, line))
    {
        std::cout << line << '\n';
    }
    */

    std::time_t t2 = std::time(0);

    long long bigNumber{t2};
    long long userInput{};
    
    std::cout << "Enter a positive integer. Enter 0 for default (current unix time)";
    std::cin >> userInput;
    if (userInput < 0)
    {
        std::cout << "Unable to factor negative numbers at this time "
            << "please input a postive integer\n";
        return -1;
    }
    if (userInput != 0)
    {
        bigNumber = userInput;
    }

    std::cout << "Input = " << bigNumber << '\n';

    Timer t;
    //start of timing

    while (bigNumber != 1)
    {
        if ((bigNumber % 2) == 0)
        {
            std::cout << "  " << 2 << '\n';
            bigNumber /= 2;
        }
        else
        {
            long long testNumber{ 3 };
            while (true)
            {
                if ((bigNumber % testNumber) == 0)
                {
                    std::cout << "  " << testNumber << '\n';
                    bigNumber /= testNumber;
                    break;
                }
                else
                {
                    testNumber += 2;
                }
            }
        }
    }
    std::cout << "done\n";
    
    //end of timing
    std::cout << "Time elapsed: " << t.elapsed() << " seconds.\n";

    //Just wait for the input. This is a dummy variable used to make the program
    //wait for the execution to finish
    int justWaitForTheInput;
    std::cin >> justWaitForTheInput;

    return 0;
}
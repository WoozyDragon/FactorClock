// FactorClock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Currently generating primes

#include <iostream>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

#include <thread>

std::vector<long long> factor(long long input)
{
    std::vector<long long> factors{};
    while (input != 1)
    {
        if ((input % 2) == 0)
        {
            factors.push_back(2);
            input /= 2;
        }
        else
        {
            long long testNumber{ 3 };
            while (true)
            {
                if ((input % testNumber) == 0)
                {
                    factors.push_back(testNumber);
                    input /= testNumber;
                    break;
                }
                else
                {
                    testNumber += 2;
                }
            }
        }
    }
    return factors;
}

std::vector<long long> values[20];
int times[20];
long long bigNumber{ std::time(0) };
int c_arrayIndex{ 0 };

void newFactor()
{  
    while (true) {
        if (times[c_arrayIndex] >= std::time(0) + 18)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }

        times[c_arrayIndex] = bigNumber;
        values[c_arrayIndex] = factor(bigNumber);


        ++c_arrayIndex;
        if (c_arrayIndex >= 20) c_arrayIndex = 0;

        ++bigNumber;
    }
}

void printFactors() {
    while (true) {
        auto start = std::chrono::system_clock::now();

        auto c_time = std::time(0);

        int x = std::distance(times, std::find(times, times + 20, c_time));

        std::cout << "Current Time is " << times[x] << '\n';
        std::cout << "Factors are : \n";

        for (auto singleFactor : values[x])
        {
            std::cout << " " << singleFactor << '\n';
        }

        auto end = std::chrono::system_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000) - (end - start));
    }
}



int main()
{

    std::thread calculations(newFactor);
    std::thread output(printFactors);

    calculations.join();
    output.join();

    return 0;
}
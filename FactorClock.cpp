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
        auto start = std::chrono::system_clock::now();

        if (bigNumber >= std::time(0) + 15)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            std::cout << "skip :: " << bigNumber;
            continue;
        }

        times[c_arrayIndex] = bigNumber;
        values[c_arrayIndex] = factor(bigNumber);


        ++c_arrayIndex;
        if (c_arrayIndex >= 20) c_arrayIndex = 0;

        ++bigNumber;

        auto end = std::chrono::system_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
        std::cout << " :: " << bigNumber << '\n';
    }
}

void printFactors() {
    while (true) {
        auto start = std::chrono::system_clock::now();

        auto c_time = std::time(0);
        std::cout << "aaa  " << c_time << '\n';
        
        int n = sizeof(times) / sizeof(times[0]);
        auto itr = std::find(times, times + n, c_time);
        int c_index{ 0 };

        if (itr == std::end(times))
        {
            std::cout << "FAIL";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            for (long long val : times)
            {
                std::cout << val << '\n';
            }
            std::cout << std::endl;
            continue;
        }
        else {
            c_index = std::distance(times, itr);;
        }

        //int c_index = std::distance(times, std::find(times, times + 20, c_time));
        std::cout << "xxx  " << c_index << '\n';

        if (times[c_index] < 100)
        {
            for (long long val : times)
            {
                std::cout << val << '\n';
            }
            std::cout << std::endl;
            //std::cout << values[x];
        }

        std::cout << "Current Time is " << times[c_index] << '\n';
        std::cout << "Factors are : \n";

        for (auto singleFactor : values[c_index])
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    std::thread output(printFactors);

    calculations.join();
    output.join();

    return 0;
}
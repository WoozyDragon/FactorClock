// FactorClock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Currently generating primes

#include <iostream>
#include <chrono>

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

extern std:list

bool isPrime(int test)
{
    //Is the number prime? Using the list of primes already known
}

int main()
{
    std::cout << "Hello World!\n";

    Timer t;

    //start of timing

    //end of timing

    std::cout << "Time elapsed: " << t.elapsed() << " seconds.";

    return 0;
}
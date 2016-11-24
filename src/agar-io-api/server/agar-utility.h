#pragma once
/*

AgarAPI Server version 0.0.0.1a
Copyright (c) 2016 Bhax Development team

*/

#ifndef AGAR_UTILITY_H_
#define AGAR_UTILITY_H_

#include <random>

namespace agar_io
{
    static std::default_random_engine generator;

    static inline int in_range(const int& min, const int& max) {
        std::uniform_int_distribution<> distribution(min, max);
        return distribution(generator);
    }

    static inline double in_range(const double& min, const double& max) {
        std::uniform_real_distribution<> distribution(min, max);
        return distribution(generator);
    }

    struct Border
    {
        double width;
        double height;
        double half_width;
        double half_height;
    };
} // namespace agar_io

#endif // AGAR_UTILITY_H_

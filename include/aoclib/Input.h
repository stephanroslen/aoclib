#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <type_traits>

template <typename Type>
std::istream& readCommaSeparatedLine(std::istream& is, auto iter)
{
    std::string line{};
    is >> line;
    std::replace(std::begin(line), std::end(line), ',', ' ');
    std::stringstream streamline{line};
    std::copy(std::istream_iterator<Type>{streamline}, std::istream_iterator<Type>{}, iter);
    return is;
}

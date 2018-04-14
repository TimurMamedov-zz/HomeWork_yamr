/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <fstream>
#include "functional"

class Reduce
{
public:
    Reduce(std::function<void()> reduceHandle_);

private:
    std::function<void()> reduceHandle;
};


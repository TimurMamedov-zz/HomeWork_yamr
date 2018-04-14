/*!
\file
\brief
*/
#pragma once
#include <vector>
#include <fstream>
#include <functional>

class Mapping
{
public:
    Mapping(std::function<void()> mapHandle_);

private:
    std::function<void()> mapHandle;
};


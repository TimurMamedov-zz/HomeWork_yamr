#include "Reduce.h"
#include <iostream>

Reduce::Reduce(std::function<void()> reduceHandle_)
    :reduceHandle(reduceHandle_)
{

}

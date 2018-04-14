#include "Mapping.h"
#include <iostream>

Mapping::Mapping(std::function<void()> mapHandle_)
    :mapHandle(mapHandle_)
{

}

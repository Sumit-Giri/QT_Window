#pragma once
#include "Triangulation.h"
class Writer
{
public:
    Writer();
    ~Writer();
    void writerStl(Triangulation& triangulation);

};
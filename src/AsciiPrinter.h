// ConsolePrinter Header file
#ifndef ASCIIPRINTER_H
#define ASCIIPRINTER_H

#include <string>
#include <vector>
#include "Monster.h"
#pragma once

class AsciiPrinter {
    public:
        AsciiPrinter();
        void printFightScreen(const Monster&, const Monster&, const int);
        void printInventory(const std::vector<Monster>&) const;
        void printInventory(const std::vector<const Monster*>&) const;
        ~AsciiPrinter();
    private:
};
#endif
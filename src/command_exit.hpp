#pragma once

#include "command.hpp"

class CommandExit : public Command
{
public:
    CommandExit() :
        Command("exit")
    {
        // do nothing
    }

    virtual bool run(const std::vector<std::string>& parts)
    {
        return false;
    }
};
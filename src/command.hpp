#pragma once

#include <string>
#include <memory>

#include "commons.hpp"
#include "messages.hpp"

class Command
{
public:

    static bool execute(const std::string& p_line, const std::vector<boost::shared_ptr<Command> >& p_commands)
    {
        std::vector<std::string> parts = split(p_line, ' ');

        if (parts.size() >= 1)
        {
            std::string requestedCommandName = parts[0];

            BOOST_FOREACH(boost::shared_ptr<Command> command, p_commands)
            {
                if (requestedCommandName == command->name())
                {
                    return command->run(parts);
                }
            }

            Messages::respondFailed(1, "Unknown command: '" + requestedCommandName + "'");
        } else
        {
            Messages::debug() << "Bad command" << std::endl;
        }

        return true;
    }

    std::string name() { return m_name; }

    virtual bool run(const std::vector<std::string>& parts) = 0;

protected:
    const std::string m_name;

    Command(const std::string& p_name) : m_name(p_name) {}
};
#pragma once

#include <string>
#include <iostream>
#include <libgen.h>

#include "commons.hpp"
#include "command.hpp"
#include "messages.hpp"

class CommandAddTorrent : public Command
{
public:
    CommandAddTorrent(libtorrent::session& p_session) :
        Command("add-torrent"), m_session(&p_session)
    {
        // do nothing
    }

    virtual bool run(const std::vector<std::string>& parts)
    {
        using namespace libtorrent;
        using namespace std;

        if (parts.size() == 3)
        {
            string torrentPath = parts[1];
            string savePath = parts[2];

            error_code ec;

            add_torrent_params params;

            params.name = torrentPath.c_str();
            params.save_path = savePath;
            params.ti = new torrent_info(torrentPath.c_str(), ec);

            if (ec)
            {
                
                Messages::respondFailed(2, "Cannot add torrent: " + ec.message());
                return true;
            }

            m_session->add_torrent(params, ec);

            if (ec)
            {
                Messages::respondFailed(3, "Cannot add torrent: " + ec.message());
                return true;
            }

            Messages::respondSucceed("Torrent " + torrentPath + " added successfully!");

        } else
        {
            Messages::respondFailed(2, "Wrong number of parameters");
        }

        return true;
    }

private:
    libtorrent::session* m_session;

    std::string basename(const std::string& p_filename)
    {
        return boost::filesystem::path(p_filename.c_str()).stem().native();
    }
};
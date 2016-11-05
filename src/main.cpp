#include <stdlib.h>
#if defined(__linux__)
#include <unistd.h>
#endif
#include <iostream>
#include "libtorrent/entry.hpp"
#include "libtorrent/bencode.hpp"
#include "libtorrent/session.hpp"
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

#include "command_listener.hpp"

#include "command_exit.hpp"
#include "command_add_torrent.hpp"
#include "command_remove_torrent.hpp"
#include "command_status.hpp"

bool has_param(const char* param, int argc, char* argv[])
{
    int len = strlen(param);
    for (int i = 0; i < argc; ++i)
    {
        if (strncmp(param, argv[i], len) == 0)
        {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    using namespace boost::filesystem;
    using namespace libtorrent;
    using namespace std;

    session s;
#if LIBTORRENT_VERSION_MAJOR >= 1 && LIBTORRENT_VERSION_MINOR >= 2 && LIBTORRENT_VERSION_TINY >= 0
    settings_pack settings;

    settings.set_int(settings_pack::active_downloads, 8);
    settings.set_int(settings_pack::active_seeds, 65536);
    settings.set_int(settings_pack::active_limit, 65536);
    settings.set_bool(settings_pack::announce_to_all_trackers, true);
    settings.set_bool(settings_pack::announce_to_all_tiers, true);

    s.apply_settings(settings);
#else
    session_settings settings;

    settings.active_downloads = 8;
    settings.active_seeds = 65536;
    settings.active_limit = 65536;
    settings.announce_to_all_trackers = true;
    settings.announce_to_all_tiers = true;

    s.set_settings(settings);
#endif

    boost::system::error_code ec;

    if (has_param("--no-dht", argc, argv))
    {
        s.stop_dht();
    }

    if (has_param("--no-lsd", argc, argv))
    {
        s.stop_lsd();
    }

    s.listen_on(std::make_pair(6881, 6889), ec);

    if (ec)
    {
        fprintf(stderr, "failed to open listen socket: %s\n", ec.message().c_str());
        return 1;
    }

    CommandListener cl;

    std::vector<boost::shared_ptr<Command> > commands;

    commands.push_back(boost::shared_ptr<Command>(new CommandExit()));
    commands.push_back(boost::shared_ptr<Command>(new CommandAddTorrent(s)));
    commands.push_back(boost::shared_ptr<Command>(new CommandRemoveTorrent(s)));
    commands.push_back(boost::shared_ptr<Command>(new CommandStatus(s)));

    string line;

    while (true)
    {
        if (cl.readCommand(line))
        {
            if (!Command::execute(line, commands))
            {
                break;
            }
        } else
        {
            cout << "standard input closed" << endl;
            break;
        }
    }
    
}
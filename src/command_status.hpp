#pragma once

#include <vector>
#include <sstream>

#include "libtorrent/entry.hpp"
#include "libtorrent/bencode.hpp"
#include "libtorrent/session.hpp"
#include "libtorrent/torrent_handle.hpp"
#include "libtorrent/torrent_status.hpp"

#if defined(USE_YAML)
#include <yaml-cpp/yaml.h>
#elif defined(USE_JSON)
#include "json.hpp"
using json = nlohmann::json;
#endif

#include "messages.hpp"
#include "command.hpp"

class CommandStatus : public Command
{
public:
    CommandStatus(libtorrent::session& p_session) :
        Command("status"), m_session(&p_session)
    {
        // do nothing
    }

    virtual bool run(const std::vector<std::string>& parts)
    {
        using namespace libtorrent;
        using namespace std;

        std::vector<torrent_status> stats;
        m_session->get_torrent_status(&stats, check);

#if defined(USE_YAML)
        YAML::Node node;
#elif defined(USE_JSON)
        json node;
        node["torrents"] = json::array();
#endif
        node["count"] = stats.size();

        BOOST_FOREACH(torrent_status status, stats)
        {
#if defined(USE_YAML)
            YAML::Node tnode;
#elif defined(USE_JSON)
            json tnode;
#endif
            tnode["name"] = status.handle.name();
            //tnode["save_path"] = status.handle.save_path();
            tnode["paused"] = status.paused;
            tnode["error"] = status.error;
            tnode["total_upload"] = status.total_upload;
            tnode["seed_rank"] = status.seed_rank;
            tnode["last_scrape"] = status.last_scrape;
            tnode["peers"] = status.num_peers;
            tnode["seeds"] = status.num_seeds;
            tnode["progress"] = status.progress;
            tnode["is_seeding"] = status.is_seeding;
            tnode["seeding_time"] = status.seeding_time;

            node["torrents"].push_back(tnode);
        }

        Messages::respondSucceed(node);

        return true;
    }

private:
    libtorrent::session* m_session;

    static bool check(libtorrent::torrent_status const& status) {
        return true;
    }
};
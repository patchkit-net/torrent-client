#pragma once

class CommandRemoveTorrent : public Command
{
public:
    CommandRemoveTorrent(libtorrent::session& p_session) :
        Command("remove-torrent"), m_session(&p_session)
    {
        // do nothing
    }

    virtual bool run(const std::vector<std::string>& parts)
    {
        using namespace libtorrent;
        using namespace std;

        if (parts.size() == 2)
        {
            string torrentName = parts[1];

            std::vector<torrent_status> stats;
            m_session->get_torrent_status(&stats, check);

            int index = findTorrent(stats, torrentName);

            if (index != -1)
            {
                m_session->remove_torrent(stats[index].handle);
                Messages::respondSucceed("Torrent " + torrentName + " successfully removed.");
            } else
            {
                Messages::respondFailed(3, "Error finding torrent: " + torrentName);
            }
        } else
        {
            Messages::respondFailed(2, "Wrong number of parameters");
        }

        return true;
    }

private:
    libtorrent::session* m_session;

    static bool check(libtorrent::torrent_status const& p_status) {
        return true;
    }

    int findTorrent(const std::vector<libtorrent::torrent_status>& p_statuses, const std::string& p_name) const
    {
        for (int i = 0; i < p_statuses.size(); ++i)
        {
            if (p_statuses[i].handle.name() == p_name) {
                return i;
            }
        }

        return -1;
    }
};

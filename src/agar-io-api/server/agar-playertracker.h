/*

AgarAPI Server version 0.0.0.1a
Copyright (c) 2016 Bhax Development team

*/

#ifndef AGAR_PLAYERTRACKER_H_
#define AGAR_PLAYERTRACKER_H_

#include <vector>
#include <memory>
#include "binary.h"

namespace agar_io
{
    class GameServer; // forward declaration
    class PlayerTracker {
        friend class GameServer;

    public:
        PlayerTracker();
        ~PlayerTracker();

        void on_destroy();

        void on_packet(const std::vector<unsigned char>& packet);

        void on_start();
    private:
        std::shared_ptr<GameServer> owner;

        unsigned int session_id;

        unsigned int protocol_version = 0;
        int protocol_accept;
        bool verified = false;

        void send_clear();
        void send_border();

    protected:

    };
} // namespace agar_io

#endif // AGAR_PLAYERTRACKER_H_

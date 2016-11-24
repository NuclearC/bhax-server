/*

    AgarAPI Server version 0.0.0.1a
    Copyright (c) 2016 Bhax Development team

*/

#ifndef AGAR_GAMESERVER_H_
#define AGAR_GAMESERVER_H_

#include <set>
#include <iostream>
#include <vector>
#include <string>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "json.hpp"


namespace agar_io
{
    class GameServer :
        public std::enable_shared_from_this<GameServer>
    {
        friend class PlayerTracker;

    public:
        enum State
        {
            kRunning,
            kClosed
        };

        GameServer();
        ~GameServer();

        void initialize(const unsigned short& port, const nlohmann::json& cfg);
        void start();

        const State& get_state();

    private:
        websocketpp::server<websocketpp::config::asio> ws;

        void on_ws_open(websocketpp::connection_hdl hdl);
        void on_ws_close(websocketpp::connection_hdl hdl);
        void on_ws_fail(websocketpp::connection_hdl hdl);
        void on_ws_packet(websocketpp::connection_hdl hdl,
            websocketpp::server<websocketpp::config::asio>::message_ptr msg);

        void send_packet(const unsigned int& player_id,
            const std::vector<unsigned char>& buffer);
        void close_player(const unsigned int& player_id);


        std::map<websocketpp::connection_hdl, PlayerTracker,
            std::owner_less<websocketpp::connection_hdl>> connections;

        unsigned int last_player_id = 1;
        unsigned int last_cell_id = 1;

        int protocol_accept = 0;

        nlohmann::json config;

        Border border;

        State state;
    protected:
    };
} // namespace agar_io

#endif // AGAR_GAMESERVER_H_

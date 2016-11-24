/*

    AgarAPI Server version 0.0.0.1a
    Copyright (c) 2016 Bhax Development team

*/

#include "agar-io-api/server/agar-utility.h"
#include "agar-io-api/server/agar-playertracker.h"
#include "agar-io-api/server/agar-gameserver.h"

namespace agar_io
{
    GameServer::GameServer()
    {
    }

    GameServer::~GameServer()
    {
    }

    void GameServer::start()
    {
        if (state != kRunning)
            ws.run();
    }

    const GameServer::State & GameServer::get_state()
    {
        return state;
    }

    void GameServer::initialize(const unsigned short& port, const nlohmann::json& cfg)
    {
        config = cfg;

        double half;
        if (config["worldArea"].is_number())
            half = sqrt(config["worldArea"].get<double>());

        border = {
            half,
            half,
            half / 2,
            half / 2
        };

        ws.set_access_channels(websocketpp::log::alevel::all);
        ws.clear_access_channels(websocketpp::log::alevel::frame_payload);

        ws.init_asio();

        ws.set_fail_handler(std::bind(&GameServer::on_ws_fail, this, 
            std::placeholders::_1));
        ws.set_close_handler(std::bind(&GameServer::on_ws_close, this,
            std::placeholders::_1));
        ws.set_open_handler(std::bind(&GameServer::on_ws_open, this,
            std::placeholders::_1));
        ws.set_message_handler(std::bind(&GameServer::on_ws_packet, this, 
            std::placeholders::_1,  std::placeholders::_2));

        ws.listen(port);

        ws.start_accept();
    }

    void GameServer::on_ws_open(websocketpp::connection_hdl hdl)
    {
        connections[hdl] = PlayerTracker();
        connections[hdl].session_id = last_player_id++;
        connections[hdl].owner = shared_from_this();
        connections[hdl].on_start();
    }

    void GameServer::on_ws_close(websocketpp::connection_hdl hdl)
    {
        if (connections.find(hdl) != connections.end())
        {
            connections[hdl].on_destroy();
            connections.erase(hdl);
        }
    }

    void GameServer::on_ws_fail(websocketpp::connection_hdl hdl)
    {
        if (connections.find(hdl) != connections.end())
        {
            connections[hdl].on_destroy();
            connections.erase(hdl);
        }
    }

    void GameServer::on_ws_packet(websocketpp::connection_hdl hdl, 
        websocketpp::server<websocketpp::config::asio>::message_ptr msg)
    {
        if (connections.find(hdl) != connections.end())
        {
            std::string str = msg->get_payload();
            std::vector<unsigned char> packet(str.begin(), str.end());
            connections[hdl].on_packet(packet);
        }
    }

    void GameServer::send_packet(const unsigned int & player_id, const std::vector<unsigned char>& buffer)
    {
        for (auto it = connections.begin(); it != connections.end(); it++)
        {
            if (it->second.session_id == player_id)
            {
                ws.send(it->first, buffer.data(), buffer.size(), websocketpp::frame::opcode::binary);
            }
        }
    }

    void GameServer::close_player(const unsigned int & player_id)
    {
        for (auto it = connections.begin(); it != connections.end(); it++)
        {
            if (it->second.session_id == player_id)
            {
                it->second.on_destroy();
                ws.close(it->first, websocketpp::close::status::subprotocol_error, "fuck off");
                connections.erase(it);
                break;
            }
        }
    }
} // namespace agar_io
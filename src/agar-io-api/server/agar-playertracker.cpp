/*

AgarAPI Server version 0.0.0.1a
Copyright (c) 2016 Bhax Development team

*/

#include "agar-io-api/server/agar-utility.h"
#include "agar-io-api/server/agar-playertracker.h"
#include "agar-io-api/server/agar-gameserver.h"

namespace agar_io
{
    PlayerTracker::PlayerTracker() {

    }

    PlayerTracker::~PlayerTracker() {

    }

    void PlayerTracker::on_start() {

    }

    void PlayerTracker::send_clear()
    {
        unsigned long long off = 0;
        std::vector<unsigned char> packet(1);

        writeToVector<unsigned char>(packet, off, 0x12);

        owner->send_packet(session_id, packet);
    }

    void PlayerTracker::send_border()
    {
        unsigned long long off = 0;
        std::vector<unsigned char> packet;

        packet.insert(packet.end(), 33, 0);
        writeToVector<unsigned char>(packet, off, 0x40);

        double minx = -owner->border.half_width;
        double miny = -owner->border.half_height;
        double maxx = owner->border.half_width;
        double maxy = owner->border.half_height;

        writeToVector<double>(packet, off, minx);
        writeToVector<double>(packet, off, miny);
        writeToVector<double>(packet, off, maxx);
        writeToVector<double>(packet, off, maxy);

        if (owner->config["gamemode"].is_number_unsigned())
        {
            packet.insert(packet.end(), 4, 0);
            writeToVector<unsigned int>(packet, off, owner->config["gamemode"].get<unsigned int>());

            if (owner->config["version"].is_string())
            {
                std::string version = owner->config["version"].get<std::string>();
                packet.insert(packet.end(), version.size() + 1, 0);

                for (auto&& ch : version)
                {
                    writeToVector<char>(packet, off, ch);
                }
            }

            writeToVector<unsigned char>(packet, off, 0x00);
        }

        owner->send_packet(session_id, packet);
    }

    void PlayerTracker::on_destroy() {

    }

    void PlayerTracker::on_packet(const std::vector<unsigned char>& packet) {
        unsigned long long off = 0;

        unsigned char packet_id = readUint8((char*)packet.data(), packet.size(), off);

        switch (packet_id)
        {
        case 0x00: // spawn
        {
            if (!verified)
                break;
        } break;
        case 0x01: // spectate
        {
            if (!verified)
                break;
        } break;
        case 0x10: // move to x,y
        {
            if (!verified)
                break;
        } break;
        case 0x11: // space
        {
            if (!verified)
                break;
        } break;
        case 0x12: // q
        {
            if (!verified)
                break;
        } break;
        case 0x13: // afk
        {
            if (!verified)
                break;
        } break;
        case 0x14: // explode
        {
            if (!verified)
                break;
        } break;
        case 0x15: // w
        {
            if (!verified)
                break;
        } break;
        case 0xfe: // protocol version
        {
            protocol_version = readUint32((char*)packet.data(), packet.size(), off);

            if (protocol_version != 9)
                owner->close_player(session_id);
        } break;
        case 0xff: // protocol accept
        {
            protocol_accept = readInt32((char*)packet.data(), packet.size(), off);

            if (protocol_accept == owner->protocol_accept && protocol_version > 0)
            {
                verified = true;
            }
            else
            {
                owner->close_player(session_id);
                break;
            }

            send_clear();
            send_border();
        } break;
        }
    }
} // namespace agar_io
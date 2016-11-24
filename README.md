# bhax-server
Agar/Ogar Server in C++

## Dependencies
* WebSocket++ (0.7.0 is fine) (https://github.com/zaphoyd/websocketpp)
* nlohmann's json library (https://github.com/nlohmann/json)
* My binary reader/writer (https://github.com/nuclearc/binary-writer-reader)

## How to use
Make a shared_ptr of agar_io::GameServer, initialize and run it
```C++
#include "agar-io-api/server/agar-utility.h"
#include "agar-io-api/server/agar-playertracker.h"
#include "agar-io-api/server/agar-gameserver.h"

int main() {
 nlohmann::json config = {
        ...
    };

    std::shared_ptr<agar_io::GameServer> srv = std::make_shared<agar_io::GameServer>();
    srv->initialize(443, config);
    srv->start();
}
```

Example configuration:
```C++
    nlohmann::json config = {
        { "version", "1.0.0" },
        { "worldArea", 200000000.0 },
        { "viewportWidth", 1980.0 },
        { "viewportHeight", 1020.0 },
        { "protocolAccept", "any" },
        { "gamemode", 0U },
    };
```

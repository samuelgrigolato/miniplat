#include "game/server.h"
#include "game/client.h"


int main() {
    game::server::Server *server = new game::server::LocalServer();
    return game::client::run(server);
}

#include "game/server.h"
#include "game/client.h"


int main() {

    char server_type;
    printf("[D]edicated [M]aster, [L]ocal or [C]lient? ");
    scanf("%c", &server_type);

    game::server::Server *server;
    switch (server_type) {
        case 'D':
            server = new game::server::LocalServer();
            while (true) {
                server->tick(NULL);
            }
            break;
        case 'M':
            server = new game::server::NetworkMasterServer();
            break;
        case 'L':
            server = new game::server::LocalServer();
            break;
        case 'C':
            server = new game::server::NetworkClientServer();
            break;
        default:
            printf("Unknown server type.");
            return -1;
    }

    return game::client::run(server);
}

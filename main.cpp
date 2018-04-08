#include "game/server.h"
#include "game/client.h"


int main() {

    char server_type;
    printf("[D]edicated, [M]aster, [L]ocal or [C]lient? ");
    scanf("%c", &server_type);

    game::server::Server *server;
    switch (server_type) {
        case 'D':
        case 'd':
            server = new game::server::NetworkMasterServer();
            while (true) {
                server->tick(NULL);
            }
        case 'M':
        case 'm':
            server = new game::server::NetworkMasterServer();
            break;
        case 'L':
        case 'l':
            server = new game::server::LocalServer();
            break;
        case 'C':
        case 'c':
            server = new game::server::NetworkClientServer();
            break;
        default:
            printf("Unknown server type.\n");
            return -1;
    }

    return game::client::run(server);
}

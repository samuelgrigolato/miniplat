#include "game/server.h"
#include "game/client.h"


int main() {

    int8_t num_local_players;
    printf("How many local players (1-3)? ");
    scanf("%d", &num_local_players);
    if (num_local_players <= 0 || num_local_players > 3) {
        printf("Invalid number of local players!\n");
        return -1;
    }

    game::server::Server *server = new game::server::Server(num_local_players);
    return game::client::run(server);

}

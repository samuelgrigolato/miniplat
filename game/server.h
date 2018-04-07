#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include "data/InputStatus.h"
#include "components/Player.h"


namespace game {
namespace server {

class Server {
public:
    Server(int8_t num_local_players);
    int8_t get_num_local_players() {
        return this->num_local_players;
    }
    void tick(data::InputStatus *input_statuses);
private:
    std::shared_ptr<components::Player> *players;
    int8_t num_local_players;
    int32_t last_time = 0;
    int32_t current_time = 0;
    int32_t elapsed_time = 0;
};

}}

#endif

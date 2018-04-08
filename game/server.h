#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <vector>
#include <stdint.h>
#include <SDL_net.h>
#include "data/InputStatus.h"
#include "components/Player.h"


namespace game {
namespace server {

class Server {
public:
    virtual int8_t get_num_local_players() = 0;
    virtual bool add_local_player() = 0;
    virtual void tick(std::vector<data::InputStatus> *input_statuses) = 0;
};

class LocalServer : public Server {
public:
    LocalServer();
    int8_t get_num_local_players() override {
        return this->players.size();
    }
    bool add_local_player() override;
    void tick(std::vector<data::InputStatus> *input_statuses) override;
private:
    std::list<std::shared_ptr<components::Player>> players;
    int32_t last_time = 0;
    int32_t current_time = 0;
    int32_t elapsed_time = 0;
};

class NetworkMasterServer : public LocalServer {
public:
    NetworkMasterServer();
    int8_t get_num_local_players() override;
    void tick(std::vector<data::InputStatus> *input_statuses) override;
private:
    TCPsocket server_socket;
    std::list<TCPsocket> sockets;
};

class NetworkClientServer : public Server {
public:
    NetworkClientServer();
    int8_t get_num_local_players() override;
    bool add_local_player() override;
    void tick(std::vector<data::InputStatus> *input_statuses) override;
private:
    TCPsocket socket;
};

}}

#endif

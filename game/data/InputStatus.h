#ifndef INPUTSTATUS_H
#define INPUTSTATUS_H


namespace game {
namespace data {

enum InputType {
    none            = 0b0000000,
    move_up         = 0b0000001,
    move_down       = 0b0000010,
    move_left       = 0b0000100,
    move_right      = 0b0001000,
    fire            = 0b0010000
};

struct InputStatus {
    void set(InputType type) {
        this->status |= type;
    }
    void unset(InputType type) {
        this->status &= 0b1111111 - type;
    }
    bool is_on(InputType type) {
        return (this->status & type) == type;
    }
private:
    uint8_t status = 0;
};

}}

#endif

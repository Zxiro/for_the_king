#ifndef KEYBOARD_INPUT_HANDLER_H
#define KEYBOARD_INPUT_HANDLER_H

#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/component.hpp"

using namespace ftxui;

class KeyboardInputHandler {
public:
    KeyboardInputHandler();
    void HandleInput(Event event);
    std::string GetLastKey() const;

private:
    std::string last_key_;
};

#endif // KEYBOARD_INPUT_HANDLER_H

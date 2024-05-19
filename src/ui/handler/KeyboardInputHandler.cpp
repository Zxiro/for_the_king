#include "KeyboardInputHandler.h"

KeyboardInputHandler::KeyboardInputHandler() : last_key_("") {}

void KeyboardInputHandler::HandleInput(Event event) {
    last_key_ = event.character();
}

std::string KeyboardInputHandler::GetLastKey() const {
    return last_key_;
}

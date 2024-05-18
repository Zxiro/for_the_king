#include "KeyboardInputUI.h"

void KeyboardInputUI::Show() {
    ScreenInteractive screen = ScreenInteractive::TerminalOutput();
    KeyboardInputHandler keyboardInputHandler;

    auto event_handler = CatchEvent([&](Event event) {
        keyboardInputHandler.HandleInput(event);
        return true;
        });

    auto renderer = Renderer([&] {
        return vbox({
            text("Press any key: "),
            text(keyboardInputHandler.GetLastKey()) | color(Color::Green)
            }) | border | center;
        });

    auto component = renderer | event_handler;

    screen.Loop(component);
}

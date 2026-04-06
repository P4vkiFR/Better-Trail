#include "Includes.hpp"
#include "PlayerObject.hpp"

void updateUpdateHook() {
    setHookEnabled(
        "PlayerObject::update",
        getSetting<"disable-pulse", bool>()
        || getSetting<"enable-ship-trail", bool>()
        || getSetting<"enable-ufo-trail", bool>()
        || getSetting<"enable-swing-trail", bool>()
        || getSetting<"enable-cube-trail", bool>()
        || getSetting<"enable-robot-trail", bool>()
        || getSetting<"enable-spider-trail", bool>()
        || getSetting<"enable-ball-trail", bool>()
    );
}

$on_mod(Loaded) {

    updateUpdateHook();

    listenForAllSettingChanges([](std::string_view, std::shared_ptr<SettingV3>) {
        updateUpdateHook();

        if (auto pl = PlayLayer::get()) {
            static_cast<ProPlayerObject*>(pl->m_player1)->updateSettings();
            static_cast<ProPlayerObject*>(pl->m_player2)->updateSettings();
        }
    });

    listenForKeybindSettingPresses("open-menu", [](Keybind const& keybind, bool down, bool repeat, double timestamp) {
        if (down && !repeat) {
            toggleSettingsPopup();
        }
    });
}
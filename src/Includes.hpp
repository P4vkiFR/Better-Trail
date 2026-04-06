#pragma once

using namespace geode::prelude;

#include <Geode/ui/GeodeUI.hpp>

inline Popup*& getPopup() {
    static Popup* s_modPopup = nullptr;
    return s_modPopup;
}

static void toggleSettingsPopup() {
    auto& s_modPopup = getPopup();

    if (!s_modPopup) {
        s_modPopup = geode::openSettingsPopup(Mod::get(), false);
        return;
    }

    if (auto scene = CCScene::get()) {
        for (auto node : scene->getChildrenExt()) {
            if (s_modPopup == node) {
                static_cast<FLAlertLayer*>(node)->keyBackClicked();
                return;
            }
        }
    }

    s_modPopup = geode::openSettingsPopup(Mod::get(), false);
}

static void setHookEnabled(std::string_view name, bool enabled) {
    for (auto hook : Mod::get()->getHooks()) {
        if (hook->getDisplayName() == name) {
            (void)(enabled ? hook->enable() : hook->disable());
            break;
        }
    }
}

template <string::ConstexprString S, typename T>
const T& getSetting() {
    static T value = (
        listenForSettingChanges<T>(S.data(), [](T val) {
            value = val;
        }),
        Mod::get()->getSettingValue<T>(S.data())
    );

    return value;
}
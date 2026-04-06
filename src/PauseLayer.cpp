#include "PauseLayer.hpp"

#include <Geode/ui/Button.hpp>

void ProPauseLayer::customSetup() {
    PauseLayer::customSetup();

    if (!getSetting<"button-in-pause-menu", bool>()) {
        return;
    }

    auto gm = GameManager::get();

    auto icon = SimplePlayer::create(gm->getPlayerFrame());
    icon->updatePlayerFrame(gm->getPlayerDart(), IconType::Wave);
    icon->setRotation(-35);
    icon->setPosition({1, 1});
    icon->setScale(0.5f);
    icon->setColors(
        gm->colorForIdx(gm->getPlayerColor()),
        gm->colorForIdx(gm->getPlayerColor2())
    );
    if (gm->getPlayerGlow()) {
        icon->setGlowOutline(gm->colorForIdx(gm->getPlayerGlowColor()));
        icon->enableCustomGlowColor(gm->colorForIdx(gm->getPlayerGlowColor()));
    }

    auto container = CCNode::create();
    container->setContentSize({15, 15});
    container->addChild(icon);

    auto spr = CircleButtonSprite::create(container, CircleBaseColor::Green, CircleBaseSize::Medium);
    spr->setScale(0.7f);
    
    auto btn = Button::createWithNode(spr, [](Button*) {
        toggleSettingsPopup();
    });
    btn->setID("button"_spr);

    if (auto menu = getChildByID("left-button-menu")) {
        menu->addChild(btn);
        menu->updateLayout();
    } else {
        addChild(btn);
        btn->setPosition({43, 278});
    }
}
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

static bool s_done = false;

// Icons first (the important part), then the extras.
static void unlockEverything() {
    auto gm = GameManager::get();

    // ---- ICONS ----
    IconType types[] = {
        IconType::Cube, IconType::Ship, IconType::Ball, IconType::Ufo,
        IconType::Wave, IconType::Robot, IconType::Spider, IconType::Swing,
        IconType::Jetpack
    };
    for (auto t : types) {
        int count = gm->countForType(t);
        for (int i = 1; i <= count; i++) {
            gm->unlockIcon(i, t);
        }
    }

    // ---- COLORS ----
    if (Mod::get()->getSettingValue<bool>("unlock-colors")) {
        for (int i = 0; i < 107; i++) {
            gm->unlockColor(i, UnlockType::Col1);
            gm->unlockColor(i, UnlockType::Col2);
        }
    }

    // ---- TRAILS, DEATH EFFECTS, SHIP FIRE ----
    if (Mod::get()->getSettingValue<bool>("unlock-effects")) {
        for (int i = 1; i <= 7; i++)  gm->unlockIcon(i, IconType::Special);   // trails
        for (int i = 1; i <= 20; i++) gm->unlockIcon(i, IconType::DeathEffect);
        for (int i = 1; i <= 6; i++)  gm->unlockIcon(i, IconType::ShipFire);
    }

    // Write to the save file NOW so the unlocks survive uninstalling the mod.
    AppDelegate::get()->trySaveGame(false);
}

class $modify(UnlockMenu, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        if (!s_done) {
            s_done = true;
            unlockEverything();
            log::info("Unlock All: done, save written");
        }
        return true;
    }
};

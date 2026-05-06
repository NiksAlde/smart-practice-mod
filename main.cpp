#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

std::vector<CCPoint> deaths;

class $modify(SmartPractice, PlayLayer) {

    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        deaths.push_back(player->getPosition());
        PlayLayer::destroyPlayer(player, obj);
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);

        auto player = m_player1;
        if (!player) return;

        int count = 0;
        for (auto& d : deaths) {
            if (ccpDistance(d, player->getPosition()) < 60) {
                count++;
            }
        }

        if (count > 5) {
            CCDirector::sharedDirector()->getScheduler()->setTimeScale(0.8f);
        } else {
            CCDirector::sharedDirector()->getScheduler()->setTimeScale(1.0f);
        }
    }
};

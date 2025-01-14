#include "Orc.h"

Orc::Orc(int level)
    : Monster("Orc", 30, 5, 3, 20, 100, level)
{
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Orc);

    int hpModifier = 16;
    int powerModifier = 6;
    int defenseModifier = 3;
    int expModifier = 60;
    int moneyModifier = 200;
    CalculateStats(hpModifier, powerModifier, defenseModifier, expModifier, moneyModifier);
    DisplayIntroduction();
}

void Orc::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);
}

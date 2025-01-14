#include "Witch.h"

Witch::Witch(int level)
    : Monster("Witch", 20, 15, 2, 10, 100, level)
{
    //초기화
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Witch);

    int hpModifier = 10;
    int powerModifier = 5;
    int defenseModifier = 2;
    int expModifier = 50;
    int moneyModifier = 150;
    CalculateStats(hpModifier, powerModifier, defenseModifier, expModifier, moneyModifier);
    DisplayIntroduction();
}

void Witch::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);

}

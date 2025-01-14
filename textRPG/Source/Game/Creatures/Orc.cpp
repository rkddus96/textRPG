#include "Orc.h"

Orc::Orc(int level)
    : Monster("Orc", 30, 5, 3, 20, 100, level)
{
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Orc);

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
    //출력 
    GameManager::GetInstance().GetUIManager()->ClearMessageToBasicCanvasEventInfoUI();
    string s = "오크의 분노를 보여주마!";
    wstring ws = LogicHelper::StringToWString(s);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws);
}

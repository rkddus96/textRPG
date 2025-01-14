#include "Goblin.h"


Goblin::Goblin(int level)
    : Monster("Goblin", 20, 10, 1, 20, 100, level)
{
    //초기화
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Goblin);

    int hpModifier = 12;
    int powerModifier = 6;
    int defenseModifier = 1;
    int expModifier = 30;
    int moneyModifier = 100;
    CalculateStats(hpModifier, powerModifier, defenseModifier, expModifier, moneyModifier);
    DisplayIntroduction();
    
}

void Goblin::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);
    //출력 
    GameManager::GetInstance().GetUIManager()->ClearMessageToBasicCanvasEventInfoUI();
    string s = "네 보물은 이제 내 거다! 하하하!";
    wstring ws = LogicHelper::StringToWString(s);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws);
}

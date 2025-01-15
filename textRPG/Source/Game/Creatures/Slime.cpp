#include "Slime.h"


Slime::Slime(int level)
    : Monster("Slime", 10, 8, 3, 20, 100, level)
{
   
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Slime);

    int hpModifier = 17;
    int powerModifier = 5;
    int defenseModifier = 3;
    int expModifier = 40;
    int moneyModifier = 120;
    CalculateStats(hpModifier, powerModifier, defenseModifier, expModifier, moneyModifier);
    DisplayIntroduction();

}

void Slime::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);
    //출력
    GameManager::GetInstance().GetUIManager()->ClearMessageToBasicCanvasEventInfoUI();
    string s = "오ㅇ...ㅇ오오옳..ㅇ";
    wstring ws = LogicHelper::StringToWString(s);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws);


}

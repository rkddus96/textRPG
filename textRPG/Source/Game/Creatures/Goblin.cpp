#include "Goblin.h"


Goblin::Goblin(int level)
    : Monster("Goblin", 10, 10, 1, 20, 100, level)
{
    //초기화
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Castle1);

    int hpModifier = 10;
    int powerModifier = 4;
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
    //정보 출력
    cout << "Name : " << Name << endl;
    cout << "Hp : " << CurHp << endl;
    cout << "Power : " << Power << endl;
    cout << "Defense : " << Defense << endl;
}

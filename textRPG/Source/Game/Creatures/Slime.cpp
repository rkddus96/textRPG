#include "Slime.h"


Slime::Slime(int level)
    : Monster("Slime", 10, 8, 3, 20, 100, level)
{
   
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Slime);

    int hpModifier = 10;
    int powerModifier = 3;
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
    //정보 출력
    cout << "Name : " << Name << endl;
    cout << "Hp : " << CurHp << endl;
    cout << "Power : " << Power << endl;
    cout << "Defense : " << Defense << endl;
}

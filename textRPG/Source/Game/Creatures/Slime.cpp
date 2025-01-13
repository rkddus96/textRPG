#include "Slime.h"


Slime::Slime(int level)
    : Monster("Slime", 100, 20, 5, 20, 100, level)
{
   
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Slime);
    CalculateStats(50, 10, 2);
    DisplayIntroduction();

}

void Slime::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);
    //정보 출력
    cout << "Name : " << name << endl;
    cout << "Hp : " << CurHp << endl;
    cout << "Power : " << Power << endl;
    cout << "Defense : " << Defense << endl;
}

#include "Goblin.h"


Goblin::Goblin(int level)
    : Monster("Goblin", 100, 20, 5, 20, 100, level)
{
    //초기화
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Castle1);
    CalculateStats(50, 10, 2);
    DisplayIntroduction();
    
}

void Goblin::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);
    //정보 출력
    cout << "Name : " << name << endl;
    cout << "Hp : " << CurHp << endl;
    cout << "Power : " << Power << endl;
    cout << "Defense : " << Defense << endl;
}

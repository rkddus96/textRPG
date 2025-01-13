#include "Goblin.h"

Goblin::Goblin()
{
    //초기화
    //MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArt::Slime);
}

void Goblin::DisplayIntroduction()
{
    //아트

    //정보 출력
    cout << "Name : " << name << endl;
    cout << "Hp : " << CurHp << endl;
    cout << "Power : " << Power << endl;
    cout << "Defense : " << Defense << endl;
}

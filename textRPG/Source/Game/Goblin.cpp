#include "Goblin.h"

Goblin::Goblin()
{
    //스탯 초기화
}

void Goblin::DisplayIntroduction()
{
    //아트 출력

    //정보 
    cout << "Name : " << name << endl;
    cout << "Hp : " << CurHp << endl;
    cout << "Power : " << Power << endl;
    cout << "Defense : " << Defense << endl;
}

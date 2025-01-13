#include "Witch.h"

Witch::Witch()
{
    //초기화
}

void Witch::DisplayIntroduction()
{
    //아트

    //정보 출력
    cout << "Name : " << name << endl;
    cout << "Hp : " << CurHp << endl;
    cout << "Power : " << Power << endl;
    cout << "Defense : " << Defense << endl;
}

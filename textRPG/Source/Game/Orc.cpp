#include "Orc.h"

Orc::Orc()
{
}

void Orc::DisplayIntroduction()
{
    //아트 출력

    //정보 
    cout << "Name : " << name << endl;
    cout << "Hp : " << CurHp << endl;
    cout << "Power : " << Power << endl;
    cout << "Defense : " << Defense << endl;
}

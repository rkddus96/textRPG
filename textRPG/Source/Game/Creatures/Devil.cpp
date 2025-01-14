#include "Devil.h"


Devil::Devil()
    : Monster("Devil", 500, 70, 20, 0, 0, 99)
{
    MaxHp = BaseHp;
    Power = BasePower;
    Defense = BaseDefense;
    
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASKIIArtContainer(EArtList::Devil);
    DisplayIntroduction();

}

void Devil::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);
}

#include "King.h"

King::King()
    : Monster("King", 444, 100, 20, 0, 0, 99)
{
    MaxHp = BaseHp;
    CurHp = MaxHp;
    Power = BasePower;
    Defense = BaseDefense;

    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::King);
    DisplayIntroduction();
}


void King::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);
    //출력 
    GameManager::GetInstance().GetUIManager()->ClearMessageToBasicCanvasEventInfoUI();
    string script1 = "나를 배신자라 부르는가? 내가 이 왕국을 지켜왔고, 그 대가로 받은 건 배신뿐이었다.";
    string script2 = "힘이 없으면 아무것도 지킬 수 없지… 그래서 선택한 것이다.마왕의 힘을!";
    string script3 = "이제 이 왕국은 나의 뜻대로 흘러갈 것이다.누구도 날 막을 수 없다!";
    wstring ws1 = LogicHelper::StringToWString(script1);
    wstring ws2 = LogicHelper::StringToWString(script2);
    wstring ws3 = LogicHelper::StringToWString(script3);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws1);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws2);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws3);
}

#include "Devil.h"


Devil::Devil()
    : Monster("Devil", 700, 90, 30, 0, 0, 99)
{
    MaxHp = BaseHp;
    CurHp = MaxHp;
    Power = BasePower;
    Defense = BaseDefense;
    
    MonsterImage = GameManager::GetInstance().GetAssetHandler()->GetASCIIArtContainer(EArtList::Devil);
    DisplayIntroduction();

}

void Devil::DisplayIntroduction()
{
    //아트
    GameManager::GetInstance().GetUIManager()->ChangeBasicCanvasArtImage(MonsterImage);
    //출력 
    GameManager::GetInstance().GetUIManager()->ClearMessageToBasicCanvasEventInfoUI();
    string script1 = "감히 나에게 도전하다니, 얼마나 웃기는 일인가.";
    string script2 = "넌 태생부터 패배할 운명이었음을 깨달아라.";
    string script3 = "이제 너를 기다리는 건 오직 영원한 절망뿐이다.";
    wstring ws1 = LogicHelper::StringToWString(script1);
    wstring ws2 = LogicHelper::StringToWString(script2);
    wstring ws3 = LogicHelper::StringToWString(script3);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws1);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws2);
    GameManager::GetInstance().GetUIManager()->AddMessageToBasicCanvasEventInfoUI(ws3);
}

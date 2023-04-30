#include "stdafx.h"
#include "GameManager.h"

#include "BloonFactory.h"
#include "TowerFactory.h"


namespace Btd
{
    void GameManager::OnBeginState()
    {
        BloonPause=false;
        GameFlow = Prepare;
        round = 0;
        TowerFactory::TowerVector.clear();
        map->InitFactoryButton();
        BloonFactory::ClearActiveBloon();
        live = map->InitLives;
        money = map->InitMoney;
        db.LoadRounds();
        map->SetRounds(db.GetRounds());
        BloonFactory::SetNextRound(map->GetRounds()[round]);
        BloonFactory::RoundRoute = 0;
        IsLose = false;
    }

    void GameManager::OnInit()
    {
        GameFlow = Prepare;
        startButton.LoadBitmapByString({"resources/start_button.bmp"});
        startButton.SetTopLeft(742, 620);
    }

    void GameManager::OnKeyUp(UINT, UINT, UINT)
    {
    }

    void GameManager::OnLButtonDown(UINT nFlags, CPoint point)
    {
        if(TowerFactory::TowerVector.empty() ||
            !TowerFactory::TowerVector.back()->IsMovable() )
        {
            willDecreaseMoney = map->HandleButtonClicked(money);
        }
        money -= TowerFactory::HandleTowerClicked(money);
        if (!TowerFactory::TowerVector.empty() &&
            TowerFactory::TowerVector.back()->IsMovable() &&
            TowerFactory::TowerVector.back()->RangeCircle.GetFrameIndexOfBitmap() == 0)
        {
            money -= willDecreaseMoney;
            TowerFactory::TowerVector.back()->SetIsMove(false);
            TowerFactory::TowerVector.back()->SetActive(true);
        }
        switch (GameFlow)
        {
        case Prepare:
            {
                if (IsCursorInObj(startButton))
                {
                    GameFlow = Shoot;
                }
                break;
            }
        default:
            break;
        }
    }

    void GameManager::OnLButtonUp(UINT nFlags, CPoint point)
    {
    }

    void GameManager::OnMouseMove(UINT nFlags, CPoint point)
    {
        if (!TowerFactory::TowerVector.empty() &&
            TowerFactory::TowerVector.back()->IsMovable())
        {
            TowerFactory::TowerVector.back()->SetCenter(GetCursorPosX(),
                                                        GetCursorPosY());
        }
    }

    void GameManager::OnRButtonDown(UINT nFlags, CPoint point)
    {
    }

    void GameManager::OnRButtonUp(UINT nFlags, CPoint point)
    {
    }

    bool isOverlapOtherTower(GameObject t)
    {
        for (int i = 0; i < static_cast<int>(TowerFactory::TowerVector.size()) - 1; i++)
        {
            if (IsOverlap(*TowerFactory::TowerVector[i], t))
            {
                return true;
            }
        }
        return false;
    }

    void GameManager::OnMove()
    {
        if (!TowerFactory::TowerVector.empty())
        {
            if (map->IsOverLapRoad(static_cast<GameObject>(*TowerFactory::TowerVector.back())) ||
                isOverlapOtherTower(static_cast<GameObject>(*TowerFactory::TowerVector.back())))
            {
                TowerFactory::TowerVector.back()->RangeCircle.SetFrameIndexOfBitmap(1);
            }
            else
            {
                TowerFactory::TowerVector.back()->RangeCircle.SetFrameIndexOfBitmap(0);
            }
        }
        map->UpdateFactoryButton();

        switch (GameFlow)
        {
        case Prepare:
            break;

        case Shoot:
            {
                bool RoundRunOut = BloonFactory::UpdateRound(BtdTimer.GetDeltaTime());
                bool isRoundEnd = BloonFactory::BloonVector.empty() && RoundRunOut;
                if (isRoundEnd)
                {
                    GameFlow = Win;
                }
                live -= BloonFactory::subLifeByGoalBloon();
                if (live <= 0)
                {
                    live = 0;
                    GameFlow = GameEnd;
                    IsLose = true;
                }
                break;
            }
        case Win:
            round++;
            if (round >= static_cast<int>(map->GetRounds().size()))
            {
                GameFlow = GameEnd;
            }
            else
            {
                BloonFactory::SetNextRound(map->GetRounds()[round]);
                GameFlow = Prepare;
                money += 100;
            }

            break;
        case GameEnd:

            break;
        default: ;
        }
        for (auto& m : TowerFactory::TowerVector)
        {
            m->Update();
        }
        if(!BloonPause)
        {
        BloonFactory::UpdateBloon();
        }
    }

    void GameManager::OnShow()
    {
        map->ShowBackground();
        map->ShowRoad();
        map->ShowFactoryButton();
        for (int i = 0; i < static_cast<int>(TowerFactory::TowerVector.size()); i++)
        {
            TowerFactory::TowerVector[i]->HandleUpgradeBtnFrame(money);
            TowerFactory::TowerVector[i]->TowerShow();
        }
        for (auto& bloon : BloonFactory::BloonVector)
        {
            bloon.BloonShow();
        }
        switch (GameFlow)
        {
        case Prepare:
            startButton.ShowBitmap();
            break;
        default:
            break;
        }
    }

    bool GameManager::GetLose()
    {
        return IsLose;
    }

    void GameManager::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
    {
        if (nChar == 'A')
        {
            BloonFactory::MakeBloon(Layer::red);
        }
        if (nChar == 'S')
        {
            BloonFactory::MakeBloon(Layer::blue);
        }
        if (nChar == 'D')
        {
            BloonFactory::MakeBloon(Layer::green);
        }
        if (nChar == 'F')
        {
            BloonFactory::MakeBloon(Layer::yellow);
        }
        if (nChar == 'Z')
        {
            BloonFactory::MakeBloon(Layer::black);
        }
        if (nChar == 'X')
        {
            BloonFactory::MakeBloon(Layer::white);
        }
        if (nChar == 'P')
        {
            live = 0;
        }
        if (nChar == 'U')
        {
            BloonPause = !BloonPause;
        }
        if (nChar == 'M')
        {
            money = 48763;
        }
    }

    shared_ptr<Map> GameManager::map = make_shared<Map>(Map());
} // namespace Btd

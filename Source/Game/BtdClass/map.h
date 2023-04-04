#ifndef MAP_H
#define MAP_H

#include "GameObject.h"
#include "BtdUtil.h"
#include "FactoryButton.h"

namespace Btd
{
    class Map : public GameObject
    {
    public:
        Map() = default;
        ~Map() override = default;
        const int InitMoney = 650;
        const int InitLives = 40;
        virtual void InitRoad();
        void ShowRoad();
        virtual void InitBackground(vector<string> backgroundBmp);
        void ShowBackground();
        void InitFactoryButton();
        void ShowFactoryButton();
        void UpdateFatoryButton();
        void HandleButtonClicked();
        GameObject GetBackground();
        vector<vector<UnitRound>> GetRounds();
        void SetRounds(vector<vector<UnitRound>> round);
        static vector<Vector2> GetRoute();
        static Vector2 GetStartPosition();
        static void SetStartPosition(Vector2);
        static void SetRoute(vector<Vector2>);
        bool IsOverLapRoad(GameObject target);

    protected:
        std::vector<GameObject> _road;
        GameObject _background;
        FactoryButton _factoryButton[5];
        static vector<Vector2> _route;
        static Vector2 _startPosition;
        vector<vector<UnitRound>> _rounds;
    };
}

#endif

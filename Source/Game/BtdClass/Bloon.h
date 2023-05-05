#pragma once
#include "GameObject.h"
#include "BtdUtil.h"
#include <list>
#include <map>

namespace Btd
{
    class Bloon : public GameObject
    {
    private:
        int nowRouteTarget = 0;
        float _speed = 3;
        int _layer = 0;
        bool _isPoped = false;
        bool _isGoaled = false;
        BloonType::BloonType type = BloonType::normal;
        int _slowerTime;
        float _slowerSpeed;
        float _originSpeed;
        int route = 0;
        bool _isFreeze;
        GameObject _frost;
        int _explodeTime;
        bool _isExplode;

    public:
        int GetExplodeTime() const;
        void SetExplodeTime(int explodeTime);

        Bloon()
        {
            _layer = 0;
            _isPoped = false;
            _slowerTime = 0;
            _isFreeze = false;
            _frost.LoadBitmapByString({"resources/bloon/frost.bmp"}, RGB(0, 0, 0));
            _explodeTime = 30;
            _isExplode = false;
        };

        Bloon(int layer): _layer(layer)
        {
        }

        static bool resistDamegeMap[5][3];

        void SetNowRouteTarget(int target);

        void Setspeed(float speed);

        void SetType(BloonType::BloonType t)
        {
            type = t;
        }

        void Update() override;
        void SetRoute(int n);
        int Getroute();
        float GetSpeed();
        BloonType::BloonType GetType();

        void Move(vector<Vector2> route);

        void Pop(int damage, DamageType::DamageType damageType);

        int GetNowRouteTarget()
        {
            return nowRouteTarget;
        }

        bool IsPoped();
        bool IsGoaled();
        void SetIsPoped(bool poped);
        void SetIsGoaled(bool goaled);
        void SetLayer(int layer);
        void SlowerInPeriod(float subSpeed, int time);
        int GetLayer();
        void BloonShow();
        void ShowExplode();
    };
}

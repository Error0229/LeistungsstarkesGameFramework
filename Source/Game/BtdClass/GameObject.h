#pragma once
#include "BtdUtil.h"
#include "../../Library/gameutil.h"

namespace Btd
{
    class GameObject : public game_framework::CMovingBitmap
    {
    protected:
        bool _isActive = true;
        string _tag = "default";
        int deltaTime = 10;

    public:
        virtual ~GameObject() = default;
        virtual void Update();
        void SetActive(bool active);
        bool GetActive();
        void SetTag(string tag);
        string GetTag();
        Vector2 GetCenter();
        void SetCenter(int x, int y);
        void SetBottomCenter(int x, int y);
        Vector2 GetBottomCenter();
    };

    bool IsOverlap(GameObject& character, GameObject& other);
}

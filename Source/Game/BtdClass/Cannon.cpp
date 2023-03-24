﻿#include "stdafx.h"
#include "Cannon.h"
#include "BallonFactory.h"
#include "Bomb.h"

namespace Btd
{
    void Cannon::PushThrowablePool()
    {
        shared_ptr<Bomb> bomb = make_shared<Bomb>(Bomb());
        bomb->LoadBitmapByString(ThrowablePath, RGB(255, 255, 255));
        throwablePool.push(bomb);
    }
}

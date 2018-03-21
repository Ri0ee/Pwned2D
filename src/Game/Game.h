#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <string>

#include "GameEntity.h"
#include "Structures.h"
#include "Utility.h"

#define DECIPATON 0.02

using std::vector;
using std::string;
using std::cout;

namespace game
{
    class TGame
    {
        public:
            TGame();
            virtual ~TGame();

            void Input(bool* keys);
            void Update(float delta_time);
            void AddEntity(TGameEntity entity);
            void ClearCollisions();
            int FindForwardCollisionM(int eID1, int eID2, float deltaTime, float &penetrationDepth);
            TGameEntity& GetEntity(string entity_name);

            vector<TGameEntity> m_vecEntities;
            vector<collision> m_vecCollisions;

            bool m_msaa;
            bool m_collision_flag;
            float m_collsion_depth;
            int m_sleep_time;
    };
}

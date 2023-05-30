#pragma once
#include "Player.h"
#include "Block.h"
#include "Ball.h"
#include "Constants.h"

void CheckCollisions(Player& player, Block levels[][NUM_BLOCKS], Ball& ball);
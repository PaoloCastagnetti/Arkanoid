#pragma once
#include "Player.h"
#include "Block.h"
#include "Ball.h"
#include "Constants.h"

bool CheckCollisions(Player& player, Ball& ball, Block levels[][NUM_BLOCKS]);
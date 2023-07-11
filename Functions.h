#pragma once
#include <iostream>
#include <random>
#include "HeaderFiles/Block.h"
#include "HeaderFiles/Player.h"
#include "HeaderFiles/Ball.h"

int RandomNumForBlock(int first, int last);
bool allBlocksDestroyed(Block** levels);
void resetPositions(Player& player, Ball& ball);
void loadLevels(Block** levels, int currentLevel);
void handleInput(Player& player);
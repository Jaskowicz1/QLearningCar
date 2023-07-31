#include "../Public/AI.h"

#include "NumCpp.hpp"

void AI::InitalizeQTable()
{
    qTable = nc::zeros<int>(2, 3);
}

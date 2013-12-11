
////////////////////////////////////////////////////////////////////////
//
//  Arturo Cepeda P�rez
//  Pathfinding
//
//  --- AStar.h ---
//
////////////////////////////////////////////////////////////////////////

#pragma once

#include "GraphSearch.h"
#include <cmath>

class AStar : public GraphSearch
{
protected:
    static const float HeuristicWeight;

    int estimateDistance(int nodeFrom, int nodeTo);
};

//  skigrid.h
//
//  Created by James Santos on 5/9/15.
//  Copyright (c) 2015 James Santos. All rights reserved.
//

#ifndef __skigrid__
#define __skigrid__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct gridType {
  int ** data;
  // Cache of longest lenght for each point
  // So we don't need to calculate again
  int ** longest;
  // Cache of steepness for each point from
  // it's longest decreasing length
  int ** steepness;

  // Max drop of the longest decreasing subsequence
  int maxSteep;
  // Max length of the longest decreasing subsequence
  int maxLength;

  int maxPosX;
  int maxPosY;

  int width;
  int height;
} SkiGrid;

typedef struct areaType {
  int width;
  int height;
} Area;

int findLongestSequenceFrom (int i, int j, SkiGrid * grid);
void findLongestSequence (SkiGrid * grid);

Area initArea (FILE * mapFile);
SkiGrid initGrid (Area area);

void freeGrid (SkiGrid * grid);
void fillGrid (SkiGrid * grid, FILE * mapFile);

#endif /* defined(__skigrid__) */

//
//  Created by James Santos on 5/9/15.
//  Copyright (c) 2015 James Santos. All rights reserved.
//

#include "skigrid.h"

int main (int argc, char ** argv) {
  char * mapPath = "./map.txt";
  FILE * mapFile = fopen(mapPath, "r");
  
  if (mapFile == NULL) {
    fprintf(stderr, "Can't open file %s", mapPath);
    exit(1);
  }
  
  Area gridArea = initArea(mapFile);
  SkiGrid grid = initGrid(gridArea);
  
  fillGrid(&grid, mapFile);
  fclose(mapFile);
  findLongestSequence(&grid);
  
  printf("Longest decreasing subsequence: %d\n", grid.maxLength);
  printf("Largest drop from the longest decreasing subsequence: %d\n", grid.maxSteep);
  
  freeGrid(&grid);
  return 0;
}

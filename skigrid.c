//
//  skigrid.c
//
//  Created by James Santos on 5/9/15.
//  Copyright (c) 2015 James Santos. All rights reserved.
//

#include "skigrid.h"

// Finds the longest decreasing subsequence from point i, j to
// its NESW neighbors and records the result so we don't need to
// calculate the longest length for some points again.
int findLongestSequenceFrom (int i, int j, SkiGrid * grid) {
  if (grid->longest[i][j] == 0) {
    int max = 0;
    // Check for neighbors in N,E,S,W
    for (int k = -1; k <= 1; k++) {
      for (int l = -1; l <= 1; l++) {
        if ((abs(k) != abs(l)) && // Don't check diagonal neighbors and itself
          i + k >= 0 && i + k < grid->width && // X bounds check
          j + l >= 0 && j + l < grid->height && // Y bounds check
          grid->data[i + k][j + l] < grid->data[i][j]) {
          int current = findLongestSequenceFrom(i + k, j + l, grid);
          if (current >= max) {
            max = current;
            int steepness = (grid->data[i][j] - grid->data[i + k][j + l]) +
            grid->steepness[i + k][j + l];
            if (grid->steepness[i][j] < steepness) {
              grid->steepness[i][j] = steepness;
            }
          }
        }
      }
    }
    grid->longest[i][j] = max + 1;
  }
  return grid->longest[i][j];
}

void findLongestSequence (SkiGrid * grid) {
  for (int i = 0; i < grid->width; i++) {
    for (int j = 0; j < grid->height; j++) {
      int current = findLongestSequenceFrom(i, j, grid);
      if (current >= grid->maxLength) {
        grid->maxLength = current;
        
        // Compares and swaps maxSteep from previous longest to current
        if (grid->maxPosX != -1 && grid->maxPosY != -1 &&
          grid->steepness[grid->maxPosX][grid->maxPosY] < grid->steepness[i][j])
        {
          grid->maxSteep = grid->steepness[i][j];
        }

        grid->maxPosX = i;
        grid->maxPosY = j;
      }
    }
  }
}

Area initArea (FILE * mapFile) {
  Area mapArea;
  
  char * sep   = " \n";
  char * line  = NULL;
  size_t len   = 0;
  ssize_t read = getline(&line, &len, mapFile);
  char * tok;
  
  if (read != -1) {
    tok = strtok(line, sep);
    mapArea.width = (int)strtol(tok, NULL, 10);
    tok = strtok(NULL, sep);
    mapArea.height = (int)strtol(tok, NULL, 10);
    
    free(line);
  }
  
  return mapArea;
}

// Initializes the grid
SkiGrid initGrid (Area area) {
  SkiGrid grid;
  
  int ** data = (int **)malloc(sizeof(int *) * area.width);
  int ** longest = (int **)malloc(sizeof(int *) * area.width);
  int ** steepness = (int **)malloc(sizeof(int *) * area.width);
  
  for (int i = 0; i < area.width; i++) {
    data[i] = malloc(sizeof(int) * area.height);
    longest[i] = malloc(sizeof(int) * area.height);
    steepness[i] = malloc(sizeof(int) * area.height);
    
    memset(data[i], 0, sizeof(int) * area.height);
    memset(longest[i], 0, sizeof(int) * area.height);
    memset(steepness[i], 0, sizeof(int) * area.height);
  }
  
  for (int i = 0; i < area.width; i++) {
    for (int j = 0; j < area.height; j++) {
      data[i][j] = 0;
      longest[i][j] = 0;
      steepness[i][j] = 0;
    }
  }
  
  grid.data      = data;
  grid.longest   = longest;
  grid.steepness = steepness;
  grid.maxLength = 0;
  grid.maxSteep  = 0;
  grid.height    = area.height;
  grid.width     = area.width;
  grid.maxPosX   = -1;
  grid.maxPosY   = -1;
  
  return grid;
}

void freeGrid (SkiGrid * grid) {
  for (int i = 0; i < grid->width; i++) {
    free(grid->data[i]);
    free(grid->longest[i]);
    free(grid->steepness[i]);
  }
  
  free(grid->data);
  free(grid->longest);
  free(grid->steepness);
}

void fillGrid (SkiGrid * grid, FILE * mapFile) {
  char * sep  = " \n";
  char * line = NULL;
  size_t len  = 0;
  
  int row = 0, col = 0;
  
  ssize_t read;
  char * tok;
  while ((read = getline(&line, &len, mapFile)) != -1) {
    if (row < grid->height) {
      tok = strtok(line, sep);
      while(tok != NULL) {
        if (col < grid->width) {
          grid->data[row][col++] = (int)strtol(tok, NULL, 10);
        }
        tok = strtok(NULL, sep);
      }
      row++;
      col = 0;
    }
  }
  free(line);
}

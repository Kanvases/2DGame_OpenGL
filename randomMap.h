//
//  randomMap.h
//  Mid_assignment
//
//  Created by 张帆 on 01/04/2018.
//  Copyright © 2018 nil. All rights reserved.
//

#ifndef randomMap_h
#define randomMap_h
#include <stdlib.h>
typedef struct Points{
    int x;
    int y;
}Points;
typedef struct mapPoint{
    Points *p;
    int length;
    
}mapPoint;
int randX(int m, int n);
mapPoint randomPoint(void);

#endif /* randomMap_h */

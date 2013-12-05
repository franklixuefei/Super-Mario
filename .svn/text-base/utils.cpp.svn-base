//
//  utils.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-20.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "utils.h"

int Utils::zeroCut(int number) {
    return number < 0 ? 0 : number;
}

unsigned long Utils::now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}
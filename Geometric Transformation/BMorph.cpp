#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <iterator>

using namespace std;

int shrink_cond[][9] = {{0, 0, 1, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 1},
            {0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 1, 0, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 0, 0, 0, 0},
            {1, 1, 0, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 1, 0, 0, 1, 1},
            {0, 0, 0, 0, 1, 1, 0, 0, 1},
            {0, 0, 1, 0, 1, 1, 0, 0, 1},
            {1, 1, 1, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 1, 1, 1},
            {1, 1, 0, 0, 1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1},
            {0, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 1, 1, 0, 1, 0},
            {0, 1, 1, 0, 1, 1, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 1, 1, 0, 1, 1},
            {1, 1, 0, 0, 1, 1, 0, 0, 1},
            {0, 1, 1, 1, 1, 0, 1, 0, 0},
            {1, 1, 1, 0, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 1, 1, 0, 1, 1, 1},
            {0, 0, 0, 0, 1, 1, 1, 1, 1},
            {0, 0, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 1, 1},
            {0, 0, 1, 0, 1, 1, 1, 1, 1},
            {0, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1},
            {0, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 0},
            {1, 1, 0, 1, 1, 0, 1, 1, 1},
            {1, 0, 0, 1, 1, 1, 1, 1, 1},
            {0, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1}};


int shrink_uncond[][9] = {
        {0, 0, 1, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 1, 1},
        {0, 1, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 0, 0, 1, 0},
        {1, 1, 0, 1, 1, 0, 0, 1, 1},
        {1, 1, 0, 1, 1, 0, 1, 0, 0},
        {1, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 1, 0, 1, 1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1, 0, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 0, 1, 1},
        {0, 1, 0, 0, 1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0},
        {1, 1, 0, 1, 1, 1, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 0, 1},
        {1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 0},
        {1, 0, 0, 1, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 1, 0},
        {1, 1, 0, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 1},
        {0, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 1, 1, 0, 1},
        {0, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 0, 1, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 0, 0, 1, 1, 0, 1, 1, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 0},
        {1, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0},
        {1, 0, 0, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 1},
        {0, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 0},
        {1, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 0, 0, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0},
        {1, 1, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 1, 1, 0, 1},
        {0, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 1, 1},
        {0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0},
        {1, 1, 0, 1, 1, 0, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 0},
        {1, 0, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 0},
        {1, 0, 0, 1, 1, 0, 1, 1, 1},
        {0, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 0, 1, 0, 0},
        {1, 1, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 0, 1, 1, 1},
        {0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 1, 1, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1, 1, 1, 1, 1},
        {0, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 0},
        {1, 0, 0, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 0},
        {1, 0, 0, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1}
        };

int border_extnsn(int index, int height){

    if(index<0){
        return (-index);
    }

    else if(index>=height){
        return(2*height-index-2);
    }
    else{
        return index;
    }

}



int convolutionMorph(int maskindex, int maskselect, int input_image[375][375], int row, int col, int image_Height, int image_Width){

    int morphsum = 0;
    int maskcount = 0;
//    int maskHlf = 1;
//    cout<<"im here"<<endl;

    if(maskselect == 0){
        for(int h=0;h<3;h++){
            for(int w=0;w<3;w++){
//                morphsum+= (shrink_cond[maskindex][w+maskcount]/255 * input_image[border_extnsn(row+h-1,image_Height)][border_extnsn(col+w-1,image_Height)]/255);
                if((shrink_cond[maskindex][w+maskcount]*255) == input_image[border_extnsn(row+h-1,image_Height)][border_extnsn(col+w-1,image_Height)]){
                    morphsum++;
                }
//                cout<<"SCond "<<shrink_cond[maskindex][w+maskcount]*255<<endl;
            }
            maskcount += 3;
        }
//        cout<<"cond"<<endl;
//        cout<<morphsum<<endl;
        return morphsum;
    }
    else{
        for(int h=0;h<3;h++){
            for(int w=0;w<3;w++){
//                morphsum+= (shrink_uncond[maskindex][w+maskcount]/255 * input_image[border_extnsn(row+h-1,image_Height)][border_extnsn(col+w-1,image_Height)]/255);
                if((shrink_uncond[maskindex][w+maskcount]*255) == input_image[border_extnsn(row+h-1,image_Height)][border_extnsn(col+w-1,image_Height)]){
                    morphsum++;
                }
            }
//            cout<<"uncond"<<endl;
//            cout<<morphsum<<endl;
            maskcount += 3;
        }
        return morphsum;
    }

}


void morphParser(int Image[][375], int Height, int Width){

    int inputCopy[375][375] = {0};
    int interImage[375][375] = {0};
    int finalImage[375][375] = {0};
    int update = 0;
    int iterate = 1;
    int counter = 0;

    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            inputCopy[i][j] = Image[i][j];
        }
    }

    while(iterate){

        counter = 0;
//        for(int c=0;c<sizeof(shrink_cond)/sizeof(*shrink_cond);c++){
//            for(int i=0;i<Height;i++){
//                for(int j=0;j<Width;j++){
//                    update = convolutionMorph(c,0,Image,i,j,Height,Width);
////                    cout<<"check "<<update<<endl;
//                    if(update == 9){
//                        interImage[i][j] = 255;
//                    }
//                    else{
//                        interImage[i][j] = 0;
//                        counter++;
//                    }
//                }
//            }
//        }

        for(int i=0;i<Height;i++){
            for(int j=0;j<Width;j++){

                    if(Image[i][j]==255){
                    for(int c=0;c<sizeof(shrink_cond)/sizeof(*shrink_cond);c++){

                        update = convolutionMorph(c,0,Image,i,j,Height,Width);
    //                    cout<<"check "<<update<<endl;
                        if(update == 9){
                            break;
                        }

                    }

                    if(update == 9){
                        interImage[i][j] = 255;
//                        counter++;
                    }
                    else{
                        interImage[i][j] = 0;
                    }
                    }
                    else{
                        interImage[i][j] = Image[i][j];
                    }

            }
        }



//        for(int i=0;i<Height;i++){
//            for(int j=0;j<Width;j++){
//                cout<<"inter "<<interImage[i][j]<<endl;
//
//            }
//        }
//        cout<<"count1 "<<counter<<endl;
//        cout<<"two"<<endl;
//        cout<<finalImage[i][j]<<endl;

//        for(int c=0;c<sizeof(shrink_uncond)/sizeof(*shrink_uncond);c++){
//            for(int i=0;i<Height;i++){
//                for(int j=0;j<Width;j++){
//                    update = convolutionMorph(c,1,interImage,i,j,Height,Width);
////                    cout<<"check "<<update<<endl;
//                    if(update == 9){
//                        finalImage[i][j] = 255;
//                        counter++;
//                    }
//                    else{
//                        finalImage[i][j] = 0;
//                    }
//                }
//            }
//        }


        for(int i=0;i<Height;i++){
            for(int j=0;j<Width;j++){
                    if(interImage[i][j] == 255){
                    for(int c=0;c<sizeof(shrink_uncond)/sizeof(*shrink_uncond);c++){

                        update = convolutionMorph(c,1,interImage,i,j,Height,Width);
    //                    cout<<"check "<<update<<endl;
                        if(update == 9){
                            break;
                        }

                    }

                    if(update == 9){
                        finalImage[i][j] = 255;
//                        counter++;
                    }
                    else{
                        finalImage[i][j] = 0;
                    }
                    }
                    else{
                        finalImage[i][j] = interImage[i][j];
                    }


            }
        }


//        cout<<"count2 "<<counter<<endl;
//        counter = 0;

        int updateCond = 0;
        for(int i=0;i<Height;i++){
            for(int j=0;j<Width;j++){
                updateCond = Image[i][j] and ((not interImage[i][j]) or finalImage[i][j]);
//                cout<<"Ucond"<<updateCond<<endl;
                if(updateCond){
                    finalImage[i][j] = 255;
                }
                else{
                    finalImage[i][j] = 0;
                }

            }
        }
        counter = 0;
        for(int i=0;i<Height;i++){
            for(int j=0;j<Width;j++){
                if(Image[i][j] == finalImage[i][j]){
                    counter++;
                }

            }
        }
        cout<<"count"<<counter<<endl;
        if(counter == (Height*Width)){
            for(int i=0;i<Height;i++){
                for(int j=0;j<Width;j++){
                    Image[i][j] = finalImage[i][j];
                    iterate = 0;
                }
            }
        }
        else{
            for(int i=0;i<Height;i++){
                for(int j=0;j<Width;j++){
                    Image[i][j] = finalImage[i][j];
                    iterate = 1;
                }
            }
        }

//        cout<<"it"<<endl;
    }


}

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	const int BytesPerPixel = 1;
	int Size = 375;
	int Height = 375;
	int Width = 375;

	// Check for proper syntax
//	if (argc < 3){
//		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
//		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
//		return 0;
//	}
//
//	// Check if image is grayscale or color
//	if (argc < 4){
//		BytesPerPixel = 1; // default is grey image
//	}
//	else {
//		BytesPerPixel = atoi(argv[3]);
//		// Check if size is specified
//		if (argc >= 5){
//			Size = atoi(argv[4]);
//		}
//	}

	// Allocate image data array
	unsigned char Imagedata[Height][Width][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    cout << "Length of array = " << (sizeof(shrink_cond)/sizeof(*shrink_cond)) << endl;
    cout << "Length of array = " << (sizeof(shrink_uncond)/sizeof(*shrink_uncond)) << endl;
    int originalImage[375][375];

    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            originalImage[i][j] = (int)Imagedata[i][j][0];
        }
    }


    morphParser(originalImage, Height, Width);
    for(int i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
//                cout<<originalImage[i][j]<<endl;
            Imagedata[i][j][0] = (unsigned char)originalImage[i][j];
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite((unsigned char*)Imagedata, sizeof(unsigned char), Height*Width*BytesPerPixel, file);
	fclose(file);

	return 0;
}

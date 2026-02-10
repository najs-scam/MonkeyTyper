//
// Created by szgod on 04.05.2025.
//

#ifndef STATSOBJECT_H
#define STATSOBJECT_H
#pragma once
#include "Difficulty.h"


class StatsObject {
public:
    StatsObject(
        int minutes,
        int seconds,
        int score,
        int total_words,
        float words_per_minute,
        Difficulty difficulty);

    StatsObject(const StatsObject &other);

    int minutes;
    int seconds;
    int score;
    int totalWords;
    float wordsPerMinute;
    Difficulty difficulty;
};



#endif //STATSOBJECT_H

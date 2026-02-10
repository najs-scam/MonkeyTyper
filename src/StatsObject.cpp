
#include "StatsObject.h"

StatsObject::StatsObject(int minutes, int seconds, int score, int total_words, float words_per_minute, Difficulty difficulty):
    minutes(minutes), seconds(seconds), score(score),
    totalWords(total_words), wordsPerMinute(words_per_minute),
    difficulty(difficulty) { }

StatsObject::StatsObject(const StatsObject &other)
: minutes(other.minutes), seconds(other.seconds), score(other.score),
  totalWords(other.totalWords), wordsPerMinute(other.wordsPerMinute),
  difficulty(other.difficulty) { }


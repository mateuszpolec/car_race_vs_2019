#include "Options.h"

float mathDotProductCalculation(const sf::Vector2f& lv, const sf::Vector2f& rv) {
	return lv.x * rv.x + lv.y * rv.y;
}

int randomValueFromScope(int start, int scope) {
	return rand() % scope + start;
}

bool isThereAnyDuplicates(std::vector<int>& pointsToSort) {
	for (short i = 0; i < pointsToSort.size(); ++i) {
		for (short j = 0; j < pointsToSort.size(); ++j) {
			if (i != j) {
				if (pointsToSort[i] == pointsToSort[j]) {
					return true;
				}
			}
		}
	}
	return false;
}

void removeDuplicatesFromVector(std::vector<int>& pointsToSort) {
	for (short i = 0; i < pointsToSort.size(); ++i) {
		for (short j = 0; j < pointsToSort.size(); ++j) {
			if (i != j) {
				if (pointsToSort[i] == pointsToSort[j]) {
					pointsToSort[i]++;
				}
			}
		}
	}
}
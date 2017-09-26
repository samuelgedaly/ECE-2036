#include <iostream>
#include <fstream>
#include "histogram.h"

using namespace std;


	WordUnit::WordUnit(string txt) {
		text = txt;
		times = 1;
	}
	WordUnit::WordUnit() {
		
	}
	string WordUnit::getText() {
		return text;
	}
	void WordUnit::addTimes() {
		times++;
	}
	int WordUnit::getTimes() {
		return times;
	}


	WordHistogram::WordHistogram(string fn) {
		//WordUnit histogram[10000];
		filename = fn;
		size = 0;
	}
	void WordHistogram::makeHistogram() {
		ifstream file(filename, ios::out);
		//file.open(filename);
		// if (!file.is_open()) 
		// 	return;

		string word;
		bool isInside;
		while(file >> word) {
			isInside = false;
			int i;
			for (i = 0; i < size; i++) {
				if (word == histogram[i].getText()) {
					histogram[i].addTimes();
					isInside = true;
					break;
				}
			}
			if (isInside == false) {
				histogram[size] = WordUnit(word);
				size++;
			}
		}
	}
	void WordHistogram::sortAlphaHistogram() {
		quickSortAlpha(histogram, 0, size - 1);
	}
	void WordHistogram::quickSortAlpha(WordUnit arr[], int left, int right) {
     	int i = left, j = right;
      	WordUnit tmp;
      	WordUnit pivot = arr[(left + right) / 2];
 
      /* partition */
      	while (i <= j) {
            while (arr[i].getText() < pivot.getText())
                  i++;
            while (arr[j].getText() > pivot.getText())
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      	};
 
      /* recursion */
      	if (left < j)
            quickSortAlpha(arr, left, j);
      	if (i < right)
            quickSortAlpha(arr, i, right);
	}
	void WordHistogram::sortFreqHistogram() {
		quickSortFreq(histogram, 0, size - 1);
	}
	void WordHistogram::quickSortFreq(WordUnit arr[], int left, int right) {
     	int i = left, j = right;
      	WordUnit tmp;
      	WordUnit pivot = arr[(left + right) / 2];
 
      /* partition */
      	while (i <= j) {
            while (arr[i].getTimes() > pivot.getTimes())
                  i++;
            while (arr[j].getTimes() < pivot.getTimes())
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      	};
 
      /* recursion */
      	if (left < j)
            quickSortFreq(arr, left, j);
      	if (i < right)
            quickSortFreq(arr, i, right);
	}
	void WordHistogram::exportHistogram(string filename) {
		ofstream file(filename, ios::out);
		//file.open (filename);
		int i;
		for (i = 0; i < size; i++) {
			file << histogram[i].getText() << " " << histogram[i].getTimes() << endl;
		}
		file.close();
	}


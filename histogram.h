#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class WordUnit {
private:
	string text;
	int times;
public:

	WordUnit();
	WordUnit(string txt);

	string getText();

	void addTimes();

	int getTimes();
};

class WordHistogram {
private:
	WordUnit histogram[10000];
	int size;
	string filename;
public:
	WordHistogram(string fn);

	void makeHistogram();

	void sortAlphaHistogram();

	void quickSortAlpha(WordUnit arr[], int left, int right);

	void sortFreqHistogram();

	void quickSortFreq(WordUnit arr[], int left, int right);

	void exportHistogram(string filename);

};
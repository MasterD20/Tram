// Tramvai.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <vector>

using namespace std;

class WayPair
{
public:
	WayPair(uint32_t start, uint32_t stop);
	~WayPair();
	uint32_t GetStart();
	uint32_t GetStop();
	void SetStart(uint32_t start);
	void SetStop(uint32_t stop);

private:
	uint32_t start = 0;
	uint32_t stop = 0;
};

WayPair::WayPair(uint32_t start, uint32_t stop)
{
	this->start = start;
	this->stop = stop;
}

WayPair::~WayPair()
{
}

uint32_t WayPair::GetStart()
{
	return this->start;
}

uint32_t WayPair::GetStop()
{
	return this->stop;
}

void WayPair::SetStart(uint32_t start)
{
	this->start = start;
}

void WayPair::SetStop(uint32_t stop)
{
	this->stop = stop;
}

class Way
{
public:
	Way(uint32_t id);
	~Way();
	void AddPair(uint32_t start, uint32_t stop);
	int GetCountPairs();
	WayPair GetPair(int id);
	uint32_t GetId();
	void SetPair(int id, uint32_t start, uint32_t stop);
	void SetPair(int id, uint32_t stop);
	vector<WayPair>& GetPairs();

private:
	vector<WayPair> way;
	uint32_t id;
};

Way::Way(uint32_t id)
{
	this->id = id;
}

Way::~Way()
{
	this->way.clear();
}

void Way::AddPair(uint32_t start, uint32_t stop)
{
	WayPair tmp = WayPair(start, stop);
	this->way.push_back(tmp);
}

int Way::GetCountPairs()
{
	return this->way.size();
}

WayPair Way::GetPair(int id)
{
	return this->way.at(id);
}

uint32_t Way::GetId()
{
	return id;
}

void Way::SetPair(int id, uint32_t start, uint32_t stop)
{
	this->way.at(id).SetStart(start);
	this->way.at(id).SetStop(stop);
}

void Way::SetPair(int id, uint32_t stop)
{
	this->SetPair(id, this->way.at(id).GetStart(), stop);
}

vector<WayPair>& Way::GetPairs()
{
	return this->way;
}

uint32_t min(uint32_t v1, uint32_t v2) {
	if (v1 > v2) {
		return v2;
	}
	return v1;
}
uint32_t max(uint32_t v1, uint32_t v2) {
	if (v1 < v2) {
		return v2;
	}
	return v1;
}
int main()
{
	ifstream infile("C:\\Users\\IhorVoronin\\source\\repos\\Tramvai\\Debug\\test3-in.txt");
	int count = 0;
	int m = 0;
	int n = 0;
	int ways = 0;

	uint32_t row = 0;
	uint32_t c1 = 0;
	uint32_t c2 = 0;

	vector< Way > data;

	if (!infile.is_open()) {
		cout << "Couldn't find file";
		return 0;
	}

	infile >> m >> n >> ways;

	

	while (infile >> row >> c1 >> c2)
	{
		for (Way& way_selected : data) {
			if (int(way_selected.GetId()) == int(row))
			{
				way_selected.AddPair(c1, c2);
			}
		}
		Way tmp = Way(row);
		tmp.AddPair(c1, c2);
		data.push_back(tmp);
	}

	uint32_t counter = 0;
	for (Way& way_selected : data) {
		int pairs_count = way_selected.GetCountPairs();
		if (pairs_count <= 1) {
			continue;
		}
		for (int i = 0; i < pairs_count - 1; i++) {
			if ((way_selected.GetPair(i).GetStart() > way_selected.GetPair(i + 1).GetStart() &&
				way_selected.GetPair(i).GetStart() < way_selected.GetPair(i + 1).GetStop()) ||
				(way_selected.GetPair(i).GetStop() > way_selected.GetPair(i + 1).GetStart() &&
					way_selected.GetPair(i).GetStart() < way_selected.GetPair(i + 1).GetStop())) {

				way_selected.GetPair(i + 1).SetStart(
					min(way_selected.GetPair(i).GetStart(), way_selected.GetPair(i + 1).GetStart())
				);
				way_selected.GetPair(i + 1).SetStop(
					min(way_selected.GetPair(i).GetStop(), way_selected.GetPair(i + 1).GetStop())
				);
				way_selected.GetPair(i).SetStart(0);
				way_selected.GetPair(i).SetStop(0);

			}

		}

		for (int i = 0; i < pairs_count; i++) {
			if (way_selected.GetPair(i).GetStart() != 0 && way_selected.GetPair(i).GetStop() != 0) {
				counter += way_selected.GetPair(i).GetStop() - way_selected.GetPair(i).GetStart() + 1;
				cout << way_selected.GetPair(i).GetStart() << " \t " << way_selected.GetPair(i).GetStop() << endl;
			}
		}
	}
	//int count = 0;
	/*for (int i = 0; i < m; ++i) {
		count += n - (ways_array[i][1] - ways_array[i][0] + 1);
	}*/
	cout << "Result: " << counter;
	cin >> m;
    return 0;
}


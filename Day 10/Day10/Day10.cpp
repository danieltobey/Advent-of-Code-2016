// Day10.cpp : From http://adventofcode.com/2016/day/10
//

#include "stdafx.h"
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> vecTokenize(string in, const char* delims)
{
	vector<string> out;

	int start = 0;
	for (int i = 0; i < in.length(); i++)
	{
		for (int j = 0; delims[j] != NULL; j++)
		{
			if (in[i] == delims[j])
			{
				out.push_back(in.substr(start, i - start));
				start = i + 1;
				break;
			}
		}
	}

	out.push_back(in.substr(start, in.length() - start));

	return out;
}

class CBots {
	// List of bots
	//  index of map is bot's ID
	//  pair is the pair of numbers bot is holding
	//   should set to -1 if bot is not holding a number
	//   left should be low, right should be high
public:
	bool Give(int botFrom, int botTo, bool low);
	void Give(int botTo, int val);
	bool CanTake(int botFrom);
	int Take(int botFrom, bool low);
	void Put(int botFrom, int output, bool low);

private:
	map<int, pair<int, int>> bots;
	map<int, int> outputs;
};

// Returns false if move not possible
bool CBots::Give(int botFrom, int botTo, bool low)
{
	int val = Take(botFrom, low);
	Give(botTo, val);
	return true;
}

void CBots::Give(int botTo, int val)
{
	// Bot doesn't exist or has no values
	if (bots.find(botTo) == bots.end() || bots[botTo].first == MAXINT)
	{
		bots[botTo].first = val;
		bots[botTo].second = MAXINT;
		return;
	}

	// New val is smaller than first val
	if (val < bots[botTo].first)
	{
		bots[botTo].second = bots[botTo].first;
		bots[botTo].first = val;
	}
	else // New val is equal or larger than first val
	{
		bots[botTo].second = val;
	}
}

// Returns true if a bot has both a low or high value
bool CBots::CanTake(int botFrom)
{
	if (bots.find(botFrom) == bots.end())
		return false;

	return bots[botFrom].first != MAXINT && bots[botFrom].second != MAXINT;
}

int CBots::Take(int botFrom, bool low)
{
	int ret = MAXINT;

	// Part 1
	//if (bots[botFrom].first == 17 && bots[botFrom].second == 61)
	//	int x = 0;

	// Low val? Return left side
	if (low)
	{
		ret =  bots[botFrom].first;
		bots[botFrom].first = MAXINT;
	}
	else // Right side
	{
		ret =  bots[botFrom].second;
		bots[botFrom].second = MAXINT;
	}

	return ret;
}

void CBots::Put(int botFrom, int output, bool low)
{
	outputs[output] = Take(botFrom, low);
}


int main()
{
	CBots bots;
	string str;
	ifstream in;
	vector<string> movesNotDone;
	in.open("in.txt");

	// First, find out which number each bot is holding
	while (getline(in, str))
	{
		if (str[0] != 'v')
		{
			// We need to initialize the bots first, so we store all other commands for later
			movesNotDone.push_back(str);
			continue;
		}

		vector<string> toks = vecTokenize(str, " ");
		int val = atoi(toks[1].c_str());
		int bot = atoi(toks[5].c_str());

		bots.Give(bot, val);
	}

	while (true)
	{
		bool ranAMove = false;
		for (int i = 0; i < movesNotDone.size(); i++)
		{
			vector<string> toks = vecTokenize(movesNotDone[i], " ");
			int botFrom = atoi(toks[1].c_str());

			// If we can't take from this bot (it has fewer than both values) then skip command
			if (!bots.CanTake(botFrom))
				continue;

			// We can run this command
			movesNotDone.erase(movesNotDone.begin() + i);
			ranAMove = true;
			int to1 = atoi(toks[6].c_str());
			int to2 = atoi(toks[11].c_str());
			// output
			if (toks[5][0] == 'o')
				bots.Put(botFrom, to1, true);
			else
				bots.Give(botFrom, to1, true);

			if (toks[10][0] == 'o')
				bots.Put(botFrom, to2, false);
			else
				bots.Give(botFrom, to2, false);

		}
		
		// If we ran the entire list and didn't find a move, break
		if (!ranAMove)
			break;
	}


    return 0;
}


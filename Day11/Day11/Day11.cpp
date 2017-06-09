// Day11.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <atlstr.h> 

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

// A floor (or elevator)
struct SFloor {
	// First letter corresponds to isotope
	vector<TCHAR> microchips;
	vector<TCHAR> generators;
};

class CFactory {
public:
	void PrintMap();

	int elevatorLevel;
	vector<SFloor> floors;
	SFloor elevator;
};

void CFactory::PrintMap()
{
	// Print out factory layout
	for (int i = 3; i >= 0; i--)
	{
		CString floorLayout;
		floorLayout.Format(_T("F%d|"), i + 1);
		if (i == elevatorLevel)
			floorLayout.Append(_T("E |"));
		else
			floorLayout.Append(_T("  |"));

		for (int gen = 0; gen < floors[i].generators.size(); gen++)
			floorLayout.AppendFormat(_T("%cG "), floors[i].generators[gen]);

		for (int micro = 0; micro < floors[i].microchips.size(); micro++)
			floorLayout.AppendFormat(_T("%cM "), floors[i].microchips[micro]);

		floorLayout.Append(_T("\n"));

		//_tprintf((TCHAR*)(LPCTSTR)floorLayout);
		_tprintf(_T("%s"), floorLayout);
	}
}

struct SFactoryState {
	CFactory factory;
	SFactoryState *sibling;
	SFactoryState *child;
};

class CMovesTree {
public:
	void GenerateTree(CFactory factory);

private:
	SFactoryState root;
};

void CMovesTree::GenerateTree(CFactory factory)
{
	root.factory = factory;
	root.sibling = NULL;
	root.child = NULL;

	while (true)
	{
		// Try to move a microchip
		//  Cannot: move to a floor with no matching generator
		// Find first microchip
		for (int floor = 0; floor < factory.floors.size(); floor++)
		{
			SFloor sFloor = factory.floors[floor];
			for (int micro = 0; micro < sFloor.microchips.size(); micro++)
			{
				
			}
		}

		// Try to move a generator
		//  Cannot: be moved away from its microchip
		//  Cannot: be moved to a floor where a microchip has no matching generator, unless this is the matching generator

		
		// Try to move a microchip and generator pair


		// Try to move a microchip and a microchip
		//  Follow same rules for microchip


		// Try to move a generator and a generator
		//  Follow same rules for generator
	}
}



int main()
{
	ifstream in;
	string str;
	in.open("in.txt");
	CFactory factory;

	// Fill the factory
	while (getline(in, str))
	{
		vector<string> tokens = vecTokenize(str, " ");

		SFloor floor;
		int tokInd = 5;
		while (tokInd + 1 < tokens.size())
		{
			// Parse isotope
			TCHAR iso = tokens[tokInd][0];

			// Parse whether generator or microchip
			if (tokens[tokInd + 1][0] == 'm')
				floor.microchips.push_back(iso);
			else
				floor.generators.push_back(iso);

			if (tokens.size() - (tokInd + 1) == 5)
				tokInd += 4;
			else
				tokInd += 3;
		}

		factory.floors.push_back(floor);
	}

	factory.PrintMap();

	getc(stdin);

    return 0;
}
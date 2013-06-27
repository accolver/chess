#include "XMLReader.h"
#include "Position.h"
#include "HTMLTokenizer.h"
#include "StringUtil.h"
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "CS240Exception.h"
using namespace std;

//------------------------------------------------------------------------------------------------
XMLReader::XMLReader() {
	inBoard = false;
	inHistory = false;
	inMove = false;
	moveNum = 0;
}

//------------------------------------------------------------------------------------------------
XMLReader::~XMLReader() {
}

//------------------------------------------------------------------------------------------------
deque<Move> XMLReader::Read(string & loadLocation) {
	try {
		ifstream file;	
		file.open(loadLocation.c_str());
		if (!file.is_open()) {
			cout << "Could not open " << loadLocation << endl;
			return moves;
		}
	
		string allXML;
		string line;
		while ( file.good() ) {
			getline (file, line);
			if (line != "" && line != "\n") {
				allXML += line;
			}
		}
		ParseXML(allXML);

		//cout << allXML << endl;
		file.close();
		return moves;
	}
	catch (FileException & e) {
	}
	catch (IOException & e) {
	}
	catch (...) {
	}
	return moves;
}

//------------------------------------------------------------------------------------------------
void XMLReader::ParseXML(string & xml) {

	HTMLTokenizer tokenizer(xml);
	while (tokenizer.HasNextToken()) {

		HTMLToken cur = tokenizer.GetNextToken();
		switch (cur.GetType()) {
			case TAG_START :
				//cout << "TAG_START:" << cur.GetValue() << endl;
				HandleStart(cur);
				break;
			case TAG_END : 
				//cout << "TAG_END:" << cur.GetValue() << endl;
				HandleEnd(cur);
				break;
			case TEXT :
				//cout << "TEXT:" << cur.GetValue() << endl;
				//HandleText(&cur);
				break;
			case END :
				//cout << "END:" << cur.GetValue() << endl;
				//HandleEnd(cur);
				break;
		}
	}
}

//------------------------------------------------------------------------------------------------
void XMLReader::HandleStart (HTMLToken t) {
	string val = StringUtil::ToLowerCopy(t.GetValue());

	if (val == "board")
		inBoard = true;
	else if (val == "history")
		inHistory = true;
	else if (val == "move") {
		moveNum = 1;
		move.SetCaptured(NOTYPE);
		inMove = true;
	}


	if (val == "piece" && inMove) {
		switch(moveNum) {
			case 0 : 
				break;
			case 1 : {
				move.SetType(GetTypeByName(t.GetAttribute("type")));
				move.SetColor(GetColorByName(t.GetAttribute("color")));
				Position pstart;
				pstart.SetRow(atoi((t.GetAttribute("row")).c_str()));
				pstart.SetCol(atoi((t.GetAttribute("column")).c_str()));
				move.SetStart(pstart);
				moveNum++;
				break;
			}
			case 2 : {
				Position pend;
				pend.SetRow(atoi((t.GetAttribute("row")).c_str()));
				pend.SetCol(atoi((t.GetAttribute("column")).c_str()));
				move.SetEnd(pend);
				moveNum++;
				break;
			}
			case 3 :
				move.SetCaptured(GetTypeByName(t.GetAttribute("type")));
				moveNum++;
				break;
		}
	}
}

//------------------------------------------------------------------------------------------------
void XMLReader::HandleEnd (HTMLToken t) {
	string val = StringUtil::ToLowerCopy(t.GetValue());

	if (val == "board")
		inBoard = false;
	else if (val == "history")
		inHistory = false;
	else if (val == "move") {
		moves.push_front(move);
		inMove = false;
		moveNum = 0;
	}
}

//------------------------------------------------------------------------------------------------
Type XMLReader::GetTypeByName(string type) {
	if (type == "pawn")
		return PAWN;
	else if (type == "knight")
		return KNIGHT;
	else if (type == "bishop")
		return BISHOP;
	else if (type == "rook")
		return ROOK;
	else if (type == "queen")
		return QUEEN;
	else if (type == "king")
		return KING;
}

//------------------------------------------------------------------------------------------------
PC XMLReader::GetColorByName(string color) {
	if (color == "white")
		return WHITE;
	else
		return BLACK;
}
//------------------------------------------------------------------------------------------------

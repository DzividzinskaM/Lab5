#include "pch.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;


bool if_flag = false; 
void read_file(ifstream &file, vector<Node*>& AST_tree)
{
	char sym;
	string str;
	bool flag_start = false;
	while (!if_flag && file.get(sym))
	{		
		if (sym != ';')
		{
			if (sym == '{')
			{
				Node* temp = new Node;
				temp->val = "#";
				AST_tree.push_back(temp);
				read_file(file, temp->sons);
				str.clear();
			}
			if (sym == '}') 
			{
				string s0;
				getline(file, s0);
				if (s0!= "else")
					if_flag = true;
				return;
			}
			if (sym != ' ')
				str += sym;
			if (str == "if")
			{
				Node* temp;
				temp = new Node;
				temp->val = "?";
				string s0;
				getline(file, s0);
				temp->sons.push_back(calc(s0));
				AST_tree.push_back(temp);
				read_file(file, temp->sons);
				str.clear();
			}
			if (str == "else") {
				str.clear();
			}
			else if (str == "<<")
				str = "«";
			else if (str == "\n") 
				str.clear();
		}
		else 
		{
			AST_tree.push_back(calc(str));
			str.clear();
		}
	}
	if (if_flag) {
		if_flag = false;
		return;
	}
}

int main()
{
	ifstream file("test.txt");
	vector<Node*> AST_tree;
	read_file(file, AST_tree);
}


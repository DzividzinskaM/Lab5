#include "pch.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include "shunting_yard.h"

using namespace std;

void optimization(Node*);
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
				if (s0 != "else")
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

void show_tree(vector<Node*> AST_tree)
{
	for (int i = 0; i < AST_tree.size(); i++)
	{
		if (AST_tree[i]->val == "«")
		{
			cout << "<<";
			print_inf_bin(AST_tree[i]->sons[1]);
		}
		else if (AST_tree[i]->val == "?")
		{
			cout << "if (" << AST_tree[i]->sons[0]->val << ")" << endl;
			for (int j = 1; j < AST_tree[i]->sons.size(); j++)
			{
				if (j == 2)
					cout << "else" << endl;
				cout << "{" << endl;
				show_tree(AST_tree[i]->sons[j]->sons);
				cout << "}" << endl;
			}
		}

		else
			print_inf_bin(AST_tree[i]);
		cout << ';' << endl;
	}
}

bool is_a_digit(string str) {
	for (int i = 0; i < str.length(); i++)
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.'))
			return false;
	return true;
}

bool is_a_zero(string str) {
	if (str == "0" || str == "0.0" || str == "0.00")
		return true;
	return false;
}

void optimize(Node* AST_tree) {

	if (AST_tree->val == "*" && is_a_zero(AST_tree->sons[0]->val)) {
		AST_tree->val = "0";
		AST_tree->sons.clear();
	}
	else
		if (AST_tree->val == "*" && is_a_zero(AST_tree->sons[1]->val)) {
			AST_tree->val = "0";
			AST_tree->sons.clear();
		}
		else
			if (AST_tree->val == "/" && is_a_zero(AST_tree->sons[0]->val))
			{
				AST_tree->val = "0";
				AST_tree->sons.clear();
			}
			else {
				for (int i = 0; i < AST_tree->sons.size(); i++)
					if (AST_tree->sons[i])
						optimize(AST_tree->sons[i]);
			}
}
int main()
{
	ifstream file("test.txt");
	vector<Node*> AST_tree;
	read_file(file, AST_tree);
	show_tree(AST_tree);
	cout << endl << endl << endl;
	for (int i = 0; i < AST_tree.size(); i++) {
		if (AST_tree[i]) {
			optimize(AST_tree[i]);
		}
	}
	show_tree(AST_tree);
}


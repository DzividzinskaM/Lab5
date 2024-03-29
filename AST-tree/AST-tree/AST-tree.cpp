#include "pch.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include "shunting_yard.h"

using namespace std;


bool if_flag = false; 
void read_file(ifstream &file, vector<node*>& AST_tree)
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
				node* temp = new node;
				temp->value = "#";
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
				node* temp;
				temp = new node;
				temp->value = "?";
				string s0;
				getline(file, s0);
				temp->sons.push_back(calculate(s0));
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
			AST_tree.push_back(calculate(str));
			str.clear();
		}
	}
	if (if_flag) {
		if_flag = false;
		return;
	}
}

void show_tree(vector<node*> AST_tree)
{
	for (int i = 0; i < AST_tree.size(); i++)
	{
		if (AST_tree[i]->value == "«")
		{
			cout << "<<";
			print_inf_bin(AST_tree[i]->sons[1]);
		}
		else if (AST_tree[i]->value == "?")
		{
			cout << "if (" << AST_tree[i]->sons[0]->value << ")" << endl;
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

void optimize(node* AST_tree) {

	if (AST_tree->value == "*" && is_a_zero(AST_tree->sons[0]->value)) {
		AST_tree->value = "0";
		AST_tree->sons.clear();
	}
	else
		if (AST_tree->value == "*" && is_a_zero(AST_tree->sons[1]->value)) {
			AST_tree->value = "0";
			AST_tree->sons.clear();
		}
		else
			if (AST_tree->value == "/" && is_a_zero(AST_tree->sons[0]->value))
			{
				AST_tree->value = "0";
				AST_tree->sons.clear();
			}
			else {
				for (int i = 0; i < AST_tree->sons.size(); i++)
					if (AST_tree->sons[i])
						optimize(AST_tree->sons[i]);
			}
}

string find_result(node* ast, map <string, double>& Map) {
	if (ast->value == "«")
		cout << find_result(ast->sons[1], Map) << endl;
	else if (ast->value == "=") {
		string a = ast->sons[0]->value;
		string b = find_result(ast->sons[1], Map);
		Map[a] = atof(b.c_str());
	}
	else if (ast->value == "#") {
		for (int i = 0; i < ast->sons.size(); i++)
			find_result(ast->sons[i], Map);
	}
	else if (ast->value == "?") {
		double cond;
		if (is_a_digit(ast->sons[0]->value))
			cond = atof(ast->sons[0]->value.c_str());
		else
			cond = Map.at(ast->sons[0]->value);
		if (cond)
			find_result(ast->sons[1], Map);
		else if (ast->sons.size() == 3)
			find_result(ast->sons[2], Map);
	}
	else if (is_operator(ast->value))
	{
		string a, b;
		if (ast->sons[0])
			a = find_result(ast->sons[0], Map);
		else
			a = "0";
		b = find_result(ast->sons[1], Map);
		double result = calculator(ast->value, atof(a.c_str()), atof(b.c_str()));
		std::ostringstream ost;
		ost << result;
		return ost.str();
	}
	else if (is_a_digit(ast->value)) {
		return ast->value;
	}
	else
	{
		double result = Map.at(ast->value);
		std::ostringstream ost;
		ost << result;
		return ost.str();
	}
	return "";
}

int main()
{
	ifstream file("test.txt");
	if (!file.is_open())
		cout << "error" << endl;
	map <string, double> Map;
	vector<node*> AST_tree;
	read_file(file, AST_tree);
	show_tree(AST_tree);
	cout << endl << endl << endl;
	for (int i = 0; i < AST_tree.size(); i++) 
		if (AST_tree[i]) 
			optimize(AST_tree[i]);
	
	show_tree(AST_tree);
	for (int i = 0; i < AST_tree.size(); i++) {
		find_result(AST_tree[i], Map);
	}
	system("pause");
	return 0;
}

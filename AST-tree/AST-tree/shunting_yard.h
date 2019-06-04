#pragma once

#ifndef shunting_yard
#define shunting_yard

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <map>
#include <cstdlib>
#include <sstream>

using namespace std;

struct node {
	string value;
	vector<node*> sons;
};
struct stack {
	node* data;
	stack* next;
};
string delete_space(string s);
void print_postf_bin(node* root);
void print_inf_bin(node* root);
void push_str(stack**, string);
void push_node(stack** s, node** node);
string get_front(stack*);
node* pop(stack**);
node* calculate(string);
string get_op(char s);
int get_priority(string op);
double calculator(string, double , double );
bool is_operator(string);


#endif

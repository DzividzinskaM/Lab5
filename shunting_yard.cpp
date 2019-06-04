#include <iostream>
#include "shunting_yard.h"

using namespace std;

void print_postf_bin(node* root){
	if (root->sons.size() != 0)
		for (int i = 0; i < root->sons.size(); i++)
			print_postf_bin(root->sons[i]);
	cout << root->value;
}
void print_inf_bin(node* root){
	if (root->sons.size() != 0)
		print_inf_bin(root->sons[0]);
	cout << root->value;
	if (root->sons.size() != 0)
		print_inf_bin(root->sons[1]);
}

void push_str(stack** s, string data)
{
	node* t = new node;
	t->value = data;
	stack* tmp = new stack;
	tmp->data = t;
	tmp->next = *s;
	*s = tmp;
}
void push_node(stack** s, node** node)
{
	stack* tmp = new stack;
	tmp->data = *node;
	tmp->next = *s;
	*s = tmp;
}
int main() {
	system("pause");
	return 0;
}


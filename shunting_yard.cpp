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

void push_str(stack** s, string data){
	node* t = new node;
	t->value = data;
	stack* temporary = new stack;
	temporary->data = t;
	temporary->next = *s;
	*s = temporary;
}
void push_node(stack** s, node** node){
	stack* temporary = new stack;
	temporary->data = *node;
	temporary->next = *s;
	*s = temporary;
}
string get_front(stack* s){
	if (!s) return "\0";
	return s->data->value;
}

node* pop(stack** s){
	if (*s == nullptr) return nullptr;
	node* t = (*s)->data;
	stack* tmp = (*s)->next;
	delete (*s);
	(*s) = tmp;
	return t;
}

void apply_bin(stack** operators, stack** output){
	node* result;
	result = pop(operators);
	node* x = pop(output);
	result->sons.push_back(pop(output));
	result->sons.push_back(x);
	push_node(output, &result);
}
int main() {
	system("pause");
	return 0;
}


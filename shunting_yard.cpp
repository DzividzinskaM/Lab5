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
int main() {
	system("pause");
	return 0;
}


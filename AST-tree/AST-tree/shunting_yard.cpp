#include "pch.h"
#include "shunting_yard.h"

using namespace std;

void print_postf_bin(node* root) {
	if (root->sons.size() != 0)
		for (int i = 0; i < root->sons.size(); i++)
			print_postf_bin(root->sons[i]);
	cout << root->value;
}
void print_inf_bin(node* root) {
	if (root->sons.size() != 0)
		print_inf_bin(root->sons[0]);
	cout << root->value;
	if (root->sons.size() != 0)
		print_inf_bin(root->sons[1]);
}

void push_str(stack** s, string data) {
	node* t = new node;
	t->value = data;
	stack* temporary = new stack;
	temporary->data = t;
	temporary->next = *s;
	*s = temporary;
}
void push_node(stack** s, node** node) {
	stack* temporary = new stack;
	temporary->data = *node;
	temporary->next = *s;
	*s = temporary;
}
string get_front(stack* s) {
	if (!s) return "\0";
	return s->data->value;
}

node* pop(stack** s) {
	if (*s == nullptr) return nullptr;
	node* t = (*s)->data;
	stack* tmp = (*s)->next;
	delete (*s);
	(*s) = tmp;
	return t;
}

void apply_bin(stack** operators, stack** output) {
	node* result;
	result = pop(operators);
	node* x = pop(output);
	result->sons.push_back(pop(output));
	result->sons.push_back(x);
	push_node(output, &result);
}

string get_op(char s) {
	switch (s) {
	case '+':
		return "+";
	case '-':
		return "-";
	case '/':
		return "/";
	case '*':
		return "*";
	case '^':
		return "^";
	case '«':
		return "«";
	case '=':
		return "=";
	default:
		return "";
	}
}

string delete_space(string s) {
	string rez = "";
	for (int i = 0; i < s.length(); i++)
		if (s[i] != ' ')
			rez += s[i];
	return rez;
}

double calculator(string op, double a, double b) {
	if (op == "+")
		return a + b;
	if (op == "-")
		return a - b;
	if (op == "*")
		return a * b;
	if (op == "/")
		return a / b;
	if (op == "^")
		return pow(a, b);
}
bool is_operator(string s) {
	if (s == "+" || s == "-" || s == "*" || s == "/" || s == "^")
		return true;
	return false;
}
int get_priority(string op)
{
	if (op == "«")
		return 6;
	if (op == "=")
		return 5;
	if (op == "(")
		return 4;
	if (op == "+" || op == "-")
		return 3;
	if (op == "/" || op == "*")
		return 2;
	if (op == "^")
		return 1;
}
node* calculate(string expr){
	stack* operators = nullptr;
	stack* output = nullptr;
	expr = delete_space(expr);
	int i = 0;
	while (expr[i] != '\0') {
		if ((expr[i] >= '0' && expr[i] <= '9') || (expr[i] >= 'a' && expr[i] <= 'z')) {
			string num = "";
			while ((expr[i] >= '0' && expr[i] <= '9') || (expr[i] >= 'a' && expr[i] <= 'z') || expr[i] == '.') {
				num += expr[i];
				i++;
			}
			push_str(&output, num);
			i--;
		}
		else if (get_op(expr[i]) != "") {
			string op = get_op(expr[i]); {
				int p = get_priority(op);
				if (p != 1)
					while (operators != nullptr && p >= get_priority(get_front(operators)))
					{
						apply_bin(&operators, &output);
					}
				push_str(&operators, op);
			}
		}
		else if (expr[i] == '(') {
			push_str(&operators, "(");
		}
		else if (expr[i] == ')') {
			while (get_front(operators) != "(") {
				apply_bin(&operators, &output);
			}
			pop(&operators);
		}
		i++;
	}
	while (operators != nullptr) {
		apply_bin(&operators, &output);
	}
	return pop(&output);
}

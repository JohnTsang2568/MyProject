#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct node
{
	int digit;
	node* prev;
	node* next;
	node() { prev = nullptr, next = nullptr; }
};

struct num
{
	node* head;
	node* tail;
	bool neg;
	int len;
};
void insertnum(int d, num& a)
{
	node* now = new node;
	now->digit = d;
	now->prev = nullptr;
	now->next = a.head;
	if (a.head != nullptr)a.head->prev = now;
	else a.tail = now;
	a.head = now;
	a.len++;
}

int comabs(num a, num b)
{
	if (a.len != b.len)
	{
		return ((a.len > b.len ? 1 : -1));
	}
	else
	{
		node* now1; node* now2;
		now1 = a.tail; now2 = b.tail;
		while (now1 != nullptr && now2 != nullptr)
		{
			if (now1->digit != now2->digit)return (now1->digit > now2->digit ? 1 : -1);
			now1 = now1->prev; now2 = now2->prev;
		}
		return 0;
	}
}

void rlz(num& a)
{
	while (a.tail != nullptr && a.tail->digit == 0 && a.len > 1)
	{
		node* now;
		now = a.tail;
		a.tail = a.tail->prev;
		a.len--;
		if (a.tail != nullptr)a.tail->next = nullptr;
		delete now;
	}
	return;
}
void rev(num& result) {
	node* current = result.head;
	node* prev = nullptr;
	while (current != nullptr) {
		node* next = current->next;
		current->next = prev;
		current->prev = next;
		prev = current;
		current = next;
	}
	node* temp = result.head;
	result.head = result.tail;
	result.tail = temp;
	return;
}
num addabs(num a, num b)
{
	node* now1 = a.head; node* now2 = b.head; int carry = 0; int curr = 0;
	num result;
	result.head = nullptr; result.tail = nullptr; result.neg = false; result.len = 0;
	while (now1 != nullptr || now2 != nullptr || carry != 0)
	{
		curr = carry;
		if (now1 != nullptr)
		{
			curr += now1->digit;
			now1 = now1->next;
		}
		if (now2 != nullptr)
		{
			curr += now2->digit;
			now2 = now2->next;
		}
		insertnum(curr % 10, result);
		carry = curr / 10;
	}
	rev(result);
	rlz(result);
	return result;
}
num subabs(num a, num b)
{
	node* now1 = a.head; node* now2 = b.head; int borr = 0; int curr = 0;
	num result;
	result.head = nullptr; result.tail = nullptr; result.neg = false; result.len = 0;
	while (now1 != nullptr)
	{
		curr = now1->digit - borr;
		if (now2 != nullptr)
		{
			curr -= now2->digit;
			now2 = now2->next;
		}
		now1 = now1->next;
		if (curr < 0)
		{
			curr += 10;
			borr = 1;
		}
		else borr = 0;
		insertnum(curr, result);
	}
	rev(result);
	rlz(result);
	return result;
}

void dele(num& a)
{
	node* now;
	while (a.tail != nullptr)
	{
		now = a.tail;
		a.tail = a.tail->prev;
		if (a.tail != nullptr) a.tail->next = nullptr;
		a.len--;
		delete now;
	}
	a.head = nullptr; a.tail = nullptr; a.len = 0; a.neg = false;
}


num gen(string s)
{
	num n; n.head = nullptr; n.tail = nullptr; n.neg = false; n.len = 0; string temp = "";
	if (!s.empty() && s[0] == '-') {
		n.neg = true;
		temp = s.substr(1);
	}
	else temp = s;
	temp.erase(remove(temp.begin(), temp.end(), ','), temp.end());
	for (int i = 0; i < temp.length(); i++)
	{
		if (isdigit(temp[i]))
		{
			insertnum((temp[i] - '0'), n);
		}
	}
	if (n.head == nullptr)insertnum(0, n);
	rlz(n);
	return n;
}

num add(num a, num b)
{
	num result;
	if (a.neg == b.neg)
	{
		result = addabs(a, b);
		result.neg = a.neg;
	}
	else
	{
		if (comabs(a, b) >= 0)
		{
			result = subabs(a, b);
			result.neg = a.neg;
		}
		else
		{
			result = subabs(b, a);
			result.neg = b.neg;
		}
	}
	if (result.len == 1 && result.head->digit == 0)
	{
		result.neg = false;
	}
	return result;
}

num sub(num a, num b)
{
	num result; num negb;
	negb.head = nullptr; negb.tail = nullptr; negb.neg = !(b.neg); negb.len = 0;
	node* current = b.tail;
	while (current != nullptr)
	{
		insertnum(current->digit, negb);
		current = current->prev;
	}
	result = add(a, negb);
	dele(negb);
	return result;
}

string tostr(const num a) {
	if (a.head == nullptr) return "0";
	string result;
	node* current = a.tail;
	while (current != nullptr) {
		result += char(current->digit + '0');
		current = current->prev;
	}
	string format;
	int cnt = 0;
	for (int i = result.size() - 1; i >= 0; --i) {
		format += result[i];
		cnt++;
		if (cnt % 3 == 0 && i != 0) {
			format += ',';
		}
	}
	reverse(format.begin(), format.end());
	if (a.neg && !(a.len == 1 && a.head->digit == 0)) {
		format.insert(0, 1, '-');
	}
	return format;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char op;
		string num1, num2;
		cin >> op;
		cin.ignore();
		getline(cin, num1);
		getline(cin, num2);
		num a = gen(num1);
		num b = gen(num2);
		num result;
		if (op == '+') {
			result = add(a, b);
		}
		else if (op == '-') {
			result = sub(a, b);
		}
		cout << tostr(result) << endl;
		dele(a); dele(b);
		dele(result);
	}
	return 0;
}

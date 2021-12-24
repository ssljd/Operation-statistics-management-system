#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

const int ROW = 3;
const int COL = 3;
const int MAXDISTANCE = 10000;
const int MAXNUM = 10000;

typedef struct _Node {
	int digit[ROW][COL];
	int dist; // distance between one state and the destination
	int dep; // the depth of node
	// So the comment function = dist + dep.
	int index; // point to the location of parent
} Node;

Node src, dest;

vector<Node> node_v; // store the nodes

bool isEmptyOfOPEN() {
	for (int i = 0; i < node_v.size(); i++) {
		if (node_v[i].dist != MAXNUM)
			return false;
	}
	return true;
}

bool isEqual(int index, int digit[][COL]) {
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			if (node_v[index].digit[i][j] != digit[i][j])
				return false;
		}
	return true;
}

ostream& operator<<(ostream& os, Node& node) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++)
			os << node.digit[i][j] << ' ';
		os << endl;
	}
	return os;
}

void PrintSteps(int index, vector<Node>& rstep_v) {
	rstep_v.push_back(node_v[index]);
	index = node_v[index].index;
	while (index != 0) {
		rstep_v.push_back(node_v[index]);
		index = node_v[index].index;
	}

	for (int i = rstep_v.size() - 1; i >= 0; i--)
		cout << "Step " << rstep_v.size() - i
		<< endl << rstep_v[i] << endl;
}

void Swap(int& a, int& b) {
	int t;
	t = a;
	a = b;
	b = t;
}

void Assign(Node& node, int index) {
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			node.digit[i][j] = node_v[index].digit[i][j];
}

int GetMinNode() {
	int dist = MAXNUM;
	int loc; // the location of minimize node
	for (int i = 0; i < node_v.size(); i++) {
		if (node_v[i].dist == MAXNUM)
			continue;
		else if ((node_v[i].dist + node_v[i].dep) < dist) {
			loc = i;
			dist = node_v[i].dist + node_v[i].dep;
		}
	}

	return loc;
}

bool isExpandable(Node& node) {
	for (int i = 0; i < node_v.size(); i++) {
		if (isEqual(i, node.digit))
			return false;
	}
	return true;
}

int Distance(Node& node, int digit[][COL]) {
	int distance = 0;
	bool flag = false;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			for (int k = 0; k < ROW; k++) {
				for (int l = 0; l < COL; l++) {
					if (node.digit[i][j] == digit[k][l]) {
						distance += abs(i - k) + abs(j - l);
						flag = true;
						break;
					}
					else
						flag = false;
				}
				if (flag)
					break;
			}
	return distance;
}

int MinDistance(int a, int b) {
	return (a < b ? a : b);
}

void ProcessNode(int index) {
	int x, y;
	bool flag;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (node_v[index].digit[i][j] == 0) {
				x = i; y = j;
				flag = true;
				break;
			}
			else flag = false;
		}
		if (flag)
			break;
	}

	Node node_up;
	Assign(node_up, index);
	int dist_up = MAXDISTANCE;
	if (x > 0) {
		Swap(node_up.digit[x][y], node_up.digit[x - 1][y]);
		if (isExpandable(node_up)) {
			dist_up = Distance(node_up, dest.digit);
			node_up.index = index;
			node_up.dist = dist_up;
			node_up.dep = node_v[index].dep + 1;
			node_v.push_back(node_up);
		}
	}

	Node node_down;
	Assign(node_down, index);
	int dist_down = MAXDISTANCE;
	if (x < 2) {
		Swap(node_down.digit[x][y], node_down.digit[x + 1][y]);
		if (isExpandable(node_down)) {
			dist_down = Distance(node_down, dest.digit);
			node_down.index = index;
			node_down.dist = dist_down;
			node_down.dep = node_v[index].dep + 1;
			node_v.push_back(node_down);
		}
	}

	Node node_left;
	Assign(node_left, index);
	int dist_left = MAXDISTANCE;
	if (y > 0) {
		Swap(node_left.digit[x][y], node_left.digit[x][y - 1]);
		if (isExpandable(node_left)) {
			dist_left = Distance(node_left, dest.digit);
			node_left.index = index;
			node_left.dist = dist_left;
			node_left.dep = node_v[index].dep + 1;
			node_v.push_back(node_left);
		}
	}

	Node node_right;
	Assign(node_right, index);
	int dist_right = MAXDISTANCE;
	if (y < 2) {
		Swap(node_right.digit[x][y], node_right.digit[x][y + 1]);
		if (isExpandable(node_right)) {
			dist_right = Distance(node_right, dest.digit);
			node_right.index = index;
			node_right.dist = dist_right;
			node_right.dep = node_v[index].dep + 1;
			node_v.push_back(node_right);
		}
	}

	node_v[index].dist = MAXNUM;
}

int main() {
	int number;

	cout << "Input source:" << endl;
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++) {
			cin >> number;
			src.digit[i][j] = number;
		}
	src.index = 0;
	src.dep = 1;

	cout << "Input destination:" << endl;
	for (int m = 0; m < ROW; m++)
		for (int n = 0; n < COL; n++) {
			cin >> number;
			dest.digit[m][n] = number;
		}

	node_v.push_back(src);

	cout << "Search..." << endl;
	clock_t start = clock();
	while (1) {
		if (isEmptyOfOPEN()) {
			cout << "Cann't solve this statement!" << endl;
			return -1;
		}
		else {
			int loc; // the location of the minimize node
			loc = GetMinNode();
			if (isEqual(loc, dest.digit)) {
				vector<Node> rstep_v;
				cout << "Source:" << endl;
				cout << src << endl;
				PrintSteps(loc, rstep_v);
				cout << "Successful!" << endl;
				cout << "Using " << (clock() - start) / CLOCKS_PER_SEC
					<< " seconds." << endl;
				break;
			}
			else
				ProcessNode(loc);
		}
	}

	return 0;
}
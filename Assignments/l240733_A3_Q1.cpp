#include <climits>  // For INT_MAX
#include <iomanip>  // For set_precision
#include <cmath>    // For power and square root
#include <iostream>
#include <vector>
#include <forward_list>
using namespace std;
void input(int& n, int& m, vector<vector<double>>& points, vector<vector<double>>& distances) {
	cin>>n>>m;
	points.resize(n, vector<double>(2, 0));
	distances.resize(n, vector<double>(n, 0.0));
	for (int i=0;i<n;++i) { cin>>points[i][0]>>points[i][1]; }
	for (int i=0;i<n;++i) {
		for (int j=0;j<n;++j)
			distances[i][j] = i<j ? sqrt(pow((points[i][0]-points[j][0]), 2)+pow((points[i][1]-points[j][1]), 2)) : 0.0;
	}
}
void displayPairs(const vector<bool>& availableGroups, const vector<forward_list<int>>& groups, const int& n) {
	cout<<"The pairs are: "<<endl;
	for (int i=0;i<n;++i) {
		if (availableGroups[i]) {
			for (const auto pairs: groups[i]) { cout<<pairs<<" "; }
			cout<<endl;
		}
	}
}
void merging(const int& n, const int& m, vector<vector<double>>& distances, vector<bool>& availableGroups, vector<forward_list<int>>& groups) {
	for (int x=1;x<=(n-m);++x) {
		double minimum=INT_MAX;
		int minX=0, minY=0;
		for (int i=0;i<n;++i) {
			for (int j=0;j<n;++j) {
				if (i<j && distances[i][j]<minimum && availableGroups[i]==true && availableGroups[j]==true) {
					minimum=distances[i][j];
					minX=i; minY=j;
				}
			}
		}
		availableGroups[minY]=false;
		for (auto k: groups[minY]) {
			groups[minX].push_front(k);
		}
		for (int k=0;k<n;++k) {
			if (k>minY) {
				distances[minX][k]=min(distances[minX][k], distances[minY][k]);
			}
		}
		// Merging the column
		for (int k=0;k<n;++k)
			distances[k][minX]=min(distances[k][minX], distances[k][minY]);
	}
}
void mainTask(const int& n, const int& m, vector<vector<double>>& distances) {
	vector<bool> availableGroups(n, true);
	vector<forward_list<int>> groups(n);
	for (int i=0;i<n;++i) {	groups[i].push_front(i); }
	merging(n, m, distances, availableGroups, groups);
	displayPairs(availableGroups, groups, n);
}
int main() {
	int n, m;
	vector<vector<double>> points, distances;
	input(n, m, points, distances);
	mainTask(n, m, distances);
	return 0;
}
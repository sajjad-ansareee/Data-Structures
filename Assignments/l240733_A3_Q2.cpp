// #include <iostream>
// #include <vector>
// #include <list>
// #include <cmath>
// using namespace std;
//
// // Helper Functions
// void displayPairs(const vector<list<int>>& pairs) {
//   cout<<"The pairs are: "<<endl;
//   for (const auto & pair : pairs) {
//     for (auto j:pair) {
//       cout<<j<<" ";
//     }
//     cout<<endl;
//   }
//   cout<<endl;
// }
// void displayMatrix(const vector<vector<int>>& matrix) {
//   cout<<"The distance matrix: \n";
//   for (int i=0;i<int(matrix.size());++i) {
//     for (int j=0;j<int(matrix[0].size());++j) {
//       cout<<matrix[i][j]<<"\t";
//     }
//     cout<<endl;
//   }
//   cout<<endl;
// }
// double distanceCalculation(double a, double b, double x, double y) {
//   double sum=pow((a-x), 2)+pow((b-y), 2);
//   return sqrt(sum);
// }
//
// class Heap {
// private:
//   class Node {
//   public:
//     double distance;
//     int group_1;
//     int group_2;
//     Node(double distance, int group_1, int group_2): distance(distance), group_1(group_1), group_2(group_2) {}
//     void swap(Node*& other) {
//       Node* temp=new Node(other->distance, other->group_1, other->group_2);
//       other->distance=this->distance;
//       other->group_1=this->group_1;
//       other->group_2=this->group_2;
//       this->distance=temp->distance;
//       this->group_1=temp->group_1;
//       this->group_2=temp->group_2;
//       delete temp;
//     }
//   };
//   vector<Node*> array;
//   static void mergeNodes(const Node*& minimum, vector<list<int>>& pairs, vector<int>& mergedIndex) {
//     // Find the merged index of the group_1 node like where it is actually now
//     int i=minimum->group_2;
//     // While we do not find the group which is not merged till now
//     while (mergedIndex[i]!=i) {
//       i=mergedIndex[i];
//     }
//     cout<<i<<endl;
//     cout<<minimum->group_1<<endl;
//     for (auto ii:pairs[i]) {
//       pairs[minimum->group_1].push_back(ii);
//     }
//     // Now we have to mark on that i-th group that it is merged into the group_2
//     mergedIndex[i]=minimum->group_1;
//   }
// public:
//   void insert(double distance, int group_1, int group_2) {
//     // Firstly we will have our array not in heap
//     // Then after completing the array we will apply build heap on it
//     this->array.push_back(new Node(distance, group_1, group_2));
//     this->heapifyUp();
//   }
//   const Node* remove() {
//     if (this->array.empty()) {
//       return nullptr;
//     }
//     const Node* removed=array[array.size()-1];
//     array[0]->swap(array[array.size()-1]);
//     this->array.pop_back();
//     this->heapifyDown();
//     return removed;
//   }
//   void heapifyUp() {
//     // Used in insertion when we require our last input to take the correct position
//     int current=int(this->array.size()-1);
//     int parent=(current-1)/2;
//     while (current!=0) {
//       // Swap the nodes if child having lesser value than the parent
//       if (array[current]->distance<array[parent]->distance) {
//         array[parent]->swap(array[current]);
//         current=parent;
//         parent=(current-1)/2;
//       }
//       else {
//         return;
//       }
//     }
//   }
//   void heapifyDown() {
//     int current=0;
//     int left=(current*2)+1;
//     int right=(current*2)+2;
//     int n=int(this->array.size());
//     // Once the left child got out of the array we know that out current is now at the leaf node
//     while (left<n-1) {
//       if (array[left]->distance < array[current]->distance && array[left]->distance<=array[right]->distance) {
//         // Swap the current with left
//         array[current]->swap(array[left]);
//         current=left;
//       }
//       else if (array[right]->distance < array[current]->distance && array[right]->distance<=array[left]->distance) {
//         // Swap the current with right
//         array[current]->swap(array[right]);
//         // current=right;
//       }
//       else {
//         return;
//       }
//       left=(current*2)+1;
//       right=(current*2)+2;
//     }
//   }
//   void display() const {
//     cout<<"The heap: "<<endl;
//     for (int i=0;i<int(this->array.size());++i) {
//       cout<<"Distance:"<<array[i]->distance<<", Group1:"<<array[i]->group_1<<", Group2:"<<array[i]->group_2<<endl;
//     }
//     cout<<endl;
//   }
//   void pairing(vector<list<int>>& pairs, int n, int m) {
//     // Initialize the pairs vector
//     for (int i=0;i<int(pairs.size());++i) {
//       pairs[i].push_back(i);
//     }
//     vector<int> mergedIndex(n, 0);
//     for (int i=0;i<n;++i) {
//       mergedIndex[i]=i;
//     }
//     for (int i=0;i<(n-m);++i) {
//       const Node* minimum=this->remove();
//       cout<<"Minimum Distance: "<<minimum->distance<<endl;
//       mergeNodes(minimum, pairs, mergedIndex);
//       displayPairs(pairs);
//     }
//   }
// };
//
// void input(int& n, int& m, vector<vector<int>>& distances, vector<vector<double>>& points, Heap& heap) {
//   cin>>n>>m;
//   distances.resize(n);
//   // Initialize the distance matrix with 0's
//   for (int i=0;i<n;++i) {
//     distances[i].resize(n, 0);
//   }
//   points.resize(n);
//   for (int i=0;i<n;++i) {
//     points[i].resize(2);
//     cin>>points[i][0]>>points[i][1];
//   }
//   // Now have to insert the distance of every point in the heap
//   int k=1;
//   for (int i=0;i<n;++i) {
//     for (int j=0;j<n;++j) {
//       if (i<j) {
//         double distance=distanceCalculation(points[i][0], points[i][1], points[j][0], points[j][1]);
//         heap.insert(distance, i, j);
//         distances[i][j]=k;
//         ++k;
//       }
//     }
//   }
// }
//
// int main() {
//   int n, m;
//   vector<vector<int>> distances;
//   vector<vector<double>> points;
//   Heap heap;
//   input(n, m, distances, points, heap);
//   displayMatrix(distances);
//   vector<list<int>> pairs(n);
//   heap.pairing(pairs, n, m);
//   displayPairs(pairs);
//   return 0;
// }
//
// // Made heap successfully
// // We have to extract the top of heap merge the groups and then insert back it in heap
// // Merging of two nodes
//
// // I will have a mark for points like in which group they are
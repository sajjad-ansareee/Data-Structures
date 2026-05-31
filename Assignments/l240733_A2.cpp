// #include <iostream>
// #include <vector>
// #include <queue>
// using namespace std;
//
// class Inventory {
// private:
// 	class Product {
// 	public:
// 		int id;
// 		string name;
// 		string category;
// 		Product *left, *right;
// 		Product(int id, string& name, string& category): id(id), name(name), category(category) {
// 			left=nullptr;
// 			right=nullptr;
// 		}
// 		void copyData(Product*& other) {
// 			this->id=other->id;
// 			this->name=other->name;
// 			this->category=other->category;
// 		}
// 		void display() const {
// 			cout<<"ID: "<<this->id<<endl;
// 		}
// 	};
// 	Product *root;
// 	int size;
// public:
// 	explicit Inventory(Product *root=nullptr, int size=0): root(root), size(size) {}
//
// 	void insert(int id, string& name, string& category) {
// 		insertP(id, name, category, this->root);
// 	}
// 	void insertP(int id, string& name, string& category, Product*& current) {
// 		if (current==nullptr) {
// 			current=new Product(id, name, category);
// 		}
// 		else if (current->id>id) {
// 			// Search on the left side
// 			insertP(id, name, category, current->left);
// 			// Perform right rotation on returning
// 			rightRotate(current);
// 		}
// 		else {
// 			insertP(id, name, category, current->right);
// 			// Perform left rotation on returning
// 			leftRotate(current);
// 		}
// 	}
//
// 	void remove(int id) {
// 		// Find the id in our inventory
// 		// Need a current pointer so there should be a wrapper function
// 		removeP(id, this->root);
// 	}
// 	void removeP(int id, Product*& current) {
// 		if (current==nullptr) {
// 			cout<<"NOT FOUND!"<<endl;
// 			return;
// 		}
// 		if (current->id > id) {
// 			removeP(id, current->left);
// 		}
// 		else if (current->id < id) {
// 			removeP(id, current->right);
// 		}
// 		else {
// 			removeProduct(current);
// 		}
// 	}
//
// 	void removeProduct(Product*& current){
// 		// If no right child existing
// 		if (current->left==nullptr) {
// 			// Simply point the current pointer to right
// 			current=current->right;
// 		}
// 		else if (current->right==nullptr) {
// 			current=current->left;
// 		}
// 		// Both of the child existing
// 		else {
// 			// Placing the predecessor at place of currently deleted node
// 			Product*& predecessor=current->left;
// 			while (predecessor->right) {
// 				predecessor=predecessor->right;
// 			}
// 			// Now we have the predecessor
// 			// Copy the data of predecessor at deleting node
// 			current->copyData(predecessor);
// 			// Now the current pointer would be pointing towards the left of predecessor
// 			Product* temp=predecessor;
// 			predecessor=predecessor->left;
// 			delete temp;
// 		}
// 	}
//
// 	void print(int id) {
// 		printP(id, this->root);
// 	}
// 	void printP(int id, const Product* current) {
// 		if (current==nullptr) {
// 			cout<<"Not Found!"<<endl;
// 			return;
// 		}
// 		if (current->id<id) {
// 			printP(id, current->right);
// 		}
// 		else if (current->id>id) {
// 			printP(id, current->left);
// 		}
// 		else {
// 			cout<<"ID: "<<current->id<<endl;
// 			cout<<"Name: "<<current->name<<endl;
// 			cout<<"Category: "<<current->category<<endl;
// 		}
// 	}
//
// 	void printAll() {
// 		if (this->root==nullptr) {
// 			cout<<"Inventory is empty!"<<endl;
// 		}
// 		printAllP(this->root);
// 	}
// 	void printAllP(const Product* current) {
// 		if (current==nullptr) {
// 			return;
// 		}
// 		// Applying the inorder traversal
// 		printAllP(current->left);
// 		current->display();
// 		printAllP(current->right);
// 	}
// 	void levelOrderTraversal() {
// 		if (this->root==nullptr) {
// 			cout<<"The inventory is empty!"<<endl;
// 			return;
// 		}
// 		cout<<"Inventory in level order hierarchy is: ";
// 		Product* current=this->root;
// 		queue<Product*> q;
// 		q.push(current);
// 		while (!q.empty()) {
// 			cout<<q.front()->id<<" ";
// 			if (q.front()->left) {
// 				q.push(q.front()->left);
// 			}
// 			if (q.front()->right) {
// 				q.push(q.front()->right);
// 			}
// 			q.pop();
// 		}
// 		cout<<endl;
// 	}
//
// 	void rightRotate(Product*& X) {
// 		// Perform right rotation on X
// 		// Safe the orphan child
// 		Product* orphan=X->left->right;
// 		Product* Y=X->left;
// 		Y->right=X;
// 		X->left=orphan;
// 		X=Y;
// 	}
// 	void leftRotate(Product*& X) {
// 		Product* orphan=X->right->left;
// 		Product* Y=X->right;
// 		Y->left=X;
// 		X->right=orphan;
// 		X=Y;
// 	}
//
// 	void organize() {
// 		// The main logic is like insertion but here we are searching for the median and then take it to the root just difference is we will not be adding a new node
// 		// Find the median
// 		vector<int> ids;
// 		inorderIds(this->root, ids);
// 		int median=ids[ids.size()/2];
// 		organizeP(this->root, median);
// 	}
// 	void organizeP(Product*& current, int median) {
// 		if (current==nullptr) {
// 			cout<<"Inventory is empty!"<<endl;
// 			return;
// 		}
// 		if (current->id==median) {
// 			cout<<"Median is "<<median<<endl;
// 			return;
// 		}
// 		if (current->id<median) {
// 			organizeP(current->right, median);
// 			// Perform left rotation here on returning
// 			leftRotate(current);
// 		}
// 		else {
// 			organizeP(current->left, median);
// 			rightRotate(current);
// 		}
// 	}
// 	void inorderIds(Product*& current, vector<int>& ids) {
// 		if (current==nullptr) {
// 			return;
// 		}
// 		inorderIds(current->left, ids);
// 		ids.push_back(current->id);
// 		inorderIds(current->right, ids);
// 	}
//
// 	void search(int id, int k) {
// 		// Considering the root to be at 0 level
// 		searchP(this->root, id, k, 0);
// 	}
// 	void searchP(Product*& current, int id, int k, int currentLevel) {
// 		// I will have a count for the levels and will check how many levels below I am
// 		if (current==nullptr) {
// 			cout<<"Not Found"<<endl;
// 			return;
// 		}
// 		if (current->id==id) {
// 			cout<<"Found"<<endl;
// 			return;
// 		}
// 		if (current->id<id) {
// 			searchP(current->right, id, k, currentLevel+1);
// 			// Now we have to apply the left rotation here, according to k mean, check if we have to apply rotation on backtracking or not
// 			// We have to check are we below the required level or not if below make the rotation
// 			if (currentLevel>=k) {
// 				leftRotate(current);
// 			}
// 		}
// 		else {
// 			searchP(current->left, id, k, currentLevel+1);
// 			// Apply the right rotation here, according to a condition
// 			if (currentLevel>=k) {
// 				rightRotate(current);
// 			}
// 		}
// 	}
// };
//
// void menu(Inventory*& inventory) {
// 	cout<<"Welcome to Inventory Management System!"<<endl;
// 	cout<<"1. Insert"<<endl;
// 	cout<<"2. Remove"<<endl;
// 	cout<<"3. Display a Product"<<endl;
// 	cout<<"4. Display all"<<endl;
// 	cout<<"5. LevelOrderTraversal"<<endl;
// 	cout<<"6. Search"<<endl;
// 	cout<<"7. Organize"<<endl;
// 	cout<<"8. Exit"<<endl;
// 	cout<<"Your Option: ";
// 	int option; cin>>option;
// 	if (option==1) {
// 		cout<<"ID: ";
// 		int id; cin>>id;
// 		cout<<"Name: ";
// 		string name="Sajjad"; cin>>name;
// 		cout<<"Category: ";
// 		string category="Model"; cin>>category;
// 		inventory->insert(id, name, category);
// 	}
// 	else if (option==2) {
// 		cout<<"ID: ";
// 		int id; cin>>id;
// 		inventory->remove(id);
// 	}
// 	else if (option==3) {
// 		cout<<"ID: ";
// 		int id; cin>>id;
// 		inventory->print(id);
// 	}
// 	else if (option==4) {
// 		inventory->printAll();
// 	}
// 	else if (option==5) {
// 		inventory->levelOrderTraversal();
// 	}
// 	else if (option==6) {
// 		cout<<"ID: ";
// 		int id; cin>>id;
// 		cout<<"New Level: ";
// 		int k; cin>>k;
// 		inventory->search(id, k);
// 	}
// 	else if (option==7) {
// 		inventory->organize();
// 	}
// 	else if (option==8) {
// 		cout<<"Bye!"<<endl;
// 		return;
// 	}
// 	else {
// 		cout<<"Invalid option!"<<endl;
// 	}
// 	menu(inventory);
// }
//
// int main() {
// 	Inventory* inventory=new Inventory();
// 	menu(inventory);
// 	delete inventory;
// 	return 0;
// }
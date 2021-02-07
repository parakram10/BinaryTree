#include<iostream>
using namespace std;


struct Tree{
	int data;
	Tree* left;
	Tree* right;
	Tree(int k){
		data = k;
		left = NULL;
		right = NULL;
	}
};

void printTree(Tree* node){
	if(node == NULL) return;
	cout<<node->data<<"   ";
	printTree(node->left);
	printTree(node->right);
	return;
}

Tree* append(Tree* root, int k){
	if(root == NULL) return new Tree(k);
	if(root->data > k)	root->left = append(root->left, k);
	else if(root->data < k)	root->right = append(root->right, k);
	return root;
}

bool search(Tree* root, int k){
	if(root == NULL) return false;
	if(root->data == k) return true;
	else if(root->data > k) return search(root->left, k);
	else if(root->data < k) return search(root->right, k);
	return false;
}

Tree* inorderSucc(Tree* root){
	root = root->right;
	while(root->left != NULL) root = root->left;
	return root;
}

Tree* deleteNode(Tree* root, int k){
	if(root == NULL) return root;
	if(root->data > k) root->left = deleteNode(root->left, k);
	else if(root->data < k) root->right = deleteNode(root->right, k);
	else{
		if(root->left == NULL){
			Tree* temp = root->right;
			delete root;
			return temp;
		}
		else if(root->right == NULL){
			Tree* temp = root->left;
			delete root;
			return temp;
		}
		else{
			Tree* curr = inorderSucc(root);
			root->data = curr->data;
			root->right = deleteNode(root->right, k);
		}
	}
	return root;
}

int i = 0;
Tree* makePostOrder(int a[], int b[], int n){
	Tree* root = NULL;
	int pos = positionInInnorder(b,a[i]);
	i++;
	while(i!=n-1){
		root = new Tree(b[pos]);
		root->left = makePostOrder(a,b,pos);
	}
}


int main(){
	int a[] = {8,3,11,4,2,9,10,5,6,12};
	Tree* tree = NULL;
	for(int i=0;i<10;i++) tree = append(tree, a[i]);
	printTree(tree);
	cout<<"\n";
	if(search(tree, 11)) cout<<"Found\n";
	else cout<<"Not Found\n";
	if(search(tree, 13)) cout<<"Found\n";
	else cout<<"Not Found\n";
	tree = deleteNode(tree, 9);
	printTree(tree);
	cout<<"\n";
	tree = deleteNode(tree, 3);
	printTree(tree);
	cout<<"\n";
}

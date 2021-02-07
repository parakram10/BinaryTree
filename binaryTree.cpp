#include<iostream>
#include<queue>
#include<stack>
#include<vector>
using namespace std;

struct Tree{
	int data;
	Tree* left;
	Tree* right;
	Tree* next;
	Tree(int val){
		data = val;
		left = NULL;
		right = NULL;
		next = NULL;
	}
};

void printtree(Tree* tree){
	if(tree==NULL) return;
	
	printtree(tree->left);
	cout<<tree->data<<"  ";
	printtree(tree->right);
}

void append(Tree** tree, int val){
	if(*tree == NULL){
		*tree = new Tree(val);
		return;
	}
	
	Tree* temp = *tree;
	queue<Tree*> q;
	q.push(temp);
	while(!q.empty()){
		int k = q.size();
		for(int i=0;i<k;i++){
			Tree* curr = q.front();
			q.pop();
			if(curr->data == -1) continue;
			if(!curr->left){
				curr->left = new Tree(val);
				return;
			}else{
				q.push(curr->left);
			}
			
			if(!curr->right){
				curr->right = new Tree(val);
				return;
			}else{
				q.push(curr->right);
			}
		}
	}
}

bool search(Tree* tree, int val){
	if(tree == NULL) return false;
	
	if(tree->data == val) return true;
	
	Tree* temp = tree;
	
	queue<Tree*> q;
	q.push(temp);
	while(!q.empty()){
		int k = q.size();
		for(int i=0;i<k;i++){
			Tree* curr = q.front();
			q.pop();
			if(curr->data == val) return true;
			if(curr->left) q.push(curr->left);
			if(curr->right) q.push(curr->right);
		}
	}
	return false;
}

Tree *findnode(Tree* root, int data)
{
	if(root==NULL)
		return NULL;
	queue<Tree *>q;
	q.push(root);
	while(!q.empty())
	{
		Tree *curr=q.front();
		q.pop();
		if(curr->data==data)
			return curr;
		if(curr->left)
			q.push(curr->left);
		if(curr->right)
			q.push(curr->right);
	}
	return NULL;
}

void inorderSucc(Tree* root, vector<int>& v){
	if(root==NULL) return;
	inorderSucc(root->left,v);
	v.push_back(root->data);
	inorderSucc(root->right,v);
}


Tree* finddeepestright(Tree* root)
{
	if(root==NULL)
		return NULL;
	queue<Tree*>q;
	q.push(root);
	Tree* curr;
	while(!q.empty())
	{
		curr=q.front();
		q.pop();
		if(curr->left)
			q.push(curr->left);
		if(curr->right)
			q.push(curr->right);
	}
	return curr;
}


Tree *deletenode(Tree *root,int data)
{
	Tree *foundnode=findnode(root,data);                      // Function to find the node which to be deleted
	Tree *deepestrightnode=finddeepestright(root);            // Function to find the deepest rightmost node of the tree so the we always have minimum height
	if(foundnode)											  // If node is present the delete
	{
		cout<<endl<<"node found "<<foundnode->data;
		cout<<endl<<"deepest node "<<deepestrightnode->data<<"\n";
		swap(foundnode->data, deepestrightnode->data);
		queue<Tree *>q;
		q.push(root);
		Tree *curr;
		while(!q.empty())
		{
			curr=q.front();
			q.pop();
			if(curr==deepestrightnode)
			{
				root=NULL;
				delete deepestrightnode;
				break;
			}
			if(curr->left)
			{
				if(curr->left==deepestrightnode)
				{
					curr->left=NULL;
					delete deepestrightnode;
					break;
				}
				else
				{
					q.push(curr->left);
				}
			}
			if(curr->right)
			{
				if(curr->right==deepestrightnode)
				{
					curr->right=NULL;
					delete deepestrightnode;
					break;
				}
				else
					q.push(curr->right);
			}
		}
	return root;
	}
}


void preOrder(Tree* tree){
	if(tree == NULL) return;
	
	stack<Tree*> s;
	Tree* curr = tree;
	s.push(curr);
	while(!s.empty()){
		curr = s.top();
		s.pop();
		cout<<curr->data<<" ";
		
		if(curr->right) s.push(curr->right);
		if(curr->left) s.push(curr->left);
	}
}

void inorder(Tree* tree){
	if(tree==NULL) return;
	
	Tree* curr = tree;
	stack<Tree*> s;
	while(curr!=NULL || !s.empty()){
	
		while(curr!=NULL){
			s.push(curr);
			curr = curr->left;
		}
		
		curr = s.top();
		s.pop();
		cout<<curr->data<<"  ";
		curr = curr->right;
	
	}
	return;
}

void preorder(Tree* tree){
	if(tree == NULL) return;
	
	Tree* curr = tree;
	stack<Tree*> s;
	s.push(curr);
	while(curr!=NULL || !s.empty()){
		curr = s.top();
		cout<<curr->data<<"  ";
		s.pop();
		if(curr->right) s.push(curr->right);
		if(curr->left) s.push(curr->left); 
	}
}


void postOrder(Tree* tree){
	if(tree == NULL) return;
	
	Tree* curr = tree;
	stack<Tree*> s;
	while(curr!=NULL || !s.empty()){
		
		while(curr!=NULL){
			if(curr->right) s.push(curr->right);
			s.push(curr);
			curr = curr->left;
		}
		
		curr = s.top();
		s.pop();
		
		if(curr->right && s.top() == curr->right) {
			s.pop();
			s.push(curr);
			curr = curr->right;
		}else{
			cout<<curr->data<<"   ";
			curr = NULL;
		}
		
	}
	return;
}


void postOrderTwoStack(Tree* tree){
	if(tree == NULL) return;
	stack<Tree*> s1,s2;
	s1.push(tree);
	while(!s1.empty()){
		tree = s1.top();
		s1.pop();
		s2.push(tree);
		if(tree->left) s1.push(tree->left);
		if(tree->right) s1.push(tree->right);
	}
	
	
	while(!s2.empty()){
		tree = s2.top();
		cout<<tree->data<<"   ";
		s2.pop();
	}
}

//int heightOfTree(Tree* tree){
//	if(tree == NULL) return -1;
//	queue<Tree*> q;
//	Tree* temp = tree;
//	int n = 0;
//	q.push(tree);
//	q.push(NULL);
//	while(!q.empty()){
//		Tree* curr = q.front();
//		q.pop();
//	}
//}

int heightRecursive(Tree* tree){
	if(tree == NULL){
		return 0;
	}
	return 1+ max(heightRecursive(tree->left), heightRecursive(tree->right)); 
}


int kthelementinInorder(Tree* tree, int m){
	if(tree == NULL) return -1;
	
	static int k = 0;
	if(k<=m){
		kthelementinInorder(tree->left, m);
		k++;
		if(k == m){
			cout<<tree->data;
			return tree->data;
		}
		kthelementinInorder(tree->right, m);
	}
	else	return -1;
}


void preorderTofind(Tree* root, vector<int>& v){
	if(root == NULL) return;
	
	if(root->left == NULL && root->right == NULL) v.push_back(root->data);
	preorderTofind(root->left, v);
	preorderTofind(root->right, v);
	
	return;
}

bool isLeaf(Tree* node){
	if(node->left == NULL && node->right == NULL) return true;
	else return false;
}

void unCommonLeaves(Tree* root1, Tree* root2){
	stack<Tree*> s1,s2;
	s1.push(root1);
	s2.push(root2);
	while(!s1.empty() && !s2.empty()){
		Tree* curr1 = s1.top();
		s1.pop();
		while(!isLeaf(curr1)){
			if(curr1->right) s1.push(curr1->right);
			if(curr1->left) s1.push(curr1->left);
			curr1 = s1.top();
			s1.pop();
		}
		
		Tree* curr2 = s2.top();
		s2.pop();
		while(!isLeaf(curr1)){
			if(curr2->right) s2.push(curr2->right);
			if(curr2->left) s2.push(curr2->left);
			curr2 = s2.top();
			s2.pop();
		}
		
		if(curr1->data != curr2->data){
			cout<<"curr1  "<<curr1->data<<"\ncurr2   "<<curr2->data;
		}
	}
}

int i1=0;
void inorderSuccVal(Tree* root, vector<int> v){
	if(root==NULL) return;
	inorderSuccVal(root->left,v);
	root->next = new Tree(v[++i1]);
	inorderSuccVal(root->right,v);	
}

void inorderSuccValPrint(Tree* root){
	if(root==NULL) return;
	inorderSuccValPrint(root->left);
	cout<<root->data<<" ---> "<<root->next->data<<"  ";
	inorderSuccValPrint(root->right);
}


void reverseInorder(Tree* root){
	if(root==NULL) return;
	Tree* next = NULL;
	reverseInorder(root->right);
	root->next = next;
	cout<<next->data<<" ";
	next = root;
	reverseInorder(root->left);
}


//Lowest Common Ancestor in binary tree using vector and finding path to both nodes

bool findnode(Tree* root, vector<Tree*>& v, int n){
	if(root == NULL) return false;
	v.push_back(root);
	if(root->data == n) return true;
	if((root->left && findnode(root->left, v, n)) || (root->right && findnode(root->right, v, n))) return true; 
	v.pop_back();
	return false;
}

Tree* lca(Tree* root, int n1, int n2){
	vector<Tree*> v1, v2;
	
	if(!findnode(root, v1, n1) || !findnode(root, v2, n2))
		return NULL;
	
	int i=0;
	for(i=0;i<v1.size() && i<v2.size();i++){
		if(v1[i] != v2[i]) {
			break;
		}
	}
	return v1[i-1];
}


// Lowest Common Ancestor (one Traversal)

// This case is valid if either both nodes are present or no one is present

Tree* lca1(Tree* root, int n1,int n2){
	if(root==NULL) return NULL;
	if(root->data == n1 || root->data == n2) return root;
	
	Tree* left = lca1(root->left,n1,n2);
	Tree* right = lca1(root->right,n1,n2);
	
	if(left && right) return root;
	
	if(!left) return right;
	else return left;
	return NULL;
}


// Construct Binary Tree From gievn PreOrder and PostOrder traversal : Iterative Approach

Tree* binaryTreeFromPreAndPostOrder(int a[], int b[], int n){
	stack<Tree*> s;
	Tree* root = new Tree(a[0]);
	s.push(root);
	for(int i=1,j=0;i<n;i++){
		while(s.top()->data == b[j]){
			s.pop();
			++j;
		}
		
		Tree* newNode = new Tree(a[i]);
		if(s.top()->left == NULL) s.top()->left = newNode;
		else s.top()->right = newNode;
		s.push(newNode);
	}
	return root;
}



int main(){
	int a[] = {1,2,3,4,5,6};
	int b[] = { 1,2,3,4,5,7};
	Tree* root = NULL;
	Tree* root1 = NULL;
	for(int i=0;i<6;i++){
		append(&root, a[i]);
		append(&root1, b[i]);
	}
//	printtree(root);
//	cout<<"\n--------------------Search--------------------------\n";
//	cout<<search(root,3)<<"\n";
//	cout<<search(root,8)<<"\n";
//	cout<<"\n-------------------Delete---------------------------\n";
//	deletenode(&root, 1);
//	printtree(root);
//	cout<<"\n----------------------------------------------\n";
//	cout<<"Inorder     ";
//	inorder(root);
//	cout<<"\n----------------------------------------------\n";
//	cout<<"Preorder     ";
//	preOrder(root);
//	cout<<"\n----------------------------------------------\n";
//	cout<<"Preorder     ";
//	preorder(root);
//	cout<<"\n----------------------------------------------\n";
//	cout<<"Postorder     ";
//	postOrder(root);
//	cout<<"\n----------------------------------------------\n";
//	cout<<"Postorder     ";
////	postOrderTwoStack(root);
//	cout<<"\n-----------------------------------------------\n";
//	cout<<heightRecursive(root);
//	cout<<"\n";
//	cout<<kthelementinInorder(root, 3);
//	vector<int> v1, v2;
//	preorderTofind(root, v1);
//	preorderTofind(root1, v2);
//	int size = v1.size()<v2.size() ? v1.size() : v2.size();
//	for(int i=0;i<size;i++){
//		if(v1[i] != v2[i]){
//			cout<<"\n"<<v1[i]<<"   "<<v2[i];
//			break;
//		}
//	}
//	unCommonLeaves(root,root1);
//	printtree(root);
//	cout<<"\n";
//	deletenode(root, 3);
//	printtree(root);
//	cout<<"\n";
//	deletenode(root, 1);
//	printtree(root);
//	vector<int> v;
//	inorderSucc(root,v);
//	v.push_back(-1);
//	inorderSuccVal(root,v);
//	cout<<"\n\n\nInorder Succ. of each node(1 Way)\n";
//	inorderSuccValPrint(root);
//	cout<<"\n\n";
//	int n=v.size();
//	cout<<"\nInorder Succ. of each node(2 way)\n";
//	for(int i=0;i<n-1;i++) cout<<v[i]<<" ---> "<<v[i+1]<<"\n";
//	cout<<"\nInorder Succ. of each node using reverse Inorder\n";
//	reverseInorder(root);
	cout<<"\n"<<lca(root,4,5)->data;
	cout<<"\n"<<lca1(root,4,5)->data;
	
	int pre[] = {1,2,4,5,3,6,7};
	int post[] = {4,5,2,6,7,3,1};
	Tree* prepost = binaryTreeFromPreAndPostOrder(pre,post,7);
	cout<<"\n\n\n";
	printtree(prepost);
}

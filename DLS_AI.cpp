#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Node{
	char value;
	vector<Node> children;
public:
	Node(char c){
		value = c;
	}

	void addChild(Node n){
		children.push_back(n);
		return;
	}

	void addChild(char n){
		Node foo(n);
		children.push_back(foo);
	}

	char getValue(){
		return value;
	}

	vector<Node> getChildren(){
		return children;
	}

	bool isLeaf(){
		return children.size()==0;
	}

	bool operator==(Node b){
		return b.value==value;
	}
};


void construct(Node *r)
{
	string foo;
	cout<<"Enter children for "<< r->getValue() <<" (-1 for leaf)"<<endl;
	cin>>foo;

	if(foo == "-1")
		return;
	else{
		for(int i = 0; i < foo.length(); i++)
		{
			Node t(foo[i]);
			construct(&t);

			r->addChild(t);
		}
	}
}


string depthLimitedSearch(Node root, Node goal)
{
	std::stack<Node> Q;
	std::vector<Node> children;
	std::stack<int> stackDepth;
	string path = "";
	int depth = 0;
	int limit = 2;
	Q.push(root);
	stackDepth.push(depth);
	while(!Q.empty()) 
	{
   	    Node t = Q.top();
		path+= t.getValue();
		Q.pop();
		depth = stackDepth.top();
		stackDepth.pop();
		if(t==goal){
		return path;
		}
		
		if(depth<limit){		
			children = t.getChildren();
			std::reverse(children.begin(), children.end());
			for(int i=0;i<children.size();i++){
				Q.push(children[i]);
				stackDepth.push(depth+1);
			}
		}		
		else{
		cout<< "Goal node is not found within the depth"<<endl;
		break;
		}
	}
}


int main(int argc, char** args)
{

	char r;
	cout<<"Enter root node"<<endl;
	cin>>r;

	Node root(r);
	construct(&root);

	cout<<"Enter Node to search for: ";
	cin>>r;

	cout<<endl;

	cout<<"DLS Path: "<<depthLimitedSearch(root, Node(r))<<endl;

	return 0;
	
}


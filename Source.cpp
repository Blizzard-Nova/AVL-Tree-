#include <iostream>
using namespace std;
struct node
{
	node* left;
	node* right;
	int data;
	int height;
};
class AVL
{
	node* root;
	
	node* insert(node* leaf, int x);
	node* max(node*leaf);
	int height(node* leaf);
	int get_balance(node* leaf);
	int MAX(int a, int b);
	node* Right_Rotation(node* x);
	node* Left_rotate(node* y);
	node* Delete_Node(node* leaf, int x);
	void Inorder_Triversal(node* leaf);

public:
	AVL();
	void Display();
	void INSERT(int val);
	void DELETE(int val);
	void INORDER_PRINT();
};

AVL::AVL()
{
	root = NULL;

}

node* AVL::insert(node* leaf, int x)
{
	if (leaf == NULL)
	{
		leaf = new node;
		leaf->data = x;
		leaf->left = NULL;
		leaf->right = NULL;
		leaf->height=1;
	}

	else
	{
		if (x > leaf->data)
		{
			leaf->right = insert(leaf->right, x);
		}

		if (x < leaf->data)
		{
			leaf->left = insert(leaf->left, x);
		}
	}
	return leaf;

	leaf->height = height(leaf);

	int balance = get_balance(leaf);

	//LEFT LEFT CASE

	if (balance > 1 && x < leaf->left->data)
	{
		return Right_Rotation(leaf);
	}

	//RIGHT RIGHT CASE

	if (balance > -1 && x > leaf->right->data)
	{
		return Left_rotate(leaf);
	}

	//LEFT RIGHT CASE

	if (balance > 1 && x > leaf->left->data)
	{
		leaf->left = Left_rotate(leaf);
		return Right_Rotation(leaf);
	}

	//RIGHT LEFT CASE

	if (balance > -1 && x < leaf->right->data)
	{
		leaf->right = Right_Rotation(leaf);
		return Left_rotate(leaf);
	}
}

node* AVL::max(node* leaf)
{
	if (leaf == NULL)
	{
		return leaf;
	}

	else
	{
		leaf->right = max(leaf->right);
	}
}


int AVL::height(node* leaf)
{
	int left_height;
	int right_height;

	if (leaf == NULL)
	{
		return 0;
	}

	if (leaf->left == NULL)
	{
		left_height = 0;
	}
	else
		left_height = 1 + leaf->left->height;

	if (leaf->right == NULL)
	{
		right_height = 0;
	}
	else
		right_height = 1 + leaf->right->height;

	if (left_height > right_height)
		return left_height;

		return right_height;
}

int AVL::get_balance(node* leaf)
{
	int left_height;
	int right_height;
	if (leaf == NULL)
	{
		return 0;
	}

	if (leaf->left == NULL)
	{
		left_height = 0;
	}

	else
		left_height = 1 + leaf->left->height;

	if (leaf->right == NULL)
	{
		right_height = 0;
	}

	else
		right_height = 1 + leaf->right->height;

	return (left_height - right_height);
}

int AVL::MAX(int a, int b)
{
	return (a > b ? a : b);

	//OR we can ALSO write it as 
	
	/*if(a>b)
	{
	return a;
	}
	else
	{
		return b;
	}*/
	
}
node* AVL::Right_Rotation(node* x)
{
	node* y = x->left;
	node* Node = y->right;

	//PERFORMING ROTATION
	y->right = x;
	x->left = Node;

	//UPDATING HEIGHTS
	x->height = MAX(height(x -> left), height(x->right)) + 1;
	y->height = MAX(height(y->left), height(y->right)) + 1;

	//Returning new root
	return y;
}

node* AVL::Left_rotate(node* y)
{
	node* x = y->right;
	node* Node2 = x->left;

	//PERFORMING ROTATION

	x->left = y;
	y->right = Node2;

	//UPDATING HEIGHTS
	y->height = MAX(height(y->left), height(y->right));
	x->height = MAX(height(x->left), height(x->right));

	return x;
}

node* AVL::Delete_Node(node* leaf,int x)
{
	if (leaf == NULL)
	{
		return NULL;
	}
	else
	if (x < leaf->data)
	{
		leaf->left = Delete_Node(leaf->left, x);
	}

	else if (x > leaf->data)
	{
		leaf->right = Delete_Node(leaf->right, x);
	}

	
	else
	{
		//NO CHILD CASE

		if (leaf->left == NULL && leaf->right == NULL)
		{
			leaf==NULL;
			
		}

		//ONE CHILD CASE
		if (leaf->left == NULL)
		{
			node* temp = leaf;
			leaf = leaf->right;
			temp==NULL;
		}
		else if (leaf->right == NULL)
		{
			node* temp = leaf;
			leaf = leaf->left;
			temp==NULL;
		}

		//TWO CHILD CASE
		else
		{
			node* temp = max(leaf->left);
			leaf->data = temp->data;
			leaf->left = Delete_Node(leaf->left, x);
		}

	}
	
	if (leaf == NULL)
	{
		return leaf;
	}

	leaf->height = 1 + MAX(height(leaf->left), height(leaf->right));
	int balance = get_balance(leaf);

	//LEFT LEFT CASE
	if (balance > 1 && get_balance(leaf->left) >= 0)
	{
		return Right_Rotation(leaf);
	}

	//LEFT RIGHT CASE
	if (balance > 1 && get_balance(leaf->left) < 0)
	{
		leaf->left = Left_rotate(leaf->left);
		return Right_Rotation(leaf);
	}

	//RIGHT RIGHT CASE
	if (balance < -1 && get_balance(leaf->right) <= 0)
	{
		return Left_rotate(leaf);
	}

	//RIGHT LEFT CASE
	if (balance < -1 && get_balance(leaf->right)>0)
	{
		leaf->right = Right_Rotation(leaf->right);
		return Left_rotate(leaf);
	}
	
	return leaf;


}

void AVL::Inorder_Triversal(node* leaf)
{
	if (leaf == NULL)
	{
		return;
	}

	else
	{
		Inorder_Triversal(leaf->left);
		cout << leaf->data << endl;
		Inorder_Triversal(leaf->right);
	}
}

void AVL::INSERT(int val)
{
	root = insert(root, val);
}

void AVL::DELETE(int val)
{
	root=Delete_Node(root, val);
}

void AVL::INORDER_PRINT()
{
	Inorder_Triversal(root);
}
void AVL::Display()
{
	AVL avl;
	avl.INSERT(20);
	avl.INSERT(10);
	avl.INSERT(25);
	avl.INSERT(30);
	avl.INSERT(42);
	avl.INSERT(15);
	avl.INSERT(7);
	avl.INSERT(70);
	cout << endl;
	cout << "Before deletion "<<endl;
	cout << endl;
	avl.INORDER_PRINT();
	cout << endl;
	cout <<"After deletion"<< endl;
	cout << endl;
	avl.DELETE(42);
	cout << endl;
	cout << endl;
	avl.INORDER_PRINT();

}
int main()
{
	AVL avlobj;
	avlobj.Display();

	return 0;
}

struct node
{
  int key_value;
  node *left;
  node *right;
};

class btree
{
    public:
		btree() { 
			root = NULL;
		}
		~btree() {
			destroy_tree();
		}

		void insert(int key) {
			if (root != NULL)
				insert(key, root);
			else
			{
				root = new node;
				root->key_value = key;
				root->left = NULL;
				root->right = NULL;
			}
		}
		node *search(int key) {
			return search(key, root);
		}
		void destroy_tree() {
			destroy_tree(root);
		}

    private:
		void destroy_tree(node *leaf) {
			if (leaf != NULL)
			{
				destroy_tree(leaf->left);
				destroy_tree(leaf->right);
				delete leaf;
			}
		}
		void insert(int key, node *leaf) {
			if (key< leaf->key_value)
			{
				if (leaf->left != NULL)
					insert(key, leaf->left);
				else
				{
					leaf->left = new node;
					leaf->left->key_value = key;
					leaf->left->left = NULL;    //Sets the left child of the child node to null
					leaf->left->right = NULL;   //Sets the right child of the child node to null
				}
			}
			else if (key >= leaf->key_value)
			{
				if (leaf->right != NULL)
					insert(key, leaf->right);
				else
				{
					leaf->right = new node;
					leaf->right->key_value = key;
					leaf->right->left = NULL;  //Sets the left child of the child node to null
					leaf->right->right = NULL; //Sets the right child of the child node to null
				}
			}
		}
		node *search(int key, node *leaf) {
			if (leaf != NULL)
			{
				if (key == leaf->key_value)
					return leaf;
				if (key<leaf->key_value)
					return search(key, leaf->left);
				else
					return search(key, leaf->right);
			}
			else return NULL;
		}

        node *root;
};



/*
void example code()
{
	btree t;
	// populate t
	btree t2;
	t2 = std::move(t);        // explicit rvalue reference creation
	t2 = btree("data.txt");   // implicit rvalue reference creation (imagining that btree has a constructor taking string, to read itself in from a file).
}
*/

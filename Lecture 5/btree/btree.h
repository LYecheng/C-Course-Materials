#include <memory>
#include <utility>
using std::unique_ptr;
using std::move;

struct node
{
  node(int key_value) : key_value(key_value) {}
  node(node const &other)
	  : key_value(other.key_value) {
	  if (other.left)
		  left.reset(new node(*other.left));
	  if (other.right)
		  right.reset(new node(*other.right));
  }

  int key_value;
  unique_ptr<node> left;
  unique_ptr<node> right;
};

class btree
{
    public:
		btree() { }
		btree(btree const &other) {
			if (other.root) {
				root.reset(new node(*other.root));
			}
		}

		// btree(btree &&other) = default; // Best way to do it, but not supported in VS2013
		btree(btree &&other) : root(move(other.root)) {}

		void operator=(btree const &other) {
			if (other.root) {
				root.reset(new node(*other.root));
			}
		}

		void operator=(btree &&other) {
			swap(root, other.root);
		}
		void insert(int key) {
			if (root)
				insert(key, root.get());
			else
				root.reset(new node(key));
		}
		node *search(int key) {
			return search(key, root.get());
		}

    private:
		void insert(int key, node *leaf) {
			if (key< leaf->key_value)
			{
				if (leaf->left != NULL)
					insert(key, leaf->left.get());
				else
					leaf->left.reset(new node(key));
			}
			else if (key >= leaf->key_value)
			{
				if (leaf->right)
					insert(key, leaf->right.get());
				else
					leaf->right.reset(new node(key));
			}
		}
		node *search(int key, node *leaf) {
			if (leaf)
			{
				if (key == leaf->key_value)
					return leaf;
				if (key<leaf->key_value)
					return search(key, leaf->left.get());
				else
					return search(key, leaf->right.get());
			}
			else return nullptr;
		}

        unique_ptr<node> root;
};


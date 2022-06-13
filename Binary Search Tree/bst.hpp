#ifndef MS549_BST
#define MS549_BST

#include <iostream>
#include <string>

namespace bst {
	/// <summary>
	/// BST Traversal Order Options
	/// </summary>
	enum TraversalOrder {
		InOrder,
		PreOrder,
		PostOrder,
	};

	/// <summary>
	/// A generic implimentation of a Binary Search Tree.
	/// </summary>
	/// <typeparam name="T">Data type that the BST stores.</typeparam>
	template <typename T> class BST {
	public:
		/// <summary>
		/// Node class for BST.
		/// </summary>
		class Node {
		private:
			/// <summary>
			/// The parrent of this node.
			/// </summary>
			Node* top;

			/// <summary>
			/// The left child of this node
			/// </summary>
			Node* left;

			/// <summary>
			/// The right child of this node
			/// </summary>
			Node* right;

			/// <summary>
			/// Allow BST class to access Node private members;
			/// </summary>
			friend class BST;

		public:
			/// <summary>
			/// The number of values stored in the tree with the value in this node.
			/// </summary>
			int count;

			/// <summary>
			/// The value contained in the node.
			/// </summary>
			T value;

			/// <summary>
			/// Node Constructor
			/// </summary>
			/// <param name="value"></param>
			/// <param name="next"></param>
			/// <param name="prev"></param>
			Node(T value, Node* top = nullptr, Node* left = nullptr, Node* right = nullptr) {
				this->count = 1;
				this->value = value;
				this->top = top;
				this->left = left;
				this->right = right;
			}

			/// <summary>
			/// Node Deconstructor
			/// </summary>
			~Node() {
				if (this->left != nullptr) delete this->left;
				if (this->right != nullptr) delete this->right;
			}

			/// <summary>
			/// Insert a new node into this node.
			/// </summary>
			/// <returns>This node.</returns>
			Node* insert(Node*& node) {
				if (node->value > this->value) {
					if (this->right == nullptr) this->right = node;
					else this->right = this->right->insert(node);
				}
				else if (node->value < this->value) {
					if (this->left == nullptr) this->left = node;
					else this->left = this->left->insert(node);
				}
				else if (this->value == node->value) {
					this->count += 1;

					//delete the duplicate node and set the passed pointer to this node
					delete node;
					node = this;
				}

				return this;
			}

			/// <summary>
			/// Get this node's sucessor and set the references to its children to null.
			/// </summary>
			/// <returns>The node to replace the current node.</returns>
			Node* sucessor() {
				Node* sucessor = nullptr;

				if (this->left == nullptr && this->right == nullptr);
				else if (this->left == nullptr) sucessor = this->right;
				else if (this->right == nullptr) sucessor = this->left;
				else {
					//move the left child to now be a child of the right node
					sucessor = this->right->insert(this->left);
				}

				this->left = nullptr;
				this->right = nullptr;

				return sucessor;
			}

			/// <summary>
			/// Defines conversion of the node to value type.
			/// </summary>
			operator T() const { return this->value; }
		};

	private:
		/// <summary>
		/// Root node of the BST.
		/// </summary>
		Node* root;

	public:
		BST() {
			this->root = nullptr;
		}

		~BST() {
			if (this->root != nullptr) delete this->root;
		}

		/// <summary>
		/// Insert a new item into the tree.
		/// </summary>
		/// <param name="item">The item to be inserted.</param>
		Node* insert(T item) {
			//create new node
			Node* node = new Node(item);

			//insert new node
			this->root = this->root == nullptr ? node : this->root->insert(node);
		
			//return the new node
			return node;
		}

		/// <summary>
		/// Find the node containing the specified value.
		/// </summary>
		/// <param name="item">Value to search for.</param>
		/// <returns>The matching node if found.</returns>
		Node* find(T item) {
			return find(this->root, item);
		}

		/// <summary>
		/// Find the node containing the specified value.
		/// </summary>
		/// <param name="current">Current node being searched.</param>
		/// <param name="item">Value to search for.</param>
		/// <returns>The matching node if found.</returns>
		Node* find(Node* current, T item) {
			if (current == nullptr) return nullptr;

			if (current->value < item) {
				return find(current->right, item);
			}
			else if (current->value > item) {
				return find(current->left, item);
			}
			else {
				return current;
			}
		}

		/// <summary>
		/// Remove all nodes from the BST.
		/// </summary>
		void remove_all() {
			while (this->root != nullptr) {
				remove();
			}
		}

		/// <summary>
		/// Remove the first node BST.
		/// </summary>
		void remove() {
			if (this->root != nullptr) {
				this->root = remove(this->root, this->root);
			}
		}

		/// <summary>
		/// Remove a specified item from the tree.
		/// </summary>
		/// <param name="item"></param>
		void remove(T item) {
			//find the node containing the specified item
			Node* node = find(item);

			//if a node was found remove it
			if (node != nullptr) {
				this->root = remove(this->root, node);
			}
		}

		/// <summary>
		/// Remove a specified node from the tree.
		/// </summary>
		/// <param name="current">The node currently being iterated over.</param>
		/// <param name="toDelete">The node to be removed.</param>
		Node* remove(Node* current, Node* toDelete) {
			if (current == nullptr) return nullptr;

			if (current->value < toDelete->value) {
				current->right = remove(current->right, toDelete);
			}
			else if (current->value > toDelete->value) {
				current->left = remove(current->left, toDelete);
			}
			else {
				//in the case the node is storing more than 1 of the same value, decrement the count and return the node
				if (toDelete->count > 1) {
					toDelete->count -= 1;
				}
				else {
					//get the sucessor for this node and delete the node, then return the sucessor
					Node* sucessor = toDelete->sucessor();
					delete toDelete;
					return sucessor;
				}
			}

			return current;
		}

		/// <summary>
		/// Traverse the tree and output to the specified stream in the specified order.
		/// </summary>
		/// <param name="stream">The stream to output to.</param>
		/// <param name="order">The order to traverse the tree in.</param>
		void traverse(TraversalOrder order = TraversalOrder::InOrder, std::wostream& stream = std::wcout) {
			//open list
			stream << L"[";
			
			//print list in specified order
			if (order == TraversalOrder::InOrder) inorder(this->root, stream);
			else if (order == TraversalOrder::PostOrder) postorder(this->root, stream);
			else if (order == TraversalOrder::PreOrder) preorder(this->root, stream);

			//remove trailing comma and add closing bracket
			stream << L"\b\b]\n";
		}

		/// <summary>
		/// Perform an postorder traversal step.
		/// </summary>
		/// <param name="current">Current node being traversed.</param>
		/// <param name="stream">Stream to output node value to.</param>
		void postorder(Node* current, std::wostream& stream = std::wcout) {
			//return once we reach null
			if (current == nullptr) return;

			//postorder traverse
			postorder(current->left, stream);
			postorder(current->right, stream);
			stream << current->value << L", ";
		}

		/// <summary>
		/// Perform an inorder traversal step.
		/// </summary>
		/// <param name="current">Current node being traversed.</param>
		/// <param name="stream">Stream to output node value to.</param>
		void inorder(Node* current, std::wostream& stream = std::wcout) {
			//return once we reach null
			if (current == nullptr) return;
				
			//inorder traverse
			inorder(current->left, stream);
			stream << current->value << L", ";
			inorder(current->right, stream);
		}

		/// <summary>
		/// Perform an preorder traversal step.
		/// </summary>
		/// <param name="current">Current node being traversed.</param>
		/// <param name="stream">Stream to output node value to.</param>
		void preorder(Node* current, std::wostream& stream = std::wcout) {
			//return once we reach null
			if (current == nullptr) return;

			//preorder traverse
			stream << current->value << L", ";
			preorder(current->left, stream);
			preorder(current->right, stream);
		}
		
		/// <summary>
		/// Return the node with the smallest value in the tree.
		/// </summary>
		/// <param name="node">Current node being iterated over.</param>
		Node* minimum(Node* node = nullptr) {
			if (node == nullptr) {
				if (this->root == nullptr) return nullptr;
				return minimum(this->root);
			}
			if (node->left == nullptr) return node;
			return minimum(node->left);
		}

		/// <summary>
		/// Return the node with the largest value in the tree.
		/// </summary>
		/// <param name="node">Current node being iterated over.</param>
		Node* maximum(Node* node = nullptr) {
			if (node == nullptr) {
				if (this->root == nullptr) return nullptr;
				return maximum(this->root);
			}
			if (node->right == nullptr) return node;
			return maximum(node->right);
		}

		/// <summary>
		/// Print the BST to the provided stream.
		/// </summary>
		/// <param name="show_null">If null values should be printed.</param>
		/// <param name="stream">The stream to output to.</param>
		void print(bool show_null = true, std::wostream& stream = std::wcout) {
			//print tree starting at node
			print(this->root, show_null, L"", false, stream);
		}
		
		/// <summary>
		/// Print the BST to the provided stream.
		/// </summary>
		/// <param name="node">Node being traversed.</param>
		/// <param name="show_null">If null values should be printed.</param>
		/// <param name="prefix">Prefix to append to the line being printed.</param>
		/// <param name="is_left">If the current node is a left side node.</param>
		/// <param name="stream">The stream to output to.</param>
		void print(Node* node, bool show_null, std::wstring prefix, bool is_left, std::wostream& stream = std::wcout) {
			if (node != nullptr) {
				//node prefix
				stream << prefix;

				//branch based on left-right node
				stream << (is_left ? L"├──" : L"└──");

				//print the value of the node
				stream << node->value << L" (" << node->count << L") " << std::endl;

				//continue to the next level of the tree
				bool child_show_null = show_null ? (node->left != nullptr || node->right != nullptr) : false;
				print(node->left, child_show_null, prefix + (is_left ? L"│   " : L"    "), (show_null ? true : !(node->left != nullptr && node->right == nullptr)), stream);
				print(node->right, child_show_null, prefix + (is_left ? L"│   " : L"    "), false, stream);
			}
			else {
				//show null nodes if this is true
				if (show_null) {
					//node prefix
					stream << prefix;

					//node branch
					stream << (is_left ? L"├──" : L"└──");

					//null node
					stream << L"null" << std::endl;
				}
			}
		}
	};
}

#endif // !

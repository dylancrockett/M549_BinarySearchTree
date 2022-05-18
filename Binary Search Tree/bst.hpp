#ifndef MS549_BST
#define MS549_BST

#include <iostream>
#include <string>

namespace bst {
	/// <summary>
	/// A generic implimentation of a Binary Search Tree.
	/// </summary>
	/// <typeparam name="T">Data type that the Doubly LinkedList stores.</typeparam>
	template <typename T> class BST {
	public:
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
				this->value = value;
				this->next = next;
				this->prev = prev;
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
		}

	};
}

#endif // !

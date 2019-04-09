

#include <iostream>
#include <queue>
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
  int val;
  COLOR color;
  Node *left, *right, *parent;

  Node(int val) : val(val) {
    parent = left = right = NULL;
    color = RED;
  }

  Node *uncle() {
    // jesli nie ma ojca ani dziadka to nie ma tez wujka
    if (parent == NULL or parent->parent == NULL)
      return NULL;

    if (parent->isOnLeft())
      // wujek po prawej
      return parent->parent->right;
    else
      // wujek po lewej
      return parent->parent->left;
  }

  // sprawdzamy czy obecny wezel jest po lewej
  bool isOnLeft() { return this == parent->left; }

  // zwracamy wskaznik do brata
  Node *brother() {
    // nie ma brata jesli nie ma ojca
    if (parent == NULL)
      return NULL;

    if (isOnLeft())
      return parent->right;

    return parent->left;
  }

  // sprowadzenie wezla na dol
  void moveDown(Node *nParent) {
    if (parent != NULL) {
      if (isOnLeft()) {
        parent->left = nParent;
      } else {
        parent->right = nParent;
      }
    }
    nParent->parent = parent;
    parent = nParent;
  }

  bool hasRedChild() {
    return (left != NULL and left->color == RED) or
           (right != NULL and right->color == RED);
  }
};

class RBTree {
  public:  Node *root;
  int counter;
  void leftRotate(Node *node) {
    Node *nParent = node->right;
    if (node == root)
      root = nParent;
    node->moveDown(nParent);
    node->right = nParent->left;
    if (nParent->left != NULL)
      nParent->left->parent = node;
    nParent->left = node;
  }

  void rightRotate(Node *node) {
    Node *nParent = node->left;

    if (node == root)
      root = nParent;

    node->moveDown(nParent);
    node->left = nParent->right;
    if (nParent->right != NULL)
      nParent->right->parent = node;
    nParent->right = node;
  }

  void swapColors(Node *node1, Node *node2) {
    COLOR temp;
    temp = node1->color;
    node1->color = node2->color;
    node2->color = temp;
  }
  void swapValues(Node *u, Node *v) {
    int temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
  }

  void findRR(Node *node) {
    if (node == root) {
      node->color = BLACK;
      return;
    }

    // Inicjalizacja
    Node *parent = node->parent, *grandparent = parent->parent,
         *uncle = node->uncle();

    if (parent->color != BLACK) {
      if (uncle != NULL && uncle->color == RED) {
        // przypadek gdy wujek i ojciec jest czerowny
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        findRR(grandparent);
      } else {
        //Jesli ojciec jest czerowony a wujek czarny
        if (parent->isOnLeft()) {
          if (node->isOnLeft()) {
            swapColors(parent, grandparent);
          } else {
            leftRotate(parent);
            swapColors(node, grandparent);
          }
          rightRotate(grandparent);
        } else {
          if (node->isOnLeft()) {
            rightRotate(parent);
            swapColors(node, grandparent);
          } else {
            swapColors(parent, grandparent);
          }
          leftRotate(grandparent);
        }
      }
    }
  }

 //znajdujemy wezel ktory nie ma lewego syna
  Node *zastepczy(Node *node) {
    Node *temp = node;

    while (temp->left != NULL)
      temp = temp->left;

    return temp;
  }

  // szukamy wezel do zastapienia usunietego
  Node *BSTreplace(Node *node) {
    // jesli wezel ma 2 synow
    if (node->left != NULL and node->right != NULL)
      return zastepczy(node->right);

    // gdy to lisc
    if (node->left == NULL and node->right == NULL)
      return NULL;

    // gdy ma jednego syna
    if (node->left != NULL)
      return node->left;
    else
      return node->right;
  }

  // usuwanie wezla
  void deleteNode(Node *v) {
    Node *u = BSTreplace(v);

    // Jezeli zastepujacy i normalny maja ten sam kolor
    bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
    Node *parent = v->parent;

    if (u == NULL) {
      if (v == root) {
        root = NULL;
      } else {
        if (uvBlack) {
          findDB(v);
        } else {
          if (v->brother() != NULL)
            v->brother()->color = RED;
        }

        // Usuwamy stary wezel
        if (v->isOnLeft()) {
          parent->left = NULL;
        } else {
          parent->right = NULL;
        }
      }
      delete v;
      return;
    }

    if (v->left == NULL or v->right == NULL) {
      // V posiada jednego syna
      if (v == root) {
        // Jezeli v to korzen, nadajemy mu wartosc u, i usuwamy u;
        v->val = u->val;
        v->left = v->right = NULL;
        delete u;
      } else {
        // Wrzucamy wezel u do gory
        if (v->isOnLeft()) {
          parent->left = u;
        } else {
          parent->right = u;
        }
        delete v;
        u->parent = parent;
        if (uvBlack) {
          // jesli u i v sa czarne
          findDB(u);
        } else {
          // jesli u i v sa czerwone
          u->color = BLACK;
        }
      }
      return;
    }

    // v ma 2 synow, zamieniamy wartosci i usuwamy u
    swapValues(u, v);
    deleteNode(u);
  }

  void findDB(Node *node) {
    if (node == root)
      return;

    Node *brother = node->brother(), *parent = node->parent;
    if (brother == NULL) {
      findDB(parent);
    } else {
      if (brother->color == RED) {
        // brat czerwony
        parent->color = RED;
        brother->color = BLACK;
        if (brother->isOnLeft()) {
          // gdy brat jest po lewej
          rightRotate(parent);
        } else {
          leftRotate(parent);
        }
        findDB(node);
      } else {
        // brat czarny
        if (brother->hasRedChild()) {
          // brat posiada co najmniej 1 czerwonego syna
          if (brother->left != NULL and brother->left->color == RED) {
            if (brother->isOnLeft()) {
              // gdy brat jest z lewej i jego syn tez z lewej
              brother->left->color = brother->color;
              brother->color = parent->color;
              rightRotate(parent);
            } else {
              // gdy brat jest z prawej i jego syn jest z lewej
              brother->left->color = parent->color;
              rightRotate(brother);
              leftRotate(parent);
            }
          } else {
            if (brother->isOnLeft()) {
              // gdy brat jest z lewej a jego syn z prawej
              brother->right->color = parent->color;
              leftRotate(brother);
              rightRotate(parent);
            } else {
              // gdy brat jest z prawej i jego syn jest z prawej
              brother->right->color = brother->color;
              brother->color = parent->color;
              leftRotate(parent);
            }
          }
          parent->color = BLACK;
        } else {
          // obaj synowie brata sa czarni
          brother->color = RED;
          if (parent->color == BLACK)
            findDB(parent);
          else
            parent->color = BLACK;
        }
      }
    }
  }

  void levelOrder(Node *node) {
    if (node == NULL)
      return;
    queue<Node *> q;
    Node *curr;
    q.push(node);

    while (!q.empty()) {
      curr = q.front();
      q.pop();
      cout << curr->val;
      if (curr->color == RED)
        cout << "+ ";
      else
        cout << " ";

      if (curr->left != NULL)
        q.push(curr->left);
      if (curr->right != NULL)
        q.push(curr->right);
    }
  }
  void inorder(Node *node) {
    if (node == NULL)
      return;
    inorder(node->left);
    cout << node->val;
    if (node->color == RED){
        cout << "+ ";
        counter++;
    }
    else
        cout << " ";
    inorder(node->right);
  }
public:
  RBTree() { root = NULL; }

  Node *getRoot() { return root; }

  Node *search(int n) {
    Node *temp = root;
    while (temp != NULL) {
      if (n < temp->val) {
        if (temp->left == NULL)
          break;
        else
          temp = temp->left;
      } else if (n == temp->val) {
        break;
      } else {
        if (temp->right == NULL)
          break;
        else
          temp = temp->right;
      }
    }

    return temp;
  }

  // Wstawianie
  void insert(int n) {
    Node *newNode = new Node(n);
    if (root == NULL) {
      newNode->color = BLACK;
      root = newNode;
    } else {
      Node *temp = search(n);

      if (temp->val == n) {
        return;
      }
      newNode->parent = temp;
      if (n < temp->val)
        temp->left = newNode;
      else
        temp->right = newNode;
      findRR(newNode);
    }
  }

  // Usuwanie
  void deleting(int n) {
    if (root == NULL)
      // Tree is empty
      return;

    Node *v = search(n), *u;

    if (v->val != n) {
      cout << "Nie znaleziono wezla o takiej wartosci:" << n << endl;
      return;
    }

    deleteNode(v);
  }

  // Funkcja drukujaca
  void printInOrder() {
    counter = 0;
    cout << "Inorder: " << endl;
    if (root == NULL)
      cout << "Drzewo jest puste" << endl;
    else
      inorder(root);
    cout << endl;
  }

  // Funkcja drukujaca w "Level order"
  void printLevelOrder() {
    cout << "Level order: " << endl;
    if (root == NULL)
      cout << "Drzewo jest puste" << endl;
    else
      levelOrder(root);
    cout << endl;
  }
  int FindMax(Node* root)
{
	if(root==NULL)
		return 0;

	else
	{
		int lb=FindMax(root->left);
		int rb=FindMax(root->right);
		return max(lb,rb)+1;
	}
}
int FindMin(Node* root)
{
	if(root==NULL)
		return 0;

	else
	{
		int lb=FindMin(root->left);
		int rb=FindMin(root->right);
		return min(lb,rb)+1;
	}
}
};
int main() {
  RBTree tree;

  tree.insert(3);
  tree.insert(10);
  tree.insert(5);
  tree.insert(8);
  tree.insert(11);
  tree.insert(26);
  tree.insert(13);
  cout << "Maksymalna wysokosc: " <<tree.FindMax(tree.root) << endl;
  cout << "Minimalna wysokosc: " <<tree.FindMin(tree.root) << endl;
  tree.printInOrder();
  tree.printLevelOrder();
  cout <<"Ilosc czerwonych: "<< tree.counter << endl;
  cout<<endl<<"Usuwamy 3 10 11"<<endl;

  tree.deleting(3);
  tree.deleting(10);
  tree.deleting(11);

  tree.printInOrder();
  tree.printLevelOrder();
  cout << "Maksymalna wysokosc: " <<tree.FindMax(tree.root) << endl;
  cout << "Minimalna wysokosc: " <<tree.FindMin(tree.root) << endl;
  cout <<"Ilosc czerwonych: "<< tree.counter << endl;
  return 0;
}

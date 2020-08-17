#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Node {
	int value;
	Node *left;
	Node *right;

	Node(int v = 0) { value = v; left = NULL; right = NULL; }
};

typedef Node *BiTree;

void destroy(BiTree tree);

void pre_ord_trav(BiTree tree);
void pre_ord_trav_norec(BiTree tree);

void in_ord_trav(BiTree tree);
void in_ord_trav_norec(BiTree tree);

void post_ord_trav(BiTree tree);
void post_ord_trav_norec(BiTree tree);

int main()
{
	// create the example bi-tree
	BiTree tree = new Node(1);
	tree->left = new Node(2);
	tree->right = new Node(3);
	tree->left->left = new Node(4);
	tree->left->right = new Node(5);
	tree->right->left = new Node(6);
	tree->left->left->left = new Node(7);
	tree->left->left->right = new Node(8);
	tree->right->left->right = new Node(9);

	// 先序遍历测试
	cout << "Pre-ordered traversal  (recur): ";
	pre_ord_trav(tree);
	cout << endl;
	cout << "Pre-ordered traversal  (no-re): ";
	pre_ord_trav_norec(tree);
	cout << endl;
	cout << "Pre-ordered traversal an empty tree: ";
	pre_ord_trav_norec(NULL);
	cout << endl;
	cout << "Pre-ordered traversal a single node tree: ";
	pre_ord_trav_norec(tree->left->right);
	cout << endl;
	cout << "Pre-ordered traversal a linear tree: ";
	pre_ord_trav_norec(tree->right);
	cout << endl;

	// 中序遍历测试
	cout << "In-ordered traversal   (recur): ";
	in_ord_trav(tree);
	cout << endl;
	cout << "In-ordered traversal   (no-re): ";
	in_ord_trav_norec(tree);
	cout << endl;
	cout << "In-ordered traversal an empty tree: ";
	in_ord_trav_norec(NULL);
	cout << endl;
	cout << "In-ordered traversal a single node tree: ";
	in_ord_trav_norec(tree->left->right);
	cout << endl;
	cout << "In-ordered traversal a linear tree: ";
	in_ord_trav_norec(tree->right);
	cout << endl;

	// 后序遍历测试
	cout << "Post-ordered traversal (recur): ";
	post_ord_trav(tree);
	cout << endl;
	cout << "Post-ordered traversal (no-re): ";
	post_ord_trav_norec(tree);
	cout << endl;
	cout << "Post-ordered traversal an empty tree: ";
	post_ord_trav_norec(NULL);
	cout << endl;
	cout << "Post-ordered traversal a single node tree: ";
	post_ord_trav_norec(tree->left->right);
	cout << endl;
	cout << "Post-ordered traversal a linear tree: ";
	post_ord_trav_norec(tree->right);
	cout << endl;

	destroy(tree);
	return 0;
}

void destroy(BiTree tree)
{
	queue<BiTree> q;
	q.push(tree);
	while (!q.empty()) {
		if (q.front()) {
			q.push(q.front()->left);
			q.push(q.front()->right);
			delete q.front();
		}
		q.pop();
	}
}

void pre_ord_trav(BiTree tree)
{
	if (tree) {
		cout << tree->value << " ";
		pre_ord_trav(tree->left);
		pre_ord_trav(tree->right);
	}
}

void pre_ord_trav_norec(BiTree tree)
{
	// 如果树根为空，则直接返回
	if (!tree) return;
	// 这是存放待处理节点的栈
	stack<BiTree> stk;
	// 从根节点开始遍历
	stk.push(tree);
	// 遍历直到栈空为止
	while (!stk.empty()) {
		// 获取当前栈顶节点
		BiTree node = stk.top();
		// 访问该节点（输出其值）
		cout << node->value << " ";
		// 该节点已经访问过，从栈中弹出
		stk.pop();
		// 依次将其右儿子和左儿子压栈，作为待访问节点。
		// 依据栈的先进后出规则，左儿子今后会先出栈，所以下一轮循环访问
		// 的将是当前所访问节点的左儿子。
		// 而访问了左儿子之后，又回依次压入左儿子的右、左两个儿子......
		// 所以当前所访问的节点之后一定是先访问完它的左子树后才会接着
		// 访问它的右子树。
		// 每一个节点被访问之后都是按照这个规则开始它的后续访问，所以
		// 最终实现的就是先序遍历，也就是深度优先的规则。
		if (node->right) stk.push(node->right);
		if (node->left)  stk.push(node->left);
	}
}

void in_ord_trav(BiTree tree)
{
	if (tree) {
		in_ord_trav(tree->left);
		cout << tree->value << " ";
		in_ord_trav(tree->right);
	}
}

void in_ord_trav_norec(BiTree tree)
{
	// 这是下一个要处理的节点，并不是下一个要访问的节点
	BiTree node = tree;
	// 这是存放待处理节点的栈
	stack<BiTree> stk;
	// 遍历的循环条件为：待处理节点的栈不空或者下一个要处理的节点存在，即如果
	// 待处理节点的栈已经空了而且下一个要处理的节点又不存在，那么遍历就结束了。
	// 注意：如果树根本身为空，此时stk为空而且node为NULL，循环将直接结束。
	while (!stk.empty() || node) {
		if (node) {
			// 如果下一个要处理的节点不为空，那么将其压栈，并且让它的
			// 左儿子成为下一个要处理的节点。
			// 通过这种方式，可以从一个节点开始一路向左向下直到找到最
			// 左下端的那个节点。这个节点一定没有左儿子了，不管它有没
			// 有右儿子，它一定就是接下来要访问的那个节点，此时下一个
			// 要处理的节点会被设置为它的左儿子，即NULL，而它本身一定
			// 是在栈顶位置。
			stk.push(node);
			node = node->left;
		} else {
			// 进入这个判断分支时，node为NULL，也就是上面所说的那种情
			// 况：栈顶是接下来要访问的节点，所以就访问它并将其弹出。
			node = stk.top();
			cout << node->value << " ";
			stk.pop();
			// 按照中序遍历规则，接下来是要处理刚被访问掉的那个节点的
			// 右子树了，所以将其右儿子设置为下一个要处理的节点。
			// 此时又分两种情况：
			// 第一种情况是这个节点确实有右子树，那么node将会指向一个
			// 实实在在存在的节点，当进入下一轮循环的时候程序就会将其
			// 视为一个根节点一样处理，如前所述，这样就能完成右子树的
			// 中序遍历；
			// 第二种情况是这个节点并没有右儿子，那么node将变成NULL，
			// 于是当进入下一轮循环时，将直接进入本分支，进而访问到这
			// 个节点的父节点，这相当于是完成了左子树中序遍历后重新回
			// 溯到父节点。
			node = node->right;
		}
	}
}

void post_ord_trav(BiTree tree)
{
	if (tree) {
		post_ord_trav(tree->left);
		post_ord_trav(tree->right);
		cout << tree->value << " ";
	}
}

void post_ord_trav_norec(BiTree tree)
{
	// node是下一个要处理的节点，last_node是上一次刚访问过的节点
	BiTree node = tree, last_node = NULL;
	// 这是存储待处理节点的栈
	stack<BiTree> stk;
	// 和中序遍历一样的循环条件：待处理节点栈不空或者下一个要处理的节点存在
	while (!stk.empty() || node) {
		if (node) {
			// 同样的，每一个要处理的节点，首先以它为根一路坐下而行
			// 直到找到没有左儿子的那个节点，这和中序遍历是一样的。
			stk.push(node);
			node = node->left;
		} else {
			// 同样的，进入node为空的这个分支就相当于是进行了回溯。
			// 此时先取得栈顶节点，但是不能和中序遍历时一样直接访问
			// 它，因为我们不知道是从左子树回溯的还是从右子树回溯的，
			// 按照后序遍历的规则，只有从右子树回溯的时候才能访问。
			node = stk.top();
			if (node->right && node->right != last_node) {
				// 栈顶节点存在右子树，而且上一次访问的节点并不
				// 是它的右儿子，说明不是从右子树回溯的，那么按
				// 照规则接下来要先去遍历它的右子树，因此把它的
				// 右儿子设置为下一个要处理的节点。
				node = node->right;
			} else {
				// 右子树不存在或者上一次刚刚访问过的就是它的右
				// 儿子，说明是从右子树回溯的，按照后序遍历规则
				// 访问这个节点并将其弹栈。
				cout << node->value << " ";
				stk.pop();
				// 每次访问一个节点之后都必须要将其设置为上一次
				// 刚访问的节点
				last_node = node;
				// 按照后序遍历的规则，每次一个节点被访问过，就
				// 说明以它为根的子树遍历结束了，那么就要回溯到
				// 它的父节点去，它的父节点一定在当前栈顶，所以
				// 把下一个要处理的节点设为空，就会在下一轮循环
				// 的时候直接进入回溯的分支。
				node = NULL;
			}
		}
	}
}


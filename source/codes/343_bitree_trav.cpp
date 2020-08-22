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
	// 创建测试用二叉树
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
	// 这是下一棵要遍历的子树，并不是下一个要访问的节点
	// 看树结构的代码，一定要牢记：根节点就是树，树就是子树
	BiTree node = tree;
	// 这是存放待遍历子树的栈
	stack<BiTree> stk;
	// 循环条件为：待遍历子树栈不空或者下一棵待遍历子树存在。反之，如果待
	// 遍历子树的栈已空且下一棵要遍历的子树也空，那么整个遍历就结束了。
	// 注意：如果参数tree为NULL，此时栈为空且node为NULL，循环将直接结束。
	while (!stk.empty() || node) {
		// 进入循环，下一棵要遍历的子树有两种情况：
		// 1. node != NULL，即下一棵要遍历的子树真实存在；
		// 2. node == NULL，即下一棵要遍历的子树其实为空。
		if (node) {
			// 如果下一棵要遍历的子树真实存在，那么根据中序遍历的
			// 规则，一定是要先遍历其左子树。
			// 所以这时便出现了一棵新的子树node->left，要先于node
			// 完成遍历，因此我们把node暂时先压入栈中，进入下一轮
			// 循环去遍历子树node->left。
			// 通过这种方式，可以从一个节点开始一路向左向下直到最
			// 左下端的那个节点。这个节点一定没有左子树了。此时下
			// 一棵要遍历的子树一定是NULL。而一路左下途经的所有节
			// 点都会按照从高到低的顺序压在栈中，今后出栈的顺序就
			// 会恰好是从低到高回溯的顺序。
			stk.push(node);
			node = node->left;
		} else {
			// 出现node == NULL时，也就是遍历从子树回溯的时候。
			// 1.从左子树回溯：此时按遍历规则应该访问其父节点，而
			//   此时该不存在的左子树的父节点一定恰是栈顶节点；
			// 2.从右子树回溯：此时按遍历规则应该从其父节点进一步
			//   回溯，如果其父节点位于左支，那么接下来应该访问父
			//   节点的父节点；反之说明父节点的父节点也应该已经被
			//   访问过了，需要继续向上回溯，如此下去直到遇到某个
			//   先代节点是位于左支上的，而此时该先代节点的父节点
			//   一定恰是栈顶节点。
			// 总之，无论是从左支还是右支回溯的，下一个一定是访问
			// 当前栈顶那个节点。
			node = stk.top();
			cout << node->value << " ";
			// 访问完毕，记得要弹出栈去，这样才能确保下次从右支回
			// 溯时栈顶节点恰是下一个要访问的节点。
			stk.pop();
			// 按照中序遍历规则，访问完一个节点之后，紧接着要遍历
			// 它的右子树了，正确设置好node后进入下一轮循环即可。
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
	// node是下一棵要遍历的子树，last_node是上一次刚遍历过的子树
	// 因为是后序遍历，所以last_node一定是刚访问过的那个节点
	BiTree node = tree, last_node = NULL;
	// 这是存放待遍历子树的栈
	stack<BiTree> stk;
	// 循环条件：待遍历子树栈不空或者下一棵要遍历的子树存在
	while (!stk.empty() || node) {
		// 进入循环，下一棵要遍历的子树有两种情况：
		// 1. node != NULL，即下一棵要遍历的子树真实存在；
		// 2. node == NULL，即下一棵要遍历的子树其实为空。
		if (node) {
			// 如果下一棵要遍历的子树真实存在，那么根据后序遍历的
			// 规则，一定是要先遍历其左子树。
			// 所以这时便出现了一棵新的子树node->left，要先于node
			// 完成遍历，因此我们把node暂时先压入栈中，进入下一轮
			// 循环去遍历子树node->left。
			// 通过这种方式，可以从一个节点开始一路向左向下直到最
			// 左下端的那个节点。这个节点一定没有左子树了。此时下
			// 一棵要遍历的子树一定是NULL。而一路左下途经的所有节
			// 点都会按照从高到低的顺序压在栈中，今后出栈的顺序就
			// 会恰好是从低到高回溯的顺序。
			stk.push(node);
			node = node->left;
		} else {
			// 出现node == NULL时，也就是从子树回溯的时候。此时先
			// 取得栈顶节点，即将要回溯到的上一个先辈节点。
			// 但是现在不能和中序遍历时一样直接访问它，因为先要弄
			// 清除是从左子树回溯的还是从右子树回溯的，按照后序遍
			// 历的规则，只有从右子树回溯的时候才能访问。
			node = stk.top();
			if (node->right && node->right != last_node) {
				// 如果将要回溯到的先辈节点存在右儿子，而且刚
				// 访问过的那个节点 node_last不是它的右儿子，
				// 那么说明是从左支回溯过去的。
				// 按照后序遍历的规则接下来要先去遍历它的右子
				// 树，因此把它的右子树设置为下一棵要遍历的子
				// 树，然后进入下一轮循环。
				node = node->right;
			} else {
				// 如果即将回溯到的先辈节点不存在右子树，那么
				// 根据后序遍历规则接下来就该访问这个先辈节点
				// 自己了。
				// 如果右子树存在而且右儿子就是刚访问过的那个
				// 节点，说明是从右子树回溯的，那么根据后序遍
				// 历规则，同样地，下一个就该访问这个先辈节点
				// 自己了。
				// 所以访问这个节点，并且将其弹栈。
				cout << node->value << " ";
				stk.pop();
				// 每次访问一个节点之后都立即将其设置为上一次
				// 刚访问过的节点last_node。
				last_node = node;
				// 按照后序遍历的规则，每次访问完一个节点，就
				// 说明以它为根的子树遍历结束了，下一步应该回
				// 溯了，所以把下一棵要遍历的子树设为空，就会
				// 在下一轮循环的时候进行回溯。
				node = NULL;
			}
		}
	}
}


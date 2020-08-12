#include <queue>
#include <iostream>

using namespace std;

struct Node {
	int value;
	Node *left;
	Node *right;

	Node() { left = NULL; right = NULL; }
};

typedef Node *BiTree;	// 将节点指针定义为一个自定义类型

BiTree create(int n);			// 按层序创建完全二叉树
void show_by_layers(BiTree root);	// 按层序输出二叉树节点数据（层序遍历，或宽度优先搜索）
void destroy(BiTree *root_p);		// 按层序销毁二叉树

int main()
{
	// 节点个数
	int n;
	cin >> n;
	// 输入n个数并创建一棵完全二叉树
	BiTree tree = create(n);
	// 按层序输出所有节点中的数据
	show_by_layers(tree);
	// 删除根节点的左子树
	destroy(&(tree->left));
	// 这一句千万不要忘记
	// tree->left = NULL;
	cout << "destroyed tree->left" << endl;
	show_by_layers(tree);
	// 删除整棵树
	destroy(&tree);
	// 这一句千万不要忘记
	// tree = NULL;
	cout << "destroyed tree" << endl;
	show_by_layers(tree);

	return 0;
}

BiTree create(int n)
{
	// 用于创建完全二叉树的队列
	queue<BiTree> q;
	// 读入第一个数并生成根节点
	BiTree root = new Node();
	cin >> root->value;
	// 根节点放入队列中
	q.push(root);
	for (int i = 1; i < n; ++i) {
		// 读入一个数并生成节点
		BiTree node = new Node();
		cin >> node->value;
		// 如果队首处节点的左子已经有了，那么就将新节点连到它的右子上
		// 并且从队列中出队；否则就将新节点连到它的左子上
		if (q.front()->left) {
			q.front()->right = node;
			q.pop();
		} else {
			q.front()->left = node;
		}
		// 新节点入队
		q.push(node);
	}
	return root;
}

void show_by_layers(BiTree root)
{
	// 用于层序访问二叉树节点的队列
	queue<BiTree> q;
	// 根节点入队
	q.push(root);
	// 访问节点直到队列为空
	while (!q.empty()) {
		// 如果队头的节点不空，就输出它的数值
		// 然后将它的左右子节点（也是左右子树根节点）入队
		// 当然也可以先左右子节点入队再输出数值
		if (q.front()) {
			cout << q.front()->value << endl;
			q.push(q.front()->left);
			q.push(q.front()->right);
		}
		// 队头的节点出队
		q.pop();
	}
}

// 注意这里的参数是指向根节点的指针的指针
// 这是为了能够在销毁之后把根节点设置为空指针
// 如果不在本函数内确保将根节点设为空，那么调用者很容易忘记这一步重要的操作
void destroy(BiTree *root_p)
{
	// 用于层序销毁节点的队列
	queue<BiTree> q;
	// 根节点入队
	q.push(*root_p);
	// 访问节点直到队列为空
	while (!q.empty()) {
		// 如果队头的节点不是空节点，则销毁它
		// 注意必须要先将左右子树的根节点入队再销毁节点
		// 否则就找不回左右子树节点的指针了
		if (q.front()) {
			q.push(q.front()->left);
			q.push(q.front()->right);
			delete q.front();
		}
		// 队头的节点出队
		q.pop();
	}
	*root_p = 0;	// 0就是空指针NULL
}


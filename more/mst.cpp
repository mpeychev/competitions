/*
 * Minimum spanning tree (Prim's algorithm with Fibonacci heap)
 * Author: Momchil Peychev
 */

#include <cstdio>
#include <cassert>

const int INF = 1 << 30;

int V;	// Number of nodes
int E;	// Number of edges

struct EdgeList {
	int from, to, weight;
	
	EdgeList* nextEdge;
	
	EdgeList(int a, int b, int c, EdgeList* currentNext) {
		from = a;
		to = b;
		weight = c;
		nextEdge = currentNext;
	}
};

struct ListData;

struct HeapNode {
	int key;
	int graphNodeIndex;	// To which node in the graph it corresponds?
	
	bool marked;		// Is the node marked? All roots should be unmarked
	int childrenCount;	// Keep the number of children
	
	HeapNode* parent;
	HeapNode* child;	// A single pointer to a HeapNode's child; the child is linked to its siblings
	HeapNode *left, *right;
	
	ListData* data;
	
	HeapNode(int _key, int _graphNodeIndex, bool _marked, int _childrenCount) {
		key = _key;
		graphNodeIndex = _graphNodeIndex;
		marked = _marked;
		childrenCount = _childrenCount;
		
		parent = NULL;
		child = NULL;
		left = right = NULL;
		data = NULL;
	}

	void setMark(bool flag) {
		marked = flag;
	}

	bool isMarked() {
		return marked;
	}
};

struct ListData {
	HeapNode *start, *end;
	
	ListData() {
		start = NULL;
		end = NULL;
	}

	ListData(HeapNode *s, HeapNode *e) {
		start = s;
		end = e;
	}
};

struct GraphNode {
	int nodeNumber;
	EdgeList* l;	// List of the neighbours
	HeapNode* p;	// Link to the HeapNode in the Fibonacci heap
	bool used;
	
	GraphNode(int number) {
		nodeNumber = number;
		l = NULL;
		used = false;
	}
};

GraphNode** G;			// An array of GraphNodes
ListData* rootList;		// Pointing to the start and the end of the Fibonacci Heap's root list
HeapNode* currentMin;	// A pointer to the minimum element in the heap; it is chained to all roots (i.e. the root list)

long long mst_cost = 0;	// Keep the total cost of the MST

void read() {
	assert(scanf("%d %d", &V, &E) == 2);
	G = new GraphNode*[V];
	
	// Init the GraphNodes
	for(int i = 0; i < V; i ++)
		G[i] = new GraphNode(i);
	
	int a, b, c;
	for(int i = 0; i < E; i ++) {
		assert(scanf("%d %d %d", &a, &b, &c) == 3);
		a --, b --;
		
		G[a] -> l = new EdgeList(a, b, c, G[a] -> l);
		G[b] -> l = new EdgeList(b, a, c, G[b] -> l);
	}
}

// Fibancci Heap Functions START
bool isEmpty(ListData* li) {
	return (li -> start == NULL && li -> end == NULL);
}

void insert(ListData* li, HeapNode* node) {
	// Inserts the node into the list

	if(isEmpty(li)) {
		li -> start = li -> end = node;
		node -> data = li;
		node -> left = node -> right = NULL;
		if(li == rootList) currentMin = node;
	}
	else {
		// Link the list end with new node (and vice verca)
		HeapNode* listEndNode = li -> end;
		
		listEndNode -> right = node;
		node -> left = listEndNode;
		node -> right = NULL;
		li -> end = node;
		node -> data = li;

		if(li == rootList && currentMin -> key > node -> key) currentMin = node;
	}
}

void updateMinimum(HeapNode* cur) {
	currentMin = cur;
	while(cur != NULL) {
		if(cur -> key < currentMin -> key) currentMin = cur;
		cur = cur -> right;
	}
}

int count(ListData* li) {
	HeapNode* cur = li -> start;
	int cnt = 0;
	while(cur != NULL) {
		cnt += 1 + cur -> childrenCount;
		cur = cur -> right;
	}
	return cnt;
}

void extractFromList(ListData* li, HeapNode* node) {
	if(li -> start == node) {
		// CurrentMin is in the beginning of the root list
		li -> start = node -> right;
		if(li -> start != NULL) li -> start -> left = NULL;
		else li -> end = NULL;
	}
	else if(li -> end == node) {
		// CurrentMin is in the end of the root list
		li -> end = node -> left;
		if(li -> end != NULL) li -> end -> right = NULL;
		else li -> start = NULL;
	}
	else {
		HeapNode* le = node -> left;
		HeapNode* ri = node -> right;

		le -> right = ri;
		ri -> left = le;
	}

	node -> data = NULL;
	node -> parent = NULL;
	node -> left = node -> right = NULL;
}

void merge(HeapNode* low, HeapNode* high) {
	// low -> key >= high -> key so low becomes a child of high
	extractFromList(rootList, low);

	high -> childrenCount ++;
	if(high -> child != NULL) insert((high -> child) -> data, low);
	else {
		high -> child = low;
		low -> data = new ListData(low, low);
	}

	low -> parent = high;
}

void extractMin() {
	extractFromList(rootList, currentMin);

	if(currentMin -> child != NULL) {
		HeapNode* firstChild = (currentMin -> child) -> data -> start;
		HeapNode* lastChild = (currentMin -> child) -> data -> end;

		if(isEmpty(rootList)) {
			rootList -> start = (currentMin -> child) -> data -> start;
			rootList -> end = (currentMin -> child) -> data -> end;

			HeapNode* iterateChild = (currentMin -> child) -> data -> start;
			delete iterateChild -> data;
			while(iterateChild != NULL) {
				iterateChild -> data = rootList;
				iterateChild = iterateChild -> right;
			}
		}
		else {
			firstChild -> left = rootList -> end;
			rootList -> end -> right = firstChild;

			rootList -> end = lastChild;

			HeapNode* iterateChild = firstChild;
			delete iterateChild -> data;
			while(iterateChild != NULL) {
				iterateChild -> data = rootList;
				iterateChild = iterateChild -> right;
			}
		}
	}

	// Rearrange the forest according to the roots degrees (if necessary)

	if(isEmpty(rootList)) currentMin = NULL;

	int arraySize = count(rootList);
	HeapNode** nodesByDegree = new HeapNode*[arraySize + 1];

	for(int i = 0; i <= arraySize; i ++)
		nodesByDegree[i] = NULL;

	HeapNode* cur = rootList -> start;

	while(cur != NULL) {
		HeapNode* A = cur;
		cur = cur -> right;

		while(nodesByDegree[A -> childrenCount] != NULL && nodesByDegree[A -> childrenCount] != A) {
			HeapNode* B = nodesByDegree[A -> childrenCount];

			nodesByDegree[A -> childrenCount] = NULL;

			if(A -> key > B -> key) {
				merge(A, B);
				A = B;
			}
			else merge(B, A);
		}

		nodesByDegree[A -> childrenCount] = A;
	}

	delete nodesByDegree;
	nodesByDegree = NULL;

	// Find new minimum

	// delete currentMin;
	currentMin = NULL;
	// find the new one
	updateMinimum(rootList -> start);
}

void cut(HeapNode *node) {
	if(node -> parent == NULL) {
		node->setMark(false);
		return;
	}

	HeapNode* par = node -> parent;
	ListData* siblings = node -> data;

	// process node
	
	extractFromList(siblings, node);
	insert(rootList, node);
	node -> parent = NULL;
	node->setMark(false);

	// process parent
	par -> childrenCount --;
	if(isEmpty(siblings)) {
		delete siblings;
		siblings = NULL;
		par -> child = NULL;
	}
	else par -> child = siblings -> start;

	if(!par->isMarked()) par->setMark(true);
	else cut(par);
}

void decreaseKey(HeapNode *node, int newKey) {
	node -> key = newKey;

	if(node -> key < currentMin -> key)
		currentMin = node;

	if(node -> parent == NULL || node -> key >= node -> parent -> key) return;

	cut(node);
}

// Fibancci Heap Functions END

// Start building the MST

void solve() {
	rootList = new ListData();

	// Assign to each GraphNode a HeapNode
	for(int i = 0; i < V; i ++) {
		G[i] -> p = new HeapNode(i == 0 ? 0 : INF, i, false, 0);
		insert(rootList, G[i] -> p);
	}

	while(!isEmpty(rootList)) {
		mst_cost += currentMin -> key;

		int v = currentMin -> graphNodeIndex;

		extractMin();

		G[v] -> used = true;
		EdgeList* neighbours = G[v] -> l;

		while(neighbours != NULL) {
			int u = neighbours -> to;
			int w = neighbours -> weight;

			if(G[u] == NULL) continue;

			if(G[u] != NULL && G[u] -> used == false && G[u] -> p != NULL && G[u] -> p -> key > w)
				decreaseKey(G[u] -> p, w);

			neighbours = neighbours -> nextEdge;
		}
	}

	printf("%lld\n", mst_cost);

	delete G;
	G = NULL;
}

int main()
{
	read();
	solve();

    return 0;
}

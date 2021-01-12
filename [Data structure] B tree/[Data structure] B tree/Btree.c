/*
 * Btree example
 *
 *
 * 20210109, youseop, jeongseo, gojae;
 *
 *
 */

 /*
 * B-Tree :
 *   1. Every node has at most 2*DEGREE children.
 *   2. Every node has at most 2*DEGREE -1 keys.
 *   2. Every node (except root) has more than DEGREE - 1 keys.
 *   3. A node with n keys contains n+1 children.
 *   5. All leaves appear in the same level.
 */

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define EMPTY 0
#define DEGREE 10 /*The degree of the tree.*/
typedef struct node
{
	int key[2 * DEGREE - 1];
	struct node* child[2 * DEGREE];
	int leaf;
	int n;
}
node;
typedef struct B_Tree
{
	node* root;
}B_Tree;
void B_Tree_Create(B_Tree* T);
void B_Tree_Insert(B_Tree* T, int k);
void B_Tree_Insert_Nonfull(node* x, int k);
int  B_Tree_Search(B_Tree* T, int k);
int  B_Tree_Search_Main(node* x, int k);
void B_Tree_Split_Child(node* x, int i);
void B_Tree_Display(B_Tree* T);
void B_Tree_Display_Main(node* x, int h);
void B_Tree_Delete(B_Tree* T, int k);
void B_Tree_Delete_main(node* x, int k);
int Find_Successor(node* x);
int Find_Predecessor(node* x);
void B_Tree_insert_items(B_Tree* T, int x, int y);
void main()
{
	B_Tree* T = malloc(sizeof(B_Tree));
	B_Tree_Create(T);
	/*node* xx = malloc(sizeof(node));
	xx->key[0] = 2;
	xx->n = 1;
	xx->leaf = 0;
	T->root = xx;
	node* yy = malloc(sizeof(node));
	node* z = malloc(sizeof(node));
	yy->key[0] = 1;
	yy->n = 1;
	yy->leaf = 1;
	z->key[0] = 3;
	z->n = 1;
	z->leaf = 1;
	xx->child[0] = yy;
	xx->child[1] = z;*/
	int command, x, y;
	printf("##########################\n\n    $ B_TREE Project $ \n\nproduced by \n\n@jeongseo \n@youseop \n@gojae\n\n##########################\n\n");
	while (1) {
		printf("\n1: insert one item\n2: insert items (x~y)\n3: delete item\n4: display\ncommad: ");
		scanf("%d", &command);
		if (command == 1) {
			printf("insert item: ");
			getchar();
			scanf("%d", &x);
			B_Tree_Insert(T, x);
			B_Tree_Display(T);
		}
		else if (command == 2) {
			printf("\ninsert x & y\n (y should be bigger than x)\nx: ");
			getchar();
			scanf("%d", &x);
			printf("y: ");
			getchar();
			scanf("%d", &y);
			B_Tree_insert_items(T, x, y);
		}
		else if (command == 3) {
			printf("\ninsert a number you wanna delete.\nk : ");
			getchar();
			scanf("%d", &x);
			B_Tree_Delete(T, x);
			B_Tree_Display(T);
		}
		else if (command == 4) {
			B_Tree_Display(T);
		}
		else if (command == 0) {
			break;
		}
		getchar();
	}
	free(T);
}
void B_Tree_insert_items(B_Tree* T, int x, int y) {
	for (int i = x; i < y + 1; i++) {
		B_Tree_Insert(T, i);
	}
	B_Tree_Display(T);
}
void B_Tree_Create(B_Tree* T)
{
	node* x = malloc(sizeof(node));
	if (x == NULL) {
		printf("memory allocation falied");
		return;
	}
	x->leaf = TRUE;
	x->n = 0;
	T->root = x;
}
void B_Tree_Insert(B_Tree* T, int k)
{
	node* r = T->root;
	if (r->n == 2 * DEGREE - 1)
	{
		node* s = malloc(sizeof(node));
		if (s == NULL) {
			printf("memory allocation falied");
			return;
		}
		T->root = s;
		s->leaf = FALSE;
		s->n = 0;
		s->child[0] = r;
		B_Tree_Split_Child(s, 0);
		B_Tree_Insert_Nonfull(s, k);
		//printf("insert %d\n", k);
	}
	else
	{
		B_Tree_Insert_Nonfull(r, k);
	}
}
void B_Tree_Insert_Nonfull(node* x, int k)
{
	int i = x->n;
	if (x->leaf)
	{
		i--;
		while (i >= 0 && k < x->key[i])
		{
			x->key[i + 1] = x->key[i];
			i--;
		}
		x->key[i + 1] = k;
		x->n = x->n + 1;
	}
	else {
		while (i >= 1 && k < x->key[i - 1])
		{
			i--;
		}
		if ((x->child[i])->n == 2 * DEGREE - 1)
		{
			B_Tree_Split_Child(x, i);
			if (k > x->key[i]) {
				i++;
			}
		}
		//printf("child#: %d k: %d\n", i, k);
		B_Tree_Insert_Nonfull(x->child[i], k);
	}
}
int B_Tree_Search(B_Tree* T, int k)
{
	node* r = T->root;
	return B_Tree_Search_Main(r, k);
}
//함수 수정 필요!
int B_Tree_Search_Main(node* x, int k)
{
	if (x->leaf)
	{
		int i = x->n - 1;
		while (i >= 0 && k < x->key[i])
		{
			i--;
		}
		if (x->key[i] == k)
		{
			printf("There is data\n");
			return TRUE;
		}
		else
		{
			printf("No data\n");
			return FALSE;
		}
	}
}
void B_Tree_Split_Child(node* x, int i)
{
	node* z = malloc(sizeof(node));
	if (z == NULL)
	{
		printf("memory allocation falied");
		return;
	}
	node* y = x->child[i]; // 0 <= i
	z->leaf = y->leaf;
	z->n = DEGREE - 1;
	for (int j = 0; j < DEGREE - 1; j++)
	{
		z->key[j] = y->key[j + DEGREE];
	}
	if (y->leaf == FALSE)
	{
		for (int j = 0; j < DEGREE; j++)
		{
			z->child[j] = y->child[j + DEGREE];
		}
	}
	y->n = DEGREE - 1;
	for (int j = x->n; j > i; j--)
	{
		x->child[j + 1] = x->child[j];
	}
	x->child[i + 1] = z;
	for (int j = x->n - 1; j > i - 1; j--)
	{
		x->key[j + 1] = x->key[j];
	}
	x->key[i] = y->key[DEGREE - 1];
	x->n = x->n + 1;
}
void B_Tree_Display(B_Tree* T)
{
	node* r = T->root;
	B_Tree_Display_Main(r, 1);
}
void B_Tree_Display_Main(node* x, int h)
{
	printf("%d : ", h);
	for (int i = 0; i < x->n; i++)
	{
		printf("%d ", x->key[i]);
	}
	printf("\n");
	if (x->leaf == 0)
	{
		for (int i = 0; i < x->n + 1; i++)
		{
			B_Tree_Display_Main(x->child[i], h + 1);
		}
	}
}
void B_Tree_Delete(B_Tree* T, int k)
{
	node* r = T->root;
	int i = r->n - 1;
	if (r->leaf == 1)
	{
		while (i >= 0 && r->key[i] > k)
		{
			i--;
		}
		if (i >= 0 && r->key[i] == k) {
			for (int j = i + 1; j < r->n; j++)
			{
				r->key[j - 1] = r->key[j];
			}
			r->n--;
			printf("delete success\n");
		}
		else {
			printf("no data");
		}
		return;
	}
	else {
		if (r->n > 1) {
			B_Tree_Delete_main(r, k);
		}
		else {
			node* left_c = r->child[0];
			node* right_c = r->child[1];
			if (left_c->n == DEGREE - 1 && right_c->n == DEGREE - 1) {
				left_c->key[DEGREE - 1] = r->key[0];
				for (int j = 0; j < DEGREE - 1; j++) {
					left_c->key[DEGREE + j] = right_c->key[j];
				}
				if (left_c->leaf == FALSE) {
					for (int j = 0; j < DEGREE; j++) {
						left_c->child[DEGREE + j] = right_c->child[j];
					}
				}
				left_c->n = DEGREE * 2 - 1;
				free(right_c);
				T->root = left_c;
				free(r);
				B_Tree_Delete_main(left_c, k);
			}
			else {
				B_Tree_Delete_main(r, k);
			}
		}
	}
}
void B_Tree_Delete_main(node* x, int k) {
	int i = x->n;
	while (i > 0 && x->key[i - 1] >= k) {
		i--;
	}
	if (i < x->n && x->key[i] == k) {
		if (x->leaf == 1) {
			for (int j = i; j < x->n - 1; j++) {
				x->key[j] = x->key[j + 1];
			}
			x->n--;
			return;
		}
		else {
			node* left_c = x->child[i];
			node* right_c = x->child[i + 1];
			if (left_c->n > DEGREE - 1) {
				int pre_k = Find_Predecessor(left_c);
				x->key[i] = pre_k;
				B_Tree_Delete_main(left_c, pre_k);
			}
			else if (right_c->n > DEGREE - 1) {
				int su_k = Find_Successor(right_c);
				x->key[i] = su_k;
				B_Tree_Delete_main(right_c, su_k);
			}
			else {
				left_c->key[DEGREE - 1] = k;
				for (int j = 0; j < DEGREE - 1; j++)
				{
					left_c->key[DEGREE + j] = right_c->key[j];
				}
				for (int j = 0; j < DEGREE; j++) {
					left_c->child[DEGREE + j] = right_c->child[j];
				}
				left_c->n = 2 * DEGREE - 1;
				for (int j = i; j < x->n - 1; j++) {
					x->key[j] = x->key[j + 1];
				}
				for (int j = i + 1; j < x->n; j++) {
					x->child[j] = x->child[j + 1];
				}
				x->n--;
				free(right_c);
				B_Tree_Delete_main(left_c, k);
			}
		}
	}
	else
	{
		printf("\n\n\n\n HERE \n\n%d\n\n", i);
		node* my_way_c = x->child[i];
		if (my_way_c->n > DEGREE - 1)
		{
			B_Tree_Delete_main(my_way_c, k);
		}
		else
		{
			if (i != 0 && (x->child[i - 1])->n > DEGREE - 1)
			{
				node* left_c = x->child[i - 1];
				for (int j = DEGREE - 2; j >= 0; j--) {
					my_way_c->key[j + 1] = my_way_c->key[j];
				}
				if (my_way_c->leaf == FALSE)
				{
					for (int j = DEGREE - 1; j >= 0; j--) {
						my_way_c->child[j + 1] = my_way_c->child[j];
					}
				}
				my_way_c->key[0] = x->key[i - 1];
				my_way_c->child[0] = left_c->child[left_c->n];
				my_way_c->n++;
				x->key[i - 1] = left_c->key[left_c->n - 1];
				left_c->n--;
			}
			else if (i != x->n && (x->child[i + 1])->n > DEGREE - 1)
			{
				node* right_c = x->child[i + 1];
				my_way_c->key[DEGREE - 1] = x->key[i];
				my_way_c->child[DEGREE] = right_c->child[0];
				my_way_c->n++;
				x->key[i] = right_c->key[0];
				for (int j = 0; j < right_c->n - 1; j++)
				{
					right_c->key[j] = right_c->key[j + 1];
				}
				for (int j = 0; j < right_c->n; j++) {
					right_c->child[j] = right_c->child[j + 1];
				}
				right_c->n--;
			}
			else {//x에 k가 없고, 풍족한 형제가 없을때!!!
				if (i == 0) {
					node* right_c = x->child[i + 1];
					for (int j = 0; j < DEGREE - 1; j++) {
						right_c->key[j + DEGREE] = right_c->key[j];
						right_c->key[j] = my_way_c->key[j];
					}
					if (right_c->leaf == 0) {
						for (int j = 0; j < DEGREE; j++) {
							right_c->child[j + DEGREE] = right_c->child[j];
							right_c->child[j] = my_way_c->child[j];
						}
					}
					right_c->key[DEGREE - 1] = x->key[i];
					right_c->n = DEGREE * 2 - 1;
					for (int j = 0; j < x->n - 1; j++) {
						x->key[j] = x->key[j + 1];
					}
					for (int j = 0; j < x->n; j++)
					{
						x->child[j] = x->child[j + 1];
					}
					free(my_way_c);
					my_way_c = right_c;
					x->n--;
				}
				else {
					node* left_c = x->child[i - 1];
					left_c->key[DEGREE - 1] = x->key[i - 1];
					for (int j = 0; j < DEGREE - 1; j++) {
						left_c->key[j + DEGREE] = my_way_c->key[j];
					}
					if (left_c->leaf == 0) {
						for (int j = 0; j < DEGREE; j++) {
							left_c->child[j + DEGREE] = my_way_c->child[j];
						}
					}
					left_c->n = 2 * DEGREE - 1;
					for (int j = i - 1; j < x->n - 1; j++) {
						x->key[j] = x->key[j + 1];
					}
					for (int j = i; j < x->n; j++) {
						x->child[j] = x->child[j + 1];
					}
					free(my_way_c);
					my_way_c = left_c;
					x->n--;
				}
			}
			B_Tree_Delete_main(my_way_c, k);
		}
	}
	return;
}
int Find_Predecessor(node* x) {
	while (x->leaf == 0) {
		x = x->child[x->n];
	}
	return x->key[x->n - 1];
}
int Find_Successor(node* x) {
	while (x->leaf == 0) {
		x = x->child[0];
	}
	return x->key[0];
}
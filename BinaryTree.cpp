// Treeee.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Tree {
	int info;
	Tree *left, *right;
};

Tree* List(int i) {
	Tree *t = new Tree;	// ������ ������
	t->info = i;		// ������������ �������������� �����						
	t->left = t->right = NULL;	// ������������ �������� �����
	return t;
}

int Create(Tree *&root, int a[]) {
	Tree *Prev = NULL, *t;
	// Prev � �������� �������� ��������
	int b, find, size = 0;
	if (!root) {   	       // ���� ������ �� �������
		cout << " Input Root :  ";
		cin >> b;
		root = List(b);   /* ������� ����� ����� root, ������� ������������� � ����*/
		a[size++] = b;
	}
	//---------- ���������� ��������� -----------
	while (1) {				//  while (true)
		cout << "Input Info :  ";
		cin >> b;
		if (b < 0) {
			break;
		}// ������� ������ � ������������� �����
		t = root;
		// ������� ��������� ���������� �� ������
		find = 0;
		// ������� ������
		while (t && !find) {
			Prev = t;
			if (b == t->info)
				find = 1;
			// ����� ������ ���� ���������
			else
				if (b < t->info) t = t->left;
				else   t = t->right;
		}
		// ���� ����� ����� � ������� Prev
		if (!find) {			//  if (find == 0)	
								// ������� ����� ����, ���������� ������
			t = List(b);
			a[size++] = b;
			// � ������������ ���, ����
			if (b < Prev->info)
				// �� ����� �����,
				Prev->left = t;
			// ���� �� ������ �����
			else    Prev->right = t;
		}
	}	 		// ����� ����� while ( 1 )
	return size;
}

void Add_List(Tree *root, int key) {
	Tree *prev = NULL, *t;
	bool find = true;			// int find = 1;
	t = root;
	while (t && find) {
		prev = t;
		if (key == t->info) {
			find = false;	 	// find = 0;	                                		
			cout << "Already exists." << endl;
		}
		else
			if (key < t->info) t = t->left;
			else
				t = t->right;
	}
	if (find) {
		t = List(key);
		if (key < prev->info)
			prev->left = t;
		else
			prev->right = t;
	}
}


Tree* Del(Tree *Root, int key) {
	Tree *Del, *Prev_Del, *R, *Prev_R;
	// Del, Prev_Del � ��������� ������� � ��� ���������� (��������); 
	// R, Prev_R � �������, �� ������� ���������� ���������, � ��� ��������;
	Del = Root;
	Prev_Del = NULL;
	// ===== ����� ���������� �������� � ��� �������� �� ����� key =====
	while (Del != NULL && Del->info != key) {
		Prev_Del = Del;
		if (Del->info > key)  Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) {		// ������� �� ������
		puts("\n NO Key!");
		return Root;
	}
	// ============ ����� �������� R ��� ������ =================
	if (Del->right == NULL) R = Del->left;
	else
		if (Del->left == NULL) R = Del->right;
		else {
			// ���� ����� ������ ���� � ����� ���������
			Prev_R = Del;
			R = Del->left;
			while (R->right != NULL) {
				Prev_R = R;
				R = R->right;
			}
			// ����� ������� ��� ������ R � ��� �������� Prev_R
			if (Prev_R == Del)
				R->right = Del->right;
			else {
				R->right = Del->right;
				Prev_R->right = R->left;
				R->left = Prev_R;
			}
		}
		if (Del == Root) { 
			Root = R;	
			return Root; 
		}// ������ ������, �������� ��� �� R
		else
			// ��������� R ������������ � �������� ���������� ����
			if (Del->info < Prev_Del->info)  Prev_Del->left = R;	// �� ����� �����
			else	Prev_Del->right = R;				// �� ������ �����
			cout << "\n Delete element " << Del->info << endl;
			delete Del;
			return Root;
}


void View(Tree *t, int level) {
	if (t) {
		if (t->left)
			View(t->left, level + 1); 		// ����� ������ ���������
		for (int i = 0; i<level; i++)  cout << "    ";
		cout << t->info << endl;
		if (t->right)
			View(t->right, level + 1);		// ����� ������� ���������
	}
}

Tree* Min_Key(Tree *p) {
	while (p->left != NULL) p = p->left;
	return p;
}

Tree* Max_Key(Tree *p) {
	while (p->right != NULL) p = p->right;;
	return p;
}

void Make_Blns(Tree **p, int n, int k, int *a) {
	if (n == k) {
		*p = NULL;
		return;
	}
	else {
		int m = (n + k) / 2;
		*p = new Tree;
		(*p)->info = a[m];
		Make_Blns(&(*p)->left, n, m, a);
		Make_Blns(&(*p)->right, m + 1, k, a);
	}
}

void Del_All(Tree *t) {
	if (t != NULL) {
		Del_All(t->left);
		Del_All(t->right);
		free(t);
	}
}

Tree* DelSmth(Tree *root, int inf) {
	Tree* ps = root, *pr = root, *w, *v = NULL;
	while ((ps != NULL) && (ps->info != inf)) {
		pr = ps;
		if (inf < ps->info) ps = ps->left;
		else ps = ps->right;
	}

	if (ps == NULL) return root;

	if ((ps->left == NULL) && (ps->right == NULL)) {
		if (ps == pr) {
			delete(ps);
			return NULL;
		}
		if (pr->left == ps)
			pr->left = NULL;
		else
			pr->right = NULL;
		delete (ps);
		return root;
	}

	if (ps->left == NULL) {
		if (ps == pr) {
			ps = ps->right;
			delete(pr);
			return ps;
		}
		if (pr->left == ps)
			pr->left = ps->right;
		else
			pr->right = ps->right;
		delete(ps);
		return root;
	}

	if (ps->right == NULL) {
		if (ps == pr) {
			ps = ps->left;
			delete(pr);
			return ps;
		}
		if (pr->left == ps)
			pr->left = ps->left;
		else
			pr->right = ps->left;
		delete(ps);
		return root;
	}

	w = ps->left;
	if (w->right == NULL)
		w->right = ps->right;
	else {
		while (w->right != NULL)
		{
			v = w;
			w = w->right;
		}
		v->right = w->left;
		w->left = ps->left;
		w->right = ps->right;
	}

	if (ps == pr) {
		delete(ps);
		return w;
	}
	if (pr->left == ps)
		pr->left = w;
	else
		pr->right = w;
	delete (ps);
	return root;
}

void qSort(int l, int r, int* a)
{
	if (l >= r) {
		return;
	}
	int i, j;
	int temp, x;
	i = l;
	j = r;
	x = a[(l + r) / 2];
	do
	{
		while (a[i] < x) i++;
		while (x < a[j]) j--;
		if (i <= j)
		{
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++; j--;
		}
	} while (i <= j);
	if (l<j) qSort(l, j, a);
	if (i<r) qSort(i, r, a);
}

void main() {
	Tree* root = NULL;
	int kod, end = 0, size = 0;
	int a[50];
	cout << "Let's start!";
	while (!end) {
		cout << "\n\tCreate - 1\n\tAdd List - 2\n\tView - 3\n\tMake Balance - 4\n\tFind Min - 5\n\tFind Max - 6\n\tDelete something - 7\n\tDelete All - 8\n\tEXIT - 0\t\t";
		cin >> kod;
		switch (kod)
		{
		case 1:
			size = Create(root, a);
			break;
		case 2:
			if (root) {
				int info;
				cout << "Info: ";
				cin >> info;
				Add_List(root, info);
			}
			else cout << "Create Tree first!" << endl;
			break;
		case 3:
			if (root) {
				View(root, 0);
			}
			else cout << "Create Tree first!" << endl;
			break;
		case 4:
			if (root) {
				qSort(0, size - 1, a);
				Make_Blns(&root, 0, size, a);
				View(root, 0);
			}
			else cout << "Create Tree first!" << endl;
			break;
		case 5: case 6:
			if (root) {
				Tree* extra = (kod == 5 ? Min_Key(root) : Max_Key(root));
				cout << extra->info << endl;
			}
			else cout << "Create Tree first!" << endl;
			break;
		case 7:
			if (root) {
				int key;
				cout << "Enter value: ";
				cin >> key;
				root = Del(root, key);				
			}
			else cout << "Nothing to delete!" << endl;
			break;
		case 8:
			if (root) {
				Del_All(root);
				cout << "Deleted" << endl;
			}
			else cout << "Tree is already empty." << endl;
			break;
		case 0:
			if (root) Del_All(root);
			end++;
		}
	}
	return;//system("pause");
}
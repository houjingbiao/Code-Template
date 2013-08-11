//problem 1: Given a time, calculate the angle between the hour and minute hands
int getAngle(int h, int m){
	return int((30*h - 5.5*m))%360;
}

/*problem 2: A sorted array has been rotated so that the elements might appear in the order 3
 456712. How would you find the minimum element? You may assume that the array has
 all unique elements */
 
/*problem 3: Example: A ransom note can be formed by cutting words out of a magazine to form a new
sentence. How would you figure out if a ransom note (represented as a string) can be formed
from a given magazine (string)?*/

/*problem 4: Example: Design an algorithm to print all permutations of a string. For simplicity, assume all characters are unique */

/*problem 5: Numbers are randomly generated and stored into an (expanding) array. How
wouldyoukeep track of the median?*/

/*the nearest common anscent
*/
void _findOneNodes(TreeNode* root, TreeNode* node1, TreeNode* node2, int& count, TreeNode** pParent){
	if(root == NULL) return;
	if(root == node1 || root == node2){
		count++;
		return;
	}
	_findOneNodes(root->left, node1, node2, count, pParent);
	if(count == 2) return;
	_findOneNodes(root->right, node1, node2, count, pParent);
	if(count == 2) return;
}
void findTwoNodes(TreeNode* root, TreeNode* node1, TreeNode* node2, int& count, TreeNode** pParent){
	if(root == NULL) return;
	if(count == 0){
		if(root == node1 || root == node2)
			count++;
		if(count == 1){
			_findOneNodes(root->left, node1, node2, count, pParent);
			if(count == 2){
				*pParent = node1;
				return;
			}
			_findOneNodes(root->right, node1, node2, count, pParent);
			if(count == 2){
				*pParent = node1;
				return;
			}
		}
		else if(count == 0){
			findTwoNodes(root->left, node1, node2, count, pParent);
			if(count == 2) return;
			else if(count == 1){
				_findOneNodes(root->right, node1, node2, count, pParent);
				if(count == 2){
					*pParent = root;
					return;
				}
			}
			_findOneNodes(root->right, node1, node2, count, pParent);
			if(count == 2) return;
			else if(count == 1) return;
		}
	}
	else if(count == 1){
		_findOneNodes(root, node1, node2, count, pParent);
		if(count == 2) return;
	}
}

TreeNode* getNearestCommonParent(TreeNode* root, TreeNode* node1, TreeNode* node2){
	if(root == node1 || root == node2)  return root;
	if(root == NULL) return NULL;
	if(node1 == NULL) return node2;
	if(node2 == NULL) return node1;
	if(node1 == node2) return node1;
	TreeNode* pParent = NULL;
	int count = 0;
	findTwoNodes(root->left, node1, node2, count, &pParent);
	if(count == 2) return pParent;
	else if(count == 1)
		return root;
	else{
		findTwoNodes(root->right, node1, node2, count, &pParent);	
		if(count == 2)
			return pParent;
		else return NULL;
	}
}

//version 1:from shunda.wang, it is very easy and readable, for it derive from the recursive travese of binary tree
int _find(node* root, int a, int b, int n, node*& res)
{
    int find = 0;
    if(root == NULL) return 0;
    if(root->val == a || root->val == b) ++find;
    if(n == find){
        return find;
    }
    find += _find(root->left, a, b, n-find, res);
    if(find == 2){
        res = res?res:root;
        return 2;
    }
    find += _find(root->right, a, b, n-find, res);
    if(find == 2){
        res = res?res:root;
        return 2;
    }
    return find;
}

node* find(node* root, int a, int b)
{
    node* res = NULL;
    _find(root, a, b, 2, res);
    return res;
}
 

//find the shortest substring which contains exactly three kinds of characters.
typedef struct statistics{
	char ch;
	int count;
} STAT;

bool add(STAT stats[], int n, char ch){
	if(stats[0].ch == ch){
		stats[0].count++;
	}
	else if(stats[1].ch == ch){
		stats[1].count++;
	}
	else if(stats[2].ch == ch){
		stats[2].count++;
	}
	else if(stats[0].ch == -1){
		stats[0].ch = ch;
		stats[0].count = 1;
	}
	else if(stats[1].ch == -1){
		stats[1].ch = ch;
		stats[1].count = 1;
	}
	else if(stats[2].ch == -1){
		stats[2].ch = ch;
		stats[2].count = 1;
	}
	else return false;
	
	return true;
}
void del(STAT stats[], int n, char ch){
	if(stats[0].ch == ch){
		stats[0].count--;
		if(stats[0].count == 0)
			stats[0].ch == -1;
	}
	else if(stats[1].ch == ch){
		stats[1].count--;
		if(stats[1].count == 0)
			stats[01].ch == -1;
	}
	else if(stats[2].ch == ch){
		stats[2].count--;
		if(stats[2].count == 0)
			stats[2].ch == -1;
	}
}
string subStrWith3Ch(string s){
	if(s.length() == 0) return "";
	int maxPos = -1, maxLen = 0;
	int i1 = 0, i2 = 0;
	STAT stats[3];
	
	while(i1 < s.length() && i2 < s.length()){
		if(add(stat, 3, s[i1])){
			i1++;
		}
		else{
			if(maxLen < i1 - i2 + 1){
				maxLen = i1 - i2 + 1;
				maxPos = i2;
			}
			del(stat, 3, s[i2]);
			i2++;
		}
	}
	if(maxLen < i1 - i2 + 1){
		maxLen = i1 - i2 + 1;
		maxPos = i2;
	}
	s.substr(maxPos, maxLen);
}

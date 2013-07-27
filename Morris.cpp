//算法伪代码：
MorrisInOrder():
	while 没有结束
		如果当前节点没有左后代
			访问该节点
			转向右节点
		否则
			找到左后代的最右节点，且使最右节点的右指针指向当前节点
			转向左后代节点


//version 1: cpp
void bst_morris_inorder(struct bst_node *root){
	struct bst_node *p = root, *tmp;
	while(p){
		if(p->left == NULL){
			printf("%d", p->key);
			p = p->right;
		}
		else{
			tmp = p->left;
			while(tmp->right != NULL && tmp->right != p)
				tmp = tmp->right;
			if(tmp->right == NULL){
				tmp->right = p;
				p = p->left;
			}
			else{ //tmp->right == p
				printf("%d", p->key);
				tmp->right = NULL;
				p = p->right;
			}
		}
	}
}

//version 2: template
template<class T>
void BST<T>::MorrisInorder() {
	BSTNode<T> *p = root, *tmp;
	while(p != 0)
		if(p->left == 0){
			visit(p);
			p = p->right;
		}
		else{
			tmp = p->left;
			while(tmp->right != 0 && tmp->right != p)
				tmp = tmpp->right;
			if(tmp->right == 0){
				tmp->right = p;
				p = p->left;
			}
			else{
				visit(p);
				tmp->right = 0;
				p = p->right;
			}
		}
}
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int value;
    struct node *left, *right;
    int ht;
} node;

// Choice function
node *insert_data(node *, int);
node *delete_data(node *, int);
void search_data(node *, int);
void show_data(node *);
void preorder(node *);

// support function
int BF(node *);
int height(node *);
int searchMin(node *);

// rotation operation function
node *R(node *);
node *L(node *);
node *RL(node *);
node *LR(node *);

// main function
int main(void){
    node *root = NULL; // data structure
    char inputSym;
    int inputNum;

    printf("Program starts with zero data inside.\n");
    do {
        printf("i : input new data\n");
        printf("d : delete existing data\n");
        printf("s : search for data\n");
        printf("p : print all existing data\n");
        printf(". : end program\n");
        printf("input : ");
        scanf(" %c", &inputSym);
        if(inputSym == 'i'){
            printf("Please input the new data : ");
            scanf("%d", &inputNum);
            root = insert_data(root,inputNum);
            printf("The number has been added\n");
        }
        else if(inputSym == 'd'){
            printf("Please input the data : ");
            scanf("%d", &inputNum);
            root = delete_data(root, inputNum);
            printf("Data has been deleted\n");
        }
        else if (inputSym == 's'){
            printf("Please input the data : ");
            scanf("%d", &inputNum);
            search_data(root, inputNum);
        }
        else if (inputSym == 'p'){
            printf("existing data : \n");
            show_data(root);
            puts("");
        }
        else if(inputSym == 'x'){
            preorder(root);
            puts("");
        }
        else if (inputSym != '.'){
            printf("Wrong input!\n");
        }
    }while(inputSym != '.');
    printf("Program ended");
    return 0;
}

// insert data function
node *insert_data(node *tree, int x){
    if (tree ==NULL){
        tree = (node *)malloc(sizeof(node));
        tree->value = x;
        tree->left = tree->right = NULL;
    }
    else {
        if (x>tree->value){
            tree->right = insert_data(tree->right,x);
            if(BF(tree) == -2){
                if(BF(tree->left)<=0){
                    tree=L(tree);
                }
                else {
                    tree=RL(tree);
                }
            }
        }
        else if(x<tree->value){
            tree->left = insert_data(tree->left,x);
            if(BF(tree) == 2){
                if (BF(tree->left)>=0){
                    tree = R(tree);
                }
                else{
                    tree= LR(tree);
                }
            }
        }
    }
    tree->ht = height(tree);
    return (tree);
}

// delete data function
node *delete_data(node *tree, int x){
    if(tree==NULL){
        return tree;
    }
    else if (tree->value > x){
        tree->left = delete_data(tree->left,x);
        if(BF(tree)==-2){
            if (BF(tree->right)<=0){
                tree = L(tree);
            }
            else{
                tree= RL(tree);
            }
        }
    }
    else if (tree->value < x){
        tree->right = delete_data(tree->right,x);
        if(BF(tree) == 2){
            if(BF(tree->left)>=0){
                tree=R(tree);
            }
            else {
                tree=LR(tree);
            }
        }
    }
    else{
        if (tree->left == NULL && tree->right == NULL){
            return NULL;
        }
        else if (tree->left == NULL){
            tree=tree->right;
        }
        else if (tree->right == NULL){
            tree=tree->left;
        }
        else{
            int min;
            min = searchMin(tree->right);
            tree->value = min;
            tree->right = delete_data(tree->right,min);
            if(BF(tree)==2){
                if (BF(tree->left)>=0){
                    tree = R(tree);
                }
                else{
                    tree= LR(tree);
                }
            }
        }
    }
    tree->ht = height(tree);
    return tree;
};

// search data function
void search_data(node *tree, int x){
    if (tree==NULL){
        printf("No data found!\n");
    }
    else if (tree->value == x){
        printf("data has been found!\n");
    }
    else if (tree->value > x){
        search_data(tree->left, x);
    }
    else {
        search_data(tree->right, x);
    }
}

// show sorted data function
void show_data(node *tree){
    if (tree!=NULL){
        show_data(tree->left);
        printf("%d ", tree->value);
        show_data(tree->right);
    }
}

// show unsorted data function
void preorder(node *T){
    if(T!=NULL){
        printf("%d(Bf=%d)",T->value,BF(T));
        preorder(T->left);
        preorder(T->right);
    }
}

// Searching minimum value in a data structure function
int searchMin(node *tree){
    if (tree->left == NULL){
        return tree->value;
    }
    return searchMin(tree->left);
};

// determining the height of one node function
int height(node *tree){
    int lh, rh;
    if(tree == NULL){
        return 0;
    }
    if(tree->left == NULL){
        lh=0;
    }
    else{
        lh = 1+tree->left->ht;
    }
    if (tree->right ==NULL){
        rh = 0;
    }
    else{
        rh = 1+tree->right->ht;
    }
    return lh>rh?lh:rh;
}

// determining the Balance Factor of a node function
int BF(node *tree){
    int lh, rh;
    if(tree == NULL){
        return 0;
    }
    if(tree->left == NULL){
        lh=0;
    }
    else{
        lh = 1 + tree->left->ht;
    }
    if (tree->right ==NULL){
        rh = 0;
    }
    else{
        rh = 1 + tree->right->ht;
    }
    return (lh-rh);
}

// right rotation function
node * R(node * tree){
    node *tree_2;
    tree_2 = tree->left;
    tree->left = tree_2->right;
    tree_2->right = tree;
    tree->ht = height(tree);
    tree_2->ht = height(tree_2);
    return (tree_2);
}

// left rotation function
node * L(node *tree){
    node *tree_2;
    tree_2 = tree->right;
    tree->right = tree_2->left;
    tree_2->left = tree;
    tree->ht = height(tree);
    tree_2->ht = height(tree_2);
    return (tree_2);
}

// right-left rotation function
node *RL(node *tree){
    tree->right = R(tree->right);
    tree = L(tree);
    return tree;
}

// left-right rotation function
node *LR(node *tree){
    tree->left = L(tree->left);
    tree = R(tree);
    return tree;
}

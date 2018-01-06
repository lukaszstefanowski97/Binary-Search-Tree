//SDIZO I1 223A LAB03
//Łukasz Stefanowski
//sl39439@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct A {
    int key;
    struct A *left;
    struct A *right;
    char c[10];
} A;


//1
A *initiate() {

    A *root = NULL;
    return root;

}



//2
int insert(A **root, int key) {

    A *newNode = (A *) malloc(sizeof(A));

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->key = key;
    sprintf(newNode->c, "%d", key);

    if (*root == NULL) {
        *root = newNode;
        return 0;
    }

    A *temp = *root;
    A *parent = *root;

    while (temp != NULL) {
        if (temp->key == key) {
            free(temp);
            return -1;
        } else if (key > temp->key) {
            parent = temp;
            temp = temp->right;
        } else {
            parent = temp;
            temp = temp->left;
        }
    }
        if (key > parent->key)
            parent->right = newNode;
        else
            parent->left = newNode;

        return 0;

}

//3


void insertXelements(int X, A** korzen) {

    for (int i = 0; i < X; i++) {
        int key = (rand() % 20000) - 10000;
//        printf("Wylosowano %d\n", klucz)
//          jeżeli się powtórzył (funkcja wstawiania
//          zwróciła 1) cofa iterację
        if (insert(korzen, key) == -1) {
//            printf("Nieprawidlowy klucz\n");
            i--;
        }

    }
}

//4
A *search(A *root, int x) {

    A *temp = root;
    while (temp != NULL) {
        if (temp->key == x) {

            printf("Znaleziono element o wartości klucza ");
            printf("%d", temp->key);
            printf(".\n");
            return temp;
        }
        if (temp->key < x)
            temp = temp->right;
        else
            temp = temp->left;
    }

    return NULL;
}

//5
int delete(A **root, int x) {
    A *parent = *root;
    A *preparent = NULL;
    A *temp = *root;
    A *child = NULL;

    if (temp == NULL) {
        printf("Drzewo jest puste\n");
        return -1;
    } else {
        //przechodzenie przez drzewo
        while (temp) {

            if (x < temp->key) {
                parent = temp;
                temp = temp->left;
            } else if (x > temp->key) {
                parent = temp;
                temp = temp->right;
            } else {

                if (temp->right && temp->left) {

                    preparent = temp;
                    child = temp->left;

                    while (child->right != NULL) {
                        preparent = child;
                        child = child->right;
                    }

                    if (child == temp->left) {
                        preparent->right = NULL;
                        child->left = temp->left;
                        child->right = temp->right;
                        if (temp == *root) {

                            *root = child;
                        } else if (parent->right == temp) {
                            parent->right = child;

                        } else {
                            parent->left = child;

                        }
                        free(temp);
                        return 0;
                    }

                    preparent->right = child->left;
                    child->left = temp->left;
                    child->right = temp->right;



                    if (temp == *root) {
                        *root = child;
                    } else if (parent->right == temp) {
                        parent->right = child;
                    } else {
                        parent->left = child;
                    }
                    free(temp);
                    return 0;
                } else if ((temp->right == NULL) && (temp->left == NULL)) {
                    if (temp == *root) {
                        *root = NULL;
                        free(temp);
                        return 0;
                    }

                    if (parent->right == temp) {
                        parent->right = NULL;
                    } else {
                        parent->left = NULL;
                    }
                    free(temp);

                    return 0;
                }

                if (temp->right != NULL) {
                    if (temp == *root)
                        *root = temp->left;

                    else if (parent->right == temp) {
                        parent->right = temp->right;
                        temp->right = NULL;
                        free(temp);
                    } else {
                        parent->left = temp->left;
                        temp->left = NULL;
                        free(temp);
                    }
                    return 0;
                }

                if (temp->left != NULL) {
                    if (temp == *root)
                        *root = temp->right;

                    else if (parent->right == temp) {
                        parent->right = temp->right;
                        temp->right = NULL;
                        free(temp);
                    } else
                        parent->left = temp->right;
                    free(temp);
                    return 0;
                }
            }
        }
    }
    return 0;
}

//6.1
double preorder(A *node) {
    A *temp = node;
    double licznik = 1.;
    double out;

    if (node == NULL) printf("Brak elementow\n");

    if (node != NULL) {

        printf("%d\n", node->key);
        if (temp->left) {
            out = preorder(temp->left);
            licznik += out;
        }
        if (temp->right) {
            out = preorder(temp->right);
            licznik += out;
        }

    }
    return licznik;
}

//6.2
double inorder(A *node) {
    A *temp = node;
    double licznik = 1.;
    double out;

    if (node == NULL) printf("Brak elementow\n");

    if (node != NULL) {
        if (temp->left) {
            out = inorder(temp->left);
            licznik += out;
        }

        printf("%d\n", node->key);

        if (temp->right) {
            out = inorder(temp->right);
            licznik += out;
        }

    }
    return licznik;
}

//6.3
double postorder(A *node) {
    A *temp = node;
    double licznik = 1.;
    double out;

    if (node == NULL) printf("Brak elementow\n");

    if (node != NULL) {
        if (temp->left) {
            out = postorder(temp->left);
            licznik += out;
        }

        if (temp->right) {
            out = postorder(temp->right);
            licznik += out;
        }

        printf("%d\n\n", node->key);

    }
    return licznik;
}


int main() {

    int X, k1, k2, k3, k4;
    FILE *fp = fopen("inlab03.txt", "r");
    if (fp == NULL)
        return -1;
    fscanf(fp, "%d %d %d %d %d", &X, &k1, &k2, &k3, &k4);
    fclose(fp);
    srand((unsigned int) time(NULL));
    clock_t begin, end;
    double time_spent;
    begin = clock();

    A *root = initiate();
//    delete(&root, k1);
    insert(&root, k1);
    insert(&root, 14);
    insert(&root, 45);
//    insert(&root, 764);
//    insert(&root, 46);
//    insert(&root, 99);
//    insertXelements(X, &root);
//    inorder(root);
    preorder(root);
//    insert(&root, k2);
//    inorder(root);
//    insert(&root, k3);
//    insert(&root, k4);
//    delete(&root, k1);
//    preorder(root);
//    search(root, k1);
//    delete(&root, k2);
//    inorder(root);
//    delete(&root, k3);
//    delete(&root, k4);

//    insert(&root, 15);
//    insert(&root, 10);
//    insert(&root, 20);
//    insert(&root, 9);
//    insert(&root, 12);
//    insert(&root, 19);
//    insert(&root, 26);
//
//    double out, out1, out2;
//    out = inorder(root);
//    printf("odwiedzono %.f wezlow\n\n", out);
//    delete(&root, 20);
//    inorder(root);

//    printf("odwiedzono %.f wezlow\n\n", out1);
//    out2 = preorder
//    inorder(root);(root);
//    printf("odwiedzono %.f wezlow\n\n", out2);
//    //usuniecie_elementu(&korzen,26);
//    //inorder(korzen);
//    search(root, 12);
//    search(root, 120);


    end = clock();
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("%lf", time_spent);

    return 0;
}
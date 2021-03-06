#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*Function that adds nodes into title tree*/
void add_node_title( struct tree_struct **root, char *title, struct title_basics *givenStruct) {
    if (*root) {
        if (strcmp(title, (*root)->key) < 0) {
            add_node_title( &((*root)->children[0]), title, givenStruct);
            /*printf ("node added to left\n");*/
        }
        else {
            add_node_title( &((*root)->children[1]), title, givenStruct);
            /*printf ("node added to right\n");*/
        }
    }
    else {
        (*root) = malloc( sizeof( struct tree_struct ));
        (*root)->key = title;
        (*root)->data = givenStruct;
        (*root)->children[0]=NULL;
        (*root)->children[1]=NULL;
    }
}

/*Function that adds nodes into name tree*/
void add_node_name( struct tree_struct **root, char *name, struct name_basics *givenStruct) {
    if (*root) {
        if (strcmp(name, (*root)->key) < 0) {
            add_node_name( &((*root)->children[0]), name, givenStruct);
            /*printf ("node added to left\n");*/
        }
        else {
            add_node_name( &((*root)->children[1]), name, givenStruct);
            /*printf ("node added to right\n");*/
        }
    }
    else {
        (*root) = malloc( sizeof( struct tree_struct ));
        (*root)->key = name;
        (*root)->data = givenStruct;
        (*root)->children[0]=NULL;
        (*root)->children[1]=NULL;
    }
}

/*Function that adds nodes into principals tree*/
void add_node_principals( struct tree_struct **root, char *principals, struct title_principals *givenStruct) {
    if (*root) {
        if (strcmp(principals, (*root)->key) < 0) {
            add_node_principals( &((*root)->children[0]), principals, givenStruct);
            /*printf ("node added to left\n");*/
        }
        else {
            add_node_principals( &((*root)->children[1]), principals, givenStruct);
            /*printf ("node added to right\n");*/
        }
    }
    else {
        (*root) = malloc( sizeof( struct tree_struct ));
        (*root)->key = principals;
        (*root)->data = givenStruct;
        (*root)->children[0]=NULL;
        (*root)->children[1]=NULL;
    }
}

/*Function that searches through entire trees*/
struct tree_struct *find( struct tree_struct *root, char *target )
{
    if (root)
    {
        if (strcmp(root->key, target) == 0)
        {
            return root;
        }
        else
        {
            if (strcmp(target, root->key) < 0 )
            {
                return find(root->children[0], target);
            }
            else /* value>=(root)->number */
            {
                return find(root->children[1], target);
            }
        }

    }
    else
    {
        return NULL;
    }
}

/*Function that prints the appropriate branches*/
struct tree_struct *print(struct name_root *nameRoot, struct title_root *titleRoot, struct principals_root *principalRoot, struct tree_struct *root, char *target )
{
    struct tree_struct *tempRoot = root;
    struct title_basics *tempTitleBasic;
    struct title_basics *titleCheck;
    struct title_principals *characterCall;

    if (root) {
        /*print*/
        if (strcmp(root->key, target) == 0) {
            if (tempRoot != NULL) {
                tempTitleBasic = tempRoot->data;
            }
            if (tempTitleBasic != NULL) {
                titleCheck = find_tconst(titleRoot, tempTitleBasic->tconst);
            }
            if (titleCheck != NULL) {
                characterCall = find_tconst_tp(principalRoot, titleCheck->tconst);
                if (characterCall != NULL && strcmp(characterCall->nconst, target) == 0) {
                    printf ("%s : %s\n", titleCheck->primaryTitle, characterCall->characters);
                }
            }
            return print(nameRoot, titleRoot, principalRoot, root->children[1], target);
        }
        else {
            if (strcmp(target, root->key) < 0 )
            {
                return print(nameRoot, titleRoot, principalRoot, root->children[0], target);
            }
            else /* value>=(root)->number */
            {
                return print(nameRoot, titleRoot, principalRoot, root->children[1], target);
            }
        }
    }
    else
    {
        return NULL;
    }
}

struct tree_struct *print_characters(struct name_root *nameRoot, struct title_root *titleRoot, struct principals_root *principalRoot, struct tree_struct *root, char *target )
{
    struct tree_struct *tempRoot = root;
    struct name_basics *tempNameBasic;
    struct name_basics *nameCheck;
    struct title_principals *characterCall;

    if (root) {
        /*print*/
        if (strcmp(root->key, target) == 0) {
            if (tempRoot != NULL) {
                tempNameBasic = tempRoot->data;
            }
            if (tempNameBasic != NULL) {
                nameCheck = find_nconst(nameRoot, tempNameBasic->primaryName);
            }
            if (nameCheck != NULL) {
                characterCall = find_nconst_tp(principalRoot, nameCheck->nconst);
                if (characterCall != NULL && strcmp(characterCall->tconst, target) == 0) {
                    printf ("%s : %s\n", nameCheck->primaryName, characterCall->characters);
                }
            }
            return print(nameRoot, titleRoot, principalRoot, root->children[0], target);
        }
        else {
            if (strcmp(target, root->key) > 0 )
            {
                return print(nameRoot, titleRoot, principalRoot, root->children[0], target);
            }
            else /* value>=(root)->number */
            {
                return print(nameRoot, titleRoot, principalRoot, root->children[1], target);
            }
        }
    }
    else
    {
        return NULL;
    }
}

void free_tree( struct tree_struct *root )
{
    if (root)
    {
        free_tree( root->children[0] );
        free_tree( root->children[1] );
    }
}

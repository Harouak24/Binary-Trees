#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct tag1
{
    char element;
    struct tag1 *left_child;
    struct tag1 *right_child;
} tree_node;

typedef struct tag2
{
    tree_node *address_node;
    struct tag2 *next;
} stack_node;

void menu();

tree_node* pop(stack_node **top);

void push(stack_node **top, stack_node *to_be_pushed);

tree_node *create_fill_node_tree(char element);

stack_node *create_fill_node_stack(tree_node *node);

tree_node *create_binary_tree(FILE *infp);

void print_infix(tree_node *root);

void print_prefix(tree_node *root);

int main(void)
{
    tree_node *root = NULL;
    int choice, flag = 1;
    FILE *infp;

    while (flag)
    {
        menu();
        printf("\n\t\tPlease enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            infp = fopen("postix.txt", "r");
            if(infp==NULL)
            {
              printf("\n\t\tFile could not be opened!\nThe file name is 'postix.txt'.\n");
            }
            else
            {
            root = create_binary_tree(infp);
            printf("\n\t\tBinary tree was successfully created.\n");
            }
            fclose(infp);
            break;
        case 2:
            if (root == NULL)
            {
                printf("\n\t\tTree is empty!\n");
            }
            else
            {
              printf("\n\t\t");
              print_infix(root);
              printf("\n");
            }
            break;
        case 3:
            if (root == NULL)
            {
                printf("\n\t\tTree is empty!\n");
            }
            else
            {
              printf("\n\t\t");
              print_prefix(root);
              printf("\n");
            }
            break;
        default:
            flag = 0;
        }
    }
    printf("\n\t\t!!WE HAD SUCH A NICE SEMESTER. \n\t\tWE HOPE THAT YOU DID TOO <3!!\n");
    return 0;
}
void menu() 
{
  printf("\n\t\t---------------MENU---------------\n");
  printf("\n\t\t1. Construct Binary Tree\n");
  printf("\n\t\t2. Display Infix Expression\n");
  printf("\n\t\t3. Display Prefix Expression\n");
  printf("\n\t\t4. Exit\n");
  printf("\n\t\t----------------------------------\n");
}

tree_node* pop(stack_node **top)
{
    tree_node *to_be_popped;
    stack_node *temp;
    temp = *top;
    *top = (*top)->next;
    to_be_popped = temp->address_node;
    free(temp);
    return to_be_popped;
}

void push(stack_node **top, stack_node *to_be_pushed)
{
    to_be_pushed->next = *top;
    *top = to_be_pushed;
}

tree_node *create_fill_node_tree(char element)
{

    tree_node *new_tree;
    new_tree = (tree_node *)malloc(sizeof(tree_node));
    new_tree->element = element;
    new_tree->left_child = NULL;
    new_tree->right_child = NULL;

    return new_tree;
}

stack_node *create_fill_node_stack(tree_node *node)
{

    stack_node *new_stack;
    new_stack = (stack_node *)malloc(sizeof(stack_node));
    new_stack->address_node = node;
    new_stack->next = NULL;

    return new_stack;
}

tree_node *create_binary_tree(FILE *infp)
{
    stack_node *top = NULL;
    tree_node *t_node, *root;
    stack_node *s_node;
    char element;
    int i = 0;
    while (1)
    {
        if(fscanf(infp," %c",&element)==EOF)
        break;
        t_node = create_fill_node_tree(element);
        if (t_node->element == '+' || t_node->element == '-' || t_node->element == '/' || t_node->element == '*' || t_node->element == '%')
        {
            t_node->right_child = pop(&top);
            t_node->left_child = pop(&top);
        }
        s_node = create_fill_node_stack(t_node);
        push(&top, s_node);
        i++;
    }
    root = pop(&top);
    return root;
}

void print_infix(tree_node *root)
{
    if (root == NULL)
        return;
    else
    {
        print_infix(root->left_child);
        printf("%c", root->element);
        print_infix(root->right_child);
    }
}

void print_prefix(tree_node *root)
{
    if (root == NULL)
        return;
    else
    {
        printf("%c", root->element);
        print_prefix(root->left_child);
        print_prefix(root->right_child);
    }
}

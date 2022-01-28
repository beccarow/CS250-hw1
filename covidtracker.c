#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct node
{
    char person[30];
    struct node * left;
    struct node * right;
}node;

typedef struct link
{
    char line[100];
    struct link * next;
}link;

node* finder(node * root, node * source);

link* create(char* line);

void sortList(link* newLink, link** head);

void printList(link* head);

void freeList(link* head);

void freeTree(node* root);

node* insertSort(node * root, node * patient, node * source);

link* printTree(node* root, link* head, int flag);

int main(int argc, char* argv[]) {

    if (argc == 1) {
        fprintf(stderr, "Please enter filename.\n");
        EXIT_SUCCESS;
        return (0);
    }

    char buf[70];
    float d;
    float p;

    FILE *f = fopen(argv[1], "r");

    if (!f) {
        fprintf(stderr, "Can't open %s for reading \n", argv[1]);
        EXIT_SUCCESS;
        return(0);
    }

    if (fgets(buf, 70, f)==NULL) {
        fprintf(stderr, "File is empty\n");
        EXIT_SUCCESS;
        return(0);
    }

    buf[strlen(buf)-1] = '\0';

    int patients = 0;
    node * first=NULL;
    
    //printf("%s", buf);

    
    while (((strcmp(buf, "DONE") !=0) && strcmp(buf, "DONE\n") !=0) && (strcmp(buf, "DON") !=0))
    {   
        //printf("%d ",patients);
        node* patient = (node*)malloc(sizeof(node));
        node* source = (node*)malloc(sizeof(node));
        int k=0;

        while(*(buf+k)!='\0' && *(buf+k)!=' ') {
            *(patient->person+k) = *(buf+k);
            k++;
        }
        *(patient->person+k)= '\0';

        k++;
        
        int i=0;
        while(*(buf+k)!='\0' && *(buf+k)!='\n') {
            *(source->person+i) = *(buf+k);
            k++;
            i++;
        }

        *(source->person+i) = '\0';

        fgets(buf, 70, f);
        buf[strlen(buf)-1] = '\0';

        if(first==NULL) {
            first=source;
            first = insertSort(first, patient, source);
            //printf("first in list");
        }
        else{
            first = insertSort(first, patient, source);
            //printf("rest of list");
        }
        patients++;

        if (((strcmp(buf, "DONE") ==0) && strcmp(buf, "DONE\n") ==0) && (strcmp(buf, "DON") ==0)) {
            free(patient);
            free(source);
        }

    } 


    link* head = NULL;
    int flag=0;  
    head = printTree(first, head, flag);
    fclose(f);
    freeList(head);
    freeTree(first);
    return 0;

}


link* printTree(node* root, link*head, int flag) {
    if (root==NULL) {
        //printf("hello");
        return head;
    }
    if (root->left==NULL){
        link* newNode = create(root->person);
        sortList(newNode, &head);
		//printf("%s \n", root->person);
	}
	else if (root->right == NULL){
		char temp[62];
		strcpy(temp,root->person);
		strcat(temp, " "); 
		strcat(temp, root->left->person);
        link* newNode = create(temp);
        sortList(newNode, &head);
		//printf("%s \n", temp);
	}
	else{
		//printf("%s %s %s \n", root->name, root->left->name, root->right->name);
		char temp[100];
		strcpy(temp,root->person);
		strcat(temp, " "); 
		strcat(temp, root->left->person); 
		strcat(temp, " "); 
		strcat(temp, root->right->person); 
        link* newNode = create(temp);
        sortList(newNode, &head);
		//printf("%s \n", temp);
	}
    //printf("%s %s\n", head->line, head->next->line);
    head = printTree(root->left, head, 1);
    head = printTree(root->right, head, 1);
    if(flag==0) {
        printList(head);
    }
    //freeList(head);
    //freeTree(root);
    return head;
}

void freeList(link* list) {
    if(list==NULL) {
        return;
    }
    freeList(list->next);
    free(list);
}

void freeTree(node* tree) {
    if(tree==NULL) {
        return;
    }
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
}

void sortList(link* newLink, link** head) {
    link* current;
    if(*head==NULL || strcmp(newLink->line, (*head)->line)<0) {
        newLink->next = *head;
        *head = newLink;
    }
    else {
        current = *head;
        while(current->next != NULL && strcmp(current->next->line, newLink->line)<0) {
            current = current->next;
        }
        newLink->next = current->next;
        current->next = newLink;
    }
}

void printList(link* head) {
    link* place = head;
    while(place != NULL) {
        printf("%s\n", place->line);
        place = place->next;
    }

}

link* create(char* line) {
    link* newLink = (link*)malloc(sizeof(link));
    strcpy(newLink->line, line);
    return newLink;
}

node * insertSort(node * root, node * patient, node * source) {
    //printf( " line 148%s %s \n", root->person, source->person);
    node * found = finder(root, source);

    if (found == NULL) {
        //printf("line202 \n");
        root = patient;
        //printf(" line 154 %s \n", root->person);
        return root;
    }

    if (found->left == NULL) {
        found->left = insertSort(found->left, patient, source);
    }

    else {
        int flag = strcmp(found->left->person, patient->person);
        if (flag < 0) {
            found->right = insertSort(found->right, patient, source);
        }
        if (flag > 0) {
            node * swap = NULL;
            swap = found->left;
            found->right = swap;
            found->left = patient;
        }
        
    }
    return root;


}

node * finder(node * root, node * source) {
    node * temp = NULL;
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(root -> person, source -> person) == 0) {
        return root;
    }

    temp = finder(root->left, source);

    if (temp != NULL) {
        return temp;
        
    }
    
    temp = finder(root->right, source);
    if (temp != NULL) {
        return temp;
        
    }
    return NULL;
}
/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* Define structures and global variables*/
int num_processes;
struct node1 {
    int processID;
    struct node1 *link;
};
typedef struct node1 linked_list_type;

struct node2 {
    int parent;
    linked_list_type *children;
}
*pcb = NULL;
typedef struct node2 pcb_type;



void print_processes() {
    /* declare local vars */
    /*int i; */
    linked_list_type *current_child;
    
    /* for each PCB index i from 0 up to (but not including) maximum number*/
    for(int i=0; i<num_processes; i++) {
        /* check if PCB[i] has a parent and children */
        if ((pcb[i].parent != -1) && (pcb[i].children != NULL)) {
            /* print message about children of the current PCB[i] */
            printf("PCB[%d] is the parent of: ", i);
            /* intilize variable to head of list of children */
            current_child= pcb[i].children;
            /* while the end of the linked list of children is not reached */
            while (current_child != NULL) {
                /* print message about current child process index */
                printf("PCB[%d] ", current_child->processID);
                /* move to next node in linked list */
                current_child = current_child->link;
            } /* while */
        }
            printf("\n");
 
    }/* for */

}/* end of procedure */





void enter_params() {
    /* declare local vars */
    /*int i; */
    /* prompt for maximum number of processes */
    printf("Enter the maximum number of processes: ");
    scanf("%d" , &num_processes);
    /* allocate memory for dynamic array of PCBs */
    pcb = (pcb_type*)malloc(num_processes * sizeof(pcb_type));
    /* Define PCB[0] */
    pcb[0].parent =0;
    pcb[0].children = NULL;
    /* for-loop to intitialize all other indices' parent to -1 */
    for (int i=1; i<num_processes; i++) {
       pcb[i].parent = -1;
    }
    return;
} /* end of procedure */




void create() {
/* define local vars */
int p;
int q=1;
linked_list_type *new_child, *current_child;
/*int new_child_index=1; */
/*int num_children=1;*/

/* prompt for parent process index p */
printf("Enter the parent process index: ");
scanf("%d" , &p);
/* search for first available index q without a parent in a while loop */
while (pcb[q].parent != -1) {
    q++;
}
/* allocate memory for new child process, initilize fields */
new_child = (linked_list_type*)malloc(sizeof(linked_list_type));
new_child->processID = q;
new_child->link = NULL;

/* record the parent's index p in PCB[q] */
pcb[q].parent = p;
/* initialize the list of children of PCB[q] as empty */
pcb[q].children = NULL;
/* create a new link containing the child's index q and append the link to the end of the linked list of PCB[p] */
if(pcb[p].children==NULL) {
   pcb[p].children = new_child;
   }
else {
   /*num_children++; */
   current_child = pcb[p].children;
   while (current_child->link != NULL) {
      current_child = current_child->link;
      /*num_children++; */
   }
   current_child->link = new_child;
}
print_processes();
/*return; */
} /* end of procedure */




void destroy_recursion(linked_list_type *node) {
int q;
if (node ==  NULL) {
   return;
}
else {
   destroy_recursion(node->link);
   q = node->processID;
   destroy_recursion(pcb[q].children);
   free(node);
   pcb[q].parent = -1;
   node = NULL;
}
return;
}


void destroy() {
   int p;
   printf("Enter the process whose descendants are to be destroyed: ");
   scanf("%d", &p);
   destroy_recursion(pcb[p].children);
   pcb[p].children  = NULL;
   print_processes();
   return;
}


void garbage_collection() {
if (pcb != NULL) {
   if (pcb[0].children != NULL) { 
        printf("Destroying remaining processes: ");
        destroy_recursion(pcb[0].children);
   }
   free(pcb);
   }
   return;
   }
   
  
int main() {
  int choice = 0;
  /*int p; */
  while (choice != 4) {
     printf("\nProcess creation and destruction\n");
     printf("--------------------------------\n");
     printf("1) Enter parameters\n");
     printf("2) Create a new child process\n");
     printf("3) Destroy all descendants of a process\n");
     printf("4) Quit program and free memory\n");
     printf("\nEnter selection: ");
     scanf("%d", &choice);
    /*p++;*/
     switch(choice) {
        case 1: enter_params();
        break;
        case 2:create();
        break;
        case 3:destroy(); 
        break;
        case 4:garbage_collection();
        printf("\nQuitting program\n");
        break;
        default: 
        printf("Invalid option!\n"); 
        break;
     }    
   }    
        return 1;
}

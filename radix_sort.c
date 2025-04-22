#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH 31
//1.node struct for Dlinkedlist

FILE *fptrOUT; //pointer to file to print results on

typedef struct node
{
    char data[ LENGTH ];//data of node
    struct node *next;//next pointer
    struct node *prev;//before node pointer
} dnode;
// function prototypes
dnode * bucketes[63];
void radix(dnode *list);
dnode *insertnode(dnode *prevnode, char *newstring);
dnode* deletefromnode(dnode *node, char* string);
dnode* insertAtEnd(dnode* head, char* newstring);
int isEmpty(dnode *node1);
void print(dnode *node);
void  Savetooutputfile(dnode *node,char *fileN);
void dfree(dnode *ptr);
int findsize(dnode *node);
int maxlength(dnode * ptr);
void addspace( dnode *node);
void convert(char word[]);
dnode * createnew();
void initial();

int main()
{

    dnode *list=NULL;
    char inputString[LENGTH];
    printf("\n\n [application of Linked Lists : Radix Sort.] \n\n");
    int option;
    do
    {
        displaymainmenu();
        printf("Enter your option:");
        scanf("%d", &option);
        switch(option)
        {
        case 1:
            printf("please Enter the Input File Name TO Load a string: ");
            scanf(" %s",inputString);
            FILE *fptrIN;//pointer to file to Read string
            fptrIN=fopen(inputString,"r");
            if (fptrIN == NULL)//Check if the file exist or not
            {
                printf("ERROR? the file dose not exist .\n");
                break;
            }
            while(fscanf(fptrIN," %s",inputString)==1)//?
            {
                printf("% s",inputString);
                printf("\n");
                list=insertnode(list,inputString);
            }

            fclose(fptrIN);
            printf("Strings are loaded.\n");
            break;
        case 2 :
            printf("strings before sorting \n");
            print(list);
            break;
        case 3:
            //radix(list);
            printf("String sorted:\n");

            break;
        case 4:
            printf("String after sorted:");
            print(list);
            break;
        case 5:
            printf("Add a new word to the list of sorted strings TO sort it : ");
            scanf(" %s", inputString);
            list = insertnode(list, inputString);
            radix(list);
            printf("string added and sorted.\n");
            break;
        case 6 :
            printf(" Enter a word to delete from the sorted strings :");
            scanf(" %s", inputString);
            list = deletefromnode(list,inputString);//delete string from this node
            radix(list);
            break;

        case 7:
            printf(" Enter filename to Save the output  in the file: ");
            scanf("% s", inputString);

            Savetooutputfile(list,inputString);
            break;
        case 8:
            dfree(list);
            printf("");
            break;

        default:
            printf("Invalid option. Please try again\n");
        }
    }
    while ( option != 8);
    return 0;
}

void displaymainmenu()
//to print menu
{
    printf("\n\n please select an operation(1-8).\n");
    printf(" 1-Load	the strings\n");
    printf(" 2-Print the strings before sorting\n");
    printf(" 3-Sort	the strings\n");
    printf(" 4-Print the sorted strings\n");
    printf(" 5-Add a new word to the list of sorted	strings	(and sort it)\n");
    printf(" 6-Delete a word from the sorted strings\n");
    printf(" 7-Save	to output file\n");
    printf(" 8-Exit \n\n");
}
//to check if the linked list is empty or not
int isEmpty(dnode *node1)
{
    return (node1->next==NULL);
}
//to create a new double linked list

dnode *createnew()
{
    dnode *node = (dnode *)malloc(sizeof(dnode));
    if (node == NULL)
    {
        printf("\n Memory allocation failed.\n");
        exit(EXIT_FAILURE);  // This line terminates the program if memory allocation fails
    }
    node->next = NULL;
    node->prev = NULL;
    return node;
}


dnode *insertnode(dnode *head, char * newstring)
{
    dnode *newnode=(dnode*)malloc(sizeof(dnode));  //allocate new node
    strcpy(newnode->data,newstring);
    newnode->prev=NULL;
    newnode->next=NULL;
    //check prev node
    if(head==NULL)
    {
        return newnode;
    }
    else
    {
        //node1 is a current pointer  thats equal prevnode
        dnode *node1= head;// make the next of prevnode as newnode and prev of new as a prevnode
        while(node1->next !=NULL)  // to check if a next node of new is null
        {
            node1=node1->next;
        }
        node1->next=newnode;//next pointer point to prev of a new
        newnode->prev=node1;//prev pointer to a new one(check)
        return head;
    }

}
//function to print the list element

void print(dnode *node)
{
    //check if a node not null
    while(node!=NULL)
    {
        printf("% s",node->data);
        printf("\n");
        node=node->next;
    }
    printf("\n");
}
//function to delete from D list
dnode* deletefromnode(dnode *node, char* string)
{
    dnode* node1 = node;
    while (node1!= NULL)
    {
        if (  strcmp(node1->data, string)== 0)
        {
            node->next->prev=node->prev;
            node->prev->next=node->next;
            free(node1);
            return node;
        }
        node1 = node1->next;
    }
    return node;//return list
}
void  Savetooutputfile(dnode *node,char *fileN)
{
    fptrOUT=fopen(fileN,"w");
    if(fptrOUT==NULL)
    {
        printf("eror!failed to open this file.\n");
        return;
    }
    else
    {
        dnode *node1=node;
        while(node1 !=NULL)
        {
            fprintf(fptrOUT,"% s",node1->data);
            node1=node1->next;
        }
    }
    fclose(fptrOUT) ;
}
void dfree(dnode *ptr)
{
    dnode *temp=ptr;
    dnode *node1;
    while(temp!=NULL)
    {
        node1=temp->next;
        free(temp);
        temp=node1;
    }
}
//to finf the size of linkedlist
int findsize(dnode *node)
{
    int cont=0;
    if(node !=NULL)
    {
        cont++;
        node =node->next;
    }
    return cont;
}

//function to find the maximum length of the strings in list
int maxlength(dnode * ptr)
{
    int max;
    while(ptr !=NULL)
    {
        int i=strlen(ptr->data);
        if(i>max)
        {
            max=i;
        }
        ptr=ptr->next;
    }
    return max;
}
//function to convert the uppercase char to lawer case to sort it
void convert(char word[])
{
    for(int i=0; word[i]!='\0'; i++) //ask
    {
        if(word[i]>= 'A' && word[i]<='Z') //check the word char
        {
            word[i] =word[i]-'A' +'a';
        }
    }
}
//Saja1 dana lina sama
//function to add space to get the same length of all strings
void addspace( dnode *node)
{
    int length=maxlength(node) ;//to find the maxlenght
    dnode*node1=node;//node1 the current node
    while(node !=NULL)
    {
        int i=strlen(node1->data);
        int k=length-i;//subtract from the max string char of the length string (node1) k(space)
        for(int j=0; j<k; j++)
        {
            strcat(node1->data, " ");
        }
        node1=node1->next;
    }
}
//Function to intilize the buckets (array of doubly linked list)
void initial()
{
    // space in index 0
    for (int i =0; i<63; i++)//a-z , 0-9
    {
        bucketes[i]=createnew();//create new node
    }
}

dnode* insertend(dnode* head, char* newstring)
{
    dnode* newnode = createnew();
    strcpy(newnode->data, newstring);

    if (head == NULL)
    {
        return newnode;
    }
    else
    {
        dnode* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newnode;
        newnode->prev = temp;

        return head;
    }
}

/*void radix(dnode *list)
{
    int len = maxlength(list);
    int index;
    addspace(list); // to have the same length of all strings in array
    dnode* arr1[63]; // create array

    for (int i = len - 1; i >= 0; i--)
    {
        initial();

        // Distribute values into buckets
        dnode *node1 = list;
        while (node1 != NULL)
        {
            char z = node1->data[i];

            if (z == ' ')
            {
                // Space char insert in the first bucket arr[0]
                arr1[0] = insertend(arr1[0], node1->data);
            }
            else if ('0' <= z && z <= '9')
            {
                // Digit 0-9 arr[1] to arr[9]
                 index = z - '0' + 1;
                arr1[index] = insertend(arr1[index], node1->data);
            }
            else if ('a' <= z && z <= 'z')
            {
                // Lowercase letters arr[10] to arr[35]
                 index = z - 'a' + 10;
                arr1[index] = insertend(arr1[index], node1->data);
            }
            else if ('A' <= z && z <= 'Z')
            {
                // Uppercase letters arr[36] to arr[61]
               index = z - 'A' + 36;
                arr1[index] = insertend(arr1[index], node1->data);
            }
             insertend(node1->data,arr1[index]);
            node1 = node1->next;
        }

        // Collect elements from buckets
        dnode *node2 = NULL;
        for (int j = 0; j < 63; j++)
        {
            node2 = insertend(node2, arr1[j]);
        }

        // Update the original list with the sorted elements
        list = node2;

        // Free memory used by buckets
        for (int k = 0; k < 63; k++)
        {
            dfree(arr1[k]);
        }
    }
}*/
/*void radix(dnode *list)
{
    int len = maxlength(list);
    addspace(list); // to have the same length of all strings in array
    dnode* arr1[63]; // create array

    for (int i = len - 1; i >= 0; i--)
    {
        initial();

        // Distribute values into buckets
        dnode *node1 = list;
        while (node1 != NULL)
        {
            char z = node1->data[i];
            int index;

            if (z == ' ')
            {
                // Space char insert in the first bucket arr[0]
                index = 0;

            }
            else if ('0' <= z && z <= '9')
            {
                // Digit 0-9 arr[1] to arr[9]
                index = z - '0' + 1;

            }
            else if ('a' <= z && z <= 'z')
            {
                // Lowercase letters arr[10] to arr[35]
                index = z - 'a' + 10;

            }
            else if ('A' <= z && z <= 'Z')
            {
                // Uppercase letters arr[36] to arr[61]
                index = z - 'A' + 36;

            }

            node1 = node1->next;
        }

        // Collect elements from buckets
        dnode *node2 = NULL;
        for (int j = 0; j < 63; j++)
        {
            node2 = insertend(node2, arr1[j]);
        }

        // Update the original list with the sorted elements
        list = node2;

        // Free memory used by buckets
        for (int k = 0; k < 63; k++)
        {
            dfree(arr1[k]);
        }
    }
}*/


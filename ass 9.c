#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>

typedef struct node{
   int idNum;
   char name[31],surname[31];
   int q1,q2,q3;
}REC;

typedef struct srec{
   REC st;
   struct srec *nxt;
}LIST;

LIST *S;

/*
int checkDupli(int id);
int isEmpty();
void makenull();
void add(REC x);
void del(int id);
void display();
void save();
void retrieve();
*/

int menu (){ // menu funtion
int i, opt; //variables
char *m[] = {"Insert","Delete","Display","Save & Exit"}; //store the options
system ("cls"); // clears the screen
printf("        STUDENT RECORD MENU\n"); // header
printf("   **************************\n");
for (i=0; i<4;i++ ) // loop four times for the options to print
    printf("\t[%d] %s\n", i+1, m[i]); // prints menu options
    printf("   **************************\n");
    printf("\n     Select (1-4): "); // prints quotated characters
    scanf(" %d",&opt); // scans rhe option
    return (opt); // return the option
}


int main(){
REC y;
int opt;
makenull(); //initialize the list
retrieve();
while (1){
    switch(menu()){
    case 1: system ("cls");
            printf("\t   : : : INSERT MODE : : :\n\n");
            printf("Input your last 4-digit ID number: "); scanf("%d",&y.idNum);
            printf("Input first name: "); scanf(" %[^\n]s", y.name);
            printf("Input last name: "); scanf("%s",y.surname); strupr(y.surname);
            printf("Input Q1 score: ");scanf("%d",&y.q1);
            printf("Input Q2 score: ");scanf("%d",&y.q2);
            printf("Input Q3 score: ");scanf("%d",&y.q3);
            add(y);
            system("pause");
            break;
    case 2: system ("cls");
            printf("\t\t\t: : : DELETE MODE : : :\n\n");
            display();
            printf("Input the ID number of student you wish to delete: "); scanf("%d",&y.idNum);
            del(y.idNum);
            system("pause");
            break;
    case 3: system ("cls");
            printf("\t\t\t: : : STUDENT RECORD : : :\n\n");
            display();
            system("pause");
            break;
    case 4: save();exit(0);
            break;
    default: printf("\n\tINVALD. 1-4 only.\n");
            system ("pause");
            break;
    }
  }
return 0;
}

void makenull () {
 S = NULL;
}

void add(REC x){
    LIST *p,*q,*temp;
    p=q=S;
    temp = (LIST*) ((malloc(sizeof(LIST))));
    temp-> st = x;
    if (checkDupli(x.idNum)){
    printf("\n\t\t<DUPLICATE DATA> \nStudent with ID: TUPM-20-%d has a record already!\n\n", x.idNum);
    }
    else {
    while(p!=NULL && p->st.surname < x.surname){
        q=p;
        p=p->nxt;
    }
    if (p==S)
        S=temp;
    else
        q->nxt = temp;

    temp->nxt = p;
    printf("\n\t<Student successfully added!>\n\n");
    save ();
    }

}

void del(int id){
LIST *p, *q;
p=q=S;
while(p!=NULL && p->st.idNum!= id){
        q=p;
        p=p->nxt;
    }
    if (p==NULL){
        printf("\n\t\t< STUDENT NOT FOUND >\n\n");
        system("pause");
        }
    else{
        if (p==S)
            S=S->nxt;//or L=p->nxt
        else
            q->nxt=p->nxt;
        free(p);
        }
        printf("\n\t    < Record deleted successfully >\n\n");
}

void display(){
    LIST *p;
    int i = 1;
    float ave;
    p=S;
    printf("   Student ID\t\tName\t\tQ1   Q2   Q3  Average   Remarks\n");
    printf("================================================================\n");
    while (p!=NULL){
        ave= (float)(p->st.q1 + p->st.q2 + p->st.q3)/3;
        printf("%d.)%-5d  %s, %-14s  %d   %d   %d   %.2f    ", i++, p->st.idNum, p->st.surname, p->st.name, p->st.q1, p->st.q2, p->st.q3, ave);
        if (ave >= 75)
        printf("Passed\n");
        else
        printf("Failed\n");
        p=p->nxt;
        }
   printf("\n\n");
}

void save(){
FILE *fp;
LIST *p;
p=S;
int i;
fp= fopen ("record.dbf", "w+");
if (fp==NULL){
    printf("File Error. \n");
    system ("pause");
} else {
     fprintf(fp,"%d %s %s\t%d %d %d\n",p->st.idNum, p->st.surname, p->st.name, p->st.q1, p->st.q2, p->st.q3); // save elements to file
    p=p->nxt;
}
fclose(fp);
}

void retrieve(){
FILE *fp;
REC y;
 if ((fp=fopen("record.dbf", "r+"))!=NULL){
   while (!feof (fp)){ //while it is not the end of the file-
   fscanf(fp,"%d %s %[^\t] %d %d %d\n", &y.idNum, y.surname, y.name, &y.q1, &y.q2, &y.q3);
   add(y);
   }
fclose(fp);
}
}
int checkDupli(int id){
LIST *p;
p=S;
 while (p != NULL) {
        if (p->st.idNum == id)
            return 1;
        p = p->nxt;
    }
    return 0;
}

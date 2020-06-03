#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct cards cards;
typedef enum colour {red,green,yellow,blue,nocolour} color;
struct cards
{
  int value;
  color c;
};
int val[13][5];
typedef struct player player;
struct player
{
  cards  p_card;
  //char name[20];
 // int  no_of_cards;
  player* rcard;
  player* lcard;
};
player  *comp=NULL;
player *clast=NULL;
player *user=NULL;
player *ulast=NULL;
cards uno[56];
cards s[56];
int top=-1;
int i;
void push(cards ca)
{
  if(top==55)
  {
    printf("error");
  }
  else{
    top++;
    s[top].value=ca.value;
    s[top].c=ca.c;
  }
}
void u_insert(cards ca)
{
  val[ca.value][ca.c]++;
  player *first=user;
  player *last=ulast;
  player *temp=(player*)malloc(sizeof(player));
  (temp->p_card).value=ca.value;
  (temp->p_card).c=ca.c;
  if(!first){ 
    first=temp;
     first->lcard=NULL;
     first->rcard=NULL;
     last=first;
  }
  else{
     temp->lcard=last;
    temp->rcard=NULL;
    last->rcard=temp; 
    last=temp;  
  }
user=first;
ulast=last;
}
void c_insert(cards ca)
{
  val[ca.value][ca.c]++;
  player *first=comp;
  player *last=clast;
  player *temp=(player*)malloc(sizeof(player));
  (temp->p_card).value=ca.value;
  (temp->p_card).c=ca.c;
  if(!first){ 
    first=temp;
     first->lcard=NULL;
     first->rcard=NULL;
     last=first;
  }
  else{
     temp->lcard=last;
    temp->rcard=NULL;
    last->rcard=temp; 
    last=temp;  
  }
  comp=first;
  clast=last;
}
void u_delete(cards ca){
 player *prev,*next;
player *first=user;
player *last=ulast;
player *p=first;
while(p)
{
   if((p->p_card).value==ca.value  && (p->p_card).c==ca.c)
       break;
    p=p->rcard;
}
if(p==first){
  next=p->rcard;
  next->lcard=NULL;
  first=next;
  free(p);
}
else if(p==last){
   prev=p->lcard;
   prev->rcard=NULL;
   last=prev;
   free(p);
}
else{  
  prev=p->lcard;
  next=p->rcard;
  prev->rcard=next;  
  next->lcard=prev;
  free(p);
 }
user=first;
ulast=last;
}
void c_delete(cards ca){
 player *prev,*next;
player *first=comp;
player *last=clast;
player *p=first;
while(p)
{
   if((p->p_card).value==ca.value  && (p->p_card).c==ca.c){
       break;
   }
      p=p->rcard;
}
if(p==first){
  next=p->rcard;
  next->lcard=NULL;
  first=next;
  free(p);
}
else if(p==last){
   prev=p->lcard;
   prev->rcard=NULL;
   last=prev;
   free(p);
}
else{  
  prev=p->lcard;
  next=p->rcard;
  prev->rcard=next;  
  next->lcard=prev;
  free(p);
 }
comp=first;
clast=last;

}
void draw_card(player *first,player *last,int top1){
  if(first==user)
    u_insert(uno[top1]);
  else
    c_insert(uno[top1]);
  if(uno[i].value==s[top].value || uno[i].c==s[top].c)
  {
  push(uno[i]);
  if(first==user)
    u_delete(uno[i]);
  else
    c_delete(uno[i]);
  }
}
void match_user(int num,int top1)
{
  int cnt=0;
  player* p=user;
  while(p && cnt<num-1)
  {
    p=p->rcard;
    cnt++;
  }
   if((p->p_card).value>10){
        push(p->p_card);
        u_delete(p->p_card);
      }
  else if((p->p_card).value!=s[top].value && (p->p_card).c!=s[top].c)
  {
    printf("\nNO MATCHING CARD. YOU LOSE YOUR TURN");
    draw_card(user,ulast,top1);
  }
  else
  {
    push(p->p_card);
    u_delete(p->p_card);
  }
}
void match(int top1)
{
  int c=0;
  player *p=comp;
   player *q=clast;
   while(p && q)
   {
  if(s[top].value==(p->p_card).value || s[top].c==(p->p_card).c ) {
             push(p->p_card);    
              c_delete(p->p_card);
              c++;
              break;
          }
  else if(s[top].value==(q->p_card).value || s[top].c==(q->p_card).c){
             push(q->p_card);    
              c_delete(q->p_card);
               c++; 
             break;
       }
  p=p->rcard;
  q=q->lcard;
 }
 p=comp;
 if(c==0){
   while(p)
   {
     if((p->p_card).value>10)
     {
     push(p->p_card);
     c_delete(p->p_card);
     c++;
     break;
     }
     p=p->rcard;
   }
   if(c==0)
       draw_card(comp,clast,top1);
   }
}
int Randoms() 
{ 
  int z,c;
  int num;
  num= (rand() % (12 - 0 + 1)) + 0;
  if(num==11 || num==12){
         c=4;
}  
else{
      c=(rand() %(3 - 0 + 1)) + 0;
  }
 val[num][c]++;
  while(val[num][c]!=0)
  {
    if(val[num][c]==1 || (num>10 && val[num][c]<4))
    {
      for(z=0;z<56;z++)
      {
        if(uno[z].value==num && uno[z].c==c)
        {
          break;
        }
      }
  break;
    }
    else
    {
      num= (rand() % (12 - 0 + 1)) + 0; 
      if(num==11 || num==12)
         c=4;
      else
       {
         c=(rand() %(3 - 0 + 1)) + 0;  
       }
       val[num][c]++;
    }   
 }
return z;
}
void shuffle()
{
  int i,plus4=0;
  srand((unsigned)time(NULL));
  for(i=0;i<28;i++)
  {
    int z=Randoms();
   cards tmp=uno[z];
    uno[z]=uno[i];
    uno[i]=tmp;
  }
}
void wild_card(int v)
{
   int col;
  switch(s[top].value)
  {
    case 10:
    if(v){
    c_insert(uno[i]);
    i++;
     c_insert(uno[i]);
    i++;
   }
   else
   {
     printf("\nComputer has placed draw two: two cards are added to your deck\n");
     u_insert(uno[i]);
    i++;
    u_insert(uno[i]);
    i++;
   }
    break;
  case 11:
   if(v)
   {
     printf("\n0 red\n1 green\n2 yellow\n3 blue");
     printf("\nEnter colour no:");
     scanf("%d",&col);
     s[top].c=col;
     printf("\nThe colour of top card is");
     if(s[top].c==0)
    printf(" red\n");
    else if(s[top].c==1)
    printf(" green\n");
    else if(s[top].c==2)
    printf(" yellow\n");
    else if(s[top].c==3)
    printf(" blue\n"); 
    else if(s[top].c==4)
    printf(" No colour\n");
   }
   else
   {
     printf("\nComputer has placed colour change:\n");
     col=(rand() % (3 - 0 + 1)) + 0;
           s[top].c=col;
     printf("\nThe colour of top card is");
     if(s[top].c==0)
    printf(" red\n");
    else if(s[top].c==1)
    printf(" green\n");
    else if(s[top].c==2)
    printf(" yellow\n");
    else if(s[top].c==3)
    printf(" blue\n"); 
    else if(s[top].c==4)
    printf(" No colour\n"); 
    }  
    break;
    case 12:
    if(v)
    {
      printf("\n0 red\n1 green\n2 yellow\n3 blue");
      printf("\nEnter colour:");
      scanf("%d",&col);
      s[top].c=col;
       printf("\nThe colour of top card is");
     if(s[top].c==0)
    printf(" red\n");
    else if(s[top].c==1)
    printf(" green\n");
    else if(s[top].c==2)
    printf(" yellow\n");
    else if(s[top].c==3)
    printf(" blue\n");  
    else if(s[top].c==4)
    printf(" No colour\n");
      for(int k=0;k<4;k++)
      {
        c_insert(uno[i]);
        i++;
      }
    }
    else
    {
      printf("\nComputer has placed draw four and colour change: four cards are added to your deck\n");
      col=(rand() %(3 - 0 + 1)) + 0;
           s[top].c=col;
           printf("\nTnhe colour of top card is");
     if(s[top].c==0)
    printf(" red\n");
    else if(s[top].c==1)
    printf(" green\n");
    else if(s[top].c==2)
    printf(" yellow\n");
    else if(s[top].c==3)
    printf(" blue\n"); 
    else if(s[top].c==4)
    printf(" No colour\n"); 
           for(int k=0;k<4;k++)
          {
        u_insert(uno[i]);
        i++;
      }
    }
    break;
  }
}
int nodes(player* p)
{
  int cnt=0;
  while(p)
  {
    cnt++;
    p=p->rcard;
  }
  return cnt;
}
void display()
{
  player* p=user;
  while(p)
  {
    printf("%d ",(p->p_card).value);
    if((p->p_card).c==0)
    printf(" red\n");
    else if((p->p_card).c==1)
    printf(" green\n");
    else if((p->p_card).c==2)
    printf(" yellow\n");
    else if((p->p_card).c==3)
    printf(" blue\n");
    else if((p->p_card).c==4)
    printf(" No colour\n");
    p=p->rcard; 
 }
}
void instructions()
{
  printf("\n\t************** UNO CARDS GAME **************\n");
printf("\n      Rules     \n");
printf("\n This is a card game played between YOU and computer \n This card game consists of 56 cards \n Of which 40 cards are number cards i.e cards which bear numbers ranging from 0 to 9 of 4 different colours,the colours being Red,Green,Blue,Yellow \n The remaining 16 cards are special cards also called WILDCARDS \n There are 3 wildcards +2 cards,Colour cards,+4 cards\n Each wildcard has  special uses\n +2 cards which are 8 in total when used make the opponent take 2 cards extra\n Colour card can be used when you have no matching colour or card and by using this you can change the colour of the game\n +4 card makes the opponent pick 4new cards along with this you can change the colour of the game\n");
printf("All you have to do is match your cards with the top deck card\n The first player who has only a single card left and selects UNO wins the game\n");
printf("\n Values of cards range from 0 to 12 where 0 to 9 are number cards with their corresponding numbers and 10 is +2 card,11 is Colour card,12 is +4 card (which includes colour change)");
}
int main()
{
  int k,j=0,choice,variable=0;
  int ccards;
  color l=0;
  instructions();
  for(int h=0;h<13;h++){
       for(int j=0;j<5;j++){
      val[h][j]=0;
   }
  }
  for(k=0;k<40;k++)
{
  uno[k].value=j;
  uno[k].c=l;
  j++;
  if(j==10)
  {
  j=0;
  l++;
  }
  if(l==4)
  l=0;
}
l=0;
for(k=40;k<48;k++)
{
  uno[k].value=10;
  uno[k].c=l;
  l++;
  if(l==4)
  l=0;
}
for(k=48;k<52;k++)
{
  uno[k].value=11;
  uno[k].c=4;
}
for(k=52;k<56;k++)
{
  uno[k].value=12;
  uno[k].c=4;
}
shuffle();
for(i=0;i<7;i++)
{
 c_insert(uno[i]);
}
for(i=7;i<14;i++)
{
  u_insert(uno[i]);
}
push(uno[i]);
i++;
do
{
  printf("\n Your cards are:\n");
  display();
printf("\n Top card is:");
printf("  \n%d ",s[top].value);
if(s[top].c==0)
    printf(" red\n");
    else if(s[top].c==1)
    printf(" green\n");
    else if(s[top].c==2)
    printf(" yellow\n");
    else if(s[top].c==3)
    printf(" blue\n");
    
variable = 0; //0 is user drws card
if(s[top].value>9)
{
  wild_card(variable);
}
printf("\n Enter your choice \n Press 1 if you do not have a matching card \n Press 2 if you have a matching card \n Press 3 for UNO\n 1. drawcard  2. match  3.uno:");
scanf("%d",&choice);
if(choice==1)
{
 draw_card(user,ulast,i);
  i++;
}
else if(choice==2)
{
  int num;
  printf("\nEnter number:");
  scanf("%d",&num);
  match_user(num,i);
  i++;
}
else if(choice==3)
{
  int cnt=nodes(user);
  if(cnt!=1)
  {
    printf("\nCheater");
  }
  else
  printf("\nCongrats you win");
  exit(1);
}
variable=1;
if(s[top].value>9)
{
  wild_card(variable);
}
printf("\n Computer is playing it's turn\n");
match(i);
i++;
ccards=nodes(comp);
if(ccards==1)
{
  printf("\nComputer wins you lose");
  exit(1);
}
}while(ccards!=1 || choice!=3);
}

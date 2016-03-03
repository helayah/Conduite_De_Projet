#include <stdio.h>
#include <stdlib.h>
struct node{
   	int id;
	double lon;
	double lat;
   struct node *p_next;
};

struct bounds{
	double minlat;
	double minlon;
   	double maxlat;
	double maxlon;
};

struct ways{
int id;
int ref;
struct ways * w_next;
};

struct ways *add_end_way (struct ways *w_head, int x1,int x2){
	struct ways *w_new = malloc (sizeof *w_new);
	if (w_new != NULL){
      w_new->id = x1;w_new->ref = x2;
      w_new->w_next = NULL;
      if (w_head == NULL){
         w_head = w_new;
      }else{
         struct ways *w = w_head;

         while (w->w_next != NULL)
         {
            
            w = w->w_next;
         }

         
         w->w_next = w_new;
      }
   }
   return w_head;
}

struct node *add_end_node (struct node *p_head, int x1,double x2,double x3)
{
   
   struct node *p_new = malloc (sizeof *p_new);

 
   if (p_new != NULL)
   {
      
      p_new->id = x1;p_new->lon = x2;p_new->lat = x3;

      
      p_new->p_next = NULL;

      
      if (p_head == NULL)
      {
         
         p_head = p_new;
      }
      else
      {
         
         struct node *p = p_head;

         while (p->p_next != NULL)
         {
            
            p = p->p_next;
         }

         
         p->p_next = p_new;
      }
   }
   return p_head;
}
void display_node (struct node *p_head){
   struct node *p = p_head;

   while (p != NULL)   {
      
      printf ("id :%d-lon :%f- lat:%f \n ", p->id,(double)p->lon,(double)p->lat);

      
      p = p->p_next;
   }
   
   printf ("RIEN\n");
}
void display_way (struct ways *w_head){
   struct ways *w = w_head;

   while (w != NULL)   {
     
      printf ("%d >> %d  \n", w->id,w->ref);

      
      w = w->w_next;
   }
   
   printf ("RIEN\n");
}





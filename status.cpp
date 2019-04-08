#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include <GLFW/glfw3.h>
#include "status.h"

using namespace std;


int main()
{
  struct status *root = NULL;
  statustree newstatus;
  printf("Enter 1 to push 2 to pop 3 to find neighbour for point 4 to find neighbour for line 0 to exit\n");
  int control;
  struct lineSegment newl;
  scanf("%d",&control);
  GLfloat xs,ys,xe,ye,ycor;
  while(control!=0)
  {
    if(control==1)
    {
        newstatus.globalinsert = 0;
        printf("Enter new line segment details and y\n");
        scanf("%f%f%f%f%f",&xs,&ys,&xe,&ye,&ycor);
        newl.startX = xs;
        newl.startY = ys;
        newl.endX = xe;
        newl.endY = ye;
        root = newstatus.insert (root,newl,ycor-1);
        printf("Inserted\n");

    }
    if(control == 2)
    {
      printf("Enter event details to delete and y\n");
      scanf("%f%f%f%f%f",&xs,&ys,&xe,&ye,&ycor);
      newl.startX = xs;
      newl.startY = ys;
      newl.endX = xe;
      newl.endY = ye;
      root = newstatus.deleteNode(root, newl,ycor+1);
      root = newstatus.deleteNode(root, newl,ycor+1);
      printf("Deleted from status \n");
    }
    if(control == 3){
      printf("enter point: \n");
      GLfloat px, py;
      scanf("%f %f", &px, &py);
      struct lineSegment leftl;
      struct lineSegment rightl;
      leftl.startX = -1;
      rightl.startX = -1;

      newstatus.getNeighbors(root, px, py-0.1, &leftl, &rightl);
      if(leftl.startX == -1){
        printf("no left line\n");
      }
      else{
        printf("left line: %f %f %f %f\n", leftl.startX, leftl.startY, leftl.endX, leftl.endY );
      }
      if (rightl.startX == -1) {
        printf("no right line\n");
      } else {
        printf("right line: %f %f %f %f\n", rightl.startX, rightl.startY, rightl.endX, rightl.endY );
      }
    }
    if(control == 4)
    {
      printf("enter line: \n");

      scanf("%f %f %f %f %f", &xs, &ys, &xe,&ye,&ycor);
      struct lineSegment leftl;
      struct lineSegment rightl;
      leftl.startX = -1;
      rightl.startX = -1;
      newl.startX = xs;
      newl.startY = ys;
      newl.endX = xe;
      newl.endY = ye;
      newstatus.getLeftNeighbor(root, newl, ycor, &leftl);
      newstatus.getRightNeighbor(root , newl, ycor, &rightl);
      if(leftl.startX == -1){
        printf("no left line\n");
      }
      else{
        printf("left line: %f %f %f %f\n", leftl.startX, leftl.startY, leftl.endX, leftl.endY );
      }
      if (rightl.startX == -1) {
        printf("no right line\n");
      } else {
        printf("right line: %f %f %f %f\n", rightl.startX, rightl.startY, rightl.endX, rightl.endY );
      }

    }
    newstatus.preOrder(root);
    printf("Enter 1 to push 2 to pop 3 to find for point 4 to find for line 0 to exit\n");
    scanf("%d",&control);

  }
    return 1;
}

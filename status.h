#ifndef STATUS_H
#define STATUS_H

#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include <GLFW/glfw3.h>
using namespace std;
/**
  * structure that stores a line segment in terms of start and end point
*/
///struct to represent a line segment
struct lineSegment
{
    double startX;
    double startY;
    double endX = -1;
    double endY = -1;
};
/**
  *main status structure from which the tree is built which contains the line as its key
  */
struct status
{
  lineSegment l;
  struct status *left;
	struct status *right;
  int height;
};
/**
  *class statustree has the functions to insert and delete a line in the status tree and to find neighbours of either a point or a line
*/
class statustree
{
private:


public:
    /// globalinsert variable to signify inserting two nodes for each line
    int globalinsert;

    /// basic constructor
    statustree()
    {
      globalinsert = 0;
    }

    ///function to find height of a node
    int height(struct status *N)
    {
    	if (N == NULL)
    		return 0;
    	return N->height;
    }

    int max(int a, int b)
    {
    	return (a > b)? a : b;
    }
    /// function to create a new node
    struct status* newstatus(lineSegment newl)
    {
    	struct status* node = (struct status*)
    						malloc(sizeof(struct status));
    	node->l = newl;
    	node->left = NULL;
    	node->right = NULL;
    	node->height = 1;
    	return(node);
    }
    ///function to righrotate about a point
    struct status *rightRotate(struct status *y)
    {
    	struct status *x = y->left;
    	struct status *T2 = x->right;

    	x->right = y;
    	y->left = T2;

    	y->height = max(height(y->left), height(y->right))+1;
    	x->height = max(height(x->left), height(x->right))+1;


    	return x;
    }
    /// function to left rottate about a point.
    struct status *leftRotate(struct status *x)
    {
    	struct status *y = x->right;
    	struct status *T2 = y->left;

    	y->left = x;
    	x->right = T2;


    	x->height = max(height(x->left), height(x->right))+1;
    	y->height = max(height(y->left), height(y->right))+1;
    	return y;
    }
    ///function to find x co-ordinate of a line given the two end points and y co-ordinate
    double findx (lineSegment l, double y)
    {
      return ((y-l.endY)*((l.endX-l.startX)/(l.endY-l.startY)))+l.endX;
    }
    /// function to get balance factor which is the max difference between the leaf nodes
    int getBalance(struct status *N)
    {
    	if (N == NULL)
    		return 0;
    	return height(N->left) - height(N->right);
    }
    /// function to insert a new line
    struct status* insert(struct status* node, lineSegment newl, double ycor)
    {
      int *justinserted = &globalinsert;

    	if (node == NULL)
      {
        *justinserted = 1;
        return(newstatus(newl));
      }


        if (findx(newl,ycor) < findx(node->l,ycor))
        {
          node->left  = insert(node->left, newl,ycor);
          if(*justinserted == 1)
          {
            node->right = newstatus(node->l);
            node->l = newl;
            *justinserted = 0;
          }
        }
        else if (findx(newl,ycor) > findx(node->l,ycor))
        {
          // printf("Going right\n");
          node->right  = insert(node->right, newl,ycor);
          if(*justinserted == 1)
          {
            // printf("copying to left leaf\n");
            node->left = newstatus(node->l);
            *justinserted = 0;
          }
        }
        else
        {
          return node;
        }
        node->height = 1 + max(height(node->left),
      						height(node->right));

      	int balance = getBalance(node);
      	if (balance > 1 && findx(newl,ycor) < findx(node->left->l,ycor))
      		return rightRotate(node);

      	if (balance < -1 && findx(newl,ycor) > findx(node->right->l,ycor))
      		return leftRotate(node);

      	if (balance > 1 && findx(newl,ycor) > findx(node->left->l,ycor))
      	{
      		node->left = leftRotate(node->left);
      		return rightRotate(node);
      	}
      	if (balance < -1 && findx(newl,ycor) < findx(node->right->l,ycor))
      	{
      		node->right = rightRotate(node->right);
      		return leftRotate(node);
      	}

      	return node;
      }
      /// function to find the node with the min value for bst deletion
      struct status * minValueNode(struct status* node)
      {
          struct status* current = node;


          while (current->left != NULL)
              current = current->left;

          return current;
      }
      /// function to delete a line
      struct status* deleteNode(struct status* root, lineSegment newl, double ycor)
      {

          if (root == NULL)
              return root;

          if ( findx(newl,ycor) < findx(root->l,ycor))
              root->left = deleteNode(root->left, newl,ycor);


          else if( findx(newl,ycor) > findx(root->l,ycor))
              root->right = deleteNode(root->right, newl,ycor);

          else
          {
              // node with only one child or no child
              if( (root->left == NULL) || (root->right == NULL) )
              {
                  struct status *temp = root->left ? root->left :
                                                   root->right;

                  if (temp == NULL)
                  {
                      temp = root;
                      root = NULL;
                  }
                  else
                   *root = *temp;
                  free(temp);
              }
              else
              {

                  struct status* temp = minValueNode(root->right);

                  // Copy the inorder successor's data to this node
                  root->l = temp->l;
                  // Delete the inorder successor
                  root->right = deleteNode(root->right, temp->l, ycor);
              }
          }

          if (root == NULL)
            return root;


          root->height = 1 + max(height(root->left),
                                 height(root->right));


          int balance = getBalance(root);


          if (balance > 1 && getBalance(root->left) >= 0)
              return rightRotate(root);

          if (balance > 1 && getBalance(root->left) < 0)
          {
              root->left =  leftRotate(root->left);
              return rightRotate(root);
          }

          if (balance < -1 && getBalance(root->right) <= 0)
              return leftRotate(root);

          if (balance < -1 && getBalance(root->right) > 0)
          {
              root->right = rightRotate(root->right);
              return leftRotate(root);
          }

          return root;
      }
      /// function to print preorder fof current tree
      void preOrder(struct status *root)
      {
      	if(root != NULL)
      	{
      		printf("%f %f %f %f %d\n", root->l.startX, root->l.startY,root->l.endX,root->l.endY,root->height);
      		preOrder(root->left);
      		preOrder(root->right);
      	}
      }

      /// Get the left neighbor of a particular line segment from the status tree for STEP 12
      void getLeftNeighbor(struct status* node, lineSegment l, double ycor, struct lineSegment* lastRight){
        if(node->height == 1){
          if(lastRight->startX == -1){
            if(findx(node->l,ycor-0.1) < findx(l,ycor-0.1)){
              *lastRight = node->l;
            }
          }
          return;
        }
        if ((findx(l,ycor-0.1) - 0.1) < findx(node->l,ycor-0.1))
        {
          getLeftNeighbor(node->left, l, ycor, lastRight);
        }
        else if ((findx(l,ycor-0.1) - 0.1) > findx(node->l, ycor-0.1))
        {
          *lastRight = node->l;
          getLeftNeighbor(node->right, l, ycor, lastRight);
        }
      }

      /// Get the left neighbor of a particular line segment from the status tree for STEP 15
      void getRightNeighbor(struct status* node, lineSegment l, double ycor, struct lineSegment* lastLeft){
        if(node->height == 1){
          if (lastLeft->startX == -1) {
            if(findx(node->l,ycor-0.1) > findx(l,ycor-0.1)){
              *lastLeft = node->l;
            }
          }
          return;
        }
        if ((findx(l,ycor-0.1) + 0.1) < findx(node->l,ycor-0.1))
        {
          *lastLeft = node->l;
          getRightNeighbor(node->left, l, ycor, lastLeft);
        }
        else if ((findx(l,ycor-0.1) + 0.1) > findx(node->l, ycor-0.1))
        {
          getRightNeighbor(node->right, l, ycor, lastLeft);
        }
      }

      /// Get left and right neighboring segments of a point, STEP 9
      /// lastLeft is the right neighbor and lastRight is the left neighbor for the point
      void getNeighbors(struct status* node, double xcor, double ycor, struct lineSegment* lastRight, struct lineSegment* lastLeft){
        if(node->height == 1){
          if(lastRight->startX == -1){
            if(findx(node->l,ycor-0.1) <= xcor){
              *lastRight = node->l;
            }
          }
          if (lastLeft->startX == -1) {
            if(findx(node->l,ycor-0.1) > xcor){
              *lastLeft = node->l;
            }
          }
          return;
        }

        if (xcor < findx(node->l,ycor-0.1))
        {
          // printf("go left");
          *lastLeft = node->l;
          getNeighbors(node->left, xcor, ycor, lastRight, lastLeft);
        }
        else if (xcor > findx(node->l, ycor-0.1))
        {
          // printf("go right");
          *lastRight = node->l;
          if (node->right == NULL) {
            return;
          }
          
          getNeighbors(node->right, xcor, ycor, lastRight, lastLeft);
        }
      }

};

#endif
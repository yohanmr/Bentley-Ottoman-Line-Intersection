#ifndef EVENT_H
#define EVENT_H

#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include <iostream>
#include <GLFW/glfw3.h>
#include "status.h"
using namespace std;
/// Structure to represent eent queue
struct q
{
	double xc,yc;
	struct q *left;
	struct q *right;
  vector<lineSegment> U;
  vector<lineSegment> C;
  vector<lineSegment> L;
	int height;
};

/// a class that contains functions to delete and insert to the tree as well as find an event point
class event
{
private:

public:
  ///function to find height of a node
  int height(struct q *N)
  {
  	if (N == NULL)
  		return 0;
  	return N->height;
  }

  // Function to find maximum of two given numbers
  int max(int a, int b)
  {
  	return (a > b)? a : b;
  }

  /**
  * function to create a new node
  * value for teller
  * 1 - upper endpoint
  * 2 - lower endpoint
  * 3 - interior point
  */

  struct q* newq(double xc, double yc, double xs, double ys, double xe, double ye, int teller)
  {

  	struct q* node = (struct q*)calloc(1,sizeof(struct q));

  	node->xc = xc;
    node->yc = yc;
    struct lineSegment* l = (struct lineSegment*)malloc(sizeof(struct lineSegment));
    l->startX = xs;
    l->startY = ys;
    l->endX = xe;
    l->endY = ye;
    if(teller == 1)
    {
      node->U.push_back(*l);
    }
    else if(teller == 2)
    {
      node->L.push_back(*l);
    }
    else if(teller == 3){
      
      node->C.push_back(*l);
    }
  	node->left = NULL;
  	node->right = NULL;
  	node->height = 1;

  	return(node);
  }

  /// function to right rightRotate about a node to rebalance
  struct q *rightRotate(struct q *y)
  {
  	struct q *x = y->left;
  	struct q *T2 = x->right;

  	x->right = y;
  	y->left = T2;

  	y->height = max(height(y->left), height(y->right))+1;
  	x->height = max(height(x->left), height(x->right))+1;


  	return x;
  }
  /// function to right leftRotate about a node to rebalance

  struct q *leftRotate(struct q *x)
  {
  	struct q *y = x->right;
  	struct q *T2 = y->left;

  	y->left = x;
  	x->right = T2;


  	x->height = max(height(x->left), height(x->right))+1;
  	y->height = max(height(y->left), height(y->right))+1;
  	return y;
  }
  /// function used as a comparator for insertion and deletion
  int mygreater(double x1, double y1, double x2, double y2)
  {
    if(y1<y2)
    return 0;
    else if(y1>y2)
    return 1;
    else
    {
      if(x1>x2)
      return 0;
      else if(x1<x2)
      return 1;
    }
  }
  /// function used as a comparator for insertion and deletion
  int mylesser(double x1, double y1, double x2, double y2)
  {
    if(y1<y2)
    return 1;
    else if(y1>y2)
    return 0;
    else
    {
      if(x1>x2)
      return 1;
      else if(x1<x2)
      return 0;
    }
  }
  /// function to get balance factor of a node
  int getBalance(struct q *N)
  {
  	if (N == NULL)
  		return 0;
  	return height(N->left) - height(N->right);
  }
  /// function to insert a new event point
  struct q* insert(struct q* node, double xc, double yc, double xs, double ys, double xe, double ye,int teller)
  {
    // printf("start insert\n");
    if (node == NULL){
         //cout<<"hello"<<endl;
  		return(newq(xc,yc,xs,ys,xe,ye,teller));
    }

      if (yc < node->yc)
      {
        // printf("Going left\n");

        node->left  = insert(node->left, xc,yc,xs,ys,xe,ye,teller);
      }
      else if (yc > node->yc)
      {
        // printf("Going right\n");
        node->right  = insert(node->right, xc,yc,xs,ys,xe,ye,teller);
      }
      else if(xc > node->xc)
      {
        // printf("Going left\n");
        node->left  = insert(node->left, xc,yc,xs,ys,xe,ye,teller);
      }
      else if(xc < node->xc)
      {
        // printf("Going right\n");
        node->right  = insert(node->right, xc,yc,xs,ys,xe,ye,teller);
      }
      else
      {
        int counter = 1;
        if(teller==1)
        {
          for(unsigned int q=0;q<node->U.size();q++)
          {
            lineSegment l = node->U[q];
            if(l.startX == xs && l.startY == ys && l.endX == xe && l.endY == ye)
            counter = 0;
          }
          if(counter ==1)
          {
            struct lineSegment *l = (struct lineSegment*)malloc(sizeof(struct lineSegment));
            l->startX = xs;
            l->startY = ys;
            l->endX = xe;
            l->endY = ye;
            node->U.push_back(*l);
          }
        }
        else if (teller == 2)
        {
          for(unsigned int q=0;q<node->L.size();q++)
          {
            lineSegment l = node->L[q];
            if(l.startX == xs && l.startY == ys && l.endX == xe && l.endY == ye)
            counter = 0;
          }
          if(counter ==1)
          {
            struct lineSegment *l = (struct lineSegment*)malloc(sizeof(struct lineSegment));
            l->startX = xs;
            l->startY = ys;
            l->endX = xe;
            l->endY = ye;
            node->L.push_back(*l);
          }
        }
        else if(teller == 3)
        {
          for(unsigned int q=0;q<node->C.size();q++)
          {
            lineSegment l = node->C[q];
            if(l.startX == xs && l.startY == ys && l.endX == xe && l.endY == ye)
            counter = 0;
          }
          if(counter ==1)
          {
            struct lineSegment *l = (struct lineSegment*)malloc(sizeof(struct lineSegment));
            l->startX = xs;
            l->startY = ys;
            l->endX = xe;
            l->endY = ye;
            node->C.push_back(*l);
          }
        }
        if(counter == 0)
        return node;
      }


    // printf("begin balancing\n");
  	node->height = 1 + max(height(node->left),
  						height(node->right));


  	int balance = getBalance(node);

  	if (balance > 1 && mylesser(xc,yc,node->left->xc,node->left->yc))
  		return rightRotate(node);

  	if (balance < -1 && mygreater(xc,yc,node->right->xc,node->right->yc))
  		return leftRotate(node);

  	if (balance > 1 && mygreater(xc,yc,node->left->xc,node->left->yc))
  	{
  		node->left = leftRotate(node->left);
  		return rightRotate(node);
  	}
  	if (balance < -1 && mylesser(xc,yc,node->right->xc,node->right->yc))
  	{
  		node->right = rightRotate(node->right);
  		return leftRotate(node);
  	}
    // printf("done balancing\n");
  	return node;
  }
  /// function to find min vale node for bst deletion
  struct q * minValueNode(struct q* node)
  {
      struct q* current = node;


      while (current->left != NULL)
          current = current->left;

      return current;
  }
  /// function to find node to pop
  struct q * maxValueNode(struct q* node)
  {
      struct q* current = node;

      if (current == NULL) {
        return current;
      }


      /* loop down to find the rightmost leaf */
      while (current->right != NULL)
          current = current->right;

      return current;
  }
  /// function to delete the enent point that is to be popped
  struct q* deleteNode(struct q* root, double xc, double yc)
  {

      if (root == NULL)
          return root;

      if ( yc < root->yc )
          root->left = deleteNode(root->left, xc,yc);


      else if( yc > root->yc )
          root->right = deleteNode(root->right, xc,yc);

      else if (xc > root->xc)
          root->left = deleteNode(root->left,  xc,yc);
      else if (xc < root->xc)
          root->right = deleteNode(root->right, xc,yc);
      else
      {
          // node with only one child or no child
          if( (root->left == NULL) || (root->right == NULL) )
          {
              struct q *temp = root->left ? root->left :
                                               root->right;

              if (temp == NULL)
              {
                  // printf("Deleting last element\n");
                  temp = root;
                  root = NULL;
              }
              else
               *root = *temp;
              free(temp);
          }
          else
          {

              struct q* temp = minValueNode(root->right);

              // Copy the inorder successor's data to this node
              root->xc = temp->xc;
              root->yc = temp->yc;
              root->U = temp->U;
              root->C = temp->C;
              root->L = temp->L;
              // Delete the inorder successor
              root->right = deleteNode(root->right, temp->xc , temp->yc);
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
  /// function to print preorder of current tree
  void preOrder(struct q *root)
  {
  	if(root != NULL)
  	{
  		printf("%f %f %d\n",root->xc, root->yc,root->height);

      for(size_t i = 0; i < root->U.size(); i++)
      {
        printf(" U:%f %f %f %f\n", root->U[i].startX, root->U[i].startY, root->U[i].endX, root->U[i].endY);
      }

      for(size_t i = 0; i < root->L.size(); i++)
      {
        printf(" L:%f %f %f %f\n", root->L[i].startX, root->L[i].startY, root->L[i].endX, root->L[i].endY);
      }
      for(size_t i = 0; i < root->C.size(); i++)
      {
        printf(" C:%f %f %f %f\n", root->C[i].startX, root->C[i].startY, root->C[i].endX, root->C[i].endY);
      }
      
  		preOrder(root->left);
  		preOrder(root->right);
  	}
  }
};

#endif

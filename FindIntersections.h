#ifndef ALGO_H
#define ALGO_H

#include <algorithm>
#include <queue>
#include "status.h"
#include "event.h"
#include <iostream>

using namespace std;

/// struct to represent a point
struct point
{
    double x;
    double y;
};

class FindIntersections
{
    private:
        /// initialise eventQueue and status
        event eventQueue;
        struct q *eventQueueRoot = NULL;
        statustree status = statustree();
        struct status *statusRoot = NULL;
    public:
        /// constructor to initialise event queue and status
        FindIntersections( vector<lineSegment> &segmentVector ){
            for(size_t i = 0; i < segmentVector.size(); i++)
            {   
                float startx, starty, endx, endy;
                if(segmentVector[i].startY >= segmentVector[i].endY){
                    startx = segmentVector[i].startX;
                    starty = segmentVector[i].startY;
                    endx = segmentVector[i].endX;
                    endy = segmentVector[i].endY;
                } else {
                    startx = segmentVector[i].endX;
                    starty = segmentVector[i].endY;
                    endx = segmentVector[i].startX;
                    endy = segmentVector[i].startY;
                }
                if (segmentVector[i].startY == segmentVector[i].endY ) {
                    if (segmentVector[i].startX <= segmentVector[i].endX) {
                        startx = segmentVector[i].startX;
                        starty = segmentVector[i].startY;
                        endx = segmentVector[i].endX;
                        endy = segmentVector[i].endY;
                    } else {
                        startx = segmentVector[i].endX;
                        starty = segmentVector[i].endY;
                        endx = segmentVector[i].startX;
                        endy = segmentVector[i].startY;
                    }
                    
                }
                
                // printf("%f %f %f %f\n", startx, starty, endx, endy);             
                
                /// insert end points into the event queue.
                eventQueueRoot = eventQueue.insert( eventQueueRoot, startx, starty, startx, starty, endx, endy, 1);
                eventQueueRoot = eventQueue.insert( eventQueueRoot, endx, endy, startx, starty, endx, endy, 2);
            }
        }
        /**
        * Given three colinear points p, q, r, the function checks if 
        * point q lies on line segment 'pr' 
        */
        bool onSegment(point p, point q, point r) 
        { 
            if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
                q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
            return true; 
        
            return false; 
        } 
        /**
        * To find orientation of ordered triplet (p, q, r). 
        * The function returns following values 
        * 0 --> p, q and r are colinear 
        * 1 --> Clockwise 
        * 2 --> Counterclockwise 
        */
        int orientation(point p, point q, point r) 
        { 
            float val = (q.y - p.y) * (r.x - q.x) - 
                    (q.x - p.x) * (r.y - q.y); 
        
            if (val == 0) return 0;  // colinear 
        
            return (val > 0)? 1: 2; // clock or counterclock wise 
        } 
        /**
        * The main function that returns true if line segment 'p1q1' 
        * and 'p2q2' intersect.
        */
        bool doIntersect(lineSegment l1, lineSegment l2)
        { 
            struct point p1, q1, p2, q2;
            p1.x = l1.startX;
            p1.y = l1.startY;
            q1.x = l1.endX;
            q1.y = l1.endY;
            p2.x = l2.startX;
            p2.y = l2.startY;
            q2.x = l2.endX;
            q2.y = l2.endY;
            /// Find the four orientations needed for general and special cases 
            int o1 = orientation(p1, q1, p2); 
            int o2 = orientation(p1, q1, q2); 
            int o3 = orientation(p2, q2, p1); 
            int o4 = orientation(p2, q2, q1); 
        
            /// General case 
            if (o1 != o2 && o3 != o4) 
                return true; 
        
            /// Special Cases 
            /// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
            if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
        
            /// p1, q1 and q2 are colinear and q2 lies on segment p1q1 
            if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
        
            /// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
            if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
        
            /// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
            if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
        
            return false; // Doesn't fall in any of the above cases 
        } 

        point intersectionOf(lineSegment l1, lineSegment l2){
            
            point intersection;
            if (doIntersect(l1, l2) == 0) 
            { 
                /// The line segments do not intersect.
                intersection.x = -1;
                intersection.y = -1;
            } 
            else
            {   
                /// Line l1 represented as a1x + b1y = c1 
                double a1 = l1.endY - l1.startY; 
                double b1 = l1.startX - l1.endX; 
                double c1 = a1*(l1.startX) + b1*(l1.startY); 
            
                /// Line l2 represented as a2x + b2y = c2 
                double a2 = l2.endY - l2.startY; 
                double b2 = l2.startX - l2.endX; 
                double c2 = a2*(l2.startX) + b2*(l2.startY); 
            
                double determinant = a1*b2 - a2*b1; 
                intersection.x = (b2*c1 - b1*c2)/determinant; 
                intersection.y = (a1*c2 - a2*c1)/determinant;
            }
            return intersection;
        }

        void findNewEvent(lineSegment sl, lineSegment sr, struct q* p){
            ///find intersection point of sl and sr
            struct point newEventPoint = intersectionOf(sl, sr);
            // printf("intersection point of %f %f %f %f AND %f %f %f %f: %f %f\n", sl.startX, sl.startY, sl.endX, sl.endY, sr.startX, sr.startY, sr.endX, sr.endY, newEventPoint.x, newEventPoint.y);
            if (newEventPoint.y != -1) {
                if(newEventPoint.y < p->yc){
                    eventQueueRoot = eventQueue.insert( eventQueueRoot, newEventPoint.x, newEventPoint.y, sl.startX, sl.startY, sl.endX, sl.endY, 3);
                    eventQueueRoot = eventQueue.insert( eventQueueRoot, newEventPoint.x, newEventPoint.y, sr.startX, sr.startY, sr.endX, sr.endY, 3);
                } else if(newEventPoint.y == p->yc && newEventPoint.x > p->xc){
                    eventQueueRoot = eventQueue.insert( eventQueueRoot, newEventPoint.x, newEventPoint.y, sl.startX, sl.startY, sl.endX, sl.endY, 3);
                    eventQueueRoot = eventQueue.insert( eventQueueRoot, newEventPoint.x, newEventPoint.y, sr.startX, sr.startY, sr.endX, sr.endY, 3);
                }
            }
            
            

            
        }

        int contains(vector<lineSegment> x, lineSegment l){
            for(size_t i = 0; i < x.size(); i++)
            {
                if(x[i].startX == l.startX && x[i].startY == l.startY && x[i].endX == l.endX && x[i].endY == l.endY){
                    return 0;
                }
            }
            return 1;
        }

        vector<lineSegment> unionOf(vector<lineSegment> a, vector<lineSegment> b){
            vector<lineSegment> unionVec;
            for(size_t i = 0; i < a.size(); i++)
            {
                unionVec.push_back(a[i]);
            }
            for(size_t i = 0; i < b.size(); i++)
            {
                if(contains(unionVec, b[i]) == 1){
                    unionVec.push_back(b[i]);
                }
            }
            return unionVec;
        }

        int empty(vector<lineSegment> x){
            if(x.size() == 0){
                return 1;
            } else {
                return 0;
            }
        }

        /// handle each event point popped from the event queue
        void handleEventPoint(struct q* eventPoint){

            /// Union of Lp, Up and Cp
            vector<lineSegment> all = unionOf(eventPoint->L, unionOf(eventPoint->U, eventPoint->C));

            if (all.size() > 1) {
                // p is an intersection
                printf("Intersection: %f %f\n", eventPoint->xc, eventPoint->yc);
            }
            /// delete elements of Lp union Cp from status
            vector<lineSegment> temp1 = unionOf(eventPoint->L, eventPoint->C);
            for(size_t i = 0; i < temp1.size(); i++)
            {
                // printf("delete line: %f %f %f %f\n",temp1[i].startX,temp1[i].startY, temp1[i].endX, temp1[i].endY);
                statusRoot = status.deleteNode(statusRoot, temp1[i], eventPoint->yc);
            }
            // printf("point: %f %f\n", eventPoint->xc, eventPoint->yc);
            // printf("after deleting:\n");
            // status.preOrder(statusRoot);
            
            ///insert segments in Up union Cp into status according to their position just below the sweep line
            vector<lineSegment> temp2 = unionOf(eventPoint->U, eventPoint->C);
            for(size_t i = 0; i < temp2.size(); i++)
            {
                statusRoot = status.insert(statusRoot, temp2[i], (eventPoint->yc - 0.1));
            }
            // printf("after reinserting:\n");
            // status.preOrder(statusRoot);

            /// check if Up union Cp is empty
            if(empty(temp2) == 1){
                struct lineSegment sl, sr;
                sl.startX = -1;
                sr.startX = -1;
                // status.preOrder(statusRoot);
                status.getNeighbors(statusRoot, eventPoint->xc, (eventPoint->yc)-0.1, &sl, &sr);
                // if(sl.startX != -1){
                //     if (sr.startX != -1) {
                //         findNewEvent(sl, sr, eventPoint);
                //     }
                // }
            } else {
                struct lineSegment sll, srr;
                float max = -1.0, min = 1001.0; 
                for(size_t i = 0; i < temp2.size(); i++)
                {
                    float x = status.findx(temp2[i], eventPoint->yc);
                    float minX = (temp2[i].startX < temp2[i].endX) ? temp2[i].startX : temp2[i].endX;
                    float maxX = (temp2[i].startX > temp2[i].endX) ? temp2[i].startX : temp2[i].endX;
                    if (x < min && x <= maxX && x >= minX) {
                        min = x;
                        sll = temp2[i];
                    }
                    if(x > max  && x <= maxX && x >= minX){
                        
                        max = x;
                        srr = temp2[i];
                    }
                    
                }
  
                struct lineSegment sl, sr;
                sl.startX = -1;
                sr.startX = -1;
                status.getLeftNeighbor(statusRoot, sll, eventPoint->yc, &sl);
                status.getRightNeighbor(statusRoot , srr, eventPoint->yc, &sr);
                
                if(sl.startX != -1 && min != 1001){
                    findNewEvent(sl, sll, eventPoint);
                }
                if(sr.startX != -1 && max != -1){
                    findNewEvent(srr, sr, eventPoint);
                }
            }
            

        }

        /// Run the algorithm to find the line intersections
        void runAlgorithm(){
            while(eventQueueRoot != NULL){
                struct q* pop = eventQueue.maxValueNode(eventQueueRoot);
                if (pop != NULL) {
                   handleEventPoint(pop); 
                   eventQueueRoot = eventQueue.deleteNode(eventQueueRoot, pop->xc, pop-> yc);
                }
                
            }
            printf("\nExecution complete\n");
        }

};

#endif
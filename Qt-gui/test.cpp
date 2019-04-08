#include <iostream> 
#include <vector>
#include <cstdlib>
#include <climits>
#include <cmath>
#include "FindIntersections.h"

int main(int argc, char const *argv[]){
    //Initializing the points
    srand(14);
    vector<lineSegment> segmentVector;
    vector<int> points_idx;
    int range=atoi(argv[1]);
    int num_point=0;
    while(num_point!=range){
        double x1=3*((double)(rand()%range))/((rand()%range));
        double y1=3*((double)(rand()%range))/((rand()%range));
        double x2=3*((double)(rand()%range))/((rand()%range));
        double y2=3*((double)(rand()%range))/((rand()%range));
        if(isinf(x1) || isinf(y1) || isinf(x2) || isinf(y2)){
            // cout<<num_point<<endl;
            // cout<<"Infinity found in input: "<<x<<", "<<y<<endl;
            continue;
            //exit(0);
        }
        /*if(x*x+y*y>3){
            continue;
        }*/
        //cout<<x<<","<<y<<endl;
        int idx=num_point;
        num_point++;
        //cin>>x>>y;
        lineSegment l1;
        l1.startX = x1;
        l1.startY = y1;
        l1.endX = x2;
        l1.endY = y2;
        segmentVector.push_back(l1);
    }

    FindIntersections findIntersection = FindIntersections(segmentVector);
    findIntersection.runAlgorithm();

    return 0;
}
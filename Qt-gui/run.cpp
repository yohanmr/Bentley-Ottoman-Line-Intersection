#include <fstream>
#include "FindIntersections.h"
#include <iostream>

using namespace std;

int main(){
    vector<lineSegment> segmentVector;

    ifstream myfile;
    myfile.open("lines.txt");

    double x1, y1, x2, y2;
    while( myfile >> x1 >> y1 >> x2 >> y2 ){
        lineSegment l1;
        l1.startX = x1;
        l1.startY = y1;
        l1.endX = x2;
        l1.endY = y2;
        segmentVector.push_back(l1);
    }

    myfile.close();
    // cout << endl << endl;
    // for(int i = 0; i < segmentVector.size(); i++)
    // {
    //     cout << segmentVector[i].startX << " " << segmentVector[i].startY << " " << segmentVector[i].endX << " " << segmentVector[i].endY << endl;
    // }

  //  cout << endl << "Points of intersections are : \n";
    FindIntersections findIntersection = FindIntersections(segmentVector);
    findIntersection.runAlgorithm();
}

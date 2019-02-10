#include "gridFiles.h"
#include <math.h>
#include <fstream>

int x, y, numberOfX, numberOfY;
int *mapperX, *mapperY; 
int numberOfPoints;

int main(){
    int choice = 1, p, i;
    cout << "Enter the Maximum X coordinate of the area : ";
    cin >> MAX_X;
    cout << "Enter the Maximum Y coordinate of the area : ";
    cin >> MAX_Y;
    
    cout << "Enter Bucket Size : ";
    cin >> BUCKET_SIZE;

    // Mapper Size Calculate

    numberOfX = 2;
    numberOfY = 2;
    
    /**
     * @brief pointsArr [i][j]
     * 
     * j -> 0 : number of Points, 1 : fileName, 2 : parentIndex, 3 : child Index
     */
    int mapperXArray[MAX_X + 1], mapperYArray[MAX_Y + 1];
    // int pointsArr[MAX_X * MAX_Y + 1][4];

    // points = pointsArr;
    // for(i = 0; i < MAX_X * MAX_Y + 1; i++){
    //     points[i] = pointsArr[i];
    // }
    points = new int*[MAX_X * MAX_Y + 1];
    for(i = 0; i < MAX_X * MAX_Y + 1; i++){
        points[i] = new int[4];
    }
    mapperX = mapperXArray;
    mapperY = mapperYArray;

    initialize();    

    // ifstream dataFileHandler(dataPointfile);
    int pointId, pointX, pointY;

    // while(dataFileHandler >> pointId >> pointX >> pointY){
    //     insertPoint(pointId, pointX, pointY);
    // }
    // dataFileHandler.close();

    // while(choice != 2){
    //     cout << "Menu\n1. KNN Query\n2. Exit\nEnter your choice : ";
    //     cin >> choice;
    //     switch(choice){
    //         case 1:
    //             cout << "Enter required number of nearest points : ";
    //             cin >> p;
    //             knnQuery(p);
    //             break;
    //         case 2:
    //             break;
    //         default:
    //             cout << "Invalid Choice! Enter a valid choice...!\n";
    //     }
    // }

    updateMapper(2, true);
    updateMapper(1, true);
    updateMapper(4, false);
    updateMapper(2, false);
    updateMapper(8, true);
    updateMapper(6, false);
    updateMapper(6, true);
    return 0;
}

int createBucket(){

    fileName++;
    auto file = bucketDirectory + to_string(fileName) + ".txt";
    ofstream f(file);
    f.close();
    return fileName;
}

void insertPoint(int id, int pointX, int pointY){

    /**
     * TODO 
     * 1. Update mapper after insertion of the point
     * 2. Insert point with 3 cases
     *      a. Insert if the bucket has some space (update all the points increment in all the points in PointArray)
     *      b. Insert if the bucket to be split's parent == him own and child == him own, then create a new split depending upon the medium and insert all the points
     *      c. Otherwise open doors for appropirate bucket and add the points into that bucket. (no need to split here)
     * 
     */

    int fiName, x = -1, y = -1;
    for(int i = 0; i < numberOfX; i++){
        if(mapperX[i] <= pointX && mapperX[i+1] >= pointX){
            x = i;
            break;
        }
    }
    for(int i = 0; i < numberOfY; i++){
        if(mapperY[i] <= pointY && mapperY[i+1] >= pointY){
            y = i;
            break;
        }
    }
    int index = (x * numberOfY) + y + 1;
    fiName = points[index][1];
    int prevFiName = points[points[index][2]][1];
    
    if(points[index][0] > 0 && (points[index][0] % BUCKET_SIZE) == 0){
        if(points[index][2] == index && points[index][3] == index){
            // Case b.
            // TODO find median, division axis and division point
        }
        else{
            // Case c.
            // TODO find appropriate point for split and rearrange the points in the pointsArr

        }
    }
    auto file = bucketDirectory + to_string(fiName) + ".txt";
    ofstream f(file, fstream::app);
    f << id << " " << pointX << " " << pointY << endl;
    points[prevFiName]++;
    f.close();
}

void initialize(){
    // int z = numberOfX * numberOfY + 1;
    numberOfPoints = 1;
    // for(int i = 1; i < z; i++){
    //     points[i][0] = -1;
    //     points[i][1] = -1;
    //     points[i][2] = -1;
    //     points[i][3] = -1;
    //     createBucket();
    // }

    for(int i = 0; i <= MAX_X; i++){
        mapperX[i] = -1;
    }
    for(int i = 0; i <= MAX_Y; i++){
        mapperY[i] = -1;
    }
    mapperX[0] = 0;
    mapperY[0] = 0;
    mapperX[1] = MAX_X;
    mapperY[1] = MAX_Y;

    points[0][0] = 112;
    points[0][1] = 1;
    points[0][2] = 0;
    points[0][3] = 0;
    createBucket();
}

/**
 * @brief 
 * 
 * @param point 
 * @param isX 
 *          @value true     parallel to y axis
 *          @value false    parallel to x axis
 */
void updateMapper(int point, bool isX){
    // TODO check for point disfunctioning sometimes above and sometimes below
    int *ptr, n, i, division, z, j, k, loop;
    if(isX == true){
        ptr = mapperX;
        n = numberOfX;
        numberOfX++;
    }
    else{
        ptr = mapperY;
        n = numberOfY;
        numberOfY++;
    }
    for(i = n - 1; i >= 0; i--){
        if(point < ptr[i]){
            ptr[i+1] = ptr[i];
        }
        else{
            break;
        }
    }
    i++;
    ptr[i] = point;
    j = i;
    // TODO update corresponding Points Array AIM where to divide and how much to divide for shifting
    // if isX = true then 
    // TODO return the index of the points being updated

    if(isX == true){
        // TODO Check
        z = numberOfPoints + (numberOfY - 1) - 1;
        loop =  (numberOfX - 1)*(numberOfY - 1) - (numberOfX - j) * (numberOfY - 1);
        for(i = numberOfPoints - 1; i >= loop; i--){
            points[z][0] = points[i][0];
            points[z][1] = points[i][1];
            points[z][2] = points[i][2];
            z--;
        }
        for(i = 1; i < numberOfY; i++){
            // TODO change to appropriate values
            fileName++;
            points[z][0] = point;
            points[z][1] = fileName;
            points[z][2] = -1;
            points[z][3] = -1;
            z--;
        }
        
        numberOfPoints += (numberOfY - 1);
    }
    else if(isX == false){
        // create array of old size
        int newArray[ numberOfPoints ][ 4 ];
        for(i = 0; i < numberOfPoints; i++){
            newArray[i][0] = points[i][0];
            newArray[i][1] = points[i][1];
            newArray[i][2] = points[i][2];
            newArray[i][3] = points[i][3];
        }

        numberOfPoints += (numberOfX - 1);
        k = 0;
        // j++;
        int bal = 0;
        for(i = 0; i < numberOfPoints; i++){
            if(bal == j){
                // TODO change to approriate values
                fileName++;
                points[i][0] = point;
                points[i][1] = fileName;
                points[i][2] = -1;
                points[i][3] = -1;
            }
            else{
                points[i][0] = newArray[k][0];
                points[i][1] = newArray[k][1];
                points[i][2] = newArray[k][2];
                points[i][3] = newArray[k][3];
                k++;
            }
            bal++;
            if(bal == (numberOfY - 1)){
                bal = 0;
            }
        }
        cout << " Done" ;
    }
}
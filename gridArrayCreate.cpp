#include "gridArray.h"
#include <math.h>
#include <fstream>

int x, y, numberOfX, numberOfY;
int *mapperX, *mapperY; 

int main(){
    int choice = 1, p;
    cout << "Enter the Maximum X coordinate of the area : ";
    cin >> MAX_X;
    cout << "Enter the Maximum Y coordinate of the area : ";
    cin >> MAX_Y;
    
    cout << "Enter the x length of grid : ";
    cin >> x;
    cout << "Enter the y length of grid : ";
    cin >> y;
    
    cout << "Enter Bucket Size : ";
    cin >> BUCKET_SIZE;

    // Mapper Size Calculate

    numberOfX = ceil(MAX_X / x);
    numberOfY = ceil(MAX_Y / y);
    cout << "Number of X : " << numberOfX;
    cout << "\nNumber of Y : " << numberOfY;
    int mapperXArray[numberOfX], mapperYArray[numberOfY];
    int pointsArr[numberOfX * numberOfY + 1];
    points = pointsArr;
    mapperX = mapperXArray;
    mapperY = mapperYArray;

    initialize();    

    ifstream dataFileHandler(dataPointfile);
    int pointId, pointX, pointY;

    while(dataFileHandler >> pointId >> pointX >> pointY){
        insertPoint(pointId, pointX, pointY);
    }
    dataFileHandler.close();

    while(choice != 2){
        cout << "Menu\n1. KNN Query\n2. Exit\nEnter your choice : ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter required number of nearest points : ";
                cin >> p;
                knnQuery(p);
                break;
            case 2:
                break;
            default:
                cout << "Invalid Choice! Enter a valid choice...!\n";
        }
    }
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

    int fiName = findFileName(pointX, pointY);
    int prevFiName = fiName;
    
    if(points[fiName] > 0 && (points[fiName] % BUCKET_SIZE) == 0){
        
        fiName = goToLastBucket(fiName);
        auto fileN = bucketDirectory + to_string(fiName) + ".txt";
        ofstream f(fileN, fstream::app);
        fileName++;
        f << "-1 " << "-1 " << fileName;
        f.close();

        fiName = fileName;
    }
    else if(points[fiName] > BUCKET_SIZE){
        fiName = goToLastBucket(fiName);
    }
    auto file = bucketDirectory + to_string(fiName) + ".txt";
    ofstream f(file, fstream::app);
    f << id << " " << pointX << " " << pointY << endl;
    points[prevFiName]++;
    f.close();
}

int findFileName(int pointX, int pointY){
    // using mapper return fileName
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
    fiName = (x * numberOfY) + y + 1;
    return fiName;
}

int goToLastBucket(int file){
    float a = points[file];
    float b = BUCKET_SIZE;
    int looper = ceil(a / b);
    int x,y,id;
    for(int i = 0; i < looper - 1; i++){
        auto fileN = bucketDirectory + to_string(file) + ".txt";
        ifstream f(fileN);

        while(f >> id >> x >> y){
            if(id == -1){
                file = y;
            }
        }
        f.close();
    }
    return file;
}

void initialize(){
    int z = numberOfX * numberOfY + 1;
    for(int i = 1; i < z; i++){
        points[i] = 0;
        createBucket();
    }

    // Linear Array for mapper so first index of mapper[i][j] is equivalent to mapperX[i] and mapperY[j]
    for(int i = 0; i <= numberOfX; i++){
        mapperX[i] = i * x;
        for(int j = 0; j <= numberOfY; j++){
            mapperY[j] = j * y;
        }
    }
}
#include<bits/stdc++.h>
#include<string>
using namespace std;

int BUCKET_SIZE;
int MAX_X, MAX_Y;
int fileName = 0;
int **points;
string bucketDirectory = "buckets/";
string dataPointfile = "dataPoints.txt";

void initialize();
int createBucket();
void insertPoint(int, int, int);
void updateMapper(int, bool);
int findFileName(int,int);
int goToLastBucket(int);
void createGridFiles();

void knnQuery(int);
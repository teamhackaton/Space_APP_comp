#include <iostream>
#include <cstdlib>
#include<string>
#include<bits/stdc++.h>
#include<ctime>
using namespace std;
int* getSleepStartTime();
bool startHeating(int *start);
double getTemperatureLevel();
void turnOffHeaters();
int main()
{
    cout << "Hello";
    bool check=startHeating(getSleepStartTime());
    while(getTemperatureLevel()>25 || getTemperatureLevel()<23)
        cout << "Not warm enough";
    turnOffHeaters();
    return 0;
}

int *getSleepStartTime(){
    srand(time(0));
    static int randtime[3];
    randtime[0]=rand()%24;
    randtime[1]=rand()%60;
    randtime[2]=rand()%60;
    return randtime;
}
void turnOnHeaters()
{

}
void turnOffHeaters()
{

}
bool startHeating(int *start)
{
    time_t now=time(0);
    static int current[3];
    tm *date=localtime(&now);
    current[0]=date->tm_hour;
    current[1]=date->tm_min;
    current[2]=date->tm_sec;
    int diff[3]={start[0]-current[0],start[1]-current[1],start[2]-current[2]};
    if(diff[0]==1 && diff[1]==0 && diff[2]==0)
    {
        turnOnHeaters();
        return true;
    }
    else
        return false;
}

double getTemperatureLevel()
{
    double sensor1,sensor2,sensor3,avgtemperature;
    srand(time(0));
    sensor1=rand()%(26-18+1)+18;
    sensor2=rand()%(27-18+1)+18;
    sensor3=rand()%(26-18+1)+18;
    avgtemperature=(sensor1+sensor2+sensor3)/3;
    return avgtemperature;
}

#include <iostream>

using namespace std;

int main()
{

    if(getTemperatureLevel()>25 || getTemperatureLevel()<23)
        turnOnHeaters();
    while(getTemperatureLevel()>25 || getTemperatureLevel()<23)
        cout << "Not warm enough";
    turnOffHeaters();
    return 0;
}

void turnOnHeaters()
{

}
void turnOffHeaters()
{

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

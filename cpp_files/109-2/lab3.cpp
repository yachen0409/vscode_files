#include <cstdlib>
#include <iostream>
#define PI 3.14
using namespace std;

class Shape
{
protected:
    float volume;
    
public:
    Shape() { volume = 0; }
    virtual void computeVolume() = 0;
    void printVolume()
    {
        cout << volume << endl;
    }
};
class Cuboid : public Shape
{
    private:
        float a, b,c;
    public:
    Cuboid(float x,float y,float z){
        a=x;
        b=y;
        c=z;
    }
    void computeVolume(){
        volume = a*b*c;
    } 

};
class Pyramid : public Shape
{
    private:
    float a, b;
    public:
    Pyramid(float x,float y){
        a=x;
        b=y;
    }
    void computeVolume(){
        volume = a * b / 3;
    } 
};
class Sphere : public Shape
{
    private:
    float a;
    public:
    Sphere(float x){
        a=x;
    }
    void computeVolume(){
        volume = a*a*a*3.14*(4/3);
    } 
};

int main()
{
    float a, b, c;
    Shape *shape;

    cin >> a >> b >> c; // Enter the height and width of Rectangle
    Cuboid cub(a, b, c);

    cin >> a >> b; // Enter the bottom and height of Triangl
    Pyramid pyr(a, b);

    cin >> a; // Enter the radius of Circle
    Sphere sph(a);
    shape = &cub;
    shape->computeVolume();
    shape->printVolume();
    shape = &pyr;
    shape->computeVolume();
    shape->printVolume();
    shape = &sph;
    shape->computeVolume();
    shape->printVolume();
    return 0;
}

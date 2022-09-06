#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <math.h>
#include <random>
#include <execution>


struct Vector2
{    

public:

    float x_;
    float y_;

    Vector2() : x_(0), y_(0) {}

    Vector2(float x, float y) : x_(x), y_(y) {}

    inline float GetLenght() const
    {
        return std::sqrt(x_ * x_ + y_ * y_);
    }

    inline Vector2 Normalize() const
    {
        return Vector2(x_ / GetLenght(), y_ / GetLenght());
    }

    Vector2 operator-(const Vector2 other)
    {
        return Vector2(x_ - other.x_, y_ - other.y_);
    }
};

float Dot(const Vector2 v1, const Vector2 v2)
{
    return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}

struct Unit
{

public:
    Vector2 location_;
    Vector2 direction_;
    float sightRadius_;
    float sightSector_;

    int visibleUnitsCount;

    Unit(Vector2 location, Vector2 direction) : location_(location), direction_(direction), sightRadius_(2), sightSector_(135.5) {}

    inline Vector2 GetLocation() const
    {
        return location_;
    }

    inline Vector2 GetDirection() const
    {
        return direction_;
    }

    void FindVisibleUnits(std::vector<Unit> units)
    {
        visibleUnitsCount = std::count_if(std::execution::par, units.begin(), units.end(), [&](Unit u)
        {
            float otherUnitDistance = (u.location_ - location_).GetLenght();

            Vector2 otherUnitDirection = (u.location_ - location_).Normalize();

            auto angle = std::acos(Dot(direction_, otherUnitDirection)) * 180 / 3.1415;

            return otherUnitDistance < sightRadius_ && angle < sightSector_ / 2;
        });
    }
};

Vector2 GenerateCoord(std::mt19937& generator, int max_coord) 
{
	const auto x = std::uniform_int_distribution(1, max_coord)(generator);
    const auto y = std::uniform_int_distribution(1, max_coord)(generator);

	return Vector2(x, y);
}

int main() 
{
    std::mt19937 generator;
    std::vector<Unit> units;

    for(auto i = 0; i < 10000; i++)
    {
        units.emplace(units.end(), GenerateCoord(generator, 100), GenerateCoord(generator, 100).Normalize());
    }

    //units.push_back(Unit(Vector2(1, 1), Vector2(0, 1)));
    //units.push_back(Unit(Vector2(1, 2), Vector2(1, 0)));
    //units.push_back(Unit(Vector2(-5, -1), Vector2(0.707, 0.707)));

    int id = 0;

    for(auto& u : units)
    {
        u.FindVisibleUnits(units);
        std::cout << "Unit" << id << " sight " << u.visibleUnitsCount << '\n';

        id++;
    }   
}
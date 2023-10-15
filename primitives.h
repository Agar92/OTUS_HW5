/*!
 * \file primitives.h
 * Implementation of geometric primitives
 */
#pragma once

#include <string>
#include <cmath>

using std::string;

/*! \brief An enum to identify color of geometric primitives */
enum class Color{
	Red,  /**< 1 Red */
	Green,/**< 2 Green */
	Blue  /**< 3 Blue */
};

//! 2D (x,y) geometric point implementation structure
struct Point{
	//! structure Point constructor
	/*! Constructor parameters:
	 *  \param[in] _x   x-coordinate
	 *  \param[in] _y   y-coordinate
	 */
	Point(double _x, double _y):x(_x),y(_y){}
	double x;/*!< point x-coordinate */
	double y;/*!< point y-coordinate */
	//! definition of operator+ for the Point structure
	Point operator+(Point rhs){
		return Point((x+rhs.x)/2, (y+rhs.y)/2);
	}
	//! definition of operator/ for the Point structure
	Point operator/(int a){
		return Point(x/2, y/2);
	}
};

//! Interface for a geometric primitive object
class IPrimitive{
public:
	//! IPrimitive constructor
	/*! 
	 *  @param _name     name of the geometric primitive
	 *  @param _center   (x,y)-coordinates of the geometric primitive
	 */ 
	IPrimitive(const string & _name, Point _center = {1.0,1.0}) : name(_name), center(_center){}
	//! returns the name of the geometric primitive
	virtual string GetName() const = 0;
protected:
	const string name;/*!< geometric primitive name */
	Point center;     /*!< (x,y)-coordinates of the geometric primitive center */
};

//! Circle geometric primitive class
class Circle : public IPrimitive {
public:
	//! Circle constructor
	/*! 
	 *  @param _radius   radius
	 *  @param color     color
	 *  @param center    (x,y)-coordinates of the geometric primitive
	 */
	Circle(double _radius=10.0, Color color=Color::Blue, Point center = {1.0,1.0}) :
	       IPrimitive("Circle", center), radius(_radius){}
	//! returns the name of the geometric primitive
	string GetName() const override {return name;}
private:
	double radius;
};

//! Interface for polygon geometric primitive objects
class Polygon : public IPrimitive {
public:
	//! IPrimitive constructor
	/*! 
	 *  @param _name        name of the geometric primitive
	 *  @param numvertices  number of vertices
	 *  @param _color       color
	 *  @param _center      (x,y)-coordinates of the geometric primitive
	 */
	Polygon(const string& _name, int numvertices, Color _color, Point _center):
	        IPrimitive(_name, _center), NumberOfVertices(numvertices), color(_color) {}
	//! returns the name of the geometric primitive
	string GetName() const override {return name;}
	//! returns the number of the geometric primitive vertices
	virtual int GetNumberOfVertices() const {return NumberOfVertices;}
private:
	const int NumberOfVertices;
	Color color;
};

//! Triangle geometric primitive class
class Triangle : public Polygon {
public:
	//! Triangle constructor
	/*! 
	 *  @param w        width
	 *  @param h        height
	 *  @param color     color
	 *  @param center    (x,y)-coordinates of the geometric primitive
	 */
	Triangle(double w=20.0, double h=30.0, Color color=Color::Blue, Point center = {1.0,1.0}) :
	         Polygon("Triangle", 3, color, center), width(w), height(h) {}
private:
	double width, height;
};

//! Rectangle geometric primitive class
class Rectangle : public Polygon {
public:
	//! Rectangle constructor
	/*! 
	 *  @param w        width
	 *  @param h        height
	 *  @param color     color
	 *  @param center    (x,y)-coordinates of the geometric primitive
	 */
	Rectangle(double w=20.0, double h=30.0, Color color=Color::Blue, Point center = {1.0,1.0}) :
	          Polygon("Rectangle", 4, color, center), width(w), height(h) {}
private:
	double width, height;
};

//! Square geometric primitive class
class Square : public Polygon {
public:
	//! Square constructor
	/*! 
	 *  @param w        square side length
	 *  @param color     color
	 *  @param center    (x,y)-coordinates of the geometric primitive
	 */
	Square(double w=20.0, Color color=Color::Blue, Point center = {1.0,1.0}) :
	       Polygon("Square", 4, color, center), width(w) {}
private:
	double width;
};

//! Line geometric primitive class
class Line : public Polygon {
public:
	//! Line constructor
	/*! 
	 *  @param begin     (x,y)-coordinates of the start point of the cut
	 *  @param end       (x,y)-coordinates of the end point of the cut
	 *  @param color     color
	 */
	Line(Point begin={0.0,0.0}, Point end={1.0,1.0}, Color color=Color::Blue) :
	     Polygon("Line", 2, color, (begin+end)/2),
	     length(std::sqrt((begin.x-end.x)*(begin.x-end.x)+(begin.y-end.y)*(begin.y-end.y))) {}
	//! get length of the line
	double GetLength() const {return length;}
private:	     
	double length;
};

/*! \brief An enum to identify the type of a geometric primitive */
enum class PRIMITIVE_TYPE{
		Circle,   /**< 1 Circle */
		Triangle, /**< 2 Triangle */
		Rectangle,/**< 3 Rectangle */
		Square,   /**< 4 Square */
		Line,     /**< 5 Line */
		None      /**< 6 None */
};

/**
 * \brief Abstract factory method that creates a geometric primitive of a given type
 * Abstract factory method that creates a geometric primitive of a given type
 * @param type type of a geometric object to create
 */
std::unique_ptr<IPrimitive> PrimitivesFactory(PRIMITIVE_TYPE type)
{
    switch(type)
    {
        case PRIMITIVE_TYPE::Circle:
            return std::unique_ptr<IPrimitive>(new Circle{});
        case PRIMITIVE_TYPE::Triangle:
            return std::unique_ptr<IPrimitive>(new Triangle{});
        case PRIMITIVE_TYPE::Rectangle:
            return std::unique_ptr<IPrimitive>(new Rectangle{});
        case PRIMITIVE_TYPE::Square:
            return std::unique_ptr<IPrimitive>(new Square{});
        case PRIMITIVE_TYPE::Line:
            return std::unique_ptr<IPrimitive>(new Line{});
    }
    return nullptr;
}
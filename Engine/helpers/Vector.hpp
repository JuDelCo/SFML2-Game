#ifndef VECTOR_HPP
#define VECTOR_HPP


#include <SFML/Graphics.hpp>


template <typename Type>
class Vector2
{
	public :
		Vector2() : x(0), y(0) {}
		Vector2(Type x, Type y) : x(x), y(y) {}
		sf::Vector2<Type> sf()
		{
			return sf::Vector2<Type>(this->x, this->y);
		}

		Type x;
		Type y;
};


typedef Vector2<int>          Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float>        Vector2f;


template <typename Type>
class Vector3
{
	public :
		Vector3() : x(0), y(0), z(0) {}
		Vector3(Type x, Type y, Type z) : x(x), y(y), z(z) {}
		sf::Vector3<Type> sf()
		{
			return sf::Vector3<Type>(this->x, this->y, this->z);
		}

		Type x;
		Type y;
		Type z;
};


typedef Vector3<int>          Vector3i;
typedef Vector3<unsigned int> Vector3u;
typedef Vector3<float>        Vector3f;


template <typename Type>
class Rect
{
	public :
		Rect() : rectLeft(0), rectTop(0), rectWidth(0), rectHeight(0) {}
		Rect(Type x1, Type x2, Type y1, Type y2) : rectLeft(x1), rectTop(x2), rectWidth(y1), rectHeight(y2) {}
		sf::Rect<Type> sf()
		{
			return sf::Rect<Type>(this->rectLeft, this->rectTop, this->rectWidth, this->rectHeight);
		}

		Type rectLeft;
		Type rectTop;
		Type rectWidth;
		Type rectHeight;
};


typedef Rect<int>		IntRect;
typedef Rect<float> 	FloatRect;


#endif // VECTOR_HPP

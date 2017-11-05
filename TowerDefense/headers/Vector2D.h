#ifndef _VECTOR2D_
#define _VECTOR2D_

template<typename T>
class Vector2D
{
public:
	explicit Vector2D(T p_x = 0, T p_y = 0) : m_x(p_x), m_y(p_y) {}
	~Vector2D() {}

	T& X() { return m_x; }
	T& Y() { return m_y; }

	void SetX(T p_x) { m_x = p_x; }
	void SetY(T p_y) { m_y = p_y; }

	T GetX() const { return m_x; }
	T GetY() const { return m_y; }

	T DistanceTo(Vector2D<T> p_otherVector) { return static_cast<T>(sqrt(pow((p_otherVector.X() - X()), 2) + pow((p_otherVector.Y() - Y()), 2))); }

	T DotProduct(Vector2D<T> p_otherVector)
	{
		return X() * p_otherVector.X() + Y() * p_otherVector.Y();
	}

	float GetLength()
	{
		return sqrt(pow(this->X(), 2) + pow(this->Y(), 2));
	}

	void Normalize()
	{
		const float length = GetLength();
		X() /= length;
		Y() /= length;
	}
	
private:
	T m_x;
	T m_y;
};

#endif // !_VECTOR2D_
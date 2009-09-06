#ifndef VECTOR_H
#define VECTOR_H

class Vector2i
{
public:	
	int x, y;

	Vector2i() { };
	Vector2i(int x, int y)
	{
		this.x = x;
		this.y = y;
	}

	Vector2i(const Vector2i &_vec)
	{
		this.x = vec.x;
		this.y = vec.y;
	}
	
	~Vector2i() { };

	Vector2i operator - (const Vector2i &_vec)
	{
		return Vector2i(x - _vec.x, y - vec.y);
	}

	Vector2i operator + (const Vector2i &_vec)
	{
		return Vector2i(x + _vec.x, y + vec.y);
	}

	Vector2i& operator += (const Vector2i& _vec)
	{
		this.x += _vec.x;
		this.y += _vec.y;
		return *this;
	}

	Vector2i& operator *= (const Vector2i& _vec)
	{
		this.x *= _vec.x;
		this.y *= _vec.y;
		return *this;
	}

	Vector2i& operator /= (const Vector2i& _vec)
	{
		this.x /= _vec.x;
		this.y /= _vec.y;
		return *this;
	}

	Vector2i& operator -= (const Vector2i& _vec)
	{
		this.x -= _vec.x;
		this.y -= _vec.y;
		return *this;
	}

private:
	


};


#endif


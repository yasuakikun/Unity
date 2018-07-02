#pragma once
#include "DxLib.h"

#define WINDOW_X 748
#define WINDOW_Y 448

template<typename T>

//矩形を表現する構造体
struct Vector2D
{
	Vector2D() :x(0),y(0){}
	Vector2D(T inx, T iny) :x(inx),y(iny){}
	T x;
	T y;

	void operator+=(const Vector2D<T> &in){
		x += in.x;
		y += in.y;
	}
	void operator-=(const Vector2D<T> & in){
		x -= in.x;
		y -= in.y;

	}
};

typedef Vector2D<int> Vector2;
typedef Vector2 Postion2;

typedef Vector2D<float> Vector2f;
typedef Vector2f Postion2f;


//Vector2D<T>のためのオペレーターオーバーロード
template<typename T>
Vector2D<T> operator+(const Vector2D<T>& lv, const Vector2D<T>& rv) 
{
	return Vector2D<T> (lv.x + rv.x ,lv.y + rv.y);
}
 

struct Size
{
	Size();
	Size(int x, int y) : w(x), h(y) {}
	int w;
	int h;
};

struct Rect
{
	Postion2 center;//Postion2 int型　x + y
	Size size;
	Rect();
	Rect(int x, int y, int w, int h);
	Rect(Postion2& pos, Size& size);

	const int Left()const;

	const int Top()const;

	const int Right()const;

	const int Botton()const;

	const int Wight()const;

	const int Height()const;

	void Draw(unsigned int color = 0xffffffff);

	void Draw(const Vector2& offset, unsigned int color = 0xffffffff);

	void SetWidth(int x)
	{
		size.w *= x;
	}
	void SetHeight(int y)
	{
		size.h *= y;
	}
};

class Geometry
{
public:
	Geometry();
	~Geometry();
};

//関数のじったいは可能な限りｃｐｐに書く。※例外としてテンプレは可能とする

//クラスやら構造体ってのは、誰か別のクラスなり関数なりから利用されることを想定しています。で、定義は基本的にヘッダ側に書かれます。
//ということは使用者はｃｐｐではなくヘッダー側に書く。
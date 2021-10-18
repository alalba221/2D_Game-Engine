namespace Alalba{
  
  class Vec2{
  public:
    float x;
    float y;
    float length;
    Vec2(){}
    Vec2(float _x,float _y) : x(_x), y(_y) {
      length = getLength();
    }
    inline float getLength(){
      return sqrt(pow(x,2)+pow(y,2));
    }
    inline Vec2 normalized(){

      return Vec2(x/length,y/length);
    }

    inline void operator +=(const Vec2& a){
      this->x +=a.x;
      this->y +=a.y;
    }
    inline Vec2 operator +(const Vec2& a){
      return Vec2(x+a.x,y+a.y);
    }

    inline Vec2 operator -(const Vec2& a){
      return Vec2(x-a.x,y-a.y);
    }
    
    inline Vec2 operator *(const float& a){
      return Vec2(x*a,y*a);
    }
    inline void operator *=(const float& a){
        this->x *=a;
        this->y *=a;
    }
    inline Vec2 operator /(const float& a){
      return Vec2(x/a,y/a);
    }
    inline float dot(const Vec2& a){
      return x*a.x+y*a.y;
    }

  };
}
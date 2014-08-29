#include <FRONTIER/System/Quaternion.hpp>
#include <FRONTIER/System/Vector3.hpp>
#include <FRONTIER/System/Vector4.hpp>
#include <FRONTIER/System/Matrix.hpp>
#include <cmath>
namespace fm
{
    
	/// Constructors /////////////////////////////////////////////////////////
	Quat::Quat() : x(0),
				   y(0),
				   z(0),
				   w(1)
	{
		
	}
    
	////////////////////////////////////////////////////////////
	Quat::Quat(const Quat &copy) : x(copy.x),
								   y(copy.y),
								   z(copy.z),
								   w(copy.w)
	{
		
	}
    
	////////////////////////////////////////////////////////////
	Quat::Quat(const vec3 &axis,const Angle &angle)
	{
		float halfAngle = (*((float*)&angle))*.5f;
		float sinA = std::sin(halfAngle);
		x = sinA*axis.x;
		y = sinA*axis.y;
		z = sinA*axis.z;
		w = std::cos(halfAngle);
	}
    
	////////////////////////////////////////////////////////////
	Quat::Quat(float X,float Y,float Z,float W) : x(X),
												  y(Y),
												  z(Z),
												  w(W)
	{
		
	}
    
	////////////////////////////////////////////////////////////
	Quat::Quat(const Angle &around_x,const Angle &around_y,const Angle &around_z)
	{
		float x = *((float*)&around_x);
		float y = *((float*)&around_y);
		float z = *((float*)&around_z);
		
		double sx = sin(x*.5);
		double cx = cos(x*.5);
		double sy = sin(y*.5);
		double cy = cos(y*.5);
		double sz = sin(z*.5);
		double cz = cos(z*.5);
		
		float cycz = cy * cz;
		float sycz = sy * cz;
		float cysz = cy * sz;
		float sysz = sy * sz;
        
		x = sx * cycz - cx * sysz;
		y = cx * sycz + sx * cysz;
		z = cx * cysz - sx * sycz;
		w = cx * cycz + sx * sysz;

		normalize();
	}
    
	////////////////////////////////////////////////////////////
	float Quat::dot(const Quat &other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
	}
    
	////////////////////////////////////////////////////////////
	Quat &Quat::normalize()
	{
		(*this) = norm();
		return *this;
	}
    
	////////////////////////////////////////////////////////////
	Quat Quat::norm() const
	{
		float l = LENGTH();
		return (l==1 || l==0) ? *this : (*this)/std::sqrt(l);
	}
    
	////////////////////////////////////////////////////////////
	Quat Quat::sgn() const
	{
		float l = LENGTH();
		return (l==1 || l==0) ? *this : (*this)/std::sqrt(l);
	}
    
	////////////////////////////////////////////////////////////
	Quat Quat::inverse() const
	{
		return Quat(-x,-y,-z,w);
	}
    
	////////////////////////////////////////////////////////////
	float Quat::length() const
	{
		return std::sqrt(x*x+y*y+z*z+w*w);
	}
    
	////////////////////////////////////////////////////////////
	float Quat::LENGTH() const
	{
		return x*x+y*y+z*z+w*w;
	}
    
	////////////////////////////////////////////////////////////
	mat4 Quat::getMatrix(MATRIX::StorageOrder storeOrder) const
	{
		if (storeOrder==MATRIX::RowMajor)
		{
			float ret[4*4]={1-2*y*y-2*z*z ,   2*x*y+2*w*z ,   2*x*z-2*w*y , 0,
							2*x*y-2*w*z   , 1-2*x*x-2*z*z ,   2*y*z+2*w*x , 0,
							2*x*z+2*w*y   ,   2*y*z-2*w*x , 1-2*x*x-2*y*y , 0,
							0             , 0             , 0             , 1};
			return fm::mat4(ret);			
		}
		float ret[4*4]={1-2*y*y-2*z*z ,   2*x*y-2*w*z ,   2*x*z+2*w*y , 0,
						2*x*y+2*w*z   , 1-2*x*x-2*z*z ,   2*y*z-2*w*x , 0,
						2*x*z-2*w*y   ,   2*y*z+2*w*x , 1-2*x*x-2*y*y , 0,
						0             , 0             , 0             , 1};
		return fm::mat4(ret);	
	}
    
	////////////////////////////////////////////////////////////
	Quat Quat::fromTo(const vec3 &from,const vec3 &to)
	{
		if (from == to)
			return identity;

		if (from == -to)
			return Quat(0,0,0,1);
		
        float szog = std::acos(from.dot(to));
        szog = szog < 0 ? fm::PI+szog : szog;
		
		vec3 axis = from.cross(to).sgn();
		float sinA = std::sin(szog*.5f);
		
		return Quat (sinA*axis.x,
					 sinA*axis.y,
					 sinA*axis.z,
					 std::cos(szog*.5f));
	}
    
	////////////////////////////////////////////////////////////
	Quat Quat::lerp(const Quat &quatAt0,const Quat &quatAt1,float deltaTime)
	{
		return quatAt0*(1.f-deltaTime)+quatAt1*deltaTime;
	}
    
	////////////////////////////////////////////////////////////
	Quat Quat::slerp(Quat quatAt0,const Quat &quatAt1,float deltaTime,float useLerpAfter)
	{
		float dot = quatAt0.dot(quatAt1);

		if (dot < 0.0f)
			quatAt0 *= -1.f,
			dot *= -1.f;

		if (dot <= 1.f-useLerpAfter)
		{
			float theta = std::acos(dot);
			float invsintheta = 1.f/std::sin(theta);
			return quatAt0*(std::sin(theta * (1.0f-deltaTime)) * invsintheta) + 
				   quatAt1*(std::sin(theta * deltaTime) * invsintheta);
		}
		
		return lerp(quatAt0,quatAt1,deltaTime);
	}
    
	////////////////////////////////////////////////////////////
	Quat Quat::identity = Quat();

	////////////////////////////////////////////////////////////
	bool operator==(const Quat &left,const Quat &right)
	{
		return left.x==right.x && left.y==right.y && left.z==right.z && left.w==right.w;
	}

	////////////////////////////////////////////////////////////
	bool operator!=(const Quat &left,const Quat &right)
	{
		return left.x!=right.x || left.y!=right.y || left.z!=right.z || left.w!=right.w;
	}

	////////////////////////////////////////////////////////////
	Quat operator- (const Quat &quat)
	{
		return Quat(-quat.x,
					-quat.y,
					-quat.z,
					-quat.w);
	}

	////////////////////////////////////////////////////////////
	Quat operator+ (const Quat &left,const Quat &right)
	{
		return Quat(left.x+right.x,
					left.y+right.y,
					left.z+right.z,
					left.w+right.w);
	}

	////////////////////////////////////////////////////////////
	Quat operator* (const Quat &left,const Quat &right)
	{
		Quat ret;

		ret.x = (right.w * left.x) + (right.x * left.w) + (right.y * left.z) - (right.z * left.y);
		ret.y = (right.w * left.y) + (right.y * left.w) + (right.z * left.x) - (right.x * left.z);
		ret.z = (right.w * left.z) + (right.z * left.w) + (right.x * left.y) - (right.y * left.x);
		ret.w = (right.w * left.w) - (right.x * left.x) - (right.y * left.y) - (right.z * left.z);

		return ret;
	}

	////////////////////////////////////////////////////////////
	vec3 operator* (const Quat &left,const vec3 &right)
	{
		vec3 uv, uuv;
		vec3 axis(left.x, left.y, left.z);
		uv   = axis.cross(right);
		uuv  = axis.cross(uv);
		uv  *= 2.0f * left.w;
		uuv *= 2.0f;

		return right + uv + uuv;
	}

	////////////////////////////////////////////////////////////
	vec4 operator* (const Quat &left,const vec4 &right)
	{
		return left*vec3(right);
	}

	////////////////////////////////////////////////////////////
	Quat operator* (const Quat &left,float right)
	{
		return Quat(left.x*right,
					left.y*right,
					left.z*right,
					left.w*right);
	}

	////////////////////////////////////////////////////////////
	Quat operator/ (const Quat &left,float right)
	{
		return Quat(left.x/right,
					left.y/right,
					left.z/right,
					left.w/right);
	}
	
	////////////////////////////////////////////////////////////
	Quat &operator*=(Quat &left,const Quat &right)
	{
		left = left*right;
		return left;
	}

	////////////////////////////////////////////////////////////
	Quat &operator*=(Quat &left,float right)
	{
		left.x*=right;
		left.y*=right;
		left.z*=right;
		left.w*=right;
		return left;
	}

	////////////////////////////////////////////////////////////
	Quat &operator/=(Quat &left,float right)
	{
		left.x/=right;
		left.y/=right;
		left.z/=right;
		left.w/=right;
		return left;
	}
}
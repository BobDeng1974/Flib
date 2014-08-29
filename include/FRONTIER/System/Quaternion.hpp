#ifndef FRONTIER_QUATERNION_HPP_INCLUDED
#define FRONTIER_QUATERNION_HPP_INCLUDED
#include <FRONTIER/Config.hpp>

#include <FRONTIER/System/macros/dont_include_inl_begin>

#include <FRONTIER/System/Vector3.hpp>
#include <FRONTIER/System/Vector4.hpp>
#include <FRONTIER/System/Matrix.hpp>

#include <FRONTIER/System/macros/dont_include_inl_end>

#define FRONTIER_QUATERNION
namespace fm
{
	class Angle;
	//////////////////////////////////
	/// @brief Class for using <a href="http://en.wikipedia.org/wiki/Quaternion">quaternions</a>
	/// 
	//////////////////////////////////
	class Quat
	{
	public:
		float x, ///< 1st imaginary part
			  y, ///< 2nd imaginary part
			  z, ///< 3rd imaginary part
			  w; ///< Real part
		typedef float value_type;
		typedef Quat &reference;
		typedef const Quat &const_reference;
		enum {
			dimensions = 4u ///< Public value indicating the amount of value_type's in the class
		};


		/////////////////////////////////////////////////////////////
		/// @brief Default constructor
		///
		/// Initalizes the quaternion with 0,0,0,1
		///
		/////////////////////////////////////////////////////////////
		Quat();
		
		/////////////////////////////////////////////////////////////
		/// @brief Copy constructor
		///
		/// @param copy Quaternion to by copied
		///
		/////////////////////////////////////////////////////////////
		Quat(const Quat &copy);
		
		/////////////////////////////////////////////////////////////
		/// @brief Construct quaternion from an axis and an angle
		/// 
		/// If you don't know why it says rotation here you should
		/// check out <a href="http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation">this</a> wikipedia article
		/// 
		/// @param axis The axis of the rotatation
		/// @param angle The angle of the rotation
		///
		/////////////////////////////////////////////////////////////
		Quat(const vec3 &axis,const Angle &angle);
		
		/////////////////////////////////////////////////////////////
		/// @brief Construct quaternion directly from the values of the imaginary and real part
		/// 
		/// @param X 1st imaginary part
		/// @param Y 2nd imaginary part
		/// @param Z 3rd imaginary part
		/// @param W real part
		///
		/////////////////////////////////////////////////////////////
		Quat(float X,float Y,float Z,float W);
		
		/////////////////////////////////////////////////////////////
		/// @brief Construct quaternion from <a href="http://en.wikipedia.org/wiki/Euler_angles">Euler angles</a>
		/// 
		/// @param around_x Angle of rotatation around the (1,0,0) axis
		/// @param around_y Angle of rotatation around the (0,1,0) axis
		/// @param around_z Angle of rotatation around the (0,0,1) axis
		///
		/////////////////////////////////////////////////////////////
		Quat(const Angle &around_x,const Angle &around_y,const Angle &around_z);
		
		/////////////////////////////////////////////////////////////
		/// @brief Calculate the <a href="http://en.wikipedia.org/wiki/Dot_product">dot product</a> of two quaternions 
		/// 
		/// @param other Right operand
		///
		/// @return The dot product
		///
		/////////////////////////////////////////////////////////////
		float dot(const Quat &other) const;
		
		/////////////////////////////////////////////////////////////
		/// @brief Divide the quaternion by its length
		/// 
		/// @return Reference to itself
		///
		/////////////////////////////////////////////////////////////
		reference normalize();
		
		/////////////////////////////////////////////////////////////
		/// @brief Calculate the normalized version of the quaternion
		/// 
		/// @return The normalized quaternion
		///
		/////////////////////////////////////////////////////////////
		Quat norm() const;
		
		/////////////////////////////////////////////////////////////
		/// @brief Calculate the normalized version of the quaternion
		/// 
		/// @return The normalized quaternion
		///
		/////////////////////////////////////////////////////////////
		Quat sgn() const;
		
		/////////////////////////////////////////////////////////////
		/// @brief Calculate the inverse of the quaternion
		/// 
		/// @return The inverse quaternion
		///
		/////////////////////////////////////////////////////////////
		Quat inverse() const;
		
		/////////////////////////////////////////////////////////////
		/// @brief Calculate the length of the quaternion
		/// 
		/// @return The length of the quaternion
		///
		/////////////////////////////////////////////////////////////
		float length() const;
		
		/////////////////////////////////////////////////////////////
		/// @brief Calculate the length of the quaternion squared
		/// 
		/// @return The length of the quaternion squared
		///
		/////////////////////////////////////////////////////////////
		float LENGTH() const;
		
		/////////////////////////////////////////////////////////////
		/// @brief Convert the quaternion to a matrix
		/// 
		/// The result is a rotation matrix for reference see <a href="http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix">this</a> wikipedia article
		/// 
		/// @param storeOrder The way to store the resulting matrix
		/// 
		/// @return The matrix
		///
		/////////////////////////////////////////////////////////////
		mat4 getMatrix(MATRIX::StorageOrder storeOrder=MATRIX::RowMajor) const;
		
		/////////////////////////////////////////////////////////////
		/// @brief Convert the quaternion to a matrix
		/// 
		/// The result is a rotation matrix for reference see <a href="http://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation#Quaternion-derived_rotation_matrix">this</a> wikipedia article
		/// 
		/// @return The matrix
		///
		/////////////////////////////////////////////////////////////
		template<MATRIX::StorageOrder storeOrder>
		mat4 getMatrix() const;
		
		/////////////////////////////////////////////////////////////
		/// @brief Create a quaternion that rotates @a from around the Origo to @a to
		/// 
		/// @return The constructed quaternion
		///
		/////////////////////////////////////////////////////////////
		static Quat fromTo(const vec3 &from,const vec3 &to);
		
		/////////////////////////////////////////////////////////////
		/// @brief Perform L_inear int_ERP_olation between two quaternions
		/// 
		/// @param quatAt0 Return value at @a deltaTime = 0
		/// @param quatAt1 Return value at @a deltaTime = 1
		/// @param deltaTime Time stamp of the interpolation
		/// 
		/// @return The interpolated quaternion
		///
		/////////////////////////////////////////////////////////////
		static Quat lerp(const Quat &quatAt0,const Quat &quatAt1,float deltaTime);
		
		/////////////////////////////////////////////////////////////
		/// @brief Perform S_pherica_L int_ERP_olation between two quaternions
		/// 
		/// @param quatAt0 Return value at @a deltaTime = 0
		/// @param quatAt1 Return value at @a deltaTime = 1
		/// @param deltaTime Time stamp of the interpolation
		/// @param useLerpAfter To avoid inaccuracies the function uses lerp if @a deltaTime > 1.f-useLerpAfter
		/// 
		/// @return The interpolated quaternion
		///
		/////////////////////////////////////////////////////////////
		static Quat slerp(Quat quatAt0,const Quat &quatAt1,float deltaTime,float useLerpAfter=.05f);

		/////////////////////////////////////////////////////////////
		/// @brief The identity quaternion
		/// 
		/// Its value is (0,0,0,1)
		/// 
		/////////////////////////////////////////////////////////////
		static Quat identity;
	};


	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator ==
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (quaternion)
	///
	/// @return True if left's all components are equal to the corresponding right's component
	///
	/////////////////////////////////////////////////////////////
	bool operator==(const Quat &left,const Quat &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator !=
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (quaternion)
	///
	/// @return True if at least one of left's components is not equal to the corresponding right's component
	///
	/////////////////////////////////////////////////////////////
	bool operator!=(const Quat &left,const Quat &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of unary operator -
	///
	/// @param quat The operand (quaternion)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Quat operator- (const Quat &quat);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator +
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (quaternion)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Quat operator+ (const Quat &left,const Quat &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator *
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (quaternion)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Quat operator* (const Quat &left,const Quat &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat fm::vector3
	/// @brief Overload of binary operator *
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (vector)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	vec3 operator* (const Quat &left,const vec3 &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat fm::vector4
	/// @brief Overload of binary operator *
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (vector)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	vec4 operator* (const Quat &left,const vec4 &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator *
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (scalar)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Quat operator* (const Quat &left,float right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator /
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (scalar)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Quat operator/ (const Quat &left,float right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator *=
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (Quaternion)
	///
	/// @return Reference to @a left
	///
	/////////////////////////////////////////////////////////////
	
	Quat &operator*=(Quat &left,const Quat &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator *=
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (scalar)
	///
	/// @return Reference to @a left
	///
	/////////////////////////////////////////////////////////////
	Quat &operator*=(Quat &left,float right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Quat
	/// @brief Overload of binary operator /=
	///
	/// @param left Left operand (quaternion)
	/// @param right Right operand (scalar)
	///
	/// @return Reference to @a left
	///
	/////////////////////////////////////////////////////////////
	Quat &operator/=(Quat &left,float right);
}

#endif //FRONTIER_QUATERNION_HPP_INCLUDED

#ifndef FRONTIER_DONT_INCLUDE_INL
	#include <FRONTIER/System/Quaternion.inl>
#endif

////////////////////////////////////////////////////////////
/// @class fm::Quat
/// @ingroup System
///
/// This class is mainly used to define and interpolate rotations
///
/// Usage example:
/// @code
/// 
/// fm::Quat q(fm::vec3(1,1,1).sgn(),180);
/// 
/// std::cout<<q*fm::vec3(-1,-1,1)<<std::endl; //will print out 1 1 -1 because (-1,-1,1) is rotated 180 degrees around (1,1,1)
/// 
/// std::cout<<fm::Quat(fm::vec3(1,0,0),60).getMatrix()<<std::endl; //print out a simple rotatation matrix
/// 
/// @endcode
///
/// @see fm::vector2
/// @see fm::vector3
/// @see fm::vector4
/// @see fm::matrix
/// @see fm::Angle
////////////////////////////////////////////////////////////
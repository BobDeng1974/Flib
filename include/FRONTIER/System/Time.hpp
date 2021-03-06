////////////////////////////////////////////////////////////////////////// <!--
/// Copyright (C) 2014-2018 Frontier (fr0nt13r789@gmail.com)           ///
///                                                                    ///
/// Flib is licensed under the terms of GNU GPL.                       ///
/// Therefore you may freely use it in your project,                   ///
/// modify it, redistribute it without any warranty on the             ///
/// condition that this disclaimer is not modified/removed.            ///
/// You may not misclaim the origin of this software.                  ///
///                                                                    ///
/// If you use this software in your program/project a                 ///
/// note about it and an email for the author (fr0nt13r789@gmail.com)  ///
/// is not required but highly appreciated.                            ///
///                                                                    ///
/// You should have received a copy of GNU GPL with this software      ///
///                                                                    ///
////////////////////////////////////////////////////////////////////////// -->
#ifndef FRONTIER_TIME_HPP_INCLUDED
#define FRONTIER_TIME_HPP_INCLUDED
#include <FRONTIER/System/util/API.h>
#define FRONTIER_TIME
namespace fm
{
	/////////////////////////////////////////////////////////////
	/// @brief Class used to represent the amount of some time
	///
	/// @ingroup System
	///
	/////////////////////////////////////////////////////////////
	class FRONTIER_API Time
	{
		double m_amount; ///< A double precision value holding the time in Microseconds
	public:
		typedef double component_type;
		typedef Time &reference;
		typedef const Time &const_reference;
		enum {
			components = 1u ///< Public value indicating the amount of component_types in the class
		};

		/////////////////////////////////////////////////////////////
		/// @brief Create fm::Time from plain value
		///
		/// @param secs The value in secnds
		///
		/////////////////////////////////////////////////////////////
		Time(double secs = 0.0);

		/////////////////////////////////////////////////////////////
		/// @brief Get time value as microseconds
		///
		/// @return Represented value as microseconds
		///
		/////////////////////////////////////////////////////////////
		double asMicroseconds() const;

		/////////////////////////////////////////////////////////////
		/// @brief Get time value as milliseconds
		///
		/// @return Represented value as milliseconds
		///
		/////////////////////////////////////////////////////////////
		double asMilliseconds() const;

		/////////////////////////////////////////////////////////////
		/// @brief Get time value as seconds
		///
		/// @return Represented value as seconds
		///
		/////////////////////////////////////////////////////////////
		double asSeconds() const;


		/////////////////////////////////////////////////////////////
		/// @brief Get time value as microseconds
		///
		/// @return Represented value as microseconds
		///
		/////////////////////////////////////////////////////////////
		double asMicsecs() const;

		/////////////////////////////////////////////////////////////
		/// @brief Get time value as milliseconds
		///
		/// @return Represented value as milliseconds
		///
		/////////////////////////////////////////////////////////////
		double asMilsecs() const;

		/////////////////////////////////////////////////////////////
		/// @brief Get time value as seconds
		///
		/// @return Represented value as seconds
		///
		/////////////////////////////////////////////////////////////
		double asSecs() const;


		/////////////////////////////////////////////////////////////
		/// @brief Get time value as microseconds
		///
		/// @return Represented value as microseconds
		///
		/////////////////////////////////////////////////////////////
		double Ms() const;

		/////////////////////////////////////////////////////////////
		/// @brief Get time value as milliseconds
		///
		/// @return Represented value as milliseconds
		///
		/////////////////////////////////////////////////////////////
		double ms() const;

		/////////////////////////////////////////////////////////////
		/// @brief Get time value as seconds
		///
		/// @return Represented value as seconds
		///
		/////////////////////////////////////////////////////////////
		double s() const;

		/////////////////////////////////////////////////////////////
		/// @brief Static const value indicating a time value of 0
		///
		/////////////////////////////////////////////////////////////
		static const Time Zero;

		/////////////////////////////////////////////////////////////
		/// @brief Static const value indicating a time value of infinite
		/// 
		/// The value matches -1 seconds
		/// 
		/////////////////////////////////////////////////////////////
		static const Time Inf;
	};

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator +
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API operator+(const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator -
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API operator-(const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of unary operator -
	///
	/// @param time Operand (Time)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API operator-(const Time &time);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator *
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (scalar)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API operator*(const Time &left,const double &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator *
	///
	/// @param left Left operand (scalar)
	/// @param right Right operand (Time)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API operator*(const double &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator /
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (scalar)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API operator/(const Time &left,const double &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator /
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return Result of the operation
	///
	/////////////////////////////////////////////////////////////
	double FRONTIER_API operator/(const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator +=
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return Reference to @a left
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API &operator+=(Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator -=
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return Reference to @a left
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API &operator-=(Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator *=
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (scalar)
	///
	/// @return Reference to @a left
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API &operator*=(Time &left,const double &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator /=
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (scalar)
	///
	/// @return Reference to @a left
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API &operator/=(Time &left,const double &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator ==
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return True if @a left and @a right are equal
	///
	/////////////////////////////////////////////////////////////
	bool FRONTIER_API operator==(const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator ==
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return True if @a left and @a right are not equal
	///
	/////////////////////////////////////////////////////////////
	bool FRONTIER_API operator!=(const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator ==
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return True if @a left is smaller than @a right
	///
	/////////////////////////////////////////////////////////////
	bool FRONTIER_API operator< (const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator ==
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return True if @a left is smaller or equal than @a right
	///
	/////////////////////////////////////////////////////////////
	bool FRONTIER_API operator<=(const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator ==
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return True if @a left is bigger than @a right
	///
	/////////////////////////////////////////////////////////////
	bool FRONTIER_API operator> (const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Overload of binary operator ==
	///
	/// @param left Left operand (Time)
	/// @param right Right operand (Time)
	///
	/// @return True if @a left is bigger or equal than @a right
	///
	/////////////////////////////////////////////////////////////
	bool FRONTIER_API operator>=(const Time &left,const Time &right);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Create fm::Time from microseconds
	///
	/// @param Msecs The value indicating time in microseconds
	///
	/// @return The create fm::Time object
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API microseconds(double Msecs);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Create fm::Time from milliseconds
	///
	/// @param msecs The value indicating time in milliseconds
	///
	/// @return The create fm::Time object
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API milliseconds(double msecs);

	/////////////////////////////////////////////////////////////
	/// @relates fm::Time
	/// @brief Create fm::Time from seconds
	///
	/// @param secs The value indicating time in seconds
	///
	/// @return The create fm::Time object
	///
	/////////////////////////////////////////////////////////////
	Time FRONTIER_API seconds(double secs);
}
#endif //FRONTIER_TIME_HPP_INCLUDED


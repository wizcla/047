/**
 * @file		WZGLMath.h
 * @brief		WZGLの数学ライブラリの定義
 *
 *	ベクトル演算などの拡張機能を使用する場合にインクルードする
 */

#ifndef __WZMath__
#define __WZMath__

#include <math.h>
#include <string.h>

/// π(パイ)を表す定数
const double WZ_PI = 3.14159265358979323846264338327950288 ;

/**
 * @brief		ディグリー角からラジアン角を得る関数
 *
 * @param[in]	degree	ディグリー角
 *
 * @return		template<class T>	ラジアン角
 */
template <class T>
inline T rad( T degree )
{
	return degree / static_cast<T>( 180.0 ) * static_cast<T>( WZ_PI ) ;
}

/**
 * @brief		ラジアン角からディグリー角を得る関数
 *
 * @param[in]	radian	ラジアン角
 *
 * @return		template<class T>	ディグリー角
 */
template <class T>
inline T deg( T radian )
{
	return radian * static_cast<T>( 180.0 ) / static_cast<T>( WZ_PI ) ;
}

/// ３次元ベクトルを表す構造体
struct  Vector3
{
	float x,                    ///< ベクトルのＸ成分
		  y,                    ///< ベクトルのＹ成分
		  z ;                   ///< ベクトルのＺ成分

	/**
	 * @brief		デフォルトコンストラクタ
	 *
	 * @return		なし (none)
	 */
	Vector3()
	{
	}

	/**
	 * @brief		コンストラクタ（初期化指定）
	 *
	 * @param[in]	i_fX	生成するベクトルのＸ座標
	 * @param[in]	i_fY	生成するベクトルのＹ座標
	 * @param[in]	i_fZ	生成するベクトルのＺ座標
	 *
	 * @return		なし (none)
	 */
	Vector3( float i_fX, float i_fY, float i_fZ )
		: x( i_fX ), y( i_fY ), z( i_fZ )
	{
	}

	/**
	 * @brief		コピーコンストラクタ
	 *
	 * @param[in]	i_Vec	コピー元のベクトル
	 *
	 * @return		なし (none)
	 */
	Vector3( const Vector3& i_Vec )
		: x( i_Vec.x ), y( i_Vec.y ), z( i_Vec.z )
	{
	}

	/**
	 * @brief		ベクトルの大きさを求める関数
	 *
	 * @return		float	ベクトルの大きさ
	 */
	float length()
	{
		return sqrt( x * x + y * y + z * z );
	}

	/**
	 * @brief		現在のベクトルを正規化したベクトルを求める関数
	 *
	 * @return		Vector3	正規化されたベクトル
	 */
	Vector3 normalize()
	{
		return Vector3( x / length(), y / length(), z / length() ) ;
	}

	/**
	 * @brief		現在のベクトルと他のベクトルとの内積を求める関数
	 *
	 * @param[in]	i_Vec	内積の右辺にあたるベクトル
	 *
	 * @return		float	内積の値
	 */
	float dot( const Vector3& i_Vec )
	{
		return x * i_Vec.x + y * i_Vec.y + z * i_Vec.z ;
	}

	/**
	 * @brief		現在のベクトルと他のベクトルとの外積を求める関数
	 *
	 * @param[in]	i_Vec	外積の右辺にあたるベクトル
	 *
	 * @return		Vector3	外積の結果にあたるベクトル
	 */
	Vector3 cross( const Vector3& i_Vec )
	{
		return Vector3( y * i_Vec.z - z * i_Vec.y, z * i_Vec.x - x * i_Vec.z, x * i_Vec.y - y * i_Vec.x );
	}

	/**
	 * @brief		正符号演算子
	 *
	 * @return		Vector3	元のベクトル
	 */
	Vector3 operator +() const
	{
		return Vector3( x, y, z ) ;
	}

	/**
	 * @brief		負符号演算子
	 *
	 * @return		Vector3	逆ベクトル
	 */
	Vector3 operator -() const
	{
		return Vector3( -x, -y, -z );
	}

	/**
	 * @brief		加算演算子
	 *
	 * @param[in]	i_Vec	加算演算の右辺にあたるベクトル
	 *
	 * @return		Vector3	ベクトル加算の演算結果にあたるベクトル
	 */
	Vector3 operator +( const Vector3& i_Vec ) const
	{
		return Vector3( x + i_Vec.x, y + i_Vec.y, z + i_Vec.z ) ;
	}

	/**
	 * @brief		減算演算子
	 *
	 * @param[in]	i_Vec	減算演算の右辺にあたるベクトル
	 *
	 * @return		Vector3	ベクトル減算の結果にあたるベクトル
	 */
	Vector3 operator -( const Vector3& i_Vec ) const
	{
		return Vector3( x - i_Vec.x, y - i_Vec.y, z - i_Vec.z ) ;
	}

	/**
	 * @brief		乗算演算子（ベクトルと実数の乗算）
	 *
	 * @param[in]	i_fScale	乗算演算の右辺にあたる実数
	 *
	 * @return		Vector3	演算後のベクトル
	 */
	Vector3 operator *( float i_fScale ) const
	{
		return Vector3( x * i_fScale, y * i_fScale, z * i_fScale ) ;
	}

	/**
	 * @brief		除算演算子（ベクトルと実数の除算）
	 *
	 * @param[in]	i_fScale	除算演算の右辺にあたる実数
	 *
	 * @return		Vector3	演算後のベクトル
	 */
	Vector3 operator /( float i_fScale ) const
	{
		return Vector3( x / i_fScale, y / i_fScale, z / i_fScale ) ;
	}

	/**
	 * @brief		加算代入演算子
	 *
	 * @param[in]	i_Vec	現在のベクトルに加えるベクトル
	 *
	 * @return		Vector3&	演算後のベクトル
	 */
	Vector3&    operator +=( const Vector3& i_Vec )
	{
		x	+= i_Vec.x ;
		y	+= i_Vec.y ;
		z	+= i_Vec.z ;

		return *this ;
	}

	/**
	 * @brief		減算代入演算子
	 *
	 * @param[in]	i_Vec	差分ベクトル
	 *
	 * @return		Vector3& operator	演算後のベクトル
	 */
	Vector3&    operator -=( const Vector3& i_Vec )
	{
		x	-= i_Vec.x ;
		y	-= i_Vec.y ;
		z	-= i_Vec.z ;

		return *this ;
	}

	/**
	 * @brief		乗算代入演算子
	 *
	 * @param[in]	i_fScale	ベクトルに掛け合わせる実数
	 *
	 * @return		Vector3&	演算後のベクトル
	 */
	Vector3&    operator *=( float i_fScale )
	{
		x	*= i_fScale ;
		y	*= i_fScale ;
		z	*= i_fScale ;

		return *this ;
	}

	/**
	 * @brief		除算代入演算子
	 *
	 * @param[in]	i_fScale	ベクトルを割る実数
	 *
	 * @return		Vector3&	演算後のベクトル
	 */
	Vector3&    operator /=( float i_fScale )
	{
		x	/= i_fScale ;
		y	/= i_fScale ;
		z	/= i_fScale ;

		return *this ;
	}

	static const Vector3 Zero ; ///< ゼロベクトル ( 0.0f, 0.0f, 0.0f )
	static const Vector3 Up ;   ///< アップベクトル ( 0.0f, 1.0f, 0.0f )
};

struct Matrix
{
	union
	{
		float m[ 16 ] ;
		struct
		{
			float _11, _12, _13, _14,
				  _21, _22, _23, _24,
				  _31, _32, _33, _34,
				  _41, _42, _43, _44 ;
		};
	};

	Matrix()
	{
	}

	Matrix( const Matrix& i_Matrix )
	{
		memcpy( m, i_Matrix.m, sizeof( float ) * 16 );
	}

	Matrix( const float i_FloatArray16[ 16 ] )
	{
		memcpy( m, i_FloatArray16, sizeof( float ) * 16 );
	}

	Matrix& identity()
	{
		const float fMatrixArray[ 16 ] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		memcpy( m, fMatrixArray, sizeof( float ) * 16 );
		
		return *this ;
	}
	
	Matrix&	translation( float i_fX, float i_fY, float i_fZ )
	{
		const float fMatrixArray[ 16 ] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			i_fX, i_fY, i_fZ, 1.0f
		};

		memcpy( m, fMatrixArray, sizeof( float ) * 16 );
		
		return *this ;
	}
	
//	Matrix	rotation( float i_fX, float i_fY, float i_fZ, float i_fRadian )
//	{
//		const float fMatrixArray[ 16 ] = {
//			1.0f, 0.0f, 0.0f, 0.0f,
//			0.0f, 1.0f, 0.0f, 0.0f,
//			0.0f, 0.0f, 1.0f, 0.0f,
//			0.0f, 0.0f, 0.0f, 1.0f
//		};
//
//		memcpy( m, fMatrixArray, sizeof( float ) * 16 );
//		
//		return *this ;
//	}

	Matrix&	rotationX( float i_fRadian )
	{
		const float fMatrixArray[ 16 ] = {
			1.0f,	0.0f,				0.0f,				0.0f,
			0.0f,	cosf(i_fRadian),	-sinf(i_fRadian),	0.0f,
			0.0f,	sinf(i_fRadian),	cosf(i_fRadian),	0.0f,
			0.0f,	0.0f,				0.0f,				1.0f
		};

		memcpy( m, fMatrixArray, sizeof( float ) * 16 );
		
		return *this ;
	}

	Matrix&	rotationY( float i_fRadian )
	{
		const float fMatrixArray[ 16 ] = {
			cosf(i_fRadian),	0.0f,	sinf(i_fRadian),	0.0f,
			0.0f,				1.0f,	0.0f,				0.0f,
			-sinf(i_fRadian),	0.0f,	cosf(i_fRadian),	0.0f,
			0.0f,				0.0f,	0.0f,				1.0f
		};

		memcpy( m, fMatrixArray, sizeof( float ) * 16 );
		
		return *this ;
	}

	Matrix&	rotationZ( float i_fRadian )
	{
		const float fMatrixArray[ 16 ] = {
			1.0f, 0.0f,				0.0f,				0.0f,
			0.0f, cosf(i_fRadian),	-sinf(i_fRadian),	0.0f,
			0.0f, sinf(i_fRadian),	cosf(i_fRadian),	0.0f,
			0.0f, 0.0f,				0.0f,				1.0f
		};

		memcpy( m, fMatrixArray, sizeof( float ) * 16 );
		
		return *this ;
	}
	
	Matrix&	scaling( float i_fX, float i_fY, float i_fZ )
	{
		const float fMatrixArray[ 16 ] = {
			i_fX, 0.0f, 0.0f, 0.0f,
			0.0f, i_fY, 0.0f, 0.0f,
			0.0f, 0.0f, i_fZ, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};

		memcpy( m, fMatrixArray, sizeof( float ) * 16 );
		
		return *this ;
	}
};

#endif
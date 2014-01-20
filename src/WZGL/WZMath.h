/**
 * @file		WZGLMath.h
 * @brief		WZGL�̐��w���C�u�����̒�`
 *
 *	�x�N�g�����Z�Ȃǂ̊g���@�\���g�p����ꍇ�ɃC���N���[�h����
 */

#ifndef __WZMath__
#define __WZMath__

#include <math.h>
#include <string.h>

/// ��(�p�C)��\���萔
const double WZ_PI = 3.14159265358979323846264338327950288 ;

/**
 * @brief		�f�B�O���[�p���烉�W�A���p�𓾂�֐�
 *
 * @param[in]	degree	�f�B�O���[�p
 *
 * @return		template<class T>	���W�A���p
 */
template <class T>
inline T rad( T degree )
{
	return degree / static_cast<T>( 180.0 ) * static_cast<T>( WZ_PI ) ;
}

/**
 * @brief		���W�A���p����f�B�O���[�p�𓾂�֐�
 *
 * @param[in]	radian	���W�A���p
 *
 * @return		template<class T>	�f�B�O���[�p
 */
template <class T>
inline T deg( T radian )
{
	return radian * static_cast<T>( 180.0 ) / static_cast<T>( WZ_PI ) ;
}

/// �R�����x�N�g����\���\����
struct  Vector3
{
	float x,                    ///< �x�N�g���̂w����
		  y,                    ///< �x�N�g���̂x����
		  z ;                   ///< �x�N�g���̂y����

	/**
	 * @brief		�f�t�H���g�R���X�g���N�^
	 *
	 * @return		�Ȃ� (none)
	 */
	Vector3()
	{
	}

	/**
	 * @brief		�R���X�g���N�^�i�������w��j
	 *
	 * @param[in]	i_fX	��������x�N�g���̂w���W
	 * @param[in]	i_fY	��������x�N�g���̂x���W
	 * @param[in]	i_fZ	��������x�N�g���̂y���W
	 *
	 * @return		�Ȃ� (none)
	 */
	Vector3( float i_fX, float i_fY, float i_fZ )
		: x( i_fX ), y( i_fY ), z( i_fZ )
	{
	}

	/**
	 * @brief		�R�s�[�R���X�g���N�^
	 *
	 * @param[in]	i_Vec	�R�s�[���̃x�N�g��
	 *
	 * @return		�Ȃ� (none)
	 */
	Vector3( const Vector3& i_Vec )
		: x( i_Vec.x ), y( i_Vec.y ), z( i_Vec.z )
	{
	}

	/**
	 * @brief		�x�N�g���̑傫�������߂�֐�
	 *
	 * @return		float	�x�N�g���̑傫��
	 */
	float length()
	{
		return sqrt( x * x + y * y + z * z );
	}

	/**
	 * @brief		���݂̃x�N�g���𐳋K�������x�N�g�������߂�֐�
	 *
	 * @return		Vector3	���K�����ꂽ�x�N�g��
	 */
	Vector3 normalize()
	{
		return Vector3( x / length(), y / length(), z / length() ) ;
	}

	/**
	 * @brief		���݂̃x�N�g���Ƒ��̃x�N�g���Ƃ̓��ς����߂�֐�
	 *
	 * @param[in]	i_Vec	���ς̉E�ӂɂ�����x�N�g��
	 *
	 * @return		float	���ς̒l
	 */
	float dot( const Vector3& i_Vec )
	{
		return x * i_Vec.x + y * i_Vec.y + z * i_Vec.z ;
	}

	/**
	 * @brief		���݂̃x�N�g���Ƒ��̃x�N�g���Ƃ̊O�ς����߂�֐�
	 *
	 * @param[in]	i_Vec	�O�ς̉E�ӂɂ�����x�N�g��
	 *
	 * @return		Vector3	�O�ς̌��ʂɂ�����x�N�g��
	 */
	Vector3 cross( const Vector3& i_Vec )
	{
		return Vector3( y * i_Vec.z - z * i_Vec.y, z * i_Vec.x - x * i_Vec.z, x * i_Vec.y - y * i_Vec.x );
	}

	/**
	 * @brief		���������Z�q
	 *
	 * @return		Vector3	���̃x�N�g��
	 */
	Vector3 operator +() const
	{
		return Vector3( x, y, z ) ;
	}

	/**
	 * @brief		���������Z�q
	 *
	 * @return		Vector3	�t�x�N�g��
	 */
	Vector3 operator -() const
	{
		return Vector3( -x, -y, -z );
	}

	/**
	 * @brief		���Z���Z�q
	 *
	 * @param[in]	i_Vec	���Z���Z�̉E�ӂɂ�����x�N�g��
	 *
	 * @return		Vector3	�x�N�g�����Z�̉��Z���ʂɂ�����x�N�g��
	 */
	Vector3 operator +( const Vector3& i_Vec ) const
	{
		return Vector3( x + i_Vec.x, y + i_Vec.y, z + i_Vec.z ) ;
	}

	/**
	 * @brief		���Z���Z�q
	 *
	 * @param[in]	i_Vec	���Z���Z�̉E�ӂɂ�����x�N�g��
	 *
	 * @return		Vector3	�x�N�g�����Z�̌��ʂɂ�����x�N�g��
	 */
	Vector3 operator -( const Vector3& i_Vec ) const
	{
		return Vector3( x - i_Vec.x, y - i_Vec.y, z - i_Vec.z ) ;
	}

	/**
	 * @brief		��Z���Z�q�i�x�N�g���Ǝ����̏�Z�j
	 *
	 * @param[in]	i_fScale	��Z���Z�̉E�ӂɂ��������
	 *
	 * @return		Vector3	���Z��̃x�N�g��
	 */
	Vector3 operator *( float i_fScale ) const
	{
		return Vector3( x * i_fScale, y * i_fScale, z * i_fScale ) ;
	}

	/**
	 * @brief		���Z���Z�q�i�x�N�g���Ǝ����̏��Z�j
	 *
	 * @param[in]	i_fScale	���Z���Z�̉E�ӂɂ��������
	 *
	 * @return		Vector3	���Z��̃x�N�g��
	 */
	Vector3 operator /( float i_fScale ) const
	{
		return Vector3( x / i_fScale, y / i_fScale, z / i_fScale ) ;
	}

	/**
	 * @brief		���Z������Z�q
	 *
	 * @param[in]	i_Vec	���݂̃x�N�g���ɉ�����x�N�g��
	 *
	 * @return		Vector3&	���Z��̃x�N�g��
	 */
	Vector3&    operator +=( const Vector3& i_Vec )
	{
		x	+= i_Vec.x ;
		y	+= i_Vec.y ;
		z	+= i_Vec.z ;

		return *this ;
	}

	/**
	 * @brief		���Z������Z�q
	 *
	 * @param[in]	i_Vec	�����x�N�g��
	 *
	 * @return		Vector3& operator	���Z��̃x�N�g��
	 */
	Vector3&    operator -=( const Vector3& i_Vec )
	{
		x	-= i_Vec.x ;
		y	-= i_Vec.y ;
		z	-= i_Vec.z ;

		return *this ;
	}

	/**
	 * @brief		��Z������Z�q
	 *
	 * @param[in]	i_fScale	�x�N�g���Ɋ|�����킹�����
	 *
	 * @return		Vector3&	���Z��̃x�N�g��
	 */
	Vector3&    operator *=( float i_fScale )
	{
		x	*= i_fScale ;
		y	*= i_fScale ;
		z	*= i_fScale ;

		return *this ;
	}

	/**
	 * @brief		���Z������Z�q
	 *
	 * @param[in]	i_fScale	�x�N�g�����������
	 *
	 * @return		Vector3&	���Z��̃x�N�g��
	 */
	Vector3&    operator /=( float i_fScale )
	{
		x	/= i_fScale ;
		y	/= i_fScale ;
		z	/= i_fScale ;

		return *this ;
	}

	static const Vector3 Zero ; ///< �[���x�N�g�� ( 0.0f, 0.0f, 0.0f )
	static const Vector3 Up ;   ///< �A�b�v�x�N�g�� ( 0.0f, 1.0f, 0.0f )
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
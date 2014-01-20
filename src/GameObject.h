#ifndef __GameObject_h__
#define __GameObject_h__

#include "WZGL\WZGL.h"
#include <d3dx9.h>
class Game ;
class Scene ;
class Player ;
class Enemy ;

//	: �Q�[���I�u�W�F�N�g�̏�Ԃ�\���񋓌^
enum ObjectState
{
	Alive,	// �ʏ폈���̑Ώۏ��
	Dead	// �j���̑Ώۏ��
};

//	: �Q�[���I�u�W�F�N�g�N���X
class GameObject
{
protected :
	D3DXVECTOR3 m_vPos ;	// �ʒu�x�N�g��
	float		m_fHalf ;	// ���a�i�n�[�t�T�C�Y�j
	D3DXVECTOR3 m_vDir ;	// �����x�N�g��
	float		m_fRotate ;	// �����p�i���W�A���P�ʁj
	float		m_fSpeed ;	// ����

	ObjectState	m_eState ;	// �I�u�W�F�N�g�̏��

public :
	GameObject( const D3DXVECTOR3& i_vPos, float i_fHalf, const D3DXVECTOR3& i_vDir, float i_fRotate, float m_fSpeed );
	GameObject( const D3DXVECTOR3& i_vPos, float i_fHalf, float i_fRotate, float m_fSpeed );	//	: �������p�x�݂̂Ŏw�肷��o�[�W����
	~GameObject();

	virtual	Scene*	Update( const Game& i_Game )	= 0 ;
	virtual	void	Draw()		= 0 ;

	//	: �Q�b�^�[�n�̊֐�
	const D3DXVECTOR3&	GetPosition( void )	const
	{
		return m_vPos ;
	}

	float	GetHalf( void )	const
	{
		return m_fHalf ;
	}

	ObjectState	GetState( void )	const
	{
		return m_eState ;
	}

	//	: �q�b�g�n�̊֐��iGameObject�N���X�ł́A���ׂĂ̎q�N���X�ɑ΂���֐����������Afalse��Ԃ��j
	virtual bool	IsHit( Player* pPlayer )
	{
		return false ;
	}

	virtual bool	IsHit( Enemy* pEnemy )
	{
		return false ;
	}
};

#endif
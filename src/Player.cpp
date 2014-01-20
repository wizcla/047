#include "Game.h"
#include "WZGL\WZGL.h"
#include "GameObject.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"

Player::Player()
	: GameObject( D3DXVECTOR3( 320.0f, 240.0f, 0.0f ), 20.0f, D3DXToRadian(270.0f), 3.0f )
{
}

Scene*	Player::Update( const Game& i_Game )
{
	const XINPUT_GAMEPAD_EX&	pad	= i_Game.GetPads()[ 0 ] ;	//	: �O�Ԗڂ̃p�b�h�ւ̎Q�Ƃ𒼐ڎ擾����
	D3DXVECTOR3 vLStick( pad.fThumbLX, -pad.fThumbLY, 0.0f );	//	: �X�e�B�b�N�̌X�����x�N�g���ɕϊ�����i�p�b�h��Y���������X�N���[�����W�ɍ��킹��j

	//	: �X�e�B�b�N���X���Ă���������ƈʒu���X�V����
	if( D3DXVec3Length( &vLStick ) > 0.0f ) {
		D3DXVec3Normalize( &m_vDir, &vLStick );		//	: �����̓X�e�B�b�N�̌X���x�N�g���𐳋K����������
		m_fRotate	= atan2( m_vDir.y, m_vDir.x );	//	: �v���C���[�̉�]�p�͌����x�N�g�������W�A���p�ɒ���������

		m_vPos	+= vLStick * m_fSpeed ;	//	: �ړ��̂Ƃ��Ɏg���x�N�g���̓X�e�B�b�N�̂��́i���K������Ă��Ȃ��j
	}

	return NULL ;
}

void	Player::Draw()
{
	fillTri( m_vPos.x, m_vPos.y, m_fHalf, D3DXToDegree( m_fRotate ) );
}

bool	Player::IsHit( Enemy* pEnemy )
{
	const D3DXVECTOR3	vToEnemy	= pEnemy->GetPosition() - m_vPos ;

	return D3DXVec3Length( &vToEnemy ) < m_fHalf + pEnemy->GetHalf() ;
}
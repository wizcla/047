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
	const XINPUT_GAMEPAD_EX&	pad	= i_Game.GetPads()[ 0 ] ;	//	: ０番目のパッドへの参照を直接取得する
	D3DXVECTOR3 vLStick( pad.fThumbLX, -pad.fThumbLY, 0.0f );	//	: スティックの傾きをベクトルに変換する（パッドのY軸方向をスクリーン座標に合わせる）

	//	: スティックが傾いていたら向きと位置を更新する
	if( D3DXVec3Length( &vLStick ) > 0.0f ) {
		D3DXVec3Normalize( &m_vDir, &vLStick );		//	: 向きはスティックの傾きベクトルを正規化したもの
		m_fRotate	= atan2( m_vDir.y, m_vDir.x );	//	: プレイヤーの回転角は向きベクトルをラジアン角に直したもの

		m_vPos	+= vLStick * m_fSpeed ;	//	: 移動のときに使うベクトルはスティックのもの（正規化されていない）
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
#ifndef __GameObject_h__
#define __GameObject_h__

#include "WZGL\WZGL.h"
#include <d3dx9.h>
class Game ;
class Scene ;
class Player ;
class Enemy ;

//	: ゲームオブジェクトの状態を表す列挙型
enum ObjectState
{
	Alive,	// 通常処理の対象状態
	Dead	// 破棄の対象状態
};

//	: ゲームオブジェクトクラス
class GameObject
{
protected :
	D3DXVECTOR3 m_vPos ;	// 位置ベクトル
	float		m_fHalf ;	// 半径（ハーフサイズ）
	D3DXVECTOR3 m_vDir ;	// 方向ベクトル
	float		m_fRotate ;	// 方向角（ラジアン単位）
	float		m_fSpeed ;	// 速さ

	ObjectState	m_eState ;	// オブジェクトの状態

public :
	GameObject( const D3DXVECTOR3& i_vPos, float i_fHalf, const D3DXVECTOR3& i_vDir, float i_fRotate, float m_fSpeed );
	GameObject( const D3DXVECTOR3& i_vPos, float i_fHalf, float i_fRotate, float m_fSpeed );	//	: 向きを角度のみで指定するバージョン
	~GameObject();

	virtual	Scene*	Update( const Game& i_Game )	= 0 ;
	virtual	void	Draw()		= 0 ;

	//	: ゲッター系の関数
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

	//	: ヒット系の関数（GameObjectクラスでは、すべての子クラスに対する関数を実装し、falseを返す）
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
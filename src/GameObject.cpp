#include "GameObject.h"

GameObject::GameObject( const D3DXVECTOR3& i_vPos, float i_fHalf, const D3DXVECTOR3& i_vDir, float i_fRotate, float i_fSpeed )
	: m_vPos( i_vPos ), m_fHalf( i_fHalf ), m_vDir( i_vDir ), m_fRotate( i_fRotate ), m_fSpeed( i_fSpeed ), m_eState( ObjectState::Alive )
{
}

GameObject::GameObject( const D3DXVECTOR3& i_vPos, float i_fHalf, float i_fRotate, float i_fSpeed )
	: m_vPos( i_vPos ), m_fHalf( i_fHalf ), m_vDir( cos(i_fRotate), sin(i_fRotate), 0.0f ), m_fRotate( i_fRotate ), m_fSpeed( i_fSpeed ), m_eState( ObjectState::Alive )
{
}

GameObject::~GameObject()
{
}
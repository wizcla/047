/**
 * @file		WZGL.h
 * @brief		WZGL���C�u�����̖{��
 *
 *	WZGL�̊�{�I�ȋ@�\���g�p���邽�߂ɍŒ���K�v�ȃw�b�_�t�@�C��
 */

#ifndef __WZGL__
#define __WZGL__
#pragma once

/**
 * @mainpage WZGL ���C�u����
 *
 * @section WZGL���C�u�����ɂ���
 *
 * WZGL���C�u�����͂b����̏����҂��ȒP�ȃO���t�B�b�N�X�����̊�b���w�Ԃ��߂̃t���[�����[�N�ł��B
 * �R���\�[���A�v���P�[�V�����̍쐬�Ɏ����R�[�f�B���O�ŒP���Ȑ}�`�`��⃊�A���^�C�������������ł��܂��B
 *
 * @section �J���Ӑ}
 *
 * �Q�[����R���s���[�^�O���t�B�N�X���̃��A���^�C�������͂b����̏��w�҂ɂ͕~���������A�b����̕��@�͗����ł�����������ǂ̂悤�Ɏg�p����΃O���t�B�N�X�����ɂȂ���̂��Ƃ��������ɂȂ�Ƌɒ[�ɂɕ~���������Ȃ��Ă��܂��܂��B
 * OpenGL��DirectX���g�p����Ώ��p���x���̍��x�ȏ������\�ł����A��{���@�𗝉������΂���̏��w�҂ɂ͔��ɓ���ł������G�ȏ����������������Ă͐�ɐi�߂܂���B
 * WZGL�͂����̃O���t�B�N�X���C�u�������g�p����Ɏ��鑫������Ƃ��āA�w�K�p�Ɏg�p���邱�Ƃ�ړI�ɊJ�����܂����B
 * �܂��A�P�ɂb����̊w�K�Ƃ����ʂɂ����Ă��O���t�B�N�X�������ނɂ��邱�ƂŁA�������x���ł̏K�n�����ҏo����ƍl���Ă���܂��B
 */

#include "WZGLCore.h"
//#include "WZMath.h"
#include <stdio.h>

#define FONT_WIDTH  ( 8 )	///< ������`��֐��Ŏg�p���镶���̕�
#define FONT_HEIGHT ( 16 )	///< ������`��֐��Ŏg�p���镶���̍���


//	: �O���[�o���֐��imain.cpp�Ŏg�p���邱�ƑO��j
int		main( void );
void	begin( void );
void	end( void );

int		strDraw( const char* i_string );
int		drawString( const char* i_string, ... );
void	setPrintPos( int i_iX, int i_iY );

void	line( float i_fStartX, float i_fStartY, float i_fEndX, float i_fEndY );
void	fillRect( float i_fStartX, float i_fStartY, float i_fWidth, float i_fHeight );
void	strokeRect( float i_fStartX, float i_fStartY, float i_fWidth, float i_fHeight );
void	fillCircle( float i_fCenterX, float i_fCenterY, float i_fRadius );
void	strokeCircle( float i_fCenterX, float i_fCenterY, float i_fRadius );
void	fillTri( float i_fCenterX, float i_fCenterY, float i_fRadius, float i_fAngle = 0.0f );
void	strokeTri( float i_fCenterX, float i_fCenterY, float i_fRadius, float i_fAngle = 0.0f );
void	fillStar( float i_fCenterX, float i_fCenterY, float i_fRadius, float i_fAngle = 0.0f );
void	strokeStar( float i_fCenterX, float i_fCenterY, float i_fRadius, float i_fAngle = 0.0f );

bool	isKeyDown( int i_iKeyCode );
float	getCursorX( void );
float	getCursorY( void );

#endif
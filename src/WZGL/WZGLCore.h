/**
 * @file		WZGLCore.h
 * @brief		WZGL���C�u�����A�v���P�[�V�����̏��������s���N���X�̒�`
 *
 *	WZGL.cpp�̃G���g���|�C���g�ŌĂяo�����
 */

#ifndef __WZGLCore__
#define __WZGLCore__

#pragma once
#pragma comment( lib, "OpenGL32.lib" )

#include <windows.h>
#include <tchar.h>
#include <process.h>
#include <gl/gl.h>

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH    ( 640 )	///< �A�v���P�[�V�����E�B���h�E�̕�
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT   ( 480 )	///< �A�v���P�[�V�����E�B���h�E�̍���
#endif

/**
 * @class		WZGL
 * @brief		�A�v���P�[�V�����������N���X�i�V���O���g���j
 */
class WZGL
{
private:
	HDC		m_hDC ;     //	: �A�v���P�[�V�����Ŏg�p����f�o�C�X�R���e�L�X�g
	HFONT	m_hFont ;   //	: �A�v���P�[�V�����Ŏg�p����t�H���g�I�u�W�F�N�g�iprintf�֐��Ŏg�p�j
	LPCTSTR m_Title ;   //	: �A�v���P�[�V�����E�B���h�E�̃^�C�g��
	HWND	m_hWnd ;    //	: �A�v���P�[�V�����E�B���h�E�̃n���h��
	HGLRC	m_hGLRC ;   //	: OpenGL�̃R���e�L�X�g

	DWORD	m_dwBeforeTime ;

private:
	void		initGL( void ); //	: OpenGL�̏��������s���֐�
	static void mainThread( void* pvArg );  //	: main()�̎��s���s�����߂̃X���b�h�p�֐�

	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );   //	: �E�B���h�E�v���V�[�W��
	void					makeWindow( void );

	WZGL( LPCTSTR i_sTitle = TEXT( "WZGL" ) );    //	: �R���X�g���N�^

public:
	/**
	 * @brief		WZGL�N���X�̃C���X�^���X���擾���邽�߂̊֐�
	 *
	 * @return		WZGL&	WZGL�N���X�̃C���X�^���X
	 */
	static WZGL& getInstance( void )   //	: WZGL�N���X�̃C���X�^���X�𓾂邽�߂̊֐�
	{
		static WZGL WZGLInstance ;    //	: �V���O���g���p�̃C���X�^���X

		return WZGLInstance ;
	}

	~WZGL();
	
	int run();

public:
	/**
	 * @brief		printf�֐��p�̃t�H���g�I�u�W�F�N�g���擾����֐�
	 *
	 * @return		const HFONT	�t�H���g�I�u�W�F�N�g
	 */
	const HFONT getFont( void ) const
	{
		return m_hFont ;
	}

	/**
	 * @brief		�A�v���P�[�V�����̃f�o�C�X�R���e�L�X�g���擾����֐�
	 *
	 * @return		const HDC	�f�o�C�X�R���e�L�X�g
	 */
	const HDC getDC( void ) const
	{
		return m_hDC ;
	}

	/**
	 * @brief		�A�v���P�[�V�����̃E�B���h�E�n���h�����擾����֐�
	 *
	 * @return		const HDC	�f�o�C�X�R���e�L�X�g
	 */
	const HWND	getWindowHandle( void ) const
	{
		return m_hWnd ;
	}

	/**
	 * @brief		FPS���U�O�𒴂��Ă��܂����Ƃ��ɁA���ߕ��X���[�v������֐�
	 *
	 * @return		�Ȃ�
	 */
	void keep60fps();
};

/**
 * @class		WZExeption
 * @brief		��O�X���[�p�̃N���X
 *
 * ����������O�̃^�C�g���Ɠ��e�𕶎���ŊǗ�����
 */
class WZExeption
{
private:
	TCHAR	m_sTitle[ 256 ] ;
	TCHAR	m_sMessage[ 256 ] ;

public:
	/**
	 * @brief		�p�����[�^�t���R���X�g���N�^
	 *
	 * @param[in]	i_sTitle	��O�̃^�C�g��
	 * @param[in]	i_sMessage	��O�̓��e
	 *
	 * @return		�Ȃ� (none)
	 */
	WZExeption( LPCTSTR i_sTitle, LPCTSTR i_sMessage )
	{
		_tcsncpy_s( m_sTitle, i_sTitle, 256 );
		_stprintf_s( m_sMessage, 256, TEXT( "%s\nin %s" ), i_sMessage, TEXT( __FILE__ ) );
	}
	

	/// �f�X�g���N�^
	~WZExeption()
	{
	}

	/**
	 * @brief		��O�̃^�C�g�����擾����֐�
	 *
	 * @return		LPCTSTR	��O�̃^�C�g��
	 */
	LPCTSTR getTitle( void )    const
	{
		return m_sTitle ;
	}

	/**
	 * @brief		��O�̓��e���擾����֐�
	 *
	 * @return		LPCTSTR	��O�̓��e
	 */
	LPCTSTR getMessage( void )  const
	{
		return m_sMessage ;
	}

	/**
	 * @brief		��O�����b�Z�[�W�{�b�N�X�ŕ\������֐�
	 *
	 * @return		�Ȃ� (none)
	 */
	void showMessage( void ) const
	{
		MessageBox( NULL, m_sMessage, m_sTitle, MB_OK );
	}
};

#endif

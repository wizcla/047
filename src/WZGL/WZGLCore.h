/**
 * @file		WZGLCore.h
 * @brief		WZGLライブラリアプリケーションの初期化を行うクラスの定義
 *
 *	WZGL.cppのエントリポイントで呼び出される
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
#define SCREEN_WIDTH    ( 640 )	///< アプリケーションウィンドウの幅
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT   ( 480 )	///< アプリケーションウィンドウの高さ
#endif

/**
 * @class		WZGL
 * @brief		アプリケーション初期化クラス（シングルトン）
 */
class WZGL
{
private:
	HDC		m_hDC ;     //	: アプリケーションで使用するデバイスコンテキスト
	HFONT	m_hFont ;   //	: アプリケーションで使用するフォントオブジェクト（printf関数で使用）
	LPCTSTR m_Title ;   //	: アプリケーションウィンドウのタイトル
	HWND	m_hWnd ;    //	: アプリケーションウィンドウのハンドル
	HGLRC	m_hGLRC ;   //	: OpenGLのコンテキスト

	DWORD	m_dwBeforeTime ;

private:
	void		initGL( void ); //	: OpenGLの初期化を行う関数
	static void mainThread( void* pvArg );  //	: main()の実行を行うためのスレッド用関数

	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );   //	: ウィンドウプロシージャ
	void					makeWindow( void );

	WZGL( LPCTSTR i_sTitle = TEXT( "WZGL" ) );    //	: コンストラクタ

public:
	/**
	 * @brief		WZGLクラスのインスタンスを取得するための関数
	 *
	 * @return		WZGL&	WZGLクラスのインスタンス
	 */
	static WZGL& getInstance( void )   //	: WZGLクラスのインスタンスを得るための関数
	{
		static WZGL WZGLInstance ;    //	: シングルトン用のインスタンス

		return WZGLInstance ;
	}

	~WZGL();
	
	int run();

public:
	/**
	 * @brief		printf関数用のフォントオブジェクトを取得する関数
	 *
	 * @return		const HFONT	フォントオブジェクト
	 */
	const HFONT getFont( void ) const
	{
		return m_hFont ;
	}

	/**
	 * @brief		アプリケーションのデバイスコンテキストを取得する関数
	 *
	 * @return		const HDC	デバイスコンテキスト
	 */
	const HDC getDC( void ) const
	{
		return m_hDC ;
	}

	/**
	 * @brief		アプリケーションのウィンドウハンドルを取得する関数
	 *
	 * @return		const HDC	デバイスコンテキスト
	 */
	const HWND	getWindowHandle( void ) const
	{
		return m_hWnd ;
	}

	/**
	 * @brief		FPSが６０を超えてしまったときに、超過分スリープさせる関数
	 *
	 * @return		なし
	 */
	void keep60fps();
};

/**
 * @class		WZExeption
 * @brief		例外スロー用のクラス
 *
 * 発生した例外のタイトルと内容を文字列で管理する
 */
class WZExeption
{
private:
	TCHAR	m_sTitle[ 256 ] ;
	TCHAR	m_sMessage[ 256 ] ;

public:
	/**
	 * @brief		パラメータ付きコンストラクタ
	 *
	 * @param[in]	i_sTitle	例外のタイトル
	 * @param[in]	i_sMessage	例外の内容
	 *
	 * @return		なし (none)
	 */
	WZExeption( LPCTSTR i_sTitle, LPCTSTR i_sMessage )
	{
		_tcsncpy_s( m_sTitle, i_sTitle, 256 );
		_stprintf_s( m_sMessage, 256, TEXT( "%s\nin %s" ), i_sMessage, TEXT( __FILE__ ) );
	}
	

	/// デストラクタ
	~WZExeption()
	{
	}

	/**
	 * @brief		例外のタイトルを取得する関数
	 *
	 * @return		LPCTSTR	例外のタイトル
	 */
	LPCTSTR getTitle( void )    const
	{
		return m_sTitle ;
	}

	/**
	 * @brief		例外の内容を取得する関数
	 *
	 * @return		LPCTSTR	例外の内容
	 */
	LPCTSTR getMessage( void )  const
	{
		return m_sMessage ;
	}

	/**
	 * @brief		例外をメッセージボックスで表示する関数
	 *
	 * @return		なし (none)
	 */
	void showMessage( void ) const
	{
		MessageBox( NULL, m_sMessage, m_sTitle, MB_OK );
	}
};

#endif

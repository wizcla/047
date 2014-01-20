/**
 * @file		WZGLCore.cpp
 * @brief		WZGLライブラリアプリケーションの初期化を行うクラスの実装
 */

#include "WZGLCore.h"
#include "WZGL.h"

/**
 * @brief		OpenGLの初期化を行う関数
 *
 * @return		なし (none)
 */
void	WZGL::initGL()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		32, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24, //Number of bits for the depthbuffer
		8, //Number of bits for the stencilbuffer
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	try{
		//	: エラーメッセージのタイトル
		LPCTSTR	sErrorTitle	= TEXT("Error in initGL() function .") ;

		//	: アプリケーションウィンドウからデバイスコンテキストを取得
		m_hDC = GetDC( m_hWnd );
		if( !m_hDC )
			throw WZExeption( sErrorTitle, TEXT("デバイスコンテキストの取得に失敗しました。") );

		//	: デバイスコンテキストが使用するピクセルフォーマットを選択
		int format = ChoosePixelFormat( m_hDC, &pfd );
		if ( !format )
			throw WZExeption( sErrorTitle, TEXT("対象となるピクセルフォーマットが存在しません。") );

		//	: OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
		if ( !SetPixelFormat( m_hDC, format, &pfd ) )  //	: DCへフォーマットを設定するのに失敗
			throw WZExeption( sErrorTitle, TEXT("デバイスコンテキストにピクセルフォーマットを設定出来ませんでした。") );

		//	: OpenGL contextを生成
		m_hGLRC = wglCreateContext( m_hDC );
		if ( !m_hGLRC )
			throw WZExeption( sErrorTitle, TEXT("OpenGL コンテキストの生成に失敗しました。") );

		//	: OpenGLコンテキストを使用する
		if ( !wglMakeCurrent( m_hDC, m_hGLRC ) )
			throw WZExeption( sErrorTitle, TEXT("OpenGL コンテキストを使用できません。") );
	}
	catch( ... )
	{
		throw ;
	}
}

/**
 * @brief		描画スレッド
 *
 * @param[in,out]	pvArg	未使用
 *
 * @return		なし (none)
 */
void WZGL::mainThread( void* pvArg )
{
	//	: OpenGLを初期化
	try {
		WZGL::getInstance().initGL();

#if	0
		//	: 垂直同期処理
		typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( BOOL );
		PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress( "wglSwapIntervalEXT" );	// : wglSwapIntervalEXT関数を取得
		if( wglSwapIntervalEXT == NULL )
			MessageBox( 0, TEXT("wglSwapInterbalEXTの取得に失敗"), TEXT("この環境ではVSyncの同期ができません。固定FPSを実現できません"), MB_OK );
		else
			wglSwapIntervalEXT( true );
#endif
	}
	catch( WZExeption& e ) {
		e.showMessage();
	}
	
	//	: 描画スレッド開始
	begin();
	main();
	end();

	_endthread();
}

/**
 * @brief		ウィンドウプロシージャ
 *
 * @param[in]		hWnd	ウィンドウハンドル
 * @param[in]		uMsg	メッセージ
 * @param[in]		wParam	パラメータ
 * @param[in,out]	lParam	パラメータ
 *
 * @return		LRESULT CALLBACK	エラーコード
 */
LRESULT CALLBACK WZGL::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0 ;

	case ( WM_KEYDOWN ):
		if ( wParam == VK_ESCAPE )  //	: ESCキーが押されたら終了
			PostQuitMessage( 0 );

		return 0 ;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

/**
 * @brief		コンストラクタ
 *
 * @param[in]	i_sTitle	ウィンドウタイトル
 *
 * @return		なし (none)
 */
WZGL::WZGL( LPCTSTR i_sTitle )
	: m_Title( i_sTitle ), m_hWnd( NULL ), m_hGLRC( NULL ), m_hDC( NULL ), m_hFont( NULL ), m_dwBeforeTime( GetTickCount() )
{
	try {
		//	: ウィンドウの作成
		makeWindow();

		//	: フォントの生成
		m_hFont = CreateFont( FONT_HEIGHT, FONT_WIDTH, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY | PROOF_QUALITY, FIXED_PITCH, 0 );
		if( !m_hFont )
			throw WZExeption( TEXT("Error in WZGL Constracter ."), TEXT("フォントの生成に失敗しました。") );
	}
	catch( WZExeption &e )
	{
		e.showMessage();
		exit( 0 );
	}

	//	: スレッドを開始
	_beginthread( mainThread, 0, NULL );
}

/**
 * @brief		デストラクタ
 *
 * 終了時にOpenGL用コンテキストとデバイスコンテキストを解放する
 * @return		なし (none)
 */
WZGL::~WZGL()
{
	//	: カレントコンテキストを無効にする
	wglMakeCurrent( NULL, NULL );
	//	: カレントコンテキストを削除
	wglDeleteContext( m_hGLRC );
	//	: デバイスコンテキスト解放
	ReleaseDC( m_hWnd, m_hDC );
}

/**
 * @brief		アプリケーションウィンドウを作成する関数
 *
 * @return		なし (none)
 */
void WZGL::makeWindow()
{
	WNDCLASS wc ;

	wc.style			= CS_HREDRAW | CS_VREDRAW ;
	wc.lpfnWndProc		= WZGL::WindowProc ;
	wc.cbClsExtra		= 0 ;
	wc.cbWndExtra		= 0 ;
	wc.hInstance		= GetModuleHandle( NULL );
	wc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground	= (HBRUSH)GetStockObject( BLACK_BRUSH );
	wc.lpszMenuName		= NULL ;
	wc.lpszClassName	= m_Title ;

	try {
		LPCTSTR	sErrorTitle	= TEXT("Error in makeWindow() Function .") ;
		
		if ( !RegisterClass( &wc ) ) {
			throw WZExeption( sErrorTitle, TEXT( "ウィンドウクラスの作成に失敗しました" ) );
		}

		//	: アプリケーション・ウィンドウの作成
		RECT R = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		AdjustWindowRect( &R, WS_OVERLAPPEDWINDOW, FALSE );
		m_hWnd = CreateWindow( m_Title, m_Title, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, R.right - R.left, R.bottom - R.top, NULL, NULL, GetModuleHandle( NULL ), NULL );
		if ( !m_hWnd ) {
			throw WZExeption( sErrorTitle, TEXT( "ウィンドウの生成に失敗しました" ) );
		}

		//	: 作成したウィンドウを表示
		ShowWindow( m_hWnd, SW_SHOW );
	}
	catch( ... )
	{
		throw ;
	}
}

/**
 * @brief		メッセージループを開始する関数
 *
 * @return		int	アプリケーション終了メッセージのパラメータ
 */
int WZGL::run()
{
	MSG msg ;

	while ( GetMessage( &msg, NULL, 0, 0 ) > 0 ) {
		DispatchMessage( &msg );
	}

	return (int)msg.wParam ;
}

/**
 * @brief		keep60fps関数
 * @author		Hiroki Tamura
 * @date		2013/07/13
 *
 * @return		なし (none)
 */
void	WZGL::keep60fps()
{
	//	: フレームレートの調整（1秒を60フレームに保つ）
	DWORD	dwNowTime		= GetTickCount();
	DWORD	dwElapsedTime	= dwNowTime - m_dwBeforeTime ;
	m_dwBeforeTime	= dwNowTime ;
	
	if( dwElapsedTime < 17 )
			Sleep( 17 - dwElapsedTime );
//	else	Sleep( 1 );
}

/**
 * @brief		エントリポイント
 *
 * WZGLライブラリの起動を行う
 * @param[in]		未使用
 * @param[in]		未使用
 * @param[in,out]	未使用
 * @param[in]		未使用
 *
 * @return		int APIENTRY
 */
int APIENTRY _tWinMain( HINSTANCE, HINSTANCE, LPTSTR, int )
{
	return WZGL::getInstance().run();
}


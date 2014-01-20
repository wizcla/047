/**
 * @file		WZGLCore.cpp
 * @brief		WZGL���C�u�����A�v���P�[�V�����̏��������s���N���X�̎���
 */

#include "WZGLCore.h"
#include "WZGL.h"

/**
 * @brief		OpenGL�̏��������s���֐�
 *
 * @return		�Ȃ� (none)
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
		//	: �G���[���b�Z�[�W�̃^�C�g��
		LPCTSTR	sErrorTitle	= TEXT("Error in initGL() function .") ;

		//	: �A�v���P�[�V�����E�B���h�E����f�o�C�X�R���e�L�X�g���擾
		m_hDC = GetDC( m_hWnd );
		if( !m_hDC )
			throw WZExeption( sErrorTitle, TEXT("�f�o�C�X�R���e�L�X�g�̎擾�Ɏ��s���܂����B") );

		//	: �f�o�C�X�R���e�L�X�g���g�p����s�N�Z���t�H�[�}�b�g��I��
		int format = ChoosePixelFormat( m_hDC, &pfd );
		if ( !format )
			throw WZExeption( sErrorTitle, TEXT("�ΏۂƂȂ�s�N�Z���t�H�[�}�b�g�����݂��܂���B") );

		//	: OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
		if ( !SetPixelFormat( m_hDC, format, &pfd ) )  //	: DC�փt�H�[�}�b�g��ݒ肷��̂Ɏ��s
			throw WZExeption( sErrorTitle, TEXT("�f�o�C�X�R���e�L�X�g�Ƀs�N�Z���t�H�[�}�b�g��ݒ�o���܂���ł����B") );

		//	: OpenGL context�𐶐�
		m_hGLRC = wglCreateContext( m_hDC );
		if ( !m_hGLRC )
			throw WZExeption( sErrorTitle, TEXT("OpenGL �R���e�L�X�g�̐����Ɏ��s���܂����B") );

		//	: OpenGL�R���e�L�X�g���g�p����
		if ( !wglMakeCurrent( m_hDC, m_hGLRC ) )
			throw WZExeption( sErrorTitle, TEXT("OpenGL �R���e�L�X�g���g�p�ł��܂���B") );
	}
	catch( ... )
	{
		throw ;
	}
}

/**
 * @brief		�`��X���b�h
 *
 * @param[in,out]	pvArg	���g�p
 *
 * @return		�Ȃ� (none)
 */
void WZGL::mainThread( void* pvArg )
{
	//	: OpenGL��������
	try {
		WZGL::getInstance().initGL();

#if	0
		//	: ������������
		typedef BOOL (APIENTRY *PFNWGLSWAPINTERVALFARPROC)( BOOL );
		PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress( "wglSwapIntervalEXT" );	// : wglSwapIntervalEXT�֐����擾
		if( wglSwapIntervalEXT == NULL )
			MessageBox( 0, TEXT("wglSwapInterbalEXT�̎擾�Ɏ��s"), TEXT("���̊��ł�VSync�̓������ł��܂���B�Œ�FPS�������ł��܂���"), MB_OK );
		else
			wglSwapIntervalEXT( true );
#endif
	}
	catch( WZExeption& e ) {
		e.showMessage();
	}
	
	//	: �`��X���b�h�J�n
	begin();
	main();
	end();

	_endthread();
}

/**
 * @brief		�E�B���h�E�v���V�[�W��
 *
 * @param[in]		hWnd	�E�B���h�E�n���h��
 * @param[in]		uMsg	���b�Z�[�W
 * @param[in]		wParam	�p�����[�^
 * @param[in,out]	lParam	�p�����[�^
 *
 * @return		LRESULT CALLBACK	�G���[�R�[�h
 */
LRESULT CALLBACK WZGL::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0 ;

	case ( WM_KEYDOWN ):
		if ( wParam == VK_ESCAPE )  //	: ESC�L�[�������ꂽ��I��
			PostQuitMessage( 0 );

		return 0 ;
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

/**
 * @brief		�R���X�g���N�^
 *
 * @param[in]	i_sTitle	�E�B���h�E�^�C�g��
 *
 * @return		�Ȃ� (none)
 */
WZGL::WZGL( LPCTSTR i_sTitle )
	: m_Title( i_sTitle ), m_hWnd( NULL ), m_hGLRC( NULL ), m_hDC( NULL ), m_hFont( NULL ), m_dwBeforeTime( GetTickCount() )
{
	try {
		//	: �E�B���h�E�̍쐬
		makeWindow();

		//	: �t�H���g�̐���
		m_hFont = CreateFont( FONT_HEIGHT, FONT_WIDTH, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, SHIFTJIS_CHARSET, OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY | PROOF_QUALITY, FIXED_PITCH, 0 );
		if( !m_hFont )
			throw WZExeption( TEXT("Error in WZGL Constracter ."), TEXT("�t�H���g�̐����Ɏ��s���܂����B") );
	}
	catch( WZExeption &e )
	{
		e.showMessage();
		exit( 0 );
	}

	//	: �X���b�h���J�n
	_beginthread( mainThread, 0, NULL );
}

/**
 * @brief		�f�X�g���N�^
 *
 * �I������OpenGL�p�R���e�L�X�g�ƃf�o�C�X�R���e�L�X�g���������
 * @return		�Ȃ� (none)
 */
WZGL::~WZGL()
{
	//	: �J�����g�R���e�L�X�g�𖳌��ɂ���
	wglMakeCurrent( NULL, NULL );
	//	: �J�����g�R���e�L�X�g���폜
	wglDeleteContext( m_hGLRC );
	//	: �f�o�C�X�R���e�L�X�g���
	ReleaseDC( m_hWnd, m_hDC );
}

/**
 * @brief		�A�v���P�[�V�����E�B���h�E���쐬����֐�
 *
 * @return		�Ȃ� (none)
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
			throw WZExeption( sErrorTitle, TEXT( "�E�B���h�E�N���X�̍쐬�Ɏ��s���܂���" ) );
		}

		//	: �A�v���P�[�V�����E�E�B���h�E�̍쐬
		RECT R = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		AdjustWindowRect( &R, WS_OVERLAPPEDWINDOW, FALSE );
		m_hWnd = CreateWindow( m_Title, m_Title, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, R.right - R.left, R.bottom - R.top, NULL, NULL, GetModuleHandle( NULL ), NULL );
		if ( !m_hWnd ) {
			throw WZExeption( sErrorTitle, TEXT( "�E�B���h�E�̐����Ɏ��s���܂���" ) );
		}

		//	: �쐬�����E�B���h�E��\��
		ShowWindow( m_hWnd, SW_SHOW );
	}
	catch( ... )
	{
		throw ;
	}
}

/**
 * @brief		���b�Z�[�W���[�v���J�n����֐�
 *
 * @return		int	�A�v���P�[�V�����I�����b�Z�[�W�̃p�����[�^
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
 * @brief		keep60fps�֐�
 * @author		Hiroki Tamura
 * @date		2013/07/13
 *
 * @return		�Ȃ� (none)
 */
void	WZGL::keep60fps()
{
	//	: �t���[�����[�g�̒����i1�b��60�t���[���ɕۂj
	DWORD	dwNowTime		= GetTickCount();
	DWORD	dwElapsedTime	= dwNowTime - m_dwBeforeTime ;
	m_dwBeforeTime	= dwNowTime ;
	
	if( dwElapsedTime < 17 )
			Sleep( 17 - dwElapsedTime );
//	else	Sleep( 1 );
}

/**
 * @brief		�G���g���|�C���g
 *
 * WZGL���C�u�����̋N�����s��
 * @param[in]		���g�p
 * @param[in]		���g�p
 * @param[in,out]	���g�p
 * @param[in]		���g�p
 *
 * @return		int APIENTRY
 */
int APIENTRY _tWinMain( HINSTANCE, HINSTANCE, LPTSTR, int )
{
	return WZGL::getInstance().run();
}


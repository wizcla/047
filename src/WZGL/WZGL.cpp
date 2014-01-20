/**
 * @file		WZGL.cpp
 * @brief		WZGL���C�u�����̖{��
 */

#include "WZGL.h"
#include "WZMath.h"

//	: �O���[�o���ϐ�
static int g_iFontPosX	= 0,            ///< printf�֐��̕�����`��J�n�ʒu�̂w���W
		   g_iFontPosY	= FONT_HEIGHT ; ///< printf�֐��̕�����`��J�n�ʒu�̂x���W

//	: begin() �� end() �̑Ή����m���ɂ��邽�߂̃t���O
static bool	g_bDrawable	= false ;

/**
 * @brief		�O���t�B�b�N�@�\�̎g�p���J�n���邽�߂̊֐�
 *
 * @return		�Ȃ� (none)
 */
void begin( void )
{
#if 0
	static DWORD	s_dwTime	= 0 ;
	static int		s_iFPS		= 0 ;
	
	static DWORD	s_dwBeforeTime	= GetTickCount();
	DWORD			dwNowTime		= GetTickCount();
	DWORD			dwElapsedTime	= dwNowTime - s_dwBeforeTime ;
	s_dwBeforeTime	= dwNowTime ;
	
	s_iFPS++ ;
	s_dwTime	+= dwElapsedTime ;
	if( s_dwTime >= 1000 ) {
		wchar_t	szTitle[ 256 ] ;
		wsprintf( szTitle, L"WZGL - FPS:%3d", s_iFPS );
		SetWindowText( WZGL::getInstance().getWindowHandle(), szTitle );
		
		s_dwTime	= 0 ;
		s_iFPS		= 0 ;
	}
#endif

	if( !g_bDrawable ) {
		g_bDrawable	= true ;
		
		g_iFontPosX = 0 ;
		g_iFontPosY = FONT_HEIGHT ;

		WZGL::getInstance().keep60fps();

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		glLoadIdentity();
		glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0.0, 1.0 );
	}
}

/**
 * @brief		�O���t�B�b�N�@�\�̎g�p���J�n���邽�߂̊֐�
 *
 * @return		�Ȃ� (none)
 */
void end( void )
{
	if( g_bDrawable ) {
		g_bDrawable	= false ;
//#if	1
//		//	: �t���[�����[�g�̒����i1�b��60�t���[���ɕۂj
//		static	DWORD	s_dwBeforeTime	= GetTickCount();
//		DWORD	dwNowTime				= GetTickCount();
//		DWORD	dwElapsedTime	= dwNowTime - s_dwBeforeTime ;
//		
//		if( dwElapsedTime < 1000 / 60 )
//				Sleep( 1000 / 60 - dwElapsedTime );
//		else	Sleep( 1 );
//		s_dwBeforeTime	= dwNowTime ;
//		
//		drawString( "%d\n", dwElapsedTime );
//#else
//		Sleep( 1 );
//#endif

		glFlush();
		SwapBuffers( WZGL::getInstance().getDC() );
	}
}

/**
 * @brief		������̕`����s���֐�
 *
 *
 * @param[in]	i_string	������
 * @param[in]	...			�ό̈���
 *
 * @return		int	�o�͕�����
 */
int drawString( const char* i_string, ... )
{
	WZGL&			wz = WZGL::getInstance();
	unsigned int	uiStringLength ;
	GLuint			uiBaseIndex ;

	//	: �ό����̉���
	char	string[ 4800 ] = { 0 } ;
	va_list valist ;

	va_start( valist, i_string );
	vsprintf_s( string, 4800, i_string, valist );
	va_end( valist );

	//	: �`�悷�镶�������Z�o
	uiStringLength = strlen( string );
	//	: �f�B�X�v���C���X�g�𐶐�
	uiBaseIndex = glGenLists( uiStringLength );

	//	: �t�H���g����r�b�g�}�b�v���쐬
	for ( unsigned int i = 0 ; i < uiStringLength ; i++ ) {
		wglUseFontBitmapsA( wz.getDC(), string[ i ], 1, uiBaseIndex + i );
	}

	//	: �`��O����
	HFONT hOldFont = (HFONT)SelectObject( wz.getDC(), wz.getFont() );       //	: �t�H���g�̑I��
	glRasterPos2i( g_iFontPosX, g_iFontPosY );  //	: �`��ʒu�̌���

	for ( unsigned int i = 0 ; i < uiStringLength ; i++ ) {
		switch ( string[ i ] )
		{
		case '\0':
			break ;

		case '\n':  //	: ���s�R�[�h�����o������`����W��܂�Ԃ�
			g_iFontPosX = 0 ;
			g_iFontPosY += FONT_HEIGHT ;
			glRasterPos2i( g_iFontPosX, g_iFontPosY );
			break ;

		default:    //	: ��������łȂ���Ε`�悷��
			glCallList( uiBaseIndex + i );
			g_iFontPosX += FONT_WIDTH ;

			//	: ��ʒ[�Ő܂�Ԃ�����
			if ( g_iFontPosX > SCREEN_WIDTH ) {
				g_iFontPosX = 0 ;
				g_iFontPosY += FONT_HEIGHT ;
				glRasterPos2i( g_iFontPosX, g_iFontPosY );
			}
		}
	}

	//	: �㏈��
	SelectObject( wz.getDC(), hOldFont );			//	: �t�H���g�����ɖ߂�
	glDeleteLists( uiBaseIndex, uiStringLength );	//	: �r�b�g�}�b�v�p�̃��X�g���폜����

	return (int)uiStringLength ;
}

/**
 * @brief		������̕`����s���֐�
 *
 *
 * @param[in]	i_string	������
 * @param[in]	�ό̈���
 *
 * @return		int	�o�͕�����
 */
int	strDraw( const char* i_string )
{
	WZGL&			wz = WZGL::getInstance();
	unsigned int	uiStringLength ;
	GLuint			uiBaseIndex ;

	//	: �`�悷�镶�������Z�o
	uiStringLength = strlen( i_string );
	//	: �f�B�X�v���C���X�g�𐶐�
	uiBaseIndex = glGenLists( uiStringLength );

	//	: �t�H���g����r�b�g�}�b�v���쐬
	for ( unsigned int i = 0 ; i < uiStringLength ; i++ ) {
		wglUseFontBitmapsA( wz.getDC(), i_string[ i ], 1, uiBaseIndex + i );
	}

	//	: �`��O����
	HFONT hOldFont = (HFONT)SelectObject( wz.getDC(), wz.getFont() );       //	: �t�H���g�̑I��
	glRasterPos2i( g_iFontPosX, g_iFontPosY );  //	: �`��ʒu�̌���

	for ( unsigned int i = 0 ; i < uiStringLength ; i++ ) {
		switch ( i_string[ i ] )
		{
		case '\0':
			break ;

		case '\n':  //	: ���s�R�[�h�����o������`����W��܂�Ԃ�
			g_iFontPosX = 0 ;
			g_iFontPosY += FONT_HEIGHT ;
			glRasterPos2i( g_iFontPosX, g_iFontPosY );
			break ;

		default:    //	: ��������łȂ���Ε`�悷��
			glCallList( uiBaseIndex + i );
			g_iFontPosX += FONT_WIDTH ;

			//	: ��ʒ[�Ő܂�Ԃ�����
			if ( g_iFontPosX > SCREEN_WIDTH ) {
				g_iFontPosX = 0 ;
				g_iFontPosY += FONT_HEIGHT ;
				glRasterPos2i( g_iFontPosX, g_iFontPosY );
			}
		}
	}

	//	: �㏈��
	SelectObject( wz.getDC(), hOldFont );			//	: �t�H���g�����ɖ߂�
	glDeleteLists( uiBaseIndex, uiStringLength );	//	: �r�b�g�}�b�v�p�̃��X�g���폜����

	return (int)uiStringLength ;
}

/**
 * @brief		printf�֐��ŕ`�悷�镶����̍��W���s�N�Z���P�ʂŎw�肷��֐�
 *
 * @param[in]	i_iX	�`��ʒu�̂w���W
 * @param[in]	i_iY	�`��ʒu�̂x���W
 *
 * @return		�Ȃ� (none)
 */
void setPrintPos( int i_iX, int i_iY )
{
	g_iFontPosX = i_iX ;
	g_iFontPosY = i_iY + FONT_HEIGHT ;
}

/**
 * @brief		������`�悷��֐�
 *
 * @param[in]	i_fStartX	�n�_�̂w���W
 * @param[in]	i_fStartY	�n�_�̂x���W
 * @param[in]	i_fEndX		�I�_�̂w���W
 * @param[in]	i_fEndY		�I�_�̂x���W
 *
 * @return		�Ȃ� (none)
 */
void line( float i_fStartX, float i_fStartY, float i_fEndX, float i_fEndY )
{
	glBegin( GL_LINES );
	glVertex2f( i_fStartX, i_fStartY );
	glVertex2f( i_fEndX, i_fEndY );
	glEnd();
}

/**
 * @brief		�h��Ԃ��ꂽ�l�p�`��`�悷��֐�
 *
 * @param[in]	i_fStartX	�l�p�`�̍�����̂w���W
 * @param[in]	i_fStartY	�l�p�`�̍�����̂x���W
 * @param[in]	i_fWidth	�l�p�`�̕�
 * @param[in]	i_fHeight	�l�p�`�̍���
 *
 * @return		�Ȃ� (none)
 */
void fillRect( float i_fStartX, float i_fStartY, float i_fWidth, float i_fHeight )
{
	glBegin( GL_QUADS );
	glVertex2f( i_fStartX, i_fStartY );
	glVertex2f( i_fStartX, i_fStartY + i_fHeight );
	glVertex2f( i_fStartX + i_fWidth, i_fStartY + i_fHeight );
	glVertex2f( i_fStartX + i_fWidth, i_fStartY );
	glEnd();
}

/**
 * @brief		�l�p�`�̘g��`�悷��֐�
 *
 * @param[in]	i_fStartX	�l�p�`�̍�����̂w���W
 * @param[in]	i_fStartY	�l�p�`�̍�����̂x���W
 * @param[in]	i_fWidth	�l�p�`�̕�
 * @param[in]	i_fHeight	�l�p�`�̍���
 *
 * @return		�Ȃ� (none)
 */
void strokeRect( float i_fStartX, float i_fStartY, float i_fWidth, float i_fHeight )
{
	glBegin( GL_LINE_LOOP );
	glVertex2f( i_fStartX, i_fStartY );
	glVertex2f( i_fStartX, i_fStartY + i_fHeight );
	glVertex2f( i_fStartX + i_fWidth, i_fStartY + i_fHeight );
	glVertex2f( i_fStartX + i_fWidth, i_fStartY );
	glEnd();
}

/**
 * @brief		�h��Ԃ��ꂽ�~��`�悷��֐�
 *
 * @param[in]	i_fCenterX	�~�̒��S�ʒu�̂w���W
 * @param[in]	i_fCenterY	�~�̒��S�ʒu�̂x���W
 * @param[in]	i_fRadius	�~�̔��a
 *
 * @return		�Ȃ� (none)
 */
void fillCircle( float i_fCenterX, float i_fCenterY, float i_fRadius )
{
	int		rank		= int( i_fRadius * i_fRadius * i_fRadius * 0.05f );
	float	level[ 10 ] = { 90.0f, 72.0f, 60.0f, 45.0f, 40.0f, 36.0f, 30.0f, 15.0f, 10.0f, 5.0f } ;
	
	if( rank >= 10 )
		rank	= 9 ;

	glBegin( GL_TRIANGLE_FAN );
	glVertex2f( i_fCenterX, i_fCenterY );
//	for ( float i = 0.0f ; i <= 360.0f ; i += 5.0f ) {
	for ( float i = 0.0f ; i <= 360.0f ; i += level[ rank ] ) {
		float	fPointX = cosf( rad( i ) ) * i_fRadius + i_fCenterX ;
		float	fPointY = sinf( rad( i ) ) * i_fRadius + i_fCenterY ;
		glVertex2f( fPointX, fPointY );
	}

	glEnd();
}

/**
 * @brief		�~�`�̘g��`�悷��֐�
 *
 * @param[in]	i_fCenterX	�~�̒��S�ʒu�̂w���W
 * @param[in]	i_fCenterY	�~�̒��S�ʒu�̂x���W
 * @param[in]	i_fRadius	�~�̔��a
 *
 * @return		�Ȃ� (none)
 */
void strokeCircle( float i_fCenterX, float i_fCenterY, float i_fRadius )
{
	int		rank		= int( i_fRadius * i_fRadius * 0.1f );
	float	level[ 10 ] = { 90.0f, 72.0f, 60.0f, 45.0f, 40.0f, 36.0f, 30.0f, 15.0f, 10.0f, 5.0f } ;
	
	if( rank >= 10 )
		rank	= 9 ;
	
	glBegin( GL_LINE_LOOP );
//	for ( float i = 0.0f ; i <= 360.0f ; i += 5.0f ) {
	for ( float i = 0.0f ; i <= 360.0f ; i += level[ rank ] ) {
		float	fPointX = cosf( rad( i ) ) * i_fRadius + i_fCenterX ;
		float	fPointY = sinf( rad( i ) ) * i_fRadius + i_fCenterY ;
		glVertex2f( fPointX, fPointY );
	}

	glEnd();
}

/**
 * @brief		�O�p�`��`�悷��֐�
 *
 * @param[in]	i_fCenterX	�O�p�`�̒��S���W�̂w����
 * @param[in]	i_fCenterY	�O�p�`�̒��S���W�̂x����
 * @param[in]	i_fRadius	�O�p�`�̒��S���璸�_�܂ł̋���
 * @param[in]	i_fAngle	�O�p�`�̉�]�p
 *
 * @return		�Ȃ� (none)
 */
void fillTri( float i_fCenterX, float i_fCenterY, float i_fRadius, float i_fAngle )
{
	glBegin( GL_TRIANGLE_FAN );
	glVertex2f( i_fCenterX, i_fCenterY );
	for ( float i = i_fAngle ; i < 480.0f + i_fAngle ; i += 120.0f ) {
		float	fPointX = cosf( rad( i ) ) * i_fRadius + i_fCenterX ;
		float	fPointY = sinf( rad( i ) ) * i_fRadius + i_fCenterY ;
		glVertex2f( fPointX, fPointY );
	}

	glEnd();
}

/**
 * @brief		�O�p�`��`�悷��֐�
 *
 * @param[in]	i_fCenterX	�O�p�`�̒��S���W�̂w����
 * @param[in]	i_fCenterY	�O�p�`�̒��S���W�̂x����
 * @param[in]	i_fRadius	�O�p�`�̒��S���璸�_�܂ł̋���
 * @param[in]	i_fAngle	�O�p�`�̉�]�p
 *
 * @return		�Ȃ� (none)
 */
void strokeTri( float i_fCenterX, float i_fCenterY, float i_fRadius, float i_fAngle )
{
	glBegin( GL_LINE_LOOP );
	for ( float i = i_fAngle ; i < 480.0f + i_fAngle ; i += 120.0f ) {
		float	fPointX = cosf( rad( i ) ) * i_fRadius + i_fCenterX ;
		float	fPointY = sinf( rad( i ) ) * i_fRadius + i_fCenterY ;
		glVertex2f( fPointX, fPointY );
	}

	glEnd();
}

/**
 * @brief		�h��Ԃ��ꂽ��䊐���`�悷��֐�
 *
 * @param[in]	i_fCenterX	��䊐��̒��S���W�̂w����
 * @param[in]	i_fCenterY	��䊐��̒��S���W�̂x����
 * @param[in]	i_fRadius	��䊐��̒��S����O���̒��_�܂ł̋���
 * @param[in]	i_fAngle	��䊐��̉�]�p
 *
 * @return		�Ȃ� (none)
 */
void fillStar( float i_fCenterX, float i_fCenterY, float i_fRadius, float i_fAngle )
{
//	static float short_line = ( 1.0f / sinf( rad( 36.0f ) ) ) /
//							  ( cosf( rad( 18.0f ) ) / sinf( rad( 18.0f ) ) + cosf( rad( 36.0f ) ) / sinf( rad( 36.0f ) ) ) ;
	static float	length_array[ 2 ]	= { 1.0f, 0.381966f } ;
	int				c					= 0 ;

	glBegin( GL_TRIANGLE_FAN );
	glVertex2f( i_fCenterX, i_fCenterY );
	for ( float i = i_fAngle - 18.0f ; i <= 360.0f + i_fAngle ; i += 36.0f ) {
		float	fPointX = cosf( rad( i ) ) * i_fRadius * length_array[ c % 2 ] + i_fCenterX ;
		float	fPointY = sinf( rad( i ) ) * i_fRadius * length_array[ c % 2 ] + i_fCenterY ;
		glVertex2f( fPointX, fPointY );
		c++ ;
	}

	glEnd();
}

/**
 * @brief		��䊐���`�悷��֐�
 *
 * @param[in]	i_fCenterX	��䊐��̒��S���W�̂w����
 * @param[in]	i_fCenterY	��䊐��̒��S���W�̂x����
 * @param[in]	i_fRadius	��䊐��̒��S����O���̒��_�܂ł̋���
 * @param[in]	i_fAngle	��䊐��̉�]�p
 *
 * @return		�Ȃ� (none)
 */
void strokeStar( float i_fCenterX, float i_fCenterY, float i_fRadius, float i_fAngle )
{
//	static float short_line = ( 1.0f / sinf( rad( 36.0f ) ) ) /
//							  ( cosf( rad( 18.0f ) ) / sinf( rad( 18.0f ) ) + cosf( rad( 36.0f ) ) / sinf( rad( 36.0f ) ) ) ;
	static float	length_array[ 2 ]	= { 1.0f, 0.381966f } ;
	int				c					= 0 ;

	glBegin( GL_LINE_LOOP );
	for ( float i = i_fAngle - 18.0f ; i <= 324.0f + i_fAngle ; i += 36.0f ) {
		float	fPointX = cosf( rad( i ) ) * i_fRadius * length_array[ c % 2 ] + i_fCenterX ;
		float	fPointY = sinf( rad( i ) ) * i_fRadius * length_array[ c % 2 ] + i_fCenterY ;
		glVertex2f( fPointX, fPointY );
		c++ ;
	}

	glEnd();
}

/**
 * @brief		�ΏۃL�[�̉�����Ԃ�Ԃ��֐�
 *
 * @param[in]	i_iKeyCode	����ΏۃL�[�̃o�[�`�����L�[�萔
 *
 * @return		bool	TRUE:�����ꂽ��� / FALSE:�����ꂽ���
 */
bool isKeyDown( int i_iKeyCode )
{
	return ( 0x8000 & ::GetAsyncKeyState( i_iKeyCode ) ) != 0 ;
}

/**
 * @brief		�}�E�X�J�[�\����X���W���擾
 *
 * @return		float	�}�E�X�J�[�\���̌��݈ʒu��X���W
 */
float	getCursorX( void )
{
	POINT	pt ;
	::GetCursorPos( &pt );
	::ScreenToClient( WZGL::getInstance().getWindowHandle(), &pt );

	return float( pt.x );
}

/**
 * @brief		�}�E�X�J�[�\����Y���W���擾
 *
 * @return		float	�}�E�X�J�[�\���̌��݈ʒu��Y���W
 */
float	getCursorY( void )
{
	POINT	pt ;
	::GetCursorPos( &pt );
	::ScreenToClient( WZGL::getInstance().getWindowHandle(), &pt );

	return float( pt.y );
}
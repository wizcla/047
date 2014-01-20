/**
 * @file		WZGL.cpp
 * @brief		WZGLライブラリの本体
 */

#include "WZGL.h"
#include "WZMath.h"

//	: グローバル変数
static int g_iFontPosX	= 0,            ///< printf関数の文字列描画開始位置のＸ座標
		   g_iFontPosY	= FONT_HEIGHT ; ///< printf関数の文字列描画開始位置のＹ座標

//	: begin() と end() の対応を確実にするためのフラグ
static bool	g_bDrawable	= false ;

/**
 * @brief		グラフィック機能の使用を開始するための関数
 *
 * @return		なし (none)
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
 * @brief		グラフィック機能の使用を開始するための関数
 *
 * @return		なし (none)
 */
void end( void )
{
	if( g_bDrawable ) {
		g_bDrawable	= false ;
//#if	1
//		//	: フレームレートの調整（1秒を60フレームに保つ）
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
 * @brief		文字列の描画を行う関数
 *
 *
 * @param[in]	i_string	文字列
 * @param[in]	...			可変個の引数
 *
 * @return		int	出力文字数
 */
int drawString( const char* i_string, ... )
{
	WZGL&			wz = WZGL::getInstance();
	unsigned int	uiStringLength ;
	GLuint			uiBaseIndex ;

	//	: 可変個引数の解決
	char	string[ 4800 ] = { 0 } ;
	va_list valist ;

	va_start( valist, i_string );
	vsprintf_s( string, 4800, i_string, valist );
	va_end( valist );

	//	: 描画する文字数を算出
	uiStringLength = strlen( string );
	//	: ディスプレイリストを生成
	uiBaseIndex = glGenLists( uiStringLength );

	//	: フォントからビットマップを作成
	for ( unsigned int i = 0 ; i < uiStringLength ; i++ ) {
		wglUseFontBitmapsA( wz.getDC(), string[ i ], 1, uiBaseIndex + i );
	}

	//	: 描画前処理
	HFONT hOldFont = (HFONT)SelectObject( wz.getDC(), wz.getFont() );       //	: フォントの選択
	glRasterPos2i( g_iFontPosX, g_iFontPosY );  //	: 描画位置の決定

	for ( unsigned int i = 0 ; i < uiStringLength ; i++ ) {
		switch ( string[ i ] )
		{
		case '\0':
			break ;

		case '\n':  //	: 改行コードを検出したら描画座標を折り返す
			g_iFontPosX = 0 ;
			g_iFontPosY += FONT_HEIGHT ;
			glRasterPos2i( g_iFontPosX, g_iFontPosY );
			break ;

		default:    //	: 特殊条件でなければ描画する
			glCallList( uiBaseIndex + i );
			g_iFontPosX += FONT_WIDTH ;

			//	: 画面端で折り返す処理
			if ( g_iFontPosX > SCREEN_WIDTH ) {
				g_iFontPosX = 0 ;
				g_iFontPosY += FONT_HEIGHT ;
				glRasterPos2i( g_iFontPosX, g_iFontPosY );
			}
		}
	}

	//	: 後処理
	SelectObject( wz.getDC(), hOldFont );			//	: フォントを元に戻す
	glDeleteLists( uiBaseIndex, uiStringLength );	//	: ビットマップ用のリストを削除する

	return (int)uiStringLength ;
}

/**
 * @brief		文字列の描画を行う関数
 *
 *
 * @param[in]	i_string	文字列
 * @param[in]	可変個の引数
 *
 * @return		int	出力文字数
 */
int	strDraw( const char* i_string )
{
	WZGL&			wz = WZGL::getInstance();
	unsigned int	uiStringLength ;
	GLuint			uiBaseIndex ;

	//	: 描画する文字数を算出
	uiStringLength = strlen( i_string );
	//	: ディスプレイリストを生成
	uiBaseIndex = glGenLists( uiStringLength );

	//	: フォントからビットマップを作成
	for ( unsigned int i = 0 ; i < uiStringLength ; i++ ) {
		wglUseFontBitmapsA( wz.getDC(), i_string[ i ], 1, uiBaseIndex + i );
	}

	//	: 描画前処理
	HFONT hOldFont = (HFONT)SelectObject( wz.getDC(), wz.getFont() );       //	: フォントの選択
	glRasterPos2i( g_iFontPosX, g_iFontPosY );  //	: 描画位置の決定

	for ( unsigned int i = 0 ; i < uiStringLength ; i++ ) {
		switch ( i_string[ i ] )
		{
		case '\0':
			break ;

		case '\n':  //	: 改行コードを検出したら描画座標を折り返す
			g_iFontPosX = 0 ;
			g_iFontPosY += FONT_HEIGHT ;
			glRasterPos2i( g_iFontPosX, g_iFontPosY );
			break ;

		default:    //	: 特殊条件でなければ描画する
			glCallList( uiBaseIndex + i );
			g_iFontPosX += FONT_WIDTH ;

			//	: 画面端で折り返す処理
			if ( g_iFontPosX > SCREEN_WIDTH ) {
				g_iFontPosX = 0 ;
				g_iFontPosY += FONT_HEIGHT ;
				glRasterPos2i( g_iFontPosX, g_iFontPosY );
			}
		}
	}

	//	: 後処理
	SelectObject( wz.getDC(), hOldFont );			//	: フォントを元に戻す
	glDeleteLists( uiBaseIndex, uiStringLength );	//	: ビットマップ用のリストを削除する

	return (int)uiStringLength ;
}

/**
 * @brief		printf関数で描画する文字列の座標をピクセル単位で指定する関数
 *
 * @param[in]	i_iX	描画位置のＸ座標
 * @param[in]	i_iY	描画位置のＹ座標
 *
 * @return		なし (none)
 */
void setPrintPos( int i_iX, int i_iY )
{
	g_iFontPosX = i_iX ;
	g_iFontPosY = i_iY + FONT_HEIGHT ;
}

/**
 * @brief		直線を描画する関数
 *
 * @param[in]	i_fStartX	始点のＸ座標
 * @param[in]	i_fStartY	始点のＹ座標
 * @param[in]	i_fEndX		終点のＸ座標
 * @param[in]	i_fEndY		終点のＹ座標
 *
 * @return		なし (none)
 */
void line( float i_fStartX, float i_fStartY, float i_fEndX, float i_fEndY )
{
	glBegin( GL_LINES );
	glVertex2f( i_fStartX, i_fStartY );
	glVertex2f( i_fEndX, i_fEndY );
	glEnd();
}

/**
 * @brief		塗りつぶされた四角形を描画する関数
 *
 * @param[in]	i_fStartX	四角形の左上隅のＸ座標
 * @param[in]	i_fStartY	四角形の左上隅のＹ座標
 * @param[in]	i_fWidth	四角形の幅
 * @param[in]	i_fHeight	四角形の高さ
 *
 * @return		なし (none)
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
 * @brief		四角形の枠を描画する関数
 *
 * @param[in]	i_fStartX	四角形の左上隅のＸ座標
 * @param[in]	i_fStartY	四角形の左上隅のＹ座標
 * @param[in]	i_fWidth	四角形の幅
 * @param[in]	i_fHeight	四角形の高さ
 *
 * @return		なし (none)
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
 * @brief		塗りつぶされた円を描画する関数
 *
 * @param[in]	i_fCenterX	円の中心位置のＸ座標
 * @param[in]	i_fCenterY	円の中心位置のＹ座標
 * @param[in]	i_fRadius	円の半径
 *
 * @return		なし (none)
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
 * @brief		円形の枠を描画する関数
 *
 * @param[in]	i_fCenterX	円の中心位置のＸ座標
 * @param[in]	i_fCenterY	円の中心位置のＹ座標
 * @param[in]	i_fRadius	円の半径
 *
 * @return		なし (none)
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
 * @brief		三角形を描画する関数
 *
 * @param[in]	i_fCenterX	三角形の中心座標のＸ成分
 * @param[in]	i_fCenterY	三角形の中心座標のＹ成分
 * @param[in]	i_fRadius	三角形の中心から頂点までの距離
 * @param[in]	i_fAngle	三角形の回転角
 *
 * @return		なし (none)
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
 * @brief		三角形を描画する関数
 *
 * @param[in]	i_fCenterX	三角形の中心座標のＸ成分
 * @param[in]	i_fCenterY	三角形の中心座標のＹ成分
 * @param[in]	i_fRadius	三角形の中心から頂点までの距離
 * @param[in]	i_fAngle	三角形の回転角
 *
 * @return		なし (none)
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
 * @brief		塗りつぶされた五芒星を描画する関数
 *
 * @param[in]	i_fCenterX	五芒星の中心座標のＸ成分
 * @param[in]	i_fCenterY	五芒星の中心座標のＹ成分
 * @param[in]	i_fRadius	五芒星の中心から外側の頂点までの距離
 * @param[in]	i_fAngle	五芒星の回転角
 *
 * @return		なし (none)
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
 * @brief		五芒星を描画する関数
 *
 * @param[in]	i_fCenterX	五芒星の中心座標のＸ成分
 * @param[in]	i_fCenterY	五芒星の中心座標のＹ成分
 * @param[in]	i_fRadius	五芒星の中心から外側の頂点までの距離
 * @param[in]	i_fAngle	五芒星の回転角
 *
 * @return		なし (none)
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
 * @brief		対象キーの押下状態を返す関数
 *
 * @param[in]	i_iKeyCode	判定対象キーのバーチャルキー定数
 *
 * @return		bool	TRUE:押された状態 / FALSE:放された状態
 */
bool isKeyDown( int i_iKeyCode )
{
	return ( 0x8000 & ::GetAsyncKeyState( i_iKeyCode ) ) != 0 ;
}

/**
 * @brief		マウスカーソルのX座標を取得
 *
 * @return		float	マウスカーソルの現在位置のX座標
 */
float	getCursorX( void )
{
	POINT	pt ;
	::GetCursorPos( &pt );
	::ScreenToClient( WZGL::getInstance().getWindowHandle(), &pt );

	return float( pt.x );
}

/**
 * @brief		マウスカーソルのY座標を取得
 *
 * @return		float	マウスカーソルの現在位置のY座標
 */
float	getCursorY( void )
{
	POINT	pt ;
	::GetCursorPos( &pt );
	::ScreenToClient( WZGL::getInstance().getWindowHandle(), &pt );

	return float( pt.y );
}
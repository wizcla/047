/**
 * @file		WZGL.h
 * @brief		WZGLライブラリの本体
 *
 *	WZGLの基本的な機能を使用するために最低限必要なヘッダファイル
 */

#ifndef __WZGL__
#define __WZGL__
#pragma once

/**
 * @mainpage WZGL ライブラリ
 *
 * @section WZGLライブラリについて
 *
 * WZGLライブラリはＣ言語の初級者が簡単なグラフィックス処理の基礎を学ぶためのフレームワークです。
 * コンソールアプリケーションの作成に似たコーディングで単純な図形描画やリアルタイム処理を実現できます。
 *
 * @section 開発意図
 *
 * ゲームやコンピュータグラフィクス等のリアルタイム処理はＣ言語の初学者には敷居が高く、Ｃ言語の文法は理解できたがそれをどのように使用すればグラフィクス処理につながるのかという部分になると極端にに敷居がたくなってしまいます。
 * OpenGLやDirectXを使用すれば商用レベルの高度な処理が可能ですが、基本文法を理解したばかりの初学者には非常に難解ですし複雑な初期化処理無くしては先に進めません。
 * WZGLはそれらのグラフィクスライブラリを使用するに至る足がかりとして、学習用に使用することを目的に開発しました。
 * また、単にＣ言語の学習という面においてもグラフィクス処理を題材にすることで、高いレベルでの習熟が期待出来ると考えております。
 */

#include "WZGLCore.h"
//#include "WZMath.h"
#include <stdio.h>

#define FONT_WIDTH  ( 8 )	///< 文字列描画関数で使用する文字の幅
#define FONT_HEIGHT ( 16 )	///< 文字列描画関数で使用する文字の高さ


//	: グローバル関数（main.cppで使用すること前提）
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
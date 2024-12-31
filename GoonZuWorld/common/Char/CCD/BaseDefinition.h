#ifndef _BASEDEFINITION_H_
#define _BASEDEFINITION_H_

#ifdef _UNICODE
#define tstring		wstring
#else
#define tstring		string
#endif

#define		MAX_FILE_NUM				50000

#define		MIN_SURFACE_NUM				1		// ���Ŀ� �� �ʿ��ϴٸ� ���α׷����� �� �����ϴ� ���

#define		CHARACTER_TILE_WIDTH		320
#define		CHARACTER_TILE_HEIGHT		240

#define		MAX_ITEMCODE_LENGTH			6
#define		MAX_ACTIONCODE_LENGTH		5

#define		MAX_ITEM_NAME				64

#define		MAX_DRAWING_SEQUENCE_NUM	8

// �̺� �߰� - SLEEP - �ڴ� ���.
// PCK : ���ڴ� ����� �漮 �߰� (09.06.16)
enum { HSU1, HTU2, HBU2, HGU2, HITU, MOVU, WT1U, WT2U, DTHU, SPCU, HSR1, HTR2, HBR2, HGR2, HITR, MOVR, WT1R, WT2R, DTHR, SPCR, SITU, FSHU, FAMU, MINU, MAMU, MHEU, MFOU, SOPU, SLEP, SLEC};
enum { CCD_SOUTH_EAST, CCD_SOUTH, CCD_SOUTH_WEST, CCD_WEST, CCD_NORTH_WEST, CCD_NORTH, CCD_NORTH_EAST, CCD_EAST };


enum { HED = 1, TOR, RHD, LHD, MTL, EQU, HRS, EFF };		//  ���, ����, ����, ����, ��, ����Ʈ

#include <windows.h>
#include <stdio.h>

class CDataLoading;
extern CDataLoading g_BaseDataMgr;

class CMinDataMgr;
extern CMinDataMgr g_MinDataMgr;

#endif
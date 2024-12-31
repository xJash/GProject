#pragma once

// Space and Tab String
#define WHITESPACE_N_TAB _T("\t ")
#define NULL_STRING ""

//enum CONTROL_TYPE
//{
//	BUTTON_TYPE = 0,
//    EDIT_TYPE = 1,
//	STATIC_TYPE = 2,
//	CHECKBOX_TYPE = 3,
//	RADIOBUTTON_TYPE = 4,
//	COMBOBOX_TYPE = 5,
//	LISTBOX_TYPE = 6,
//	GROUPBOX_TYPE = 7
//};

// error
#define	ERROR_CODE -1

// ddf file 
#define DLG_PAPER_STR						"dialog"
#define DLG_REPLACE_PAPER_STR				"dialog"
#define DLG_HEADER_SPLITTER_STR				">"
#define DLG_REPLACE_HEADER_SPLITTER_STR		"\\shiftright"
#define DLG_ITEM_SPLITTER_STR				","
#define DLG_ITEM_SPLITTER_CHAR				','
#define	DLG_CHILD_FILENAME_SPLITTER_CHAR	','
#define	DLG_CHILD_FILENAME_SPLITTER_STR		","
#define DLG_REPLACE_ITEM_SPLITTER_STR		"\\comma"
#define DLG_ENDLINE_STR						";"
#define DLG_ENDLINE_CHAR					';'
#define DLG_REPLACE_ENDLINE_STR				"\\semicolon"
#define DLG_NEWLINE_STR						"\r\n"
#define DLG_REPLACE_NEWLINE					"\\newline"
#define DLG_FILE_COMMENT_SIGN				"#"				// ���Ͽ��� �ĸ�Ʈ ���� ����
#define DLG_FILE_TRIM_LETTER				"\t "			// ����� ���� �߶�
#define FILE_PATH_SPLITTER_BACKSLASH		'\\'
#define FILE_PATH_SPLITTER_SLASH			'/'

// string
#define STR_EMPTY							""				// NULL ��Ʈ��
#define STR_ZERO							"0"				// 0 ��Ʈ��
#define STR_ONE								"1"				// 0 ��Ʈ��
#define STR_TRIM_LETTER						"\t "			// ����� ���� �߶�

// filename meaning / tile font
#define WHOLE_IMAGE_STYLE_FONTNUM			1				// �� �̹��� ��� ��Ʈ ��
#define TILEINFO_COUNT_OF_FILENAME			3				// �����̸����� Ÿ�� ������ �����ϴ� �ڿ��� ������ ����
#define TILEIMAGENUM_START_POS				1				// ���ϸ��� Ÿ�� ���� �κп��� Ÿ�� �̹��� ������ ���۵Ǵ� ��ġ
#define TILEIMAGENUM_CHAR_LENGTH			2				// ���ϸ��� Ÿ�� ���� �κп��� Ÿ�� �̹��� ���� ���� ��
#define TILEMODE_POS						0				// ���ϸ��� Ÿ�� ���� �κп��� Ÿ�� ��� ����� ���� ��ġ
#define TILEMODE_CHAR_LENGTH				1				// ���ϸ��� Ÿ�� ���� �κп��� Ÿ�� ��� ����� ���� ��
#define VALID_TILEIMAGE_NUM0				0				// Ÿ���� Ÿ�� �̹��� ����
#define VALID_TILEIMAGE_NUM1				1	
#define VALID_TILEIMAGE_NUM3				3
#define VALID_TILEIMAGE_NUM9				9

#define BASIC_ID_FORMAT						"%s_NONAME%d"		// ��Ʈ�� �� ���̾�α� ID ����� �⺻ ����
#define EX_ID_FORMAT						"%s_%s_NONAME%d"	// ��Ʈ�� �� ���̾�α� ID ����� Ȯ�� ����
#define DIALOG_DESIGN_FORMAT_EXT			"ddf"				// ���� Ȯ����
#define SAVE_FILE_PREFIX					"DLG_�������"		// ����Ʈ ���ϸ�

// Interface
#define MARKERSIZE_X						4				// ��Ʈ�� ��ü ���ý� ����� �簢�� X��
#define MARKERSIZE_Y						4				// ��Ʈ�� ��ü ���ý� ����� �簢�� Y��
#define DLG_MARGIN_MIN_LENGTH				0				// �ּ� ���� ���� �� - x,y ������
#define DLG_GRID_MIN_LENGTH					8				// �ּ� �׸��� ���� �� - x,y ������

// letter font 
#define DEFAULT_FONT_COLOR					0
#define DEFAULT_FONT_STYLE					"" //"����"
#define DEFAULT_FONT_SIZE					12
#define DEFAULT_FONT_WEIGHT					400				// ��� : 100, ���� 400, ���� 700

// dialog property
//#define DLG_PROPERTY_COUNT 19
#define DLG_SIZE_X							400				// Dialog Default Width
#define DLG_SIZE_Y							600				// Dialog Default Height
#define DLG_DEFAULT_TITLE					""
#define DLG_CHILD_FILENUM					1				// �ڽ�â ���� => ���� 10������ �þ �� ����
#define DLG_FILE_PROPERTY_COUNT				(DLG_PROPERTY_COUNT+DLG_CHILD_FILENUM - 1)
#define DLG_DEFAULT_CHILD_FILENAMES			",,,,,,,,,"

enum DIALOG_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	DLG_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	DLG_RESOURCE_ID,		// ID : ���ҽ� ID							
	DLG_X_COORD,			// X��ǥ						
	DLG_Y_COORD,			// Y��ǥ						
	DLG_WIDTH,				// ������					
	DLG_HEIGHT,				// ������					
	DLG_BG_IMAGE_FULLPATH,	// ��׶��� �̹��� 								
	DLG_BG_WIDTH,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
	DLG_BG_HEIGHT,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
	DLG_BG_TILE,			// ��׶��� �̹����� Ÿ�� ���� ������� ����						
								// true : Ÿ�Ϲ��, false : ��� ���		
	DLG_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	DLG_BG_START_FONT,		// ���Ͽ��� ��׶��� �̹��� ���� ��ġ							
	DLG_TEXT_COLOR,		// �ؽ�Ʈ �÷�							
	DLG_TEXT_STYLE,		// �ؽ�Ʈ ����ü							
	DLG_TEXT_SIZE,			// �ؽ�Ʈ ũ��						
	/// ####################################################									
										
    //DLG_CALLBACK_POINTER,// ���̾�α� �ݹ� �Լ� �����͸�										
	DLG_TITLE_STR,			// ���̾�α� Ÿ��Ʋ ��						
	DLG_TITLE_VISIBLE,		// ���̾�α� Ÿ��Ʋ�� ���̴��� �Ⱥ��̴��� ����							
	DLG_MOVABLE,			// ���̾�αװ� �̵� �������� ����						
	DLG_CLOSABLE,			// ���̾�α� �ݱ� ��ư ���� ����						
										
	//DLG_CHILD_FILENAMES = 20	// �ڽ� ���̾�α� ID								
	DLG_PROPERTY_COUNT,		// �Ӽ� ��
};										
										
// ������� �ʴ´�... ���ŵ� 2005-03-03										
enum DIALOG_PROPERTY_EXCEPTION										
{										
	DLG_CALLBACK_POINTER,// ���̾�α� �ݹ� �Լ� �����͸�									
	DLG_CHILD_FILENAMES = 101	// �ڽ� ���̾�α� ID								
};										
										
// button property										
//#define BTN_PROPERTY_COUNT 21										
#define BTN_DEFAULT_TITLE ""										
#define BTN_SIZE_X 100										
#define BTN_SIZE_Y 100										
										
enum BUTTON_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	BTN_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	BTN_RESOURCE_ID,		// ID : ���ҽ� ID							
	BTN_X_COORD,			// X��ǥ						
	BTN_Y_COORD,			// Y��ǥ						
	BTN_WIDTH,				// ������					
	BTN_HEIGHT,				// ������					
	BTN_BG_IMAGE_FULLPATH,	// ��׶��� �̹��� 								
	BTN_BG_WIDTH,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
	BTN_BG_HEIGHT,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
	BTN_BG_TILE,			// ��׶��� �̹����� Ÿ�� ���� ������� ����						
								// true : Ÿ�Ϲ��, false : ��� ���		
	BTN_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	BTN_BG_START_FONT,		// ���Ͽ��� ��׶��� �̹��� ���� ��ġ							
	BTN_TEXT_COLOR,		// �ؽ�Ʈ �÷�							
	BTN_TEXT_STYLE,		// �ؽ�Ʈ ����ü							
	BTN_TEXT_SIZE,			// �ؽ�Ʈ ũ��						
	BTN_GROUP_NUM,			// control group ��ȣ						
	/// ####################################################									
										
	BTN_TEXT_STR,			// ��ư�� ����� TEXT						
										
	BTN_ANIMATION,	// ��ư ���� ���콺 ��ġ�� �ִϸ��̼� ���� ����								
	BTN_TEXT_COLOR_R,		// R									
	BTN_TEXT_COLOR_G,		// G						
	BTN_TEXT_COLOR_B,		// B							

	BTN_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	BTN_PROPERTY_COUNT,
};										
										
// ComboBox Property										
//#define CBX_PROPERTY_COUNT 21										
#define CBX_DEFAULT_TITLE ""										
#define CBX_SIZE_X 100										
#define CBX_SIZE_Y 100										
#define CBX_ROW_HT 17	// �޺��ڽ� �� �� ����									
#define CBX_POPUP_HT CBX_ROW_HT*15	// �޺��ڽ� �˾�â�� ���� : �⺻�� : ���ٳ��� * 20 ��									
#define CBX_LINE_HT  17										
										
enum COMBOBOX_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	CBX_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	CBX_RESOURCE_ID,	// ID : ���ҽ� ID								
	CBX_X_COORD,		// X��ǥ							
	CBX_Y_COORD,		// Y��ǥ							
	CBX_WIDTH,			// ������						
	CBX_HEIGHT,			// ������						
	CBX_BG_IMAGE_FULLPATH,// ��׶��� �̹��� 									
	CBX_BG_WIDTH,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	CBX_BG_HEIGHT,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	CBX_BG_TILE,	// ��׶��� �̹����� Ÿ�� ���� ������� ����								
						// true : Ÿ�Ϲ��, false : ��� ���				
	CBX_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	CBX_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	CBX_TEXT_COLOR,	// �ؽ�Ʈ �÷�								
	CBX_TEXT_STYLE,	// �ؽ�Ʈ ����ü								
	CBX_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	CBX_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
										
	CBX_POPUP_HEIGHT,	// �޺� �ڽ��� ������ ���� POP-UPâ ����								
	CBX_LINE_HEIGHT,	// �޺� �ڽ��� ������ ����								

	CBX_TEXT_COLOR_R,		// R									
	CBX_TEXT_COLOR_G,		// G						
	CBX_TEXT_COLOR_B,		// B							

	CBX_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	CBX_PROPERTY_COUNT, // ��
						
};										
										
/**										
leon add										
* EditBox Property Order										
*/										
//#define ETB_PROPERTY_COUNT 19										
										
#define ETB_DEFAULT_TITLE ""										
#define ETB_SIZE_X 100										
#define ETB_SIZE_Y 100										
										
enum EDITBOX_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	ETB_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	ETB_RESOURCE_ID,	// ID : ���ҽ� ID								
	ETB_X_COORD,		// X��ǥ							
	ETB_Y_COORD,		// Y��ǥ							
	ETB_WIDTH,			// ������						
	ETB_HEIGHT,			// ������						
	ETB_BG_IMAGE_FULLPATH,// ��׶��� �̹��� 									
	ETB_BG_WIDTH,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	ETB_BG_HEIGHT,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	ETB_BG_TILE,	// ��׶��� �̹����� Ÿ�� ���� ������� ����								
						// true : Ÿ�Ϲ��, false : ��� ���				
	ETB_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	ETB_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	ETB_TEXT_COLOR,	// �ؽ�Ʈ �÷�								
	ETB_TEXT_STYLE,	// �ؽ�Ʈ ����ü								
	ETB_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	ETB_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
										
	ETB_TEXT_STR,		// ó���� ����� TEXT							
	ETB_MULTI_LINE,	// true : Multi-line, false : single line								
	ETB_READONLY,		// true : ReadOnly,	  false : ���� ����						

	ETB_TEXT_COLOR_R,		// R									
	ETB_TEXT_COLOR_G,		// G						
	ETB_TEXT_COLOR_B,		// B							

	ETB_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	ETB_PROPERTY_COUNT
};										
										
/**										
leon add										
* STATIC TEXT Property Order										
*/										
//#define STATT_PROPERTY_COUNT 17										
										
#define STATT_DEFAULT_TITLE ""										
#define STATT_SIZE_X 100										
#define STATT_SIZE_Y 100										
										
enum STATIC_TEXT_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	STATT_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	STATT_RESOURCE_ID,	// ID : ���ҽ� ID								
	STATT_X_COORD,		// X��ǥ							
	STATT_Y_COORD,		// Y��ǥ							
	STATT_WIDTH,			// ������						
	STATT_HEIGHT,			// ������						
	STATT_BG_IMAGE_FULLPATH,// ��׶��� �̹��� 									
	STATT_BG_WIDTH,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	STATT_BG_HEIGHT,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	STATT_BG_TILE,	// ��׶��� �̹����� Ÿ�� ���� ������� ����								
						// true : Ÿ�Ϲ��, false : ��� ���				
	STATT_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	STATT_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	STATT_TEXT_COLOR,	// �ؽ�Ʈ �÷�								
	STATT_TEXT_STYLE,	// �ؽ�Ʈ ����ü								
	STATT_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	STATT_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
										
	STATT_TEXT_STR,	// ó���� ����� TEXT							

	STATT_TEXT_COLOR_R,		// R									
	STATT_TEXT_COLOR_G,		// G						
	STATT_TEXT_COLOR_B,		// B							

	STATT_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	STATT_PROPERTY_COUNT,
};										
										
// IMAGE STATIC Property										
//#define IMGSTT_PROPERTY_COUNT 16										
#define IMGSTT_SIZE_X 100										
#define IMGSTT_SIZE_Y 100										
										
enum IMAGE_STATIC_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	IMGSTT_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	IMGSTT_RESOURCE_ID,	// ID : ���ҽ� ID								
	IMGSTT_X_COORD,		// X��ǥ							
	IMGSTT_Y_COORD,		// Y��ǥ							
	IMGSTT_WIDTH,			// ������						
	IMGSTT_HEIGHT,			// ������						
	IMGSTT_BG_IMAGE_FULLPATH,// ��׶��� �̹��� 									
	IMGSTT_BG_WIDTH,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	IMGSTT_BG_HEIGHT,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	IMGSTT_BG_TILE,	// ��׶��� �̹����� Ÿ�� ���� ������� ����								
						// true : Ÿ�Ϲ��, false : ��� ���				
	IMGSTT_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	IMGSTT_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	IMGSTT_TEXT_COLOR,	// �ؽ�Ʈ �÷�								
	IMGSTT_TEXT_STYLE,	// �ؽ�Ʈ ����ü								
	IMGSTT_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	IMGSTT_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
	IMGSTT_TEXT_COLOR_R,		// R									
	IMGSTT_TEXT_COLOR_G,		// G						
	IMGSTT_TEXT_COLOR_B,		// B							

	IMGSTT_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	IMGSTT_PROPERTY_COUNT,
};										
										
// LISTBOX Property Order										
//#define LSTB_PROPERTY_COUNT 20										
#define LSTB_DEFAULT_TITLE ""										
#define LSTB_SIZE_X 100										
#define LSTB_SIZE_Y 100										
#define LSTB_LINE_HT 14										
										
enum LISTBOX_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	LSTB_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	LSTB_RESOURCE_ID,	// ID : ���ҽ� ID								
	LSTB_X_COORD,		// X��ǥ							
	LSTB_Y_COORD,		// Y��ǥ							
	LSTB_WIDTH,			// ������						
	LSTB_HEIGHT,			// ������						
	LSTB_BG_IMAGE_FULLPATH,// ��׶��� �̹��� 									
	LSTB_BG_WIDTH,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	LSTB_BG_HEIGHT,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	LSTB_BG_TILE,	// ��׶��� �̹����� Ÿ�� ���� ������� ����								
						// true : Ÿ�Ϲ��, false : ��� ���				
	LSTB_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	LSTB_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	LSTB_TEXT_COLOR,	// �ؽ�Ʈ �÷�								
	LSTB_TEXT_STYLE,	// �ؽ�Ʈ ����ü								
	LSTB_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	LSTB_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
										
	LSTB_MULTI_COLUMN,	// true : Multi-Column, false : single Column								
	LSTB_MULTI_SELECTION, // true : Multi-Selection, false : �Ұ���									
	LSTB_LINE_HEIGHT, // �� ���� ����									
	LSTB_FIXED_ROW_VISIBLE, // �׸��� ������ ����Ʈ �ڽ����� fixed Row�� �������� ����									

	LSTB_TEXT_COLOR_R,		// R									
	LSTB_TEXT_COLOR_G,		// G						
	LSTB_TEXT_COLOR_B,		// B							

	LSTB_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	LSTB_PROPERTY_COUNT,
};										
										
// LISTVIEW Property Order										
//#define LSTV_PROPERTY_COUNT 27										
#define LSTV_SIZE_X 100										
#define LSTV_SIZE_Y 100										
#define LSTV_TOOLTIP_SIZE_WIDTH		150		// ���� surface Max x						
#define LSTV_TOOLTIP_SIZE_HEIGHT	300		// ���� surface Max y							
#define LSTV_ITEM_START_POS_X 0										
#define LSTV_ITEM_START_POS_Y 0										
#define LSTV_ITEM_OFFSET_POS_X 0										
#define LSTV_ITEM_OFFSET_POS_Y 0										
#define	LSTV_ITEM_DEFAULT_SIZE_X 40									
#define	LSTV_ITEM_DEFAULT_SIZE_Y 40									
										
enum LISTVIEW_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	LSTV_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	LSTV_RESOURCE_ID,	// ID : ���ҽ� ID								
	LSTV_X_COORD,		// X��ǥ							
	LSTV_Y_COORD,		// Y��ǥ							
	LSTV_WIDTH,			// ������						
	LSTV_HEIGHT,			// ������						
	LSTV_BG_IMAGE_FULLPATH,// ��׶��� �̹��� 									
	LSTV_BG_WIDTH,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	LSTV_BG_HEIGHT,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	LSTV_BG_TILE,	// ��׶��� �̹����� Ÿ�� ���� ������� ����								
										
	LSTV_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	LSTV_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	LSTV_TEXT_COLOR,	// �ؽ�Ʈ �÷�								
	LSTV_TEXT_STYLE,	// �ؽ�Ʈ ����ü								
	LSTV_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	LSTV_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
										
	LSTV_ITEM_EMPTY,		// �κ��丮���� �� ������ ǥ�� ����							
	LSTV_ITEM_COUNT_VISIBLE, // �κ��丮���� ������ ���� ǥ�� ����									
	LSTV_ITEM_TOOLTIP_USABLE,			// �κ��丮���� ������ ���� ����						
										
	LSTV_ITEM_TOOLTIP_WIDTH,	// ���� ��								
	LSTV_ITEM_TOOLTIP_HEIGHT,	// ���� ����								
										
	LSTV_ITEM_START_X,	// ������ ���� ��ġ X								
	LSTV_ITEM_START_Y,	// ������ ���� ��ġ Y								
										
	LSTV_ITEM_OFFSET_X,			// ������ ������ X��						
	LSTV_ITEM_OFFSET_Y,			// ������ ������ Y��						
										
	LSTV_ITEM_SIZE_X,	// ������ ������ X								
	LSTV_ITEM_SIZE_Y,	// ������ ������ Y								

	LSTV_TEXT_COLOR_R,		// R									
	LSTV_TEXT_COLOR_G,		// G						
	LSTV_TEXT_COLOR_B,		// B							

	LSTV_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	LSTV_PROPERTY_COUNT,
										
};										
										
// CheckBox Property - 2005-03-07										
//#define CHKB_PROPERTY_COUNT 17										
#define CHKB_SIZE_X 100										
#define CHKB_SIZE_Y 100										
#define CHKB_DEFAULT_TITLE	""									
										
enum CHECKBOX_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	CHKB_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	CHKB_RESOURCE_ID,		// ID : ���ҽ� ID							
	CHKB_X_COORD,			// X��ǥ						
	CHKB_Y_COORD,			// Y��ǥ						
	CHKB_WIDTH,				// ������					
	CHKB_HEIGHT,			// ������						
	CHKB_BG_IMAGE_FULLPATH,	// ��׶��� �̹��� 								
	CHKB_BG_WIDTH,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
	CHKB_BG_HEIGHT,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
	CHKB_BG_TILE,			// ��׶��� �̹����� Ÿ�� ���� ������� ����						
								// true : Ÿ�Ϲ��, false : ��� ���		
	CHKB_BG_TILE_IMAGE_NUM,// Ÿ�� �̹��� ���� 1, 3, 9									
	CHKB_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	CHKB_TEXT_COLOR,		// �ؽ�Ʈ �÷�							
	CHKB_TEXT_STYLE,		// �ؽ�Ʈ ����ü							
	CHKB_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	CHKB_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
										
	CHKB_TEXT_STR,			// ��ư�� ����� TEXT						

	CHKB_TEXT_COLOR_R,		// R									
	CHKB_TEXT_COLOR_G,		// G						
	CHKB_TEXT_COLOR_B,		// B							

	CHKB_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	CHKB_PROPERTY_COUNT,
};										
										
// Radio Property - 2005-03-07										
//#define RADB_PROPERTY_COUNT 18										
#define RADB_SIZE_X 100										
#define RADB_SIZE_Y 100										
#define RADB_DEFAULT_TITLE	""									
										
enum RADIOBUTTON_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	RADB_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	RADB_RESOURCE_ID,		// ID : ���ҽ� ID							
	RADB_X_COORD,			// X��ǥ						
	RADB_Y_COORD,			// Y��ǥ						
	RADB_WIDTH,				// ������					
	RADB_HEIGHT,			// ������						
	RADB_BG_IMAGE_FULLPATH,	// ��׶��� �̹��� 								
	RADB_BG_WIDTH,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
	RADB_BG_HEIGHT,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
	RADB_BG_TILE,			// ��׶��� �̹����� Ÿ�� ���� ������� ����						
								// true : Ÿ�Ϲ��, false : ��� ���		
	RADB_BG_TILE_IMAGE_NUM,// Ÿ�� �̹��� ���� 1, 3, 9									
	RADB_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	RADB_TEXT_COLOR,		// �ؽ�Ʈ �÷�							
	RADB_TEXT_STYLE,		// �ؽ�Ʈ ����ü							
	RADB_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	RADB_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
										
	RADB_TEXT_STR,			// ��ư�� ����� TEXT						
	RADB_GROUP_ID,			// ���� ��ư �׷� ID						

	RADB_TEXT_COLOR_R,		// R									
	RADB_TEXT_COLOR_G,		// G						
	RADB_TEXT_COLOR_B,		// B							

	RADB_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	RADB_PROPERTY_COUNT,
};										
										
/**										
leon add										
* CHAT EDITBOX Property Order										
*/										
//#define CHTETB_PROPERTY_COUNT 21										
										
#define CHTETB_DEFAULT_TITLE ""										
#define CHTETB_SIZE_X 100										
#define CHTETB_SIZE_Y 100										
#define CHTETB_LINE_HT 14										
#define CHTETB_AUTO_SCROLL_VALUE 1										
#define CHTETB_OFFSET_X_VALUE 2										
#define CHTETB_OFFSET_Y_VALUE 2										
										
enum CHATEDIT_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	CHTETB_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	CHTETB_RESOURCE_ID,	// ID : ���ҽ� ID								
	CHTETB_X_COORD,		// X��ǥ							
	CHTETB_Y_COORD,		// Y��ǥ							
	CHTETB_WIDTH,			// ������						
	CHTETB_HEIGHT,			// ������						
	CHTETB_BG_IMAGE_FULLPATH,// ��׶��� �̹��� 									
	CHTETB_BG_WIDTH,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	CHTETB_BG_HEIGHT,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	CHTETB_BG_TILE,	// ��׶��� �̹����� Ÿ�� ���� ������� ����								
						// true : Ÿ�Ϲ��, false : ��� ���				
	CHTETB_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	CHTETB_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	CHTETB_TEXT_COLOR,	// �ؽ�Ʈ �÷�								
	CHTETB_TEXT_STYLE,	// �ؽ�Ʈ ����ü								
	CHTETB_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	CHTETB_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
	CHTETB_TEXT_STR,			// ����� TEXT						
	CHTETB_LINE_HEIGHT,	// ���� ����								
	CHTETB_AUTOSCROLL,		// true : �ڵ� ��ũ��, false : ��ũ�� ����							
	CHTETB_OFFSET_X,		// offset x��							
	CHTETB_OFFSET_Y,		// offset y��							

	CHTETB_TEXT_COLOR_R,		// R									
	CHTETB_TEXT_COLOR_G,		// G						
	CHTETB_TEXT_COLOR_B,		// B							

	CHTETB_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	CHTETB_PROPERTY_COUNT,
};										
										
/**										
leon add										
* OUTLINE Property Order										
*/										
//#define OUTLNE_PROPERTY_COUNT 17										
										
#define OUTLNE_DEFAULT_TITLE ""										
#define OUTLNE_SIZE_X 100										
#define OUTLNE_SIZE_Y 100										
										
enum OUTLINE_PROPERTY										
{										
	// ���� PROPERTY#######################################									
	OUTLNE_KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����						
	OUTLNE_RESOURCE_ID,	// ID : ���ҽ� ID								
	OUTLNE_X_COORD,		// X��ǥ							
	OUTLNE_Y_COORD,		// Y��ǥ							
	OUTLNE_WIDTH,			// ������						
	OUTLNE_HEIGHT,			// ������						
	OUTLNE_BG_IMAGE_FULLPATH,// ��׶��� �̹��� 									
	OUTLNE_BG_WIDTH,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	OUTLNE_BG_HEIGHT,		// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
	OUTLNE_BG_TILE,	// ��׶��� �̹����� Ÿ�� ���� ������� ����								
						// true : Ÿ�Ϲ��, false : ��� ���				
	OUTLNE_BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9								
	OUTLNE_BG_START_FONT,	// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
	OUTLNE_TEXT_COLOR,	// �ؽ�Ʈ �÷�								
	OUTLNE_TEXT_STYLE,	// �ؽ�Ʈ ����ü								
	OUTLNE_TEXT_SIZE,		// �ؽ�Ʈ ũ��							
	OUTLNE_GROUP_NUM,		// control group ��ȣ							
	/// ####################################################									
										
	OUTLNE_TEXT_STR,		// ó���� ����� TEXT							

	OUTLNE_TEXT_COLOR_R,		// R									
	OUTLNE_TEXT_COLOR_G,		// G						
	OUTLNE_TEXT_COLOR_B,		// B							

	OUTLNE_WEIGHT,				// ��Ʈ ���� - ��� : 400, ���� : 700, ���� : 800

	OUTLNE_PROPERTY_COUNT,
};										
//##########################################################										
// �� ��Ʈ�� �� ���� ������Ƽ�� �迭 ��ȣ ����										
#define	CTRL_COUNT			11						
										
#define BUTTON_POS			0							
#define COMBOBOX_POS		1								
#define EDITBOX_POS			2							
#define STATIC_TEXT_POS		3								
#define IMAGE_STATIC_POS	4									
#define LISTBOX_POS			5							
#define LISTVIEW_POS		6								
#define CHECKBOX_POS		7								
#define	RADIOBUTTON_POS		8							
#define	CHATEDIT_POS		9							
#define	OUTLINE_POS			10						
										
#define BTN_STR				"button"						
#define CBX_STR				"combobox"						
#define ETB_STR				"editbox"						
#define STATT_STR			"statictext"							
#define IMGSTT_STR			"imagestatic"							
#define LSTB_STR			"listbox"							
#define LSTV_STR			"listview"							
#define CHKB_STR			"checkbox"							
#define RADB_STR			"radiobutton"							
#define CHTETB_STR			"chatedit"							
#define OUTLNE_STR			"outline"							
										
#define COMMON_PROPERTY_COUNT 16										
//KIND_NAME,			// ���̾�α� Ȥ�� ��Ʈ�� ����							
//RESOURCE_ID,			// ID : ���ҽ� ID							
//X_COORD,				// X��ǥ						
//Y_COORD,				// Y��ǥ						
//WIDTH,				// ������						
//HEIGHT,				// ������						
//BG_IMAGE_FULLPATH,	// ��׶��� �̹��� 									
//BG_WIDTH,				// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������						
//BG_HEIGHT,			// ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������							
//BG_TILE,				// ��׶��� �̹����� Ÿ�� ���� ������� ����						
//							// true : Ÿ�Ϲ��, false : ��� ���			
//BG_TILE_IMAGE_NUM,	// Ÿ�� �̹��� ���� 1, 3, 9									
//BG_START_FONT,		// ���Ͽ��� ��׶��� �̹��� ���� ��ġ								
//TEXT_COLOR,			// �ؽ�Ʈ �÷�							
//TEXT_STYLE,			// �ؽ�Ʈ ����ü							
//TEXT_SIZE,			// �ؽ�Ʈ ũ��							
//GROUP_NUM,			// control group ��ȣ							
										
										
// �� ��Ʈ�Ѻ� �Ӽ��� �迭 ��ȣ										
// ����  -1�� ��� == �׷� �Ӽ� ����										
struct CTRL_PROPERTY_COUNT_INFO										
{										
	char* type;									
	int	  num;								
};										
										
// ��Ʈ�� �Ӽ� Ÿ�� �� ���� ���� => 2���� ���� ( DiagramEditor.cpp�� AddObject�� DLGEditorSDoc.cpp�� Serialize!!)										
struct CTRL_SAVING_ORDER_INFO										
{										
	char* type;									
	int pos;									
};										

enum {

/*#define*/ KIND_NAME = 0, //=	0		, // ���̾�α� Ȥ�� ��Ʈ�� ����, //	
/*#define*/ RESOURCE_ID, //	1		, // ID : ���ҽ� ID, //	
/*#define*/ X_COORD, //		2		, // X��ǥ, //
/*#define*/ Y_COORD, //		3		, // Y��ǥ, //
/*#define*/ WIDTH, //		4		, // ������, //
/*#define*/ HEIGHT, //		5		, // ������, //
/*#define*/ BG_IMAGE_FULLPATH,//		6		, // ��׶��� �̹��� , //, //
/*#define*/ BG_WIDTH, //	7		, // ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������, //	
/*#define*/ BG_HEIGHT, //	8		, // ��Ʈ�� Ȥ�� ���̾�α��� �ִ� ������, //	
/*#define*/ BG_TILE, //		9		, // ��׶��� �̹����� Ÿ�� ���� ������� ����, //
//, //, //, //	, // true : Ÿ�Ϲ�� false : ��� ���
/*#define*/ BG_TILE_IMAGE_NUM, //	10		, // Ÿ�� �̹��� ���� 1, 3, 9, //, //
/*#define*/ BG_START_FONT, //11		, // ���Ͽ��� ��׶��� �̹��� ���� ��ġ, //		
/*#define*/ TEXT_COLOR, //	12		, // �ؽ�Ʈ �÷�, //	
/*#define*/ TEXT_STYLE, //	13		, // �ؽ�Ʈ ����ü, //	
/*#define*/ TEXT_SIZE, //	14		, // �ؽ�Ʈ ũ��, //	
/*#define*/ GROUP_NUM, //	15		, // control group ��ȣ		
};
//, //, //, //	
										
#define ID_LENGTH	31									
										
// �� ��Ʈ�� ���� ���� ����!! => 2���� ���� ( DiagramEditor.cpp�� AddObject�� DLGEditorSDoc.cpp�� Serialize!!)										
static CTRL_SAVING_ORDER_INFO ctrl_saving_order[CTRL_COUNT] = 										
{										
	IMGSTT_STR, 0, 									
	STATT_STR, 1,									
	CHKB_STR, 2,									
	RADB_STR, 3,									
	BTN_STR, 4,									
	ETB_STR, 5,									
	CHTETB_STR, 6,									
	LSTB_STR, 7, 									
	LSTV_STR, 8,									
	CBX_STR, 9,									
	OUTLNE_STR, 10,									
};										


#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE { MODE_FULL, MODE_WIN };
	enum BUFFERID{ BUFFER_TRICOL, BUFFER_RCCOL, BUFFER_RCTEX, BUFFER_TERRINTEX, BUFFER_END	};
	enum INFO { INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };

	// DYNAMIC�� ��� �� �����Ӹ��� ������ �ʿ��� ������Ʈ
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END};
}


#endif // Engine_Enum_h__

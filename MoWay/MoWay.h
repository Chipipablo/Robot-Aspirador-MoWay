
// MoWay.h: archivo de encabezado principal para la aplicaci�n PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// S�mbolos principales


// CMoWayApp:
// Consulte la secci�n MoWay.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CMoWayApp : public CWinApp
{
public:
	CMoWayApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementaci�n

	DECLARE_MESSAGE_MAP()
};

extern CMoWayApp theApp;
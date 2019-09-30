
// MoWay.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// Símbolos principales


// CMoWayApp:
// Consulte la sección MoWay.cpp para obtener información sobre la implementación de esta clase
//

class CMoWayApp : public CWinApp
{
public:
	CMoWayApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CMoWayApp theApp;
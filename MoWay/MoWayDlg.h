
// MoWayDlg.h: archivo de encabezado
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Cuadro de diálogo de CMoWayDlg
class CMoWayDlg : public CDialogEx
{
// Construcción
public:
	CMoWayDlg(CWnd* pParent = NULL);	// Constructor estándar

// Datos del cuadro de diálogo
	enum { IDD = IDD_MOWAY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void Conectar();
	afx_msg void Desconectar();
	afx_msg void Front();
	afx_msg void Brake();
	afx_msg void Red();
	afx_msg void Green();
	afx_msg void velocidad(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void Avanzar();
	afx_msg void Stop();
	afx_msg void Izquierda();
	afx_msg void Derecha();
	afx_msg void Retroceder();
	CSliderCtrl slider_izq;
	afx_msg void slider_izquierda(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl slider_der;
	afx_msg void slider_derecha(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void act_sensores();
	CProgressCtrl s_izq2;
	CProgressCtrl s_izq1;
	CProgressCtrl s_der1;
	CProgressCtrl s_der2;
	CProgressCtrl s_luz;
	CProgressCtrl s_bateria;
	CButton vel_25;
//	afx_msg void ir_recto();
	bool v_25;
	afx_msg void recto_25();
	afx_msg void recto_75();
	afx_msg void recto_100();
	afx_msg void recto_50();
	afx_msg void recto_giro_25();
	afx_msg void recto_giro();
	afx_msg void giro90();
	afx_msg void giro180();
	afx_msg void aspiradora();
	afx_msg void espiral();
	afx_msg void OnNMCustomdrawProgress4(NMHDR *pNMHDR, LRESULT *pResult);
};


// MoWayDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "MoWay.h"
#include "MoWayDlg.h"
#include "afxdialogex.h"
#include "CMoway.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMoway mimoway;

boolean conectado=false;

boolean front, brake, red, green = false;

// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cuadro de diálogo de CMoWayDlg




CMoWayDlg::CMoWayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMoWayDlg::IDD, pParent)
	, v_25(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMoWayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_IZQ, slider_izq);
	DDX_Control(pDX, IDC_SLIDER_DER, slider_der);
	DDX_Control(pDX, IDC_PROGRESS4, s_izq2);
	DDX_Control(pDX, IDC_PROGRESS8, s_izq1);
	DDX_Control(pDX, IDC_PROGRESS3, s_der1);
	DDX_Control(pDX, IDC_PROGRESS5, s_der2);
	DDX_Control(pDX, IDC_PROGRESS6, s_luz);
	DDX_Control(pDX, IDC_PROGRESS7, s_bateria);
	DDX_Control(pDX, IDCANCEL, vel_25);
}

BEGIN_MESSAGE_MAP(CMoWayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMoWayDlg::Conectar)
	ON_BN_CLICKED(IDC_BUTTON2, &CMoWayDlg::Desconectar)
	ON_BN_CLICKED(IDC_BUTTON5, &CMoWayDlg::Front)
	ON_BN_CLICKED(IDC_BUTTON6, &CMoWayDlg::Brake)
	ON_BN_CLICKED(IDC_BUTTON3, &CMoWayDlg::Red)
	ON_BN_CLICKED(IDC_BUTTON4, &CMoWayDlg::Green)
	ON_BN_CLICKED(IDC_BUTTON9, &CMoWayDlg::Avanzar)
	ON_BN_CLICKED(IDC_BUTTON11, &CMoWayDlg::Stop)
	ON_BN_CLICKED(IDC_BUTTON7, &CMoWayDlg::Izquierda)
	ON_BN_CLICKED(IDC_BUTTON8, &CMoWayDlg::Derecha)
	ON_BN_CLICKED(IDC_BUTTON10, &CMoWayDlg::Retroceder)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_IZQ, &CMoWayDlg::slider_izquierda)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DER, &CMoWayDlg::slider_derecha)
	ON_BN_CLICKED(actualizar_sensores, &CMoWayDlg::act_sensores)
	//ON_BN_CLICKED(IDOK2, &CMoWayDlg::ir_recto)
	ON_BN_CLICKED(IDOK5, &CMoWayDlg::recto_25)
	ON_BN_CLICKED(IDOK4, &CMoWayDlg::recto_75)
	ON_BN_CLICKED(IDOK3, &CMoWayDlg::recto_100)
	ON_BN_CLICKED(IDOK2, &CMoWayDlg::recto_50)
	ON_BN_CLICKED(IDOK9, &CMoWayDlg::recto_giro_25)
	ON_BN_CLICKED(IDOK6, &CMoWayDlg::recto_giro)
	ON_BN_CLICKED(IDOK8, &CMoWayDlg::giro90)
	ON_BN_CLICKED(IDOK7, &CMoWayDlg::giro180)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CMoWayDlg::aspiradora)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS4, &CMoWayDlg::OnNMCustomdrawProgress4)
END_MESSAGE_MAP()


// Controladores de mensaje de CMoWayDlg

BOOL CMoWayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Establecer el icono para este cuadro de diálogo. El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	// TODO: agregar aquí inicialización adicional

	slider_izq.SetRange(-100,100,TRUE);
	slider_der.SetRange(-100,100,TRUE);
	UpdateData(FALSE);
	s_luz.SetRange(0,100);
	s_bateria.SetRange(0,100);
	s_izq1.SetRange(0,255);
	s_izq2.SetRange(0,255);
	s_der1.SetRange(0,255);
	s_der2.SetRange(0,255);
	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CMoWayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono. Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CMoWayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CMoWayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMoWayDlg::Conectar()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	conectado = mimoway.ConnectMoway(4);
	if (conectado) mimoway.ChangeLEDState(CMoway::LED_FRONT, CMoway::ON);
}


void CMoWayDlg::Desconectar()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.ChangeLEDState(CMoway::LED_FRONT, CMoway::OFF);
	mimoway.ChangeLEDState(CMoway::LED_BRAKE, CMoway::OFF);
	mimoway.ChangeLEDState(CMoway::LED_TOP_RED, CMoway::OFF);
	mimoway.ChangeLEDState(CMoway::LED_TOP_GREEN, CMoway::OFF);
	mimoway.MotorStop();

	mimoway.ChangeLEDState(CMoway::LED_FRONT, CMoway::OFF);
	mimoway.DisconnectMoway();


}


void CMoWayDlg::Front()
{	
	if(!front) mimoway.ChangeLEDState(CMoway::LED_FRONT, CMoway::ON);
	else mimoway.ChangeLEDState(CMoway::LED_FRONT, CMoway::OFF);
	front=!front;
}


void CMoWayDlg::Brake()
{
	if(!brake) mimoway.ChangeLEDState(CMoway::LED_BRAKE, CMoway::ON);
	else mimoway.ChangeLEDState(CMoway::LED_BRAKE, CMoway::OFF);
	brake=!brake;
	// apaga LED de freno
}


void CMoWayDlg::Red()
{
	if(!red) mimoway.ChangeLEDState(CMoway::LED_TOP_RED, CMoway::ON);
	else mimoway.ChangeLEDState(CMoway::LED_TOP_RED, CMoway::OFF);
	red=!red;
	// apaga el LED verde
}


void CMoWayDlg::Green()
{
	if(!green) mimoway.ChangeLEDState(CMoway::LED_TOP_GREEN, CMoway::ON);
	else mimoway.ChangeLEDState(CMoway::LED_TOP_GREEN, CMoway::OFF);
	green=!green;
	// enciende el LED rojo
}



void CMoWayDlg::Avanzar()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.GoStraight(50,CMoway::FORWARD);
	slider_izq.SetPos(50);
	slider_der.SetPos(50);
	UpdateData(FALSE);
}


void CMoWayDlg::Stop()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.MotorStop();
	slider_izq.SetPos(0);
	slider_der.SetPos(0);
	UpdateData(FALSE);
}


void CMoWayDlg::Izquierda()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.SetSpeed(0,25);
	slider_izq.SetPos(0);
	slider_der.SetPos(25);
	UpdateData(FALSE);
}


void CMoWayDlg::Derecha()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.SetSpeed(25,0);
	slider_izq.SetPos(25);
	slider_der.SetPos(0);
	UpdateData(FALSE);
}


void CMoWayDlg::Retroceder()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.GoStraight(50,CMoway::BACKWARD);
	slider_izq.SetPos(-50);
	slider_der.SetPos(-50);
	UpdateData(FALSE);
}


void CMoWayDlg::slider_izquierda(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Agregue aquí su código de controlador de notificación de control

	
	UpdateData(TRUE);
	CMoway::direction izq_dir;
	CMoway::direction der_dir;
	int izq = slider_izq.GetPos();
	int der = slider_der.GetPos();
	if (izq < 0){ izq=-izq; izq_dir=CMoway::BACKWARD;}
	else izq_dir=CMoway::FORWARD;
	if(der<0) {der=-der; der_dir=CMoway::BACKWARD;}
	else der_dir=CMoway::FORWARD;
	mimoway.SetSpeed(izq,der,izq_dir,der_dir);
	
	*pResult = 0;
	
}


void CMoWayDlg::slider_derecha(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Agregue aquí su código de controlador de notificación de control

	
	UpdateData(TRUE);
	CMoway::direction izq_dir;
	CMoway::direction der_dir;
	int izq = slider_izq.GetPos();
	int der = slider_der.GetPos();
	if (izq < 0) {izq=-izq; izq_dir=CMoway::BACKWARD;}
	else izq_dir=CMoway::FORWARD;
	if(der<0) {der=-der; der_dir=CMoway::BACKWARD;}
	else der_dir=CMoway::FORWARD;
	mimoway.SetSpeed(izq,der,izq_dir,der_dir);
	*pResult = 0;
}



void CMoWayDlg::act_sensores()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	//luz
	int luz;
	mimoway.ReadAmbientLightSensor(&luz);
	s_luz.SetPos(luz);

	//bateria
	int bateria;
	mimoway.ReadBatteryStatus(&bateria);
	s_bateria.SetPos(bateria);

	//izq1
	int izq1;
	int izq2;
	int der1;
	int der2;
	mimoway.ReadProximitySensors(&izq2,&izq1,&der1,&der2);

	//izq1
	s_izq1.SetPos(izq1);
	//izq2
	
	s_izq2.SetPos(izq2);

	//der1
	
	s_der1.SetPos(der1);

	//der2
	
	s_der2.SetPos(der2);
}


//void CMoWayDlg::ir_recto()
//{
//	// TODO: Agregue aquí su código de controlador de notificación de control
//	
//	if (v_25) {
//		mimoway.GoStraightDistance(25,CMoway::FORWARD,160);
//	}
//}


void CMoWayDlg::recto_25()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.GoStraightDistance(25,CMoway::FORWARD,160);
}


void CMoWayDlg::recto_50()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.GoStraightDistance(50,CMoway::FORWARD,160);
}


void CMoWayDlg::recto_75()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.GoStraightDistance(75,CMoway::FORWARD,160);
}


void CMoWayDlg::recto_100()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.GoStraightDistance(100,CMoway::FORWARD,160);
}


void CMoWayDlg::recto_giro_25()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	//mimoway.GoStraightDistance(50,CMoway::FORWARD,160);
	//mimoway.SetSpeed(0,50);
	mimoway.GoStraightDistance(50,CMoway::FORWARD,90);
	Sleep(450);
	mimoway.SetSpeedDistance(1,100,CMoway::FORWARD,CMoway::FORWARD,125,190);
}


void CMoWayDlg::recto_giro()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.GoStraightDistance(50,CMoway::FORWARD,160);
	Sleep(1100);
	mimoway.SetSpeed(0,50);
	Sleep(650);
	mimoway.GoStraightDistance(50,CMoway::FORWARD,40);
	
}


void CMoWayDlg::giro90()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.SetSpeed(25,25,CMoway::BACKWARD,CMoway::FORWARD);
	Sleep(300);
	mimoway.MotorStop();
}


void CMoWayDlg::giro180()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	mimoway.SetSpeed(25,25,CMoway::BACKWARD,CMoway::FORWARD);
	Sleep(730);
	mimoway.MotorStop();
}


void CMoWayDlg::aspiradora()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
		int izq1,izq2,der1,der2;
		int random_time;

		while (conectado){
			//sensores
			mimoway.ReadProximitySensors(&izq2,&izq1,&der1,&der2);
			s_izq1.SetPos(izq1);
			s_izq2.SetPos(izq2);
			s_der1.SetPos(der1);
			s_der2.SetPos(der2);

			

			if (izq2 > 225){
				mimoway.SetSpeed(25,25,CMoway::FORWARD,CMoway::BACKWARD);
				random_time=rand() % 300 + 200;
				Sleep(random_time);
			}else if (der2 > 225){
				mimoway.SetSpeed(25,25,CMoway::BACKWARD,CMoway::FORWARD);
				random_time=rand() % 300 + 200;
				Sleep(random_time);
			}else if (izq1 > 225){
				mimoway.SetSpeed(25,25,CMoway::FORWARD,CMoway::BACKWARD);
				random_time=rand() % 800 + 200;
				Sleep(random_time);
			}else if (der1 > 225){
				mimoway.SetSpeed(25,25,CMoway::BACKWARD,CMoway::FORWARD);
				random_time=rand() % 800 + 200;
				Sleep(random_time);
			}

			mimoway.SetSpeed(25,25,CMoway::FORWARD,CMoway::FORWARD);

			if ((random_time=rand() % 6) > 4){
				int cont = 0;
				while (cont < 6 && izq2 < 225 && der2 < 225 && izq1 < 225 && der1 < 225){
					Sleep(200);
					cont++;
				}
				if (cont > 5) espiral();
			}
		
		}

}

void CMoWayDlg::espiral(){


		int izq1,izq2,der1,der2=0;
		int random_time;
		int sleep1=1,sleep2=100;
			//sensores
			mimoway.ReadProximitySensors(&izq2,&izq1,&der1,&der2);
		int timeout = 0;
			while (timeout < 10 && izq2 < 225 && der2 < 225 && izq1 < 225 && der1 < 225){
				mimoway.ReadProximitySensors(&izq2,&izq1,&der1,&der2);
				mimoway.SetSpeed(10,10,CMoway::FORWARD,CMoway::FORWARD);
				Sleep(sleep1);
				mimoway.SetSpeed(0,10,CMoway::FORWARD,CMoway::FORWARD);
				Sleep(sleep2);
				sleep1+=50;
				sleep2+=10;
				timeout++;
			}

		
		
}


void CMoWayDlg::OnNMCustomdrawProgress4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Agregue aquí su código de controlador de notificación de control
	*pResult = 0;
}


// CoordCheckDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoordCheck.h"
#include "CoordCheckDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.14159265358979323846
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCoordCheckDlg 对话框



CCoordCheckDlg::CCoordCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCoordCheckDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoordCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Lon);
	DDX_Control(pDX, IDC_EDIT2, m_Lat);
	DDX_Control(pDX, IDC_EDIT4, m_X);
	DDX_Control(pDX, IDC_EDIT5, m_Y);
	DDX_Control(pDX, IDC_EDIT3, m_CenterLon);
}

BEGIN_MESSAGE_MAP(CCoordCheckDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCoordCheckDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCoordCheckDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCoordCheckDlg 消息处理程序

BOOL CCoordCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_CenterLon.SetWindowTextW(L"105");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCoordCheckDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCoordCheckDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCoordCheckDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//BJ54 WGS84
void CCoordCheckDlg::OnBnClickedButton1()
{
	double centerLon;
	CString str;
	m_CenterLon.GetWindowTextW(str);
	centerLon = _ttof(str);
	if (centerLon > 160 || centerLon < 60)
	{
		MessageBox(L"请输入正确的 中央子午线");
	}
	//
	m_X.GetWindowTextW(str);
	double x = _ttof(str);
	//
	m_Y.GetWindowTextW(str);
	double y = _ttof(str);
	//
	double lon, lat;
	BJ54ToWGS84(centerLon, y, x, lon, lat);
	//
	str.Format(L"%0.8f", lon); m_Lon.SetWindowTextW(str);
	str.Format(L"%0.8f", lat); m_Lat.SetWindowTextW(str);
}

//WGS84  BJ54
void CCoordCheckDlg::OnBnClickedButton2()
{
	double centerLon;
	CString str;
	m_CenterLon.GetWindowTextW(str);
	centerLon = _ttof(str);
	if (centerLon > 160 || centerLon < 60)
	{
		MessageBox(L"请输入正确的 中央子午线");
	}
	//
	m_Lon.GetWindowTextW(str);
	double lon = _ttof(str);
	//
	m_Lat.GetWindowTextW(str);
	double lat = _ttof(str);
	//
	double x, y;
	WGS84ToBJ54(lon, lat, y, x, centerLon);
	//
	str.Format(L"%0.3f", x); m_X.SetWindowTextW(str);
	str.Format(L"%0.3f", y); m_Y.SetWindowTextW(str);
}
//坐标正算
void CCoordCheckDlg::WGS84ToBJ54(double lon, double lat, double &X, double &Y, int E0)
{
	double sa, sb, sep, sn, sy2, st, sm, sx, hb;
	double xx, yy, hd, sd;

	//判断值的范围
	if (lon > 360 || lon < 0 || lat > 360 || lat < 0)
	{
		X = lon;
		Y = lat;
		return;
	}

	lon = lon - E0;
	sa = 6378245;
	sb = 6356863.019;
	sep = 0.006738525415;
	hd = lat*PI;
	hb = hd / 180.0;
	st = tan(hb);

	sn = pow(sa, (double)2) / sqrt(pow(sa, (double)2)*pow(cos(hb), (double)2)
		+ pow(sb, (double)2)*pow(sin(hb), (double)2));

	sy2 = sep*pow(cos(hb), (double)2);
	sd = cos(hb)*lon*PI;
	sm = sd / 180.0;
	sx = 111134.861*lat - (32005.78*sin(hb) + 133.924*pow(sin(hb), (double)3) + 0.697*pow(sin(hb), (double)5))*cos(hb);
	xx = sx + sn*st*(0.5*pow(sm, (double)2) + 1.0 / 24.0*(5.0 - pow(st, (double)2) + 9.0*sy2)*pow(sm, (double)4));
	yy = sn*(sm + 1.0 / 6.0*(1.0 - pow(st, (double)2) + sy2)*pow(sm, (double)3) + 1.0 / 120.0*(5.0 - 18.0*pow(st, (double)2) + pow(st, (double)4))*pow(sm, (double)5));
	X = xx;
	Y = yy + 500000;
}

void CCoordCheckDlg::BJ54ToWGS84(double E0, double X, double Y, double &lon, double &lat)
{
	double bf, vf, nf, ynf, tf, yf2, hbf;
	double sa, sb, se2, sep2, mf;
	double w1, w2, w, w3, w4;
	double pi = 3.1415926535898;

	X = X / 1000000.0;
	Y = Y - 500000.0;

	bf = 9.04353692458*X - 0.00001007623*pow(X, 2.0) - 0.00074438304*pow(X, 3.0) - 0.00000463064*pow(X, 4.0) + 0.00000505846*pow(X, 5.0) - 0.00000016754*pow(X, 6.0);
	hbf = bf * pi / 180.0;
	sa = 6378245.0;
	sb = 6356863.019;
	//0.0066934216239182 0.0067385254156487
	se2 = 0.006693421623;
	sep2 = 0.006738525415;

	w1 = sin(hbf);
	w2 = 1.0 - se2 * pow(w1, (double)2);
	w = sqrt(w2);
	mf = sa*(1.0 - se2) / pow(w, (double)3);
	w3 = cos(hbf);

	w4 = pow(sa, (double)2)*pow(w3, (double)2) + pow(sb, (double)2)*pow(w1, (double)2);
	nf = pow(sa, (double)2) / sqrt(w4);

	ynf = Y / nf;
	vf = nf / mf;
	tf = tan(hbf);

	yf2 = sep2 * pow(w3, (double)2);

	lat = bf - 1.0 / 2.0 * vf * tf * (pow(ynf, (double)2) - 1.0 / 12.0*(5.0 + 3.0*pow(tf, (double)2) + yf2 - 9.0*yf2*pow(tf, (double)2))*pow(ynf, (double)4))*180.0 / pi;
	lon = 1.0 / w3*ynf*(1.0 - 1.0 / 6.0*(1.0 + 2.0*pow(tf, (double)2) + yf2)*pow(ynf, (double)2) + 1.0 / 120.0*(5.0 + 28.0*pow(tf, (double)2) + 24.0*pow(tf, (double)2) + 6.0*yf2 + 8.0*yf2*pow(tf, (double)2))*pow(ynf, (double)4))*180.0 / pi;
	lon = E0 + lon;
}
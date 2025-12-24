
// A_Priceboard_toolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "A_Priceboard_tool.h"
#include "A_Priceboard_toolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CA_Priceboard_toolDlg 对话框

CA_Priceboard_toolDlg::CA_Priceboard_toolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CA_Priceboard_toolDlg::IDD, pParent)
	, m_i_step(_T(""))
	, m_i_x(_T(""))
	, m_i_y(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CA_Priceboard_toolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STEP, m_i_step);
	DDX_Text(pDX, IDC_EDIT_X, m_i_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_i_y);
	DDX_Text(pDX, IDC_EDIT_LINESPACE, cs_linspace);
}

BEGIN_MESSAGE_MAP(CA_Priceboard_toolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UP, &CA_Priceboard_toolDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CA_Priceboard_toolDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CA_Priceboard_toolDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CA_Priceboard_toolDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CA_Priceboard_toolDlg::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDOK, &CA_Priceboard_toolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADVANCED, &CA_Priceboard_toolDlg::OnBnClickedButtonAdvanced)
END_MESSAGE_MAP()


// CA_Priceboard_toolDlg 消息处理程序

BOOL CA_Priceboard_toolDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CString t_s_x = _T("");
	CString t_s_y = _T("");

	m_i_step = _T("2.0"); //默认步阶 单位mm

	GetPrivateProfileString(_T("label"), _T("x"), _T(""), t_s_x.GetBuffer(MAX_PATH), MAX_PATH, _T("c:\\mdcas\\memberpriceboard.ini"));
	GetPrivateProfileString(_T("label"), _T("y"), _T(""), t_s_y.GetBuffer(MAX_PATH), MAX_PATH, _T("c:\\mdcas\\memberpriceboard.ini"));
	GetPrivateProfileString(_T("label"), _T("x"), _T(""), m_i_x.GetBuffer(MAX_PATH), MAX_PATH, _T("c:\\mdcas\\memberpriceboard.ini"));
	GetPrivateProfileString(_T("label"), _T("y"), _T(""), m_i_y.GetBuffer(MAX_PATH), MAX_PATH, _T("c:\\mdcas\\memberpriceboard.ini"));
	GetPrivateProfileString(_T("label"), _T("linespace"), _T(""), cs_linspace.GetBuffer(MAX_PATH), MAX_PATH, _T("c:\\mdcas\\memberpriceboard.ini"));

	t_s_x.ReleaseBuffer();
	t_s_y.ReleaseBuffer();
	m_i_x.ReleaseBuffer();
	m_i_y.ReleaseBuffer();
	m_i_step.ReleaseBuffer();
	cs_linspace.ReleaseBuffer();

	int xpot = t_s_x.Find(_T("."));
	int ypot = t_s_y.Find(_T("."));
	int steppot = m_i_step.Find(_T("."));
	
	

	CString s_idx = _T("");
	CString s_idy = _T("");
	CString s_fdx = _T("");
	CString s_fdy = _T("");
	CString s_idstep = _T("");
	CString s_fdstep = _T("");

	if (xpot != -1) 
	{
		s_idx = t_s_x.Left(xpot);
		s_fdx = t_s_x.Right(t_s_x.GetLength() - xpot - 1);
	}
	else 
	{
		s_idx = t_s_x.Left(t_s_x.GetLength());
		s_fdx = _T("0");
	}
	if (ypot != -1) 
	{
		s_idy = t_s_y.Left(ypot);
		s_fdy = t_s_y.Right(t_s_y.GetLength() - ypot - 1);
	}
	else
	{
		s_idy = t_s_y.Left(t_s_y.GetLength());
		s_fdy = _T("0");
	}
	if (steppot != -1)
	{
		s_idstep = m_i_step.Left(steppot);
		s_fdstep = m_i_step.Right(m_i_step.GetLength() - steppot - 1);
	}
	else
	{
		s_idstep = m_i_step.Left(m_i_step.GetLength());
		s_fdstep = _T("0");
	}
	

	i_idx = _wtoi(s_idx);
	i_idy = _wtoi(s_idy);
	i_fdx = _wtoi(s_fdx);
	i_fdy = _wtoi(s_fdy);
	i_istep = _wtoi(s_idstep);
	i_fstep = _wtoi(s_fdstep);

	b_xSF = FALSE;
	b_ySF = FALSE;

	if (i_idx < 0)b_xSF = TRUE;
	if (i_idy < 0)b_ySF = TRUE;

	//到此已得到位置信息

	UpdateData(FALSE);

	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_X);        //获取控件指针，IDC_EDIT1为控件ID号
	pWnd = GetDlgItem(IDC_EDIT_Y);        //获取控件指针，IDC_EDIT1为控件ID号
	advanced = TRUE;


	::AfxMessageBox(_T("本程序会自动退出当前的“小房子”程序，如已做保存请点击确认。"));
	//::system("TASKKILL /IM shop.exe /F");
	::WinExec("TASKKILL /IM shop.exe /F",SW_HIDE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CA_Priceboard_toolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CA_Priceboard_toolDlg::OnPaint()
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
HCURSOR CA_Priceboard_toolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CA_Priceboard_toolDlg::OnBnClickedButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	compute_final_value(8);
	SaveDatatoCString();
	UpdateData(FALSE);
}


void CA_Priceboard_toolDlg::OnBnClickedButtonDown()
{
	UpdateData(TRUE);
	compute_final_value(5);
	SaveDatatoCString();
	UpdateData(FALSE);
}


void CA_Priceboard_toolDlg::OnBnClickedButtonLeft()
{
	UpdateData(TRUE);
	compute_final_value(4);
	SaveDatatoCString();
	UpdateData(FALSE);
}


void CA_Priceboard_toolDlg::OnBnClickedButtonRight()
{
	UpdateData(TRUE);
	compute_final_value(6);
	SaveDatatoCString();
	UpdateData(FALSE);
}


void CA_Priceboard_toolDlg::OnBnClickedButtonTest()
{
	::WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);

	WritePrivateProfileString(_T("label"), _T("x"), m_i_x, _T("c:\\mdcas\\memberpriceboard.ini"));
	WritePrivateProfileString(_T("label"), _T("y"), m_i_y, _T("c:\\mdcas\\memberpriceboard.ini"));
	WritePrivateProfileString(_T("label"), _T("linespace"), cs_linspace, _T("c:\\mdcas\\memberpriceboard.ini"));
	
	m_i_x.ReleaseBuffer();
	m_i_y.ReleaseBuffer();
	cs_linspace.ReleaseBuffer();

	::WinExec("c:\\mdcas\\shop.exe",SW_NORMAL);
}


void CA_Priceboard_toolDlg::OnBnClickedOk()
{

	UpdateData(TRUE);

	WritePrivateProfileString(_T("label"),_T("x"),m_i_x,_T("c:\\mdcas\\memberpriceboard.ini"));
	WritePrivateProfileString(_T("label"),_T("y"),m_i_y,_T("c:\\mdcas\\memberpriceboard.ini"));
	WritePrivateProfileString(_T("label"), _T("linespace"), cs_linspace, _T("c:\\mdcas\\memberpriceboard.ini"));
	
	m_i_x.ReleaseBuffer();
	m_i_y.ReleaseBuffer();
	cs_linspace.ReleaseBuffer();

	CDialogEx::OnOK();
}

BOOL CA_Priceboard_toolDlg::compute_final_value(int denumber)
{
	//get newest step number and seprate it to int part and float part
	int steppot = m_i_step.Find(_T("."));

	m_i_step.ReleaseBuffer();

	CString s_idstep = m_i_step.Left(steppot);
	CString s_fdstep = m_i_step.Right(m_i_step.GetLength() - steppot - 1);

	i_istep = _wtoi(s_idstep);
	i_fstep = _wtoi(s_fdstep);

	int t_xCF = 0;
	int t_yCF = 0;


	if (i_idx < 0)b_xSF = TRUE;
	if (i_idy < 0)b_ySF = TRUE;

	if (denumber == 8) 
	{
		if (b_ySF) //初始值为负数
		{
			i_fdy += i_fstep;//小数部分

			if (i_fdy >= 10)   //进位处理
			{
				i_fdy -= 10;
				t_yCF += -1;
			}

			i_idy = i_idy - i_istep + t_yCF; //整数部分
		}
		else //初始值为正数
		{
			i_fdy -= i_fstep;//小数部分
			i_idy -= i_istep;//整数部分

			if (i_fdy < 0) //进位处理
			{
				if(i_idy > 0)
				{
					i_fdy += 10;
					t_yCF += -1;
				}
				else 
				{
					b_ySF = TRUE;
					i_fdy = -1 * i_fdy;
				}
				
			}
			else if (i_fdy == 0)
			{
				
			}

			i_idy += t_yCF;//整数部分
		}
	}
	if (denumber == 5) 
	{
		if (b_ySF) //初始值为负数
		{
			i_fdy -= i_fstep;//小数部分
			i_idy += i_istep;//整数部分

			if (i_fdy < 0)   //进位处理
			{
				if (i_idy < 0)
				{
					i_fdy += 10;
					t_yCF += 1;
				}
				else
				{
					b_ySF = FALSE;
					i_fdy = -1 * i_fdy;
				}
				
			}

			i_idy += t_yCF; //整数部分
		}
		else //初始值为正数
		{
			i_fdy += i_fstep;//小数部分

			if (i_fdy >= 10) //进位处理
			{
				i_fdy -= 10;
				t_yCF += 1;
			}

			i_idy = i_idy + i_istep + t_yCF; //整数部分
		}
	}
	if (denumber == 4) 
	{
		if (b_xSF) //初始值为负数
		{
			i_fdx += i_fstep;//小数部分

			if (i_fdx >= 10)   //进位处理
			{
				i_fdx -= 10;
				t_xCF += -1;
			}
			i_idx = i_idx - i_istep + t_xCF; //整数部分
		}
		else //初始值为正数
		{
			i_fdx -= i_fstep;//小数部分
			i_idx -= i_istep;//整数部分

			if (i_fdx < 0 ) //进位处理
			{
				if (i_idx > 0) 
				{
					i_fdx += 10;
					t_xCF += -1;
				}
				else
				{
					b_xSF = TRUE;
					i_fdx = -1 * i_fdx;
				}
				
			}
			i_idx += t_xCF; //整数部分
		}
	}
	if (denumber == 6) 
	{
		if (b_xSF) //初始值为负数
		{
			i_fdx -= i_fstep;//小数部分
			i_idx += i_istep;//整数部分

			if (i_fdx < 0)   //进位处理
			{
				if (i_idx < 0) 
				{
					i_fdx += 10;
					t_xCF += 1;
				}
				else 
				{
					b_xSF = FALSE;
					i_fdx = -1 * i_fdx;
					//::AfxMessageBox(_T("test"));
				}
				
			}
			else
			{

			}

			i_idx += t_xCF; //整数部分
		}
		else //初始值为正数
		{
			i_fdx += i_fstep;//小数部分

			if (i_fdx >= 10) //进位处理
			{
				i_fdx -= 10;
				t_xCF += 1;
			}

			i_idx = i_idx + i_istep + t_xCF; //整数部分
		}
	}

	if (i_idx < 0)b_xSF = TRUE;
	else if(i_idx == 0 && i_fdx < 0)b_xSF = TRUE;
	//else b_xSF = FALSE;

	if (i_idy < 0)b_ySF = TRUE;
	else if(i_idy == 0 && i_fdy < 0)b_ySF = TRUE;
	//else b_ySF = FALSE;

	if (i_idx == 0)b_xZF = TRUE;
	else b_xZF = FALSE;
	if (i_idy == 0)b_yZF = TRUE;
	else b_yZF = FALSE;

	return TRUE;
}

BOOL CA_Priceboard_toolDlg::SaveDatatoCString()
{
	m_i_x.ReleaseBuffer();
	m_i_y.ReleaseBuffer();

	m_i_x.Format(_T("%d.%d"),i_idx,i_fdx);
	m_i_y.Format(_T("%d.%d"),i_idy,i_fdy);

	int pot1 = m_i_x.Find(_T(".0"));
	int pot2 = m_i_x.Find(_T("."));
	int pot3 = m_i_y.Find(_T(".0"));
	int pot4 = m_i_y.Find(_T("."));

	m_i_x.ReleaseBuffer();
	m_i_y.ReleaseBuffer();

	if (pot1 == -1)
		m_i_x = m_i_x.Left(m_i_x.GetLength());
	else if (pot1 == pot2)
		m_i_x.Left(pot1);//整数
	if (pot3 == -1)
		m_i_y = m_i_y.Left(m_i_y.GetLength());
	else if (pot3 == pot4)
		m_i_y.Left(pot3);//整数

	m_i_x.ReleaseBuffer();
	m_i_y.ReleaseBuffer();

	if (b_xSF == TRUE && b_xZF == TRUE)
		if (i_fdx != 0)
			m_i_x = _T("-") + m_i_x;
	if (b_ySF == TRUE && b_yZF == TRUE)
		if (i_fdy != 0)
			m_i_y = _T("-") + m_i_y;

	return TRUE;
}

void CA_Priceboard_toolDlg::OnBnClickedButtonAdvanced()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if(advanced ==FALSE)
	{
		GetDlgItem(IDC_EDIT_X)->ShowWindow(SW_NORMAL);        //获取控件指针，IDC_EDIT1为控件ID号
		GetDlgItem(IDC_EDIT_Y)->ShowWindow(SW_NORMAL);        //获取控件指针，IDC_EDIT1为控件ID号
		GetDlgItem(IDC_STATICX)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STATICY)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_BUTTON_ADVANCED)->SetWindowTextW(_T("隐藏坐标>>"));
		advanced = TRUE;
		
	}else if (advanced == TRUE)
	{
		GetDlgItem(IDC_EDIT_X)->ShowWindow(SW_HIDE);        //获取控件指针，IDC_EDIT1为控件ID号
		GetDlgItem(IDC_EDIT_Y)->ShowWindow(SW_HIDE);        //获取控件指针，IDC_EDIT1为控件ID号
		GetDlgItem(IDC_STATICX)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATICY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_ADVANCED)->SetWindowTextW(_T("<<显示坐标"));
		advanced = FALSE;
	}
	

}

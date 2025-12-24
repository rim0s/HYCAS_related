
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_ANIMATE1, m_avi);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BT_BLUE, &CMFCApplication1Dlg::OnBnClickedBtBlue)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_TOOLD, &CMFCApplication1Dlg::OnBnClickedButtonToold)
	//ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BT2CBlue, &CMFCApplication1Dlg::OnBnClickedBt2cblue)
	ON_BN_CLICKED(IDC_BTGreenMB, &CMFCApplication1Dlg::OnBnClickedBtgreenmb)
	ON_BN_CLICKED(IDC_BT324, &CMFCApplication1Dlg::OnBnClickedBt324)
	ON_BN_CLICKED(IDC_BT_Force_init, &CMFCApplication1Dlg::OnBnClickedBtForceinit)
	ON_BN_CLICKED(IDC_BUTTON_327, &CMFCApplication1Dlg::OnBnClickedButton327)
	ON_BN_CLICKED(IDC_BUTTON_327B, &CMFCApplication1Dlg::OnBnClickedButton327b)
	ON_BN_CLICKED(IDC_BUTTON_327_1905, &CMFCApplication1Dlg::OnBnClickedButton3271905)
	
	ON_BN_CLICKED(IDC_BT_WHITE321, &CMFCApplication1Dlg::OnBnClickedBtWhite321)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到 系统菜单中。

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

	// TODO: 在此添加额外的初始化代码

	::AfxMessageBox(_T("本程序会自动退出当前的“小房子”程序，如已做保存请点击确认。"));
	//::system("TASKKILL /IM shop.exe /F");
	::WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);


	CString labelw , labelh;
	GetPrivateProfileStringW(_T("label"), _T("labwidth"), _T(""),labelw.GetBuffer(MAX_PATH), MAX_PATH, _T("c:\\mdcas\\memberpriceboard.ini"));
	GetPrivateProfileStringW(_T("label"), _T("labheight"), _T(""), labelh.GetBuffer(MAX_PATH),MAX_PATH, _T("c:\\mdcas\\memberpriceboard.ini"));
	int labelc = GetPrivateProfileInt(_T("label"), _T("columns"), 0, _T("c:\\mdcas\\memberpriceboard.ini"));
	int labell = GetPrivateProfileInt(_T("label"), _T("lines"), 0, _T("c:\\mdcas\\memberpriceboard.ini"));
	


	if (labelc == 2)
	{
		if (labelw == _T("90") && labelh == _T("36.8"))
		{
			hytype = 2;//会员蓝色价格签
		}
		else if (labelw == _T("81") && labelh == _T("36.9"))
		{
			hytype = 4;//2列蓝色非会员
		}
		else if (labelw == _T("93") && labelh == _T("35.9"))
		{
			hytype = 5;//绿色会员
		}
		else AfxMessageBox(_T("初始化错误PD:2C UD"));
	}


		else if (labelc == 3 && labell == 8)
		{
			hytype = 1;//3列24个价格签
		}
		else if (labelc == 3 && labell == 9)
		{
			//hytype = 3;//3列27个价格签远古版
			if (labelw == _T("56.5") && labelh == _T("27"))
			{
				hytype = 6;//3列27个价格签B版
			}
			else if (labelw == _T("56") && labelh == _T("26.9"))
			{
				hytype = 7;//3列27个价格签1905版
			}
			else if (labelw == _T("59.5") && labelh == _T("30"))
			{
				hytype = 3;//3列27个价格签原始版本
			}
			else AfxMessageBox(_T("初始化错误PD:3*27"));
				
		}
		//判断目标目录中是否有相应的价签版式文件
		int labelbc = GetPrivateProfileInt(_T("label"), _T("columns"), 0, _T("c:\\mdcas\\324_memberpriceboard.ini"));
		int labelblc = GetPrivateProfileInt(_T("label"), _T("columns"), 0, _T("c:\\mdcas\\BLUE_memberpriceboard.ini"));
		int labelbnc = GetPrivateProfileInt(_T("label"), _T("columns"), 0, _T("c:\\mdcas\\2CBlue_memberpriceboard.ini"));
		int labelgnc = GetPrivateProfileInt(_T("label"), _T("columns"), 0, _T("c:\\mdcas\\Green_memberpriceboard.ini"));
		int labelbnewc = GetPrivateProfileInt(_T("label"), _T("columns"), 0, _T("c:\\mdcas\\327_memberpriceboard.ini"));
		int labelbnewcB = GetPrivateProfileInt(_T("label"), _T("columns"), 0, _T("c:\\mdcas\\327_B_memberpriceboard.ini"));
		int labelbnewcC = GetPrivateProfileInt(_T("label"), _T("columns"), 0, _T("c:\\mdcas\\327_C_memberpriceboard.ini"));

		//如果没有则从软件目录中拷贝相应版式文件
		//======================
		if (labelbc == 0)
			init324();
		if (labelblc == 0)
			initblue();
		if (labelbnc == 0)
			init2CBlue();
		if (labelgnc == 0)
			initGreen();
		if (labelbnewc == 0)
			init327();
		if (labelbnewcB == 0)
			init327b();
		if (labelbnewcC == 0)
			init327c();
		//======================








	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	WinExec("A_Priceboard_tool.exe", SW_NORMAL);
}

BOOL CMFCApplication1Dlg::init324()
{
	BOOL ret = CopyFile(_T("324_memberpriceboard.ini"), _T("c:\\mdcas\\324_memberpriceboard.ini"), false);
	if(ret==false)AfxMessageBox(_T("初始化失败324"));
	return ret;
}

BOOL CMFCApplication1Dlg::initblue()
{
	BOOL ret = CopyFile(_T("BLUE_memberpriceboard.ini"),_T("c:\\mdcas\\BLUE_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("初始化失败BLUE"));
	return ret;
}
BOOL CMFCApplication1Dlg::initGreen()
{
	BOOL ret = CopyFile(_T("Green_memberpriceboard.ini"), _T("c:\\mdcas\\Green_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("初始化失败Green"));
	return ret;
}
BOOL CMFCApplication1Dlg::init2CBlue()
{
	BOOL ret = CopyFile(_T("2CBlue_memberpriceboard.ini"), _T("c:\\mdcas\\2CBlue_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("初始化失败2CBlue"));
	return ret;
}
BOOL CMFCApplication1Dlg::init327()
{
	BOOL ret = CopyFile(_T("327_memberpriceboard.ini"), _T("c:\\mdcas\\327_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("初始化失败327A"));
	return ret;
}
BOOL CMFCApplication1Dlg::init327b()
{
	BOOL ret = CopyFile(_T("327_B_memberpriceboard.ini"), _T("c:\\mdcas\\327_B_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("初始化失败327B"));
	return ret;
}
BOOL CMFCApplication1Dlg::init327c()
{

	BOOL ret = CopyFile(_T("327_C_memberpriceboard.ini"), _T("c:\\mdcas\\327_C_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("初始化失败327C"));
	return ret;
}
///////////备份已经调整过的当前版式////////////////////////////
BOOL CMFCApplication1Dlg::bc324()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\memberpriceboard.ini"),_T("c:\\mdcas\\324_memberpriceboard.ini"),false);
	if (ret == false)AfxMessageBox(_T("备份324失败"));
	return ret;
}
BOOL CMFCApplication1Dlg::bc327()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\memberpriceboard.ini"), _T("c:\\mdcas\\327_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("备份327A失败"));
	return ret;
}
BOOL CMFCApplication1Dlg::bc327b()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\memberpriceboard.ini"), _T("c:\\mdcas\\327_B_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("备份327B失败"));
	return ret;
}
BOOL CMFCApplication1Dlg::bc327c()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\memberpriceboard.ini"), _T("c:\\mdcas\\327_C_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("备份327C失败"));
	return ret;
}
BOOL CMFCApplication1Dlg::bcOld()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\memberpriceboard.ini"),_T("c:\\mdcas\\last_memberpriceboard.ini"),false);
	if (ret == false)AfxMessageBox(_T("备份OLD失败"));
	return ret;
}

BOOL CMFCApplication1Dlg::bcblue()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\memberpriceboard.ini"),_T("c:\\mdcas\\BLUE_memberpriceboard.ini"),false);
	if (ret == false)AfxMessageBox(_T("备份会员蓝色价格签失败"));
	return ret;
}

BOOL CMFCApplication1Dlg::bcGreen()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\memberpriceboard.ini"), _T("c:\\mdcas\\Green_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("备份绿色会员价格签失败"));
	return ret;
}

BOOL CMFCApplication1Dlg::bc2CBlue()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\memberpriceboard.ini"), _T("c:\\mdcas\\2CBlue_memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("备份蓝色2列普通价格签失败"));
	return ret;
}

BOOL CMFCApplication1Dlg::to324()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\324_memberpriceboard.ini"),_T("c:\\mdcas\\memberpriceboard.ini"),false);
	if (ret == false)AfxMessageBox(_T("切换为3列8行版价签出错"));
	else AfxMessageBox(_T("已为您切换为3列8行版价签"));
	return ret;
}

BOOL CMFCApplication1Dlg::toblue()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\BLUE_memberpriceboard.ini"),_T("c:\\mdcas\\memberpriceboard.ini"),false);
	if (ret == false)AfxMessageBox(_T("切换为会员蓝色价格签出错"));
	else AfxMessageBox(_T("已为您切换为会员蓝色价格签"));
	return ret;
}

BOOL CMFCApplication1Dlg::toGreen()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\Green_memberpriceboard.ini"), _T("c:\\mdcas\\memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("切换为绿色会员价格签出错"));
	else AfxMessageBox(_T("已为您切换为绿色会员价格签"));
	return ret;
}

BOOL CMFCApplication1Dlg::to2CBlue()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\2CBlue_memberpriceboard.ini"), _T("c:\\mdcas\\memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("切换为蓝色2列普通价格签出错"));
	else AfxMessageBox(_T("已为您切换为蓝色2列普通价格签"));
	return ret;
}

BOOL CMFCApplication1Dlg::toOld()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\Last_memberpriceboard.ini"), _T("c:\\mdcas\\memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("恢复为老版价签出错"));
	else AfxMessageBox(_T("恢复为老版价签成功"));
	return ret;
}
BOOL CMFCApplication1Dlg::to327()
{
	BOOL ret = CopyFile(_T("c:\\mdcas\\327_memberpriceboard.ini"), _T("c:\\mdcas\\memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("切换为3列9行A版价签出错"));
	else AfxMessageBox(_T("已为您切换为3列9行A版价签"));
	return ret;
}
BOOL CMFCApplication1Dlg::to327b()
{
	//XX
	BOOL ret = CopyFile(_T("c:\\mdcas\\327_B_memberpriceboard.ini"), _T("c:\\mdcas\\memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("切换为3列9行B版价签出错"));
	else AfxMessageBox(_T("已为您切换为3列9行B版价签"));
	return ret;
}
BOOL CMFCApplication1Dlg::to327c()
{
	//XX
	BOOL ret = CopyFile(_T("c:\\mdcas\\327_C_memberpriceboard.ini"), _T("c:\\mdcas\\memberpriceboard.ini"), false);
	if (ret == false)AfxMessageBox(_T("切换为3列9行C版价签出错"));
	else AfxMessageBox(_T("已为您切换为3列9行C版价签"));
	return ret;
}
//----------
void CMFCApplication1Dlg::OnBnClickedButtonToold()//已不再使用
{
	//// TODO: 在此添加控件通知处理程序代码
	//if (hytype == 1)
	//{
	//	bc324();
	//	toOld();
	//	hytype = 0;
	//	//AfxMessageBox(_T("已经切换成 \"会员蓝色价格签\" "));
	//}
	//else if (hytype == 2)
	//{
	//	bcblue();
	//	toOld();
	//	hytype = 0;
	//	//AfxMessageBox(_T("已经切换成 \"会员蓝色价格签\" "));
	//}
	//else if (hytype == 3)
	//{
	//	bcblue();
	//	toOld();
	//	hytype = 0;
	//	//AfxMessageBox(_T("已经切换成 \"会员蓝色价格签\" "));
	//}
	//else AfxMessageBox(_T("正在使用此种价签，无需切换"));
}
//--------------------------------------------------------------------------------

void CMFCApplication1Dlg::OnBnClickedBtBlue()
{
	// TODO: 在此添加控件通知处理程序代码
	//1 3列24个价格签
	//2 会员蓝色价格签
	//3 3列27个价格签
	//4 2列蓝色非会员
	//5 绿色会员
	if (hytype == 1)
	{
		bc324();
		if(toblue())
			hytype = 2;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 3)
	{
		bc327();
		if (toblue())
			hytype = 2;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 4)
	{
		bc2CBlue();
		if(toblue())
			hytype = 2;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 5)
	{
		bcGreen();
		if(toblue())
			hytype = 2;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 6)
	{
		bc327b();
		if (toblue())
			hytype = 2;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 7)
	{
		bc327c();
		if (toblue())
			hytype = 2;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else AfxMessageBox(_T("正在使用此种价签，无需切换"));
	WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
}


void CMFCApplication1Dlg::OnBnClickedBt2cblue()
{
	// TODO: 在此添加控件通知处理程序代码
	//1 3列24个价格签
	//2 会员蓝色价格签
	//3 3列27个价格签
	//4 2列蓝色非会员
	//5 绿色会员
	if (hytype == 1)
	{
		bc324();
		if(to2CBlue())
			hytype = 4;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 3)
	{
		bc327();
		if (to2CBlue())
			hytype = 4;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 2)
	{
		bcblue();
		if(to2CBlue())
			hytype = 4;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 5)
	{
		bcGreen();
		if(to2CBlue())
			hytype = 4;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 6)
	{
		bc327b();
		if (to2CBlue())
			hytype = 4;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 7)
	{
		bc327c();
		if (to2CBlue())
			hytype = 4;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else AfxMessageBox(_T("正在使用此种价签，无需切换"));
	WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
}


void CMFCApplication1Dlg::OnBnClickedBtgreenmb()
{
	// TODO: 在此添加控件通知处理程序代码

	//1 3列24个价格签
	//2 会员蓝色价格签
	//3 3列27个价格签
	//4 2列蓝色非会员
	//5 绿色会员
	if (hytype == 1)
	{
		bc324();
		if(toGreen())
			hytype = 5;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 3)
	{
		bc327();
		if (toGreen())
			hytype = 5;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 2)
	{
		bcblue();
		if(toGreen())
			hytype = 5;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 4)
	{
		bc2CBlue();
		if(toGreen())
			hytype = 5;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 6)
	{
		bc327b();
		if (toGreen())
			hytype = 5;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 7)
	{
		bc327c();
		if (toGreen())
			hytype = 5;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else AfxMessageBox(_T("正在使用此种价签，无需切换"));
	WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
}


void CMFCApplication1Dlg::OnBnClickedBt324()
{
	// TODO: 在此添加控件通知处理程序代码

		//1 3列24个价格签
		//2 会员蓝色价格签
		//3 3列27个价格签
		//4 2列蓝色非会员
		//5 绿色会员
	if (hytype == 2)
	{
		bcblue();
		if(to324())
			hytype = 1;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 3)
	{
		bc327();
		if (to324())
			hytype = 1;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 4)
	{
		bc2CBlue();
		if(to324())
			hytype = 1;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 5)
	{
		bcGreen();
		if(to324())
			hytype = 1;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 6)
	{
		bc327b();
		if (to324())
			hytype = 1;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 7)
	{
		bc327c();
		if (to324())
			hytype = 1;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else AfxMessageBox(_T("正在使用此种价签，无需切换"));
	WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
}


void CMFCApplication1Dlg::OnBnClickedBtForceinit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AfxMessageBox(_T("此操作会使所有价签位置均恢复初始值需要对每种价格签重新调整位置。是否继续？"), 1, 0) == IDOK)
	{
		init324();
		initblue();
		init2CBlue();
		initGreen();
		init327();
		init327b();
		init327c();
		WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
		AfxMessageBox(_T("重置完成，请在使用前调整位置"));
	}
	else
		;
}


void CMFCApplication1Dlg::OnBnClickedButton327()
{
	// TODO: 在此添加控件通知处理程序代码
	//1 3列24个价格签
	//2 会员蓝色价格签
	//3 3列27个价格签
	//4 2列蓝色非会员
	//5 绿色会员
	if (hytype == 2)
	{
		bcblue();
		if (to327())
			hytype = 3;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 1)
	{
		bc324();
		if (to327())
			hytype = 3;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 4)
	{
		bc2CBlue();
		if (to327())
			hytype = 3;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 5)
	{
		bcGreen();
		if (to327())
			hytype = 3;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 6)
	{
		bc327b();
		if (to327())
			hytype = 3;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 7)
	{
		bc327c();
		if (to327())
			hytype = 3;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else AfxMessageBox(_T("正在使用此种价签，无需切换"));
	WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
}


void CMFCApplication1Dlg::OnBnClickedButton3271905()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	//1 3列24个价格签
	//2 会员蓝色价格签
	//3 3列27个价格签
	//4 2列蓝色非会员
	//5 绿色会员
	if (hytype == 2)
	{
		bcblue();
		if (to327c())
			hytype = 7;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 1)
	{
		bc324();
		if (to327c())
			hytype = 7;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 3)
	{
		bc327();
		if (to327c())
			hytype = 7;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 4)
	{
		bc2CBlue();
		if (to327c())
			hytype = 7;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 5)
	{
		bcGreen();
		if (to327c())
			hytype = 7;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 6)
	{
		bc327b();
		if (to327c())
			hytype = 7;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else AfxMessageBox(_T("正在使用此种价签，无需切换"));
	WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
}


void CMFCApplication1Dlg::OnBnClickedButton327b()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	//1 3列24个价格签
	//2 会员蓝色价格签
	//3 3列27个价格签
	//4 2列蓝色非会员
	//5 绿色会员
	if (hytype == 2)
	{
		bcblue();
		if (to327b())
			hytype = 6;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 1)
	{
		bc324();
		if (to327b())
			hytype = 6;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 3)
	{
		bc327();
		if (to327b())
			hytype = 6;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 4)
	{
		bc2CBlue();
		if (to327b())
			hytype = 6;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 5)
	{
		bcGreen();
		if (to327b())
			hytype = 6;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else if (hytype == 7)
	{
		bc327c();
		if (to327b())
			hytype = 6;
		//AfxMessageBox(_T("已经切换成 \"3列24个\" 价签 "));
	}
	else AfxMessageBox(_T("正在使用此种价签，无需切换"));
	WinExec("TASKKILL /IM shop.exe /F", SW_HIDE);
}


void CMFCApplication1Dlg::OnBnClickedBtWhite321()
{
	// TODO: 在此添加控件通知处理程序代码


}

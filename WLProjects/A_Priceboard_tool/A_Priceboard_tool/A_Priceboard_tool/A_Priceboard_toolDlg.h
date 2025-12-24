
// A_Priceboard_toolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CA_Priceboard_toolDlg 对话框
class CA_Priceboard_toolDlg : public CDialogEx
{
// 构造
public:
	CA_Priceboard_toolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_A_PRICEBOARD_TOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonTest();
	BOOL SaveDatatoCString();
	BOOL compute_final_value(int deNum); // 8 up ;4 left;5 down;6 right
	

	//计算器相关变量
	int i_idx;
	int i_idy;
	int i_fdx;
	int i_fdy;
	int i_istep;
	int i_fstep;

	BOOL b_xSF; //X值符号标志，负数时为1，否则为0
	BOOL b_ySF; //Y值符号标志，负数时为1，否则为0
	BOOL b_xZF; //x 整数部分为零时 为TRUE 
	BOOL b_yZF; //y
	//

	CString m_i_step;
	CString m_i_x;
	CString m_i_y;
	CString cs_linspace;

	BOOL advanced;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonAdvanced();
};

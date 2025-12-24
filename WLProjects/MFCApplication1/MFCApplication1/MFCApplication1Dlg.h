 
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

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
	CAnimateCtrl m_avi;
	//afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtBlue();

	int hytype;  
	//0 老式价签 
	//1 3列24个价签  
	//2 会员蓝色价格签
	//3 3列27个价格签
	//4 2列蓝色非会员
	//5 绿色会员
	//6 3列27个价格签B版
	//7 3列27个价格签1905版

	afx_msg void OnBnClickedButton3(); //调整位置
	BOOL init324();
	BOOL initblue();
	BOOL initGreen();
	BOOL init2CBlue();
	BOOL init327();//2018年初 微利公司从151店开始增加了3列9行版本窄版价签
	BOOL init327b();//2018年末 微利公司更改了3列9行价签
	BOOL init327c();//2019年中旬 微利公司对第二版3列9行价签进行更改 单签高度变窄

	BOOL bcOld();
	BOOL bc324();
	BOOL bcblue();
	BOOL bcGreen();
	BOOL bc2CBlue();
	BOOL bc327();//2018年初 微利公司从151店开始增加了3列9行版本窄版价签
	BOOL bc327b();//2018年末 微利公司更改了3列9行价签
	BOOL bc327c();//2019年中旬 微利公司对第二版3列9行价签进行更改 单签高度变窄

	BOOL to324();
	BOOL toblue();
	BOOL toOld();
	BOOL toGreen();
	BOOL to2CBlue();
	BOOL to327();
	BOOL to327b();
	BOOL to327c();

	afx_msg void OnBnClickedButtonToold();
	//afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedBt2cblue();
	afx_msg void OnBnClickedBtgreenmb();
	afx_msg void OnBnClickedBt324();
	afx_msg void OnBnClickedBtForceinit();
	afx_msg void OnBnClickedButton327();
	afx_msg void OnBnClickedButton3271905();
	afx_msg void OnBnClickedButton327b();
	afx_msg void OnBnClickedBtWhite321();
};

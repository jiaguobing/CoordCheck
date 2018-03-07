
// CoordCheckDlg.h : 头文件
//

#pragma once


// CCoordCheckDlg 对话框
class CCoordCheckDlg : public CDialogEx
{
// 构造
public:
	CCoordCheckDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COORDCHECK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CEdit m_Lon;
	CEdit m_Lat;
	CEdit m_X;
	CEdit m_Y;
	CEdit m_CenterLon;
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	void WGS84ToBJ54(double lon, double lat, double &X, double &Y, int E0);
	void BJ54ToWGS84(double E0, double X, double Y, double &lon, double &lat);
};

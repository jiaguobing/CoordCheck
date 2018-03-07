
// CoordCheckDlg.h : ͷ�ļ�
//

#pragma once


// CCoordCheckDlg �Ի���
class CCoordCheckDlg : public CDialogEx
{
// ����
public:
	CCoordCheckDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COORDCHECK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CEdit m_Lon;
	CEdit m_Lat;
	CEdit m_X;
	CEdit m_Y;
	CEdit m_CenterLon;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

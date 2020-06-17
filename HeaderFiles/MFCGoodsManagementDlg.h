
// MFCGoodsManagementDlg.h : header file
//

#pragma once


// CMFCGoodsManagementDlg dialog
class CMFCGoodsManagementDlg : public CDialogEx
{
// Construction
public:
	CMFCGoodsManagementDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCGOODSMANAGEMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CEdit edit_admin;
	CEdit edit_pass;
public:
	afx_msg void OnBnClickedBtnLogin();
};

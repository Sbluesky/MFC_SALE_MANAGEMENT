#pragma once


// ORDERMANAGERMENT dialog

class ORDERMANAGERMENT : public CDialogEx
{
	DECLARE_DYNAMIC(ORDERMANAGERMENT)

public:
	ORDERMANAGERMENT(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ORDERMANAGERMENT();
	BOOL OnInitDialog();



// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORDERMANAGERMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CListCtrl ctrllistorder;
private:
	void addDatainListControl(CString str_id);
	int Number_Order = 0;
	void Updatedailog();
public:
	afx_msg void OnBnClickedBtnAddorder();
	afx_msg void OnBnClickedBtnCheckorder2();
};

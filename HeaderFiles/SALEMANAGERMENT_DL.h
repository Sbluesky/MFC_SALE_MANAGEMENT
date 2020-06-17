#pragma once


// SALEMANAGERMENT_DL dialog

class SALEMANAGERMENT_DL : public CDialogEx
{
	DECLARE_DYNAMIC(SALEMANAGERMENT_DL)

public:
	SALEMANAGERMENT_DL(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SALEMANAGERMENT_DL();
	BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SALEMANAGERMENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CDateTimeCtrl ctrl_DateTime;
	CEdit edit_dayprofit;
	CListCtrl listcontrol_Input;
	CListCtrl listcontrol_Output;
	CButton radio_input;
	CButton radio_output;

private:
	int Number_Order_Input = 0;
	int Number_Order_Output = 0;
	void addData(CString query, int iquery);
	void addDatainListControl(CString str_name, CString str_cost, CString str_amount, CString str_totalcost, int temp);
	void UpdateDataFromUpdateBotton(CListCtrl &controllist, int iquery);

public:

protected:
	CEdit edit_Gname;
	CEdit edit_Gcost;
	CEdit adit_GAmount;
public:
	afx_msg void OnDtnDatetimechangeDatetime(NMHDR *pNMHDR, LRESULT *pResult);
	void selectData();
	
	afx_msg void OnBnClickedBtnInput();
	afx_msg void OnBnClickedBtnOutput();
	afx_msg void OnLvnItemchangedListInput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListOutput(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnDelete();
};

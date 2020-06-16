// DL_CHECKORDERS.cpp : implementation file
//

#include "pch.h"
#include "MFCGoodsManagement.h"
#include "DL_CHECKORDERS.h"
#include "afxdialogex.h"
#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

#import "C:\\Program files\\Common Files\\System\\Ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;


// DL_CHECKORDERS dialog

IMPLEMENT_DYNAMIC(DL_CHECKORDERS, CDialogEx)

DL_CHECKORDERS::DL_CHECKORDERS(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHECKORDERS, pParent)
{

}

DL_CHECKORDERS::~DL_CHECKORDERS()
{
}

void DL_CHECKORDERS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTORDERS, edltlistctrl_checkorders);
	DDX_Control(pDX, IDC_EDT_CUSTOMERID, edit_cid);
	DDX_Control(pDX, IDC_EDT_TIME, edit_time);
	DDX_Control(pDX, IDC_EDT_IDBILL, edit_billid);
	DDX_Control(pDX, IDC_EDT_COST, edit_cost);
}


BEGIN_MESSAGE_MAP(DL_CHECKORDERS, CDialogEx)
END_MESSAGE_MAP()


BOOL DL_CHECKORDERS::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_checkid = 0;
	edltlistctrl_checkorders.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	edltlistctrl_checkorders.InsertColumn(0, _T("Goods Name"), LVCFMT_LEFT, 150);
	edltlistctrl_checkorders.InsertColumn(1, _T("Amount"), LVCFMT_LEFT, 50);
	edltlistctrl_checkorders.InsertColumn(2, _T("Cost"), LVCFMT_LEFT, 50);
	edltlistctrl_checkorders.InsertColumn(3, _T("Total Cost"), LVCFMT_LEFT, 80);

	_RecordsetPtr pRstEmployee = NULL;
	HRESULT hr1 = pRstEmployee.CreateInstance(__uuidof(Recordset));
	_bstr_t strCon("testDNS");
	if (FAILED(hr1))
	{
		MessageBox(_T("Failed creating record set instancen"));

	}

	pRstEmployee->Open("use GoodsManager; SELECT * FROM G_Bill", strCon, adOpenForwardOnly, adLockReadOnly, adCmdText);
	int val_check;
	int Sum = 0, i = 0;
	pRstEmployee->MoveFirst();
	//Loop through the Record set
	if (!pRstEmployee->EndOfFile)
	{
	
		while (!pRstEmployee->EndOfFile)
		{
			val_check = pRstEmployee->Fields->GetItem("GB_Check")->Value.intVal;
			if (val_check == 1)
			{
				int val_cid = pRstEmployee->Fields->GetItem("GB_IdCustomer")->Value.intVal;
				int val_billid = pRstEmployee->Fields->GetItem("GB_IdBill")->Value.intVal;
				_bstr_t val_time = pRstEmployee->Fields->GetItem("GB_Time")->Value;
				_bstr_t val_name = pRstEmployee->Fields->GetItem("GB_Name")->Value;
				int val_amount = pRstEmployee->Fields->GetItem("GB_Amount")->Value.intVal;
				int val_cost = pRstEmployee->Fields->GetItem("GB_Cost")->Value.intVal;
				int val_totalcost = pRstEmployee->Fields->GetItem("GB_TotalCost")->Value.intVal;
				Sum += val_totalcost;
				CString str_cid, str_billid, str_time, str_name, str_amount, str_cost, str_totalcost;
				
				str_cid.Format(_T("%d"), val_cid);
				str_billid.Format(_T("%d"), val_billid);
				str_amount.Format(_T("%d"), val_amount);
				str_cost.Format(_T("%d"), val_cost);
				str_totalcost.Format(_T("%d"), val_totalcost);
				str_time = (LPCTSTR)val_time;
				str_name = (LPCTSTR)val_name;

				edit_cid.SetWindowTextW(str_cid);
				edit_billid.SetWindowTextW(str_billid);
				edit_time.SetWindowTextW(str_time);
				edltlistctrl_checkorders.InsertItem(i, str_name);
				edltlistctrl_checkorders.SetItemText(i, 1, str_amount);
				edltlistctrl_checkorders.SetItemText(i, 2, str_cost);
				edltlistctrl_checkorders.SetItemText(i, 3, str_totalcost);

				i++;
			}

			pRstEmployee->MoveNext();
		}
		CString str_sum;
		str_sum.Format(_T("%d"), Sum);

		edit_cost.SetWindowTextW(str_sum);

	}

	//Close the database
	pRstEmployee->Close();
	UpdateData(TRUE);

	//gan bien check tro lai 0;
	_ConnectionPtr pConn = NULL;
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	hr = pConn.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
	{
		MessageBox(_T("Error instantiating Connection objectn"));
	}
	
	//open the sql server connection
	hr = pConn->Open(strCon, "", "", 0);
	if (FAILED(hr))
	{
		MessageBox(_T("Error to open database using ADO"));

	}
	hr = Cmd1.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
	{
		MessageBox(_T("Error creating command instance"));
	}	

	CString query = _T("use GoodsManager; UPDATE G_Bill SET GB_Check = 0 WHERE GB_Check= 1;");
	_bstr_t strsql = query;
	Cmd1->ActiveConnection = pConn;
	Cmd1->CommandText = strsql;
	Cmd1->CommandType = adCmdText;

	Cmd1->Execute(NULL, NULL, adCmdText);
	pConn->Close();

	return TRUE;
}
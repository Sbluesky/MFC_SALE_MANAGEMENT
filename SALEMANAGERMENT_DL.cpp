// SALEMANAGERMENT_DL.cpp : implementation file
//

#include "pch.h"
#include "MFCGoodsManagement.h"
#include "SALEMANAGERMENT_DL.h"
#include "afxdialogex.h"
#import "C:\\Program Files (x86)\\Common Files\\System\\ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

#import "C:\\Program files\\Common Files\\System\\Ado\\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile") 
using namespace ADOCG;

// SALEMANAGERMENT_DL dialog

IMPLEMENT_DYNAMIC(SALEMANAGERMENT_DL, CDialogEx)

SALEMANAGERMENT_DL::SALEMANAGERMENT_DL(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SALEMANAGERMENT_DIALOG, pParent)
{

}

SALEMANAGERMENT_DL::~SALEMANAGERMENT_DL()
{
}

void SALEMANAGERMENT_DL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIME, ctrl_DateTime);
	DDX_Control(pDX, IDC_EDT_DAYPROFIT, edit_dayprofit);
	DDX_Control(pDX, IDC_LIST_INPUT, listcontrol_Input);
	DDX_Control(pDX, IDC_LIST_OUTPUT, listcontrol_Output);
	DDX_Control(pDX, IDC_RADIO_INPUT, radio_input);
	DDX_Control(pDX, IDC_RADIO_OUTPUT, radio_output);
	DDX_Control(pDX, IDC_EDT_GOODSNAME, edit_Gname);
	DDX_Control(pDX, IDC_EDT_GOODSCOST, edit_Gcost);
	DDX_Control(pDX, IDC_EDT_GOODAMOUNT, adit_GAmount);
}


BEGIN_MESSAGE_MAP(SALEMANAGERMENT_DL, CDialogEx)

	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIME, &SALEMANAGERMENT_DL::OnDtnDatetimechangeDatetime)
	ON_BN_CLICKED(IDC_BTN_INPUT, &SALEMANAGERMENT_DL::OnBnClickedBtnInput)
	ON_BN_CLICKED(IDC_BTN_OUTPUT, &SALEMANAGERMENT_DL::OnBnClickedBtnOutput)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_INPUT, &SALEMANAGERMENT_DL::OnLvnItemchangedListInput)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_OUTPUT, &SALEMANAGERMENT_DL::OnLvnItemchangedListOutput)
	ON_BN_CLICKED(IDC_BTN_DELETE, &SALEMANAGERMENT_DL::OnBnClickedBtnDelete)
END_MESSAGE_MAP()

void ConnecttoDatabase1(_ConnectionPtr &pConn, _CommandPtr &Cmd1, HRESULT &hr)
{
	_bstr_t strCon("testDNS");
	//create the connection pointer
	hr = pConn.CreateInstance(__uuidof(Connection));
	if (FAILED(hr))
	{
		printf("Error instantiating Connection objectn");
	}
	//open the sql server connection
	hr = pConn->Open(strCon, "", "", 0);
	if (FAILED(hr))
	{
		printf("Error to open database using ADO");

	}
	hr = Cmd1.CreateInstance(__uuidof(Command));
	if (FAILED(hr))
	{
		printf("Error creating command instance");
	}
}

void SALEMANAGERMENT_DL::addDatainListControl(CString str_name, CString str_cost, CString str_amount, CString str_totalcost, int temp)
{
	
	if (temp == 1) // Import of Goods
	{
		CString str_Number_Order;
		str_Number_Order.Format(_T("%d"), Number_Order_Input);
		listcontrol_Input.InsertItem(Number_Order_Input, str_Number_Order);
		listcontrol_Input.SetItemText(Number_Order_Input, 1, str_name);
		listcontrol_Input.SetItemText(Number_Order_Input, 2, str_cost);
		listcontrol_Input.SetItemText(Number_Order_Input, 3, str_amount);
		listcontrol_Input.SetItemText(Number_Order_Input, 4, str_totalcost);
		Number_Order_Input += 1;

	}
	else if (temp == 2) //Export of goods.
	{
		CString str_Number_Order;
		str_Number_Order.Format(_T("%d"), Number_Order_Output);
		listcontrol_Output.InsertItem(Number_Order_Output, str_Number_Order);
		listcontrol_Output.SetItemText(Number_Order_Output, 1, str_name);
		listcontrol_Output.SetItemText(Number_Order_Output, 2, str_cost);
		listcontrol_Output.SetItemText(Number_Order_Output, 3, str_amount);
		listcontrol_Output.SetItemText(Number_Order_Output, 4, str_totalcost);
		Number_Order_Output += 1;
	}
	

}

BOOL SALEMANAGERMENT_DL::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//set radio_input luon chon
	radio_input.SetCheck(TRUE);

	//list control code 

	listcontrol_Input.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	listcontrol_Input.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 50);
	listcontrol_Input.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 150);
	listcontrol_Input.InsertColumn(2, _T("Cost (VND)"), LVCFMT_LEFT, 100);
	listcontrol_Input.InsertColumn(4, _T("Amount (Kg)"), LVCFMT_LEFT, 100);
	listcontrol_Input.InsertColumn(5, _T("Total Cost (VND)"), LVCFMT_LEFT, 100);

	listcontrol_Output.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	listcontrol_Output.InsertColumn(0, _T("Number"), LVCFMT_LEFT, 50);
	listcontrol_Output.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 150);
	listcontrol_Output.InsertColumn(2, _T("Cost"), LVCFMT_LEFT, 100);
	listcontrol_Output.InsertColumn(4, _T("Amount  (Kg)"), LVCFMT_LEFT, 100);
	listcontrol_Output.InsertColumn(5, _T("Total Cost (VND)"), LVCFMT_LEFT, 100);

	selectData();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// SALEMANAGERMENT_DL message handlers




void SALEMANAGERMENT_DL::OnDtnDatetimechangeDatetime(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	selectData();

	CString query, str_time;

	_bstr_t strCon("testDNS");
	CoInitialize(NULL);
	_RecordsetPtr pRstEmployee = NULL;
	HRESULT hr1 = pRstEmployee.CreateInstance(__uuidof(Recordset));

	if (FAILED(hr1))
	{
		MessageBox(_T("Failed creating record set instancen"));
	}

	CTime timeTime;
	DWORD dwResult = ctrl_DateTime.GetTime(timeTime);
	str_time = timeTime.Format(_T("20%y-%m-%d"));
	query = _T("use GoodsManager; SELECT GMI_TotalCost FROM GM_Input WHERE GMI_Time = '") + str_time + _T("';") ;
	variant_t query1 = query.AllocSysString();
	pRstEmployee->Open(query1, strCon, adOpenForwardOnly, adLockReadOnly, adCmdText);
	int val_totalcost, SumInput = 0, SumOutput = 0, Sum = 0;

	//Loop through the Record set Input
	if (!pRstEmployee->EndOfFile)
	{
		while (!pRstEmployee->EndOfFile)
		{
			val_totalcost = pRstEmployee->Fields->GetItem("GMI_TotalCost")->Value.intVal;
			SumInput = SumInput + val_totalcost;
			pRstEmployee->MoveNext();
		}
	}
	pRstEmployee->Close();
	HRESULT hr2 = pRstEmployee.CreateInstance(__uuidof(Recordset));

	//Lay TotalCost Output
	query = _T("use GoodsManager; SELECT GMO_TotalCost FROM GM_Output WHERE GMO_Time = '") + str_time + _T("';");
	query1 = query.AllocSysString();
	pRstEmployee->Open(query1, strCon, adOpenForwardOnly, adLockReadOnly, adCmdText);
	//Loop through the Record set Output
	if (!pRstEmployee->EndOfFile)
	{
		while (!pRstEmployee->EndOfFile)
		{
			val_totalcost = pRstEmployee->Fields->GetItem("GMO_TotalCost")->Value.intVal;
			SumOutput = SumOutput + val_totalcost;
			pRstEmployee->MoveNext();
		}
	}
	pRstEmployee->Close();
	Sum = SumOutput - SumInput;
	CString profit;
	profit.Format(_T("%d"), Sum);
	UpdateData();
	edit_dayprofit.SetWindowTextW(profit);
}

void SALEMANAGERMENT_DL::selectData()
{

	_bstr_t strCon("testDNS");
	CoInitialize(NULL);

	try
	{

		_RecordsetPtr pRstEmployee = NULL;
		_RecordsetPtr pRstEmployee1 = NULL;

		HRESULT hr1 = pRstEmployee.CreateInstance(__uuidof(Recordset));

		if (FAILED(hr1))
		{
			MessageBox(_T("Failed creating record set instancen"));

		}


		pRstEmployee->Open("use GoodsManager; SELECT * FROM GM_Input", strCon, adOpenForwardOnly, adLockReadOnly, adCmdText);

		_bstr_t val_name;
		_bstr_t val_time;
		int val_totalcost;
		int val_amount;
		int val_cost;

		pRstEmployee->MoveFirst();

		//Loop through the Record set
		if (!pRstEmployee->EndOfFile)
		{
			Number_Order_Input = 0;
			listcontrol_Input.DeleteAllItems();
			while (!pRstEmployee->EndOfFile)
			{
				val_name = pRstEmployee->Fields->GetItem("GMI_Name")->Value;
				val_cost = pRstEmployee->Fields->GetItem("GMI_Cost")->Value.intVal;
				val_time = pRstEmployee->Fields->GetItem("GMI_Time")->Value;
				val_amount = pRstEmployee->Fields->GetItem("GMI_Amount")->Value.intVal;
				val_totalcost = pRstEmployee->Fields->GetItem("GMI_TotalCost")->Value.intVal;


				//Add data vao list control
				CString str_name, str_cost, str_amount, str_totalcost, str_time;
				str_cost.Format(_T("%d"), val_cost);
				str_amount.Format(_T("%d"), val_amount);
				str_totalcost.Format(_T("%d"), val_totalcost);

				//check gia tri time
				CTime timeTime;
				DWORD dwResult = ctrl_DateTime.GetTime(timeTime);

				str_time = timeTime.Format(_T("20%y-%m-%d"));

				if ((LPCTSTR)val_time == str_time)
				{
					addDatainListControl((LPCTSTR)val_name, str_cost, str_amount, str_totalcost, 1);
				}

				pRstEmployee->MoveNext();
			}
		}
		pRstEmployee->Close();

		//EXPORT OF GOODS:
		HRESULT hr2 = pRstEmployee1.CreateInstance(__uuidof(Recordset));

		if (FAILED(hr2))
		{
			MessageBox(_T("Failed creating record set instancen"));

		}
		pRstEmployee1->Open("use GoodsManager; SELECT * FROM GM_Output", strCon, adOpenForwardOnly, adLockReadOnly, adCmdText);
		//Loop through the Record set
		if (!pRstEmployee1->EndOfFile)
		{
			Number_Order_Output = 0;
			listcontrol_Output.DeleteAllItems();

			while (!pRstEmployee1->EndOfFile)
			{
				val_name = pRstEmployee1->Fields->GetItem("GMO_Name")->Value;
				val_cost = pRstEmployee1->Fields->GetItem("GMO_Cost")->Value.intVal;
				val_time = pRstEmployee1->Fields->GetItem("GMO_Time")->Value;
				val_amount = pRstEmployee1->Fields->GetItem("GMO_Amount")->Value.intVal;
				val_totalcost = pRstEmployee1->Fields->GetItem("GMO_TotalCost")->Value.intVal;


				//Add data vao list control
				CString str_cost, str_amount, str_totalcost;
				str_cost.Format(_T("%d"), val_cost);
				str_amount.Format(_T("%d"), val_amount);
				str_totalcost.Format(_T("%d"), val_totalcost);

				//check gia tri time
				CTime timeTime;
				DWORD dwResult = ctrl_DateTime.GetTime(timeTime);

				CString str_time;
				str_time = timeTime.Format(_T("20%y-%m-%d"));

				if ((LPCTSTR)val_time == str_time)
				{
					addDatainListControl((LPCTSTR)val_name, str_cost, str_amount, str_totalcost, 2);

				}

				pRstEmployee1->MoveNext();
			}
		}

		//Close the database
		pRstEmployee1->Close();
		UpdateData(TRUE);



	}
	catch (_com_error &ce)
	{
		MessageBox(_T("You failed, haha. Don't let any fields empty"));

	}
}



void SALEMANAGERMENT_DL::OnBnClickedBtnInput()
{
	int i = 1;
	if (radio_input.GetCheck())
	{
		CString query = _T("use GoodsManager; Insert into GM_Input Values ('");
		addData(query, i);
	}
	else if (radio_output.GetCheck())
	{
		i = 2;
		CString query = _T("use GoodsManager; Insert into GM_Output Values ('");
		addData(query, i);
	}

}

void SALEMANAGERMENT_DL::addData(CString query, int iquery) //iupdateofadd == 1 == add else == 2 == update
{
	_bstr_t strName;
	_ConnectionPtr pConn = NULL;
	_bstr_t strCon("testDNS");
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	ConnecttoDatabase1(pConn, Cmd1, hr);

	try
	{

		//create the connection pointer

		UpdateData();
		CString str_cost, str_amount, str_name, str_time, str_totalcost;
		edit_Gcost.GetWindowText(str_cost);
		edit_Gname.GetWindowText(str_name);
		adit_GAmount.GetWindowText(str_amount);
		int totalcost = _ttoi(str_cost) * _ttoi(str_amount);
		str_totalcost.Format(_T("%d"), totalcost);
		CTime timeTime;
		DWORD dwResult = ctrl_DateTime.GetTime(timeTime);
		str_time = timeTime.Format(_T("20%y-%m-%d"));



		if (!str_cost.IsEmpty() || !str_name.IsEmpty() || !str_amount.IsEmpty())
		{
			query = query + str_time + _T("','") + str_name + _T("',") + str_amount + _T(",") + str_cost + _T(",") + str_totalcost + _T(");");

			_bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);
			MessageBox(_T("Data added successfully"));

			//update data vao list control
			addDatainListControl(str_name, str_cost, str_amount, str_totalcost, iquery);


		}
		//Close the database
		pConn->Close();
		UpdateData(TRUE);

	}
	catch (_com_error &ce)
	{
		MessageBox(_T("You failed, haha. Don't let any fields empty"));

	}
}


void SALEMANAGERMENT_DL::OnBnClickedBtnOutput()
{
	if (radio_input.GetCheck())
	{
		UpdateDataFromUpdateBotton(listcontrol_Input, 1); //iquery == 1 Input
	}
	else if (radio_output.GetCheck())
	{
		UpdateDataFromUpdateBotton(listcontrol_Output, 2);  //iquery == 2 Output
	}
}

void SALEMANAGERMENT_DL::UpdateDataFromUpdateBotton(CListCtrl &controllist, int iquery)
{
	CString str_cost, str_amount, str_name, str_totalcost, str_time;

	_ConnectionPtr pConn = NULL;
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	ConnecttoDatabase1(pConn, Cmd1, hr);

	for (int i = 0; i < controllist.GetItemCount(); i++)
	{
		BOOL bCheck = controllist.GetCheck(i);
		if (bCheck)
		{

			//Set edit control thanh cac item da chon
			UpdateData();
			edit_Gname.GetWindowText(str_name);
			edit_Gcost.GetWindowText(str_cost);
			adit_GAmount.GetWindowText(str_amount);
			int totalcost = _ttoi(str_cost) * _ttoi(str_amount);
			str_totalcost.Format(_T("%d"), totalcost);
			CTime timeTime;
			DWORD dwResult = ctrl_DateTime.GetTime(timeTime);
			str_time = timeTime.Format(_T("20%y-%m-%d"));
			CString get_val_update = controllist.GetItemText(i, 1);
			CString query;
			if (iquery == 1)
				query = _T("use GoodsManager; UPDATE GM_Input SET GMI_Name = '") + str_name + _T("', GMI_Cost = '") + str_cost + _T("', GMI_Amount = '") + str_amount + _T("' , GMI_TotalCost = '") + str_totalcost  + _T("' WHERE GMI_Name='") + get_val_update + _T("' AND GMI_Time = '") + str_time + _T("';");
			else if (iquery == 2)
				query = _T("use GoodsManager; UPDATE GM_Output SET GMO_Name = '") + str_name + _T("', GMO_Cost = '") + str_cost + _T("', GMO_Amount = '") + str_amount + +_T("' , GMO_TotalCost = '") + str_totalcost + _T("' WHERE GMO_Name='") + get_val_update + _T("' AND GMO_Time = '") + str_time + _T("';");
			_bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);
			MessageBox(_T("Update Data Successfully!"));
			controllist.SetItemText(i, 1, str_name);
			controllist.SetItemText(i, 2, str_cost);
			controllist.SetItemText(i, 3, str_amount);
			controllist.SetItemText(i, 4, str_totalcost);

			break;
		}
	}
	edit_Gname.SetWindowTextW(_T(""));
	edit_Gcost.SetWindowTextW(_T(""));
	adit_GAmount.SetWindowTextW(_T(""));
	pConn->Close();
}


void SALEMANAGERMENT_DL::OnLvnItemchangedListInput(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	for (int i = 0; i < listcontrol_Input.GetItemCount(); i++)
	{
		BOOL bCheck = listcontrol_Input.GetCheck(i);
		if (bCheck)
		{
			//Lay data tu cac item da chon sang cho cac edit control
			UpdateData();
			CString get_valname = listcontrol_Input.GetItemText(i, 1);
			CString get_valcost = listcontrol_Input.GetItemText(i, 2);
			CString get_valamount = listcontrol_Input.GetItemText(i, 3);

			edit_Gname.SetWindowTextW(get_valname);
			edit_Gcost.SetWindowTextW(get_valcost);
			adit_GAmount.SetWindowTextW(get_valamount);
			break;
		}
	}
	
	*pResult = 0;
}


void SALEMANAGERMENT_DL::OnLvnItemchangedListOutput(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	for (int i = 0; i < listcontrol_Output.GetItemCount(); i++)
	{
		BOOL bCheck = listcontrol_Output.GetCheck(i);
		if (bCheck)
		{
			//Lay data tu cac item da chon sang cho cac edit control 
			UpdateData();
			CString get_valname = listcontrol_Output.GetItemText(i, 1);
			CString get_valcost = listcontrol_Output.GetItemText(i, 2);
			CString get_valamount = listcontrol_Output.GetItemText(i, 3);

			edit_Gname.SetWindowTextW(get_valname);
			edit_Gcost.SetWindowTextW(get_valcost);
			adit_GAmount.SetWindowTextW(get_valamount);
			break;
		}
	}
	*pResult = 0;
}


void SALEMANAGERMENT_DL::OnBnClickedBtnDelete()
{
	//delete item in database
	_ConnectionPtr pConn = NULL;
	_CommandPtr Cmd1;
	HRESULT hr = S_OK;
	CoInitialize(NULL);
	ConnecttoDatabase1(pConn, Cmd1, hr);
	CString get_valname_delete, query, str_time;

	CTime timeTime;
	DWORD dwResult = ctrl_DateTime.GetTime(timeTime);
	str_time = timeTime.Format(_T("20%y-%m-%d"));

	for (int i = 0; i < listcontrol_Input.GetItemCount(); i++)
	{
		BOOL bCheck = listcontrol_Input.GetCheck(i);
		if (bCheck)
		{

			 get_valname_delete = listcontrol_Input.GetItemText(i, 1);
			 query = _T("use GoodsManager; DELETE FROM GM_Input WHERE GMI_Name='") + get_valname_delete + _T("' AND GMI_Time = '") + str_time + _T("';");
			_bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);

			// item is checked
			listcontrol_Input.DeleteItem(i);
		}
	}

	for (int i = 0; i < listcontrol_Output.GetItemCount(); i++)
	{
		BOOL bCheck = listcontrol_Output.GetCheck(i);
		if (bCheck)
		{

			 get_valname_delete = listcontrol_Output.GetItemText(i, 1);
			 query = _T("use GoodsManager; DELETE FROM GM_Output WHERE GMO_Name='") + get_valname_delete + _T("' AND GMO_Time = '") + str_time + _T("';");
			 _bstr_t strsql = query;
			Cmd1->ActiveConnection = pConn;
			Cmd1->CommandText = strsql;
			Cmd1->CommandType = adCmdText;

			Cmd1->Execute(NULL, NULL, adCmdText);

			// item is checked
			listcontrol_Output.DeleteItem(i);
		}
	}
	pConn->Close();
}

// maindialog.cpp : implementation file
//

#include "pch.h"
#include "MFCGoodsManagement.h"
#include"SALEMANAGERMENT_DL.h"
#include "maindialog.h"
#include "afxdialogex.h"
#include "GLdialog.h"
#include "ORDERMANAGERMENT.h"


// maindialog dialog

IMPLEMENT_DYNAMIC(maindialog, CDialogEx)

maindialog::maindialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINDIALOG, pParent)
{

}

maindialog::~maindialog()
{
}

void maindialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_GL, btn_gl);
}


BEGIN_MESSAGE_MAP(maindialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_GL, &maindialog::OnBnClickedBtnGl)
	ON_BN_CLICKED(IDC_BTN_GM, &maindialog::OnBnClickedBtnGm)
	ON_BN_CLICKED(IDC_BTN_GB, &maindialog::OnBnClickedBtnGb)
END_MESSAGE_MAP()


// maindialog message handlers


void maindialog::OnBnClickedBtnGl()
{
	GLdialog GL_dialog;
	GL_dialog.DoModal();
}


void maindialog::OnBnClickedBtnGm()
{
	// TODO: Add your control notification handler code here
	SALEMANAGERMENT_DL saleM;
	saleM.DoModal();

}


void maindialog::OnBnClickedBtnGb()
{
	ORDERMANAGERMENT orderDL;
	orderDL.DoModal();
}


// ImageSettingDlg.cpp : implementation file
//

#include "pch.h"
#include "OPENCV_GUI.h"
#include "ImageSettingDlg.h"
#include "afxdialogex.h"


// ImageSettingDlg dialog

IMPLEMENT_DYNAMIC(ImageSettingDlg, CDialogEx)

ImageSettingDlg::ImageSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_SETTING, pParent)
{
	lighting_adjust_ = 0.0;
}

ImageSettingDlg::~ImageSettingDlg()
{
}

void ImageSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_DCR, btn_decre_);
	DDX_Control(pDX, IDC_EDIT1, edt_adjust_light);
	DDX_Control(pDX, IDC_BUTTON_ICR, btn_incre_);
}


BEGIN_MESSAGE_MAP(ImageSettingDlg, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_DCR, &ImageSettingDlg::OnBnClickedButtonDcr)
	ON_BN_CLICKED(IDC_BUTTON_ICR, &ImageSettingDlg::OnBnClickedButtonIcr)
END_MESSAGE_MAP()


// ImageSettingDlg message handlers

//lab7

//tự động gọi khi dialog được show 
	//nên không cần khai báo ánh xạ thông điệp
BOOL ImageSettingDlg::OnInitDialog()
{
	BOOL ret = CDialogEx::OnInitDialog();

	edt_adjust_light.SetWindowText(_T("0.0"));
	UpdateData(FALSE);
	//thiết lập giá trị ban đầu cho edit box là 0.0 

	return ret;
}

float ImageSettingDlg::GetAdjustLight()
{
	return lighting_adjust_;
}


void ImageSettingDlg::OnBnClickedButtonDcr()
{
	CString currentVal;
	edt_adjust_light.GetWindowText(currentVal);
	lighting_adjust_ = _tstof(currentVal);
	lighting_adjust_ -= 10.0;

	CString strVal;
	strVal.Format(_T("%f"), lighting_adjust_);
	edt_adjust_light.SetWindowText(strVal);

	UpdateData(FALSE);
}


void ImageSettingDlg::OnBnClickedButtonIcr()
{
	CString currentVal;
	edt_adjust_light.GetWindowText(currentVal);
	lighting_adjust_ = _tstof(currentVal);
	lighting_adjust_ += 10.0;

	CString strVal;
	strVal.Format(_T("%f"), lighting_adjust_);
	edt_adjust_light.SetWindowText(strVal);

	UpdateData(FALSE);
}

//endlap7
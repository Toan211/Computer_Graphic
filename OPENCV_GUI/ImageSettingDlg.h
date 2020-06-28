#pragma once


// ImageSettingDlg dialog

class ImageSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ImageSettingDlg)

public:
	ImageSettingDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ImageSettingDlg();

	//lab7

	BOOL OnInitDialog();
	float GetAdjustLight();

	float lighting_adjust_;

	//endlab7
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	CButton btn_decre_;
	CEdit edt_adjust_light;
	CButton btn_incre_;

	//lab7
	

	
public:
	afx_msg void OnBnClickedButtonDcr();
	afx_msg void OnBnClickedButtonIcr();
	
	//endlab7
};

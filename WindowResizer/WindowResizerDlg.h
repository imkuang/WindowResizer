
// WindowResizerDlg.h: 头文件
//

#pragma once


// CWindowResizerDlg 对话框
class CWindowResizerDlg : public CDialogEx
{
// 构造
public:
	CWindowResizerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOWRESIZER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// 界面中所有的编辑框控件变量
	CEdit m_editShowHandle;
	CEdit m_editShowTitle;
	CEdit m_editShowCurWidth;
	CEdit m_editShowCurHeight;
	CEdit m_editSetWidth;
	CEdit m_editSetHeight;
	CEdit m_editSetPercentage;

	// 从指定窗口获取到的一些原始数据，不会被修改
	HWND m_hWindowHandle;       //查找到的窗口的句柄
	CString m_szWindowTitle;    //查找到的窗口的标题
	CWnd* m_pWnd{ nullptr };	//查找到的窗口的指针
	CSize m_sizeOriginalWindow; //查找到的窗口的原始大小

	int m_nScalePercentage{ 100 };          //窗口要缩放的百分比
	bool m_bScaleIsCustomized{ false };     //按比例缩放处是否选择了自定义
	bool m_bClickedSetPercentage{ false };  //最后一次设置大小是否为百分比缩放
	int m_nTempOriginalWidth;               //按比例缩放时需要临时记录当前窗口的大小作为缩放基准
	int m_nTempOriginalHeight;
	int m_nRadioSelect;                     //按比例缩放处控制选取哪一个复选框

	bool m_bIsSetMaxSize{ false };          //是否设置过最大化

	void UpdateSizeShow(int width,int height); //更新对话框上宽度和高度的显示
	bool IsWindowValid();                      //判断已选中的窗口是否有效
	void SetPercentageEditEnable();	           //设置按比例缩放处的编辑框是否可用
	void IsEnableAllControls(bool bIsEnable);  //设置除“开始查找窗口”按钮之外的所有控件的可用性
	void SetMaxSizeButtonEnable();             //设置最大化按钮是否可用
public:
	afx_msg void OnBnClickedButtonFindWindow();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonSetSize();
	afx_msg void OnBnClickedRadio50();
	afx_msg void OnBnClickedRadio100();
	afx_msg void OnBnClickedRadio125();
	afx_msg void OnBnClickedRadio150();
	afx_msg void OnBnClickedRadio200();
	afx_msg void OnBnClickedRadioCustom();
	afx_msg void OnBnClickedButtonSetPercentage();
	afx_msg void OnBnClickedButtonMaxSize();
	afx_msg void OnBnClickedButtonRestore();
	afx_msg void OnBnClickedButtonAbout();
};

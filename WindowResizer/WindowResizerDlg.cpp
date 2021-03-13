
// WindowResizerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "WindowResizer.h"
#include "WindowResizerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickSyslinkCheckUpdate(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_CHECK_UPDATE, &CAboutDlg::OnNMClickSyslinkCheckUpdate)
END_MESSAGE_MAP()


// CWindowResizerDlg 对话框



CWindowResizerDlg::CWindowResizerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDOWRESIZER_DIALOG, pParent)
	, m_nRadioSelect(1)      //启动时按比例缩放处默认选取100%
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWindowResizerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_HANDLE, m_editShowHandle);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editShowTitle);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_editShowCurWidth);
	DDX_Control(pDX, IDC_EDIT_HEIGHT, m_editShowCurHeight);
	DDX_Control(pDX, IDC_EDIT_SET_WIDTH, m_editSetWidth);
	DDX_Control(pDX, IDC_EDIT_SET_HEIGHT, m_editSetHeight);
	DDX_Control(pDX, IDC_EDIT_PERCENTAGE_CUSTOM, m_editSetPercentage);
	DDX_Radio(pDX, IDC_RADIO_50, m_nRadioSelect);
}

BEGIN_MESSAGE_MAP(CWindowResizerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIND_WINDOW, &CWindowResizerDlg::OnBnClickedButtonFindWindow)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SET_SIZE, &CWindowResizerDlg::OnBnClickedButtonSetSize)
	ON_BN_CLICKED(IDC_RADIO_50, &CWindowResizerDlg::OnBnClickedRadio50)
	ON_BN_CLICKED(IDC_RADIO_100, &CWindowResizerDlg::OnBnClickedRadio100)
	ON_BN_CLICKED(IDC_RADIO_125, &CWindowResizerDlg::OnBnClickedRadio125)
	ON_BN_CLICKED(IDC_RADIO_150, &CWindowResizerDlg::OnBnClickedRadio150)
	ON_BN_CLICKED(IDC_RADIO_200, &CWindowResizerDlg::OnBnClickedRadio200)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, &CWindowResizerDlg::OnBnClickedRadioCustom)
	ON_BN_CLICKED(IDC_BUTTON_SET_PERCENTAGE, &CWindowResizerDlg::OnBnClickedButtonSetPercentage)
	ON_BN_CLICKED(IDC_BUTTON_MAX_SIZE, &CWindowResizerDlg::OnBnClickedButtonMaxSize)
	ON_BN_CLICKED(IDC_BUTTON_RESTORE, &CWindowResizerDlg::OnBnClickedButtonRestore)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CWindowResizerDlg::OnBnClickedButtonAbout)
END_MESSAGE_MAP()


// CWindowResizerDlg 消息处理程序

BOOL CWindowResizerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	IsEnableAllControls(false);   //初始状态未选中窗口所有控件都不可用

	// 已弃用，现在通过修改int型变量m_nRadioSelect的值（已默认设为1）来修改Radio Button选中状态
	//((CButton*)GetDlgItem(IDC_RADIO_100))->SetCheck(TRUE); //比例缩放默认选中100%

	SetTimer(2, 1000, NULL);     //设置定时器，每隔一秒检查一次窗口的有效性

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWindowResizerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWindowResizerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWindowResizerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWindowResizerDlg::UpdateSizeShow(int width,int height)
{
	CString szWidth,szHeight;
	szWidth.Format(_T("%d"), width);
	szHeight.Format(_T("%d"), height);
	m_editShowCurWidth.SetWindowTextW(szWidth);
	m_editShowCurHeight.SetWindowTextW(szHeight);
}


void CWindowResizerDlg::OnBnClickedButtonFindWindow()
{
	SetTimer(1, 1000, NULL);
}




void CWindowResizerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		CWnd* pWnd = GetForegroundWindow();
		m_hWindowHandle = pWnd->GetSafeHwnd();
		if (m_hWindowHandle != NULL && m_hWindowHandle != m_hWnd)//只有处于前台的窗口不是程序本身的窗口，才说明找到了
		{
			m_pWnd = pWnd;
			CString szHandle;
			szHandle.Format(_T("%.8x"), m_hWindowHandle);
			szHandle.MakeUpper();
			m_editShowHandle.SetWindowTextW(szHandle);

			pWnd->GetWindowTextW(m_szWindowTitle);
			m_editShowTitle.SetWindowTextW(m_szWindowTitle);

			//获取窗口的大小
			CRect rect;
			::GetWindowRect(m_hWindowHandle, rect);
			m_sizeOriginalWindow = rect.Size();
			UpdateSizeShow(m_sizeOriginalWindow.cx, m_sizeOriginalWindow.cy);

			IsEnableAllControls(IsWindowValid());
			
			KillTimer(1);       //找到窗口之后停掉定时器
		}
		// 不管窗口是否有效，每次点击“查找窗口”按钮之后这些值都需要重新初始化
		m_bClickedSetPercentage = false;
		m_bIsSetMaxSize = false;
	}
	else if (nIDEvent == 2)
	{
		//每隔1秒钟检查一次要操作的窗口是否有效，并调用控件的启用或禁用状态
		IsEnableAllControls(IsWindowValid());
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CWindowResizerDlg::OnBnClickedButtonSetSize()
{
	if (IsWindowValid())
	{
		int nWidth, nHeight;
		CString szWidth, szHeight;
		m_editSetWidth.GetWindowTextW(szWidth);
		m_editSetHeight.GetWindowTextW(szHeight);
		nWidth = _ttoi(szWidth);
		nHeight = _ttoi(szHeight);
		if (nWidth == 0 || nHeight == 0)
			return;

		::SetWindowPos(m_hWindowHandle, NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER | SWP_NOMOVE);

		UpdateSizeShow(nWidth, nHeight);
		m_bClickedSetPercentage = false;
	}

}


void CWindowResizerDlg::OnBnClickedRadio50()
{
	m_nScalePercentage = 50;
	m_bScaleIsCustomized = false;
	SetPercentageEditEnable();
}


void CWindowResizerDlg::OnBnClickedRadio100()
{
	m_nScalePercentage = 100;
	m_bScaleIsCustomized = false;
	SetPercentageEditEnable();
}


void CWindowResizerDlg::OnBnClickedRadio125()
{
	m_nScalePercentage = 125;
	m_bScaleIsCustomized = false;
	SetPercentageEditEnable();
}


void CWindowResizerDlg::OnBnClickedRadio150()
{
	m_nScalePercentage = 150;
	m_bScaleIsCustomized = false;
	SetPercentageEditEnable();
}


void CWindowResizerDlg::OnBnClickedRadio200()
{
	m_nScalePercentage = 200;
	m_bScaleIsCustomized = false;
	SetPercentageEditEnable();
}


void CWindowResizerDlg::OnBnClickedRadioCustom()
{
	m_bScaleIsCustomized = true;
	SetPercentageEditEnable();
}


void CWindowResizerDlg::OnBnClickedButtonSetPercentage()
{
	if (!IsWindowValid())
		return;
	if (!m_bClickedSetPercentage)       //如果最后一次改变窗口大小不是按比例缩放的则记录当前窗口大小作为后续按比例缩放的基准
	{
		CRect rect;
		::GetWindowRect(m_hWindowHandle, rect);
		m_nTempOriginalWidth = rect.Size().cx;
		m_nTempOriginalHeight = rect.Size().cy;
	}
	if (m_bScaleIsCustomized)           //如果选中了自定义，则比例调整为自定义的值
	{
		CString szPercentage;
		m_editSetPercentage.GetWindowText(szPercentage);
		m_nScalePercentage = _ttoi(szPercentage);
		if (m_nScalePercentage <= 0)
			return;
	}
	int nWidth;
	int nHeight;
	nWidth = m_nTempOriginalWidth * m_nScalePercentage / 100;
	nHeight = m_nTempOriginalHeight * m_nScalePercentage / 100;
	::SetWindowPos(m_hWindowHandle, NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER | SWP_NOMOVE);

	UpdateSizeShow(nWidth, nHeight);
	m_bClickedSetPercentage = true;
}


void CWindowResizerDlg::OnBnClickedButtonMaxSize()
{
	if (!IsWindowValid())
		return;
	if (m_pWnd->IsZoomed())  //只有窗口本身不是最大化的才有效
		return;
	m_pWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_bIsSetMaxSize = true;

	//重新获取窗口的大小
	CRect rect;
	::GetWindowRect(m_hWindowHandle, rect);
	UpdateSizeShow(rect.Size().cx, rect.Size().cy);
	m_bClickedSetPercentage = false;
}


void CWindowResizerDlg::OnBnClickedButtonRestore()
{
	if (!IsWindowValid())
		return;
	if(m_bIsSetMaxSize)
		m_pWnd->ShowWindow(SW_RESTORE);      //取消最大化

	// 还原初始大小
	::SetWindowPos(m_hWindowHandle, NULL, 0, 0, m_sizeOriginalWindow.cx, m_sizeOriginalWindow.cy, SWP_NOZORDER | SWP_NOMOVE);

	// 按比例缩放处恢复到选中100%
	m_nRadioSelect = 1;
	UpdateData(FALSE);
	OnBnClickedRadio100();

	// 重新获取窗口大小并显示出来
	CRect rect;
	::GetWindowRect(m_hWindowHandle, rect);
	UpdateSizeShow(rect.Size().cx, rect.Size().cy);
	m_bClickedSetPercentage = false;
}


void CWindowResizerDlg::OnBnClickedButtonAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

// 判断已选中的窗口是否可用
bool CWindowResizerDlg::IsWindowValid()
{
	if (m_pWnd == nullptr)                 //还未选中窗口
		return false;
	HWND handle = m_pWnd->GetSafeHwnd();   //获取所选中窗口的句柄
	if (handle == NULL)
		return false;
	if (!IsWindow(handle))
		return false;
	return true;
}

// 按比例缩放处的编辑框只有在选中自定义时才可以使用
void CWindowResizerDlg::SetPercentageEditEnable()
{
	if (IsWindowValid())
		m_editSetPercentage.EnableWindow(m_bScaleIsCustomized);
	else
		m_editSetPercentage.EnableWindow(false);
}


// 只有窗口本身不是最大化才能够使用最大化按钮
void CWindowResizerDlg::SetMaxSizeButtonEnable()
{
	if (IsWindowValid())
		GetDlgItem(IDC_BUTTON_MAX_SIZE)->EnableWindow(!m_pWnd->IsZoomed());
	else
		GetDlgItem(IDC_BUTTON_MAX_SIZE)->EnableWindow(false);
}


void CWindowResizerDlg::IsEnableAllControls(bool bIsEnable)
{
	GetDlgItem(IDC_EDIT_HANDLE)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_EDIT_TITLE)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_EDIT_WIDTH)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_EDIT_HEIGHT)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_EDIT_SET_WIDTH)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_EDIT_SET_HEIGHT)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_BUTTON_SET_SIZE)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_RADIO_50)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_RADIO_100)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_RADIO_125)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_RADIO_150)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_RADIO_200)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_RADIO_CUSTOM)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_BUTTON_SET_PERCENTAGE)->EnableWindow(bIsEnable);
	GetDlgItem(IDC_BUTTON_RESTORE)->EnableWindow(bIsEnable);
	SetMaxSizeButtonEnable();
	SetPercentageEditEnable();
}



void CAboutDlg::OnNMClickSyslinkCheckUpdate(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(NULL, _T("open"), _T("https://github.com/inkuang/WindowResizer/releases"), NULL, NULL, SW_SHOW);
	*pResult = 0;
}


// MrChen.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MrChen.h"
#include "MainFrm.h"

#include "MrChenDoc.h"
#include "MrChenView.h"
#include "Param.h"
#include "CWndMyStatic.h" 

#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMrChenApp

BEGIN_MESSAGE_MAP(CMrChenApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMrChenApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_NEW, &CMrChenApp::OnFileNew)
END_MESSAGE_MAP()


// CMrChenApp 构造
PPARAM CMrChenApp::m_param = new PARAM;
CString CMrChenApp::m_strAppPath = _T("");
CMrChenApp::CMrChenApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MrChen.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的 CMrChenApp 对象

CMrChenApp theApp;


// CMrChenApp 初始化

BOOL CMrChenApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要 AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMrChenDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CMrChenView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// APP 初始化
	InitilizationApp();

	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo); //默认是有有一个打开FileNew文档的命令

	if(m_param->moduleFileName.IsEmpty())
		m_param->moduleFileName = Str_File_Module_Defalt;

	CString strpathname = m_strAppPath + Str_Backslash + m_param->moduleFileName;// + _0T(".wll");
	CFindFile file;

	file.First(strpathname);
	if (file.IsOk())
	{
		cmdInfo.m_strFileName = strpathname;
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileOpen;
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}
	else 
	{
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
		CDocument *pDoc = theMainFrame->GetActiveDocument();
		pDoc->DoSave(strpathname, TRUE);
	}


	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	/*if (!ProcessShellCommand(cmdInfo))
		return FALSE;*/


	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CMrChenApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	SaveConfig();
	return CWinAppEx::ExitInstance();
}

BOOL CMrChenApp::LoadConfig()
{
	CString strProfile = m_strAppPath + APP_CONFIG_FILE;
	if (m_iniFile.Open(strProfile,CFile::modeRead) == 0 )
	{
		TRACE(_T("未找到配置文件"));
		//m_iniFile.Open(strProfile, CFile::modeCreate);
		return FALSE;
	}
	CArchive ar(&m_iniFile,CArchive::CArchive::load);

	try {
		ar >> m_param->m_VerNum;


	}
	catch (CFileException* e)
	{
		if (e->m_cause == CFileException::fileNotFound)
			printf("FileException  Error :not found file\n");
	}
	catch (...)
	{ }


	ar.Flush();
	ar.Close();
	m_iniFile.Close();
	return 0;
}

BOOL CMrChenApp::SaveConfig()
{
	CString strProfile = m_strAppPath + APP_CONFIG_FILE;
	
	//CFile::modeNoTruncate若文件不存在，则创建新文件；否则，如果该文件已存在，则将其附加到 CFile 对象。
	m_iniFile.Open(strProfile, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);

	CArchive ar(&m_iniFile, CArchive::CArchive::store);

	try {
		ar << m_param->m_VerNum;

	}
	catch (...)
	{
		AfxMessageBox(_T("保存文件出错"));
	}
	ar.Flush();
	ar.Close();
	m_iniFile.Close();
	return 0;
}

// CMrChenApp 消息处理程序


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
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedNetAddr();
	CWndMyStatic m_ulr;
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_NET_ADDR, &CAboutDlg::OnStnClickedNetAddr)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMrChenApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMrChenApp 自定义加载/保存方法

void CMrChenApp::PreLoadState()
{
	//加载菜单栏
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);

	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);

	bNameValid = strName.LoadString(IDS_OUTPOP_CTRL);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_OUTPUT_CTRL);
}

void CMrChenApp::LoadCustomState()
{
}

void CMrChenApp::SaveCustomState()
{
}

// CMrChenApp 消息处理程序


BOOL CMrChenApp::OnIdle(LONG lCount)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CWinAppEx::OnIdle(lCount);
}

void CMrChenApp::InitilizationApp()
{
	//获取App当前路径
	TCHAR path[512];
	GetModuleFileName(NULL, path, 512);
	TRACE(_T("main directory is %s\n"), path);
	size_t i = _tcslen(path);
	while (i > 0)
	{
		i--;
		if (path[i] == '\\')
		{
			path[i] = '\0';
			TRACE(_T("%s\n"), path);
			m_strAppPath = path;
			break;
		}
	}

	LoadConfig();
	

	
	
}





//////////////////////////////////////////////////////////////About


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	
	m_ulr.Create(_T("http://www.welllih.com"), WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY,
		CRect(60, 90, 500, 130), this, IDC_NET_ADDR);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnOK();
}


void CAboutDlg::OnStnClickedNetAddr()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUlr;
	m_ulr.GetWindowText(strUlr);
	ShellExecute(NULL, _T("open"), strUlr, NULL, NULL, SW_SHOWNORMAL);
}
; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSpooferDlg
LastTemplate=CEdit
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Spoofer.h"

ClassCount=10
Class1=CSpooferApp
Class2=CSpooferDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMSocket
Class5=CDRKEdit
Resource3=IDD_RESOLVER
Class6=CProtoInfoDlg
Resource4=IDD_PROTOINFO
Class7=CResolverDlg
Resource5=IDD_SPOOFER_DIALOG
Class8=CDetailDlg
Resource6=IDD_RDWINDOW
Class9=CHelpDlg
Class10=CDRKEdit2
Resource7=IDD_HELP

[CLS:CSpooferApp]
Type=0
HeaderFile=Spoofer.h
ImplementationFile=Spoofer.cpp
Filter=N
LastObject=CSpooferApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CSpooferDlg]
Type=0
HeaderFile=SpooferDlg.h
ImplementationFile=SpooferDlg.cpp
Filter=T
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_SBUFFER

[CLS:CAboutDlg]
Type=0
HeaderFile=SpooferDlg.h
ImplementationFile=SpooferDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDC_WEB,button,1342275584
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342181390
Control6=IDC_STATIC,static,1350565902
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352

[DLG:IDD_SPOOFER_DIALOG]
Type=1
Class=CSpooferDlg
ControlCount=41
Control1=IDC_IPADDR,SysIPAddress32,1342242816
Control2=IDC_PORT,edit,1350631552
Control3=IDC_TCP,button,1342242825
Control4=IDC_UDP,button,1342242825
Control5=IDC_CREATE,button,1342242816
Control6=IDC_DESROY,button,1342242816
Control7=IDC_RIPADDR,SysIPAddress32,1342242816
Control8=IDC_RPORT,edit,1350631552
Control9=IDC_CONNECT,button,1342242816
Control10=IDC_SBUFFER,edit,1352732804
Control11=IDC_SEND,button,1342242817
Control12=IDC_NOROUTE,button,1342242819
Control13=IDC_OOB,button,1342242819
Control14=IDC_RCLR,button,1342242816
Control15=IDC_SCLR,button,1342242816
Control16=IDC_ABOUT,button,1342242816
Control17=IDCANCEL,button,1342242816
Control18=IDC_RBUFFER,edit,1352734852
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,button,1342177287
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_PACKETS,static,1342308352
Control27=IDC_BYTES,static,1342308352
Control28=IDC_LAST,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_KEEPALIVE,button,1342246915
Control34=IDC_NODELAY,button,1342246915
Control35=IDC_NETSTAT,button,1342242816
Control36=IDC_DNSRES,button,1342242816
Control37=IDC_RDETAIL,button,1342246915
Control38=IDC_HELPB,button,1342242816
Control39=IDC_BIND,button,1342242816
Control40=IDC_DEBUG,button,1342246915
Control41=IDC_PARSE,button,1342242819

[CLS:CMSocket]
Type=0
HeaderFile=MSocket.h
ImplementationFile=MSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CMSocket

[CLS:CDRKEdit]
Type=0
HeaderFile=DRKEdit.h
ImplementationFile=DRKEdit.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC
LastObject=CDRKEdit

[DLG:IDD_PROTOINFO]
Type=1
Class=CProtoInfoDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_INFO,edit,1352734852

[CLS:CProtoInfoDlg]
Type=0
HeaderFile=ProtoInfoDlg.h
ImplementationFile=ProtoInfoDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CProtoInfoDlg

[DLG:IDD_RESOLVER]
Type=1
Class=CResolverDlg
ControlCount=5
Control1=IDC_NAME,edit,1350631552
Control2=IDC_RESOLVE,button,1342242817
Control3=IDOK,button,1342242816
Control4=IDC_RESULT,edit,1352734852
Control5=IDC_STATIC,static,1342308352

[CLS:CResolverDlg]
Type=0
HeaderFile=ResolverDlg.h
ImplementationFile=ResolverDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CResolverDlg
VirtualFilter=dWC

[DLG:IDD_RDWINDOW]
Type=1
Class=CDetailDlg
ControlCount=3
Control1=IDC_SCREEN,edit,1352734852
Control2=IDC_APPEND,button,1342242819
Control3=IDC_BOUNDARIES,button,1342242819

[CLS:CDetailDlg]
Type=0
HeaderFile=DetailDlg.h
ImplementationFile=DetailDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_APPEND
VirtualFilter=dWC

[DLG:IDD_HELP]
Type=1
Class=CHelpDlg
ControlCount=3
Control1=IDC_HELPSCREEN,edit,1353717764
Control2=IDC_SWITCH,button,1342242817
Control3=IDC_SWHELP,button,1342242816

[CLS:CHelpDlg]
Type=0
HeaderFile=HelpDlg.h
ImplementationFile=HelpDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHelpDlg

[CLS:CDRKEdit2]
Type=0
HeaderFile=DRKEdit2.h
ImplementationFile=DRKEdit2.cpp
BaseClass=CEdit
Filter=W
VirtualFilter=WC


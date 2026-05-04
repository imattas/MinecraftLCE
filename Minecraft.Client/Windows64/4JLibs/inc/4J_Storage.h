#pragma once
using namespace std;

#define MAX_DISPLAYNAME_LENGTH 128
#define MAX_SAVEFILENAME_LENGTH 32
#define USER_INDEX_ANY 0x000000FF
#define RESULT	LONG

class StringTable;

typedef struct
{
	time_t			modifiedTime;
	unsigned int	dataSize;
	unsigned int	thumbnailSize;
}
CONTAINER_METADATA;

typedef struct  
{
	wchar_t UTF16SaveFilename[MAX_SAVEFILENAME_LENGTH];
	wchar_t UTF16SaveTitle[MAX_DISPLAYNAME_LENGTH];
	CONTAINER_METADATA metaData;
	PBYTE thumbnailData;
	uint64_t totalSize;
	bool	needsSync;
}
SAVE_INFO,*PSAVE_INFO;

typedef struct  
{
	int iSaveC;
	int iThumbnailC;
	PSAVE_INFO SaveInfoA;
}
SAVE_DETAILS,*PSAVE_DETAILS;

// XCONTENT_DATA and XMARKETPLACE_OFFERING_TYPE are defined in extraX64.h

typedef struct _MARKETPLACE_CONTENTOFFER_INFO
{
	WCHAR *wszProductID;
	WCHAR *wszOfferName;
	BOOL fUserHasPurchased;
	WCHAR *wszSellText;
	WCHAR *wszCurrencyPrice;
	WCHAR *wszSignedOfferID;
} MARKETPLACE_CONTENTOFFER_INFO, *PMARKETPLACE_CONTENTOFFER_INFO;

enum eWebServiceState
{
	eWebService_idle,
	eWebService_notsignedin,
	eWebService_pending,
	eWebService_error,
	eWebService_busy
};

enum eTitleStorageState
{
	eTitleStorage_idle,
	eTitleStorage_notsignedin,
	eTitleStorage_pending,
	eTitleStorage_complete,
	eTitleStorage_readcomplete,
	eTitleStorage_readfilelistcomplete,
	eTitleStorage_writecomplete,
	eTitleStorage_deletecomplete,
	eTitleStorage_error,
	eTitleStorage_readerror,
	eTitleStorage_readfilelisterror,
	eTitleStorage_writeerror,
	eTitleStorage_deleteerror,
	eTitleStorage_busy
};

// Current version of the dlc data creator
#define CURRENT_DLC_VERSION_NUM 3

class C4JStorage
{
public:

	struct PROFILESETTINGS
	{
		int iYAxisInversion;
		int iControllerSensitivity;
		int iVibration;
		bool bSwapSticks;
	};

	typedef struct  
	{
		unsigned int	uiFileSize;
		DWORD			dwType;
		DWORD			dwWchCount;
		WCHAR			wchFile[1];
	}
	DLC_FILE_DETAILS, *PDLC_FILE_DETAILS;

	typedef struct
	{
		DWORD	dwType;
		DWORD	dwWchCount;
		WCHAR	wchData[1];
	}
	DLC_FILE_PARAM, *PDLC_FILE_PARAM;

	typedef struct  
	{
		DWORD dwVersion;
		DWORD dwNewOffers;
		DWORD dwTotalOffers;
		DWORD dwInstalledTotalOffers;
		BYTE bPadding[1024-sizeof(DWORD)*4];
	}
	DLC_TMS_DETAILS;

	typedef struct  
	{
		DWORD dwSize;
		PBYTE pbData;
	}
	TMSPP_FILEDATA, *PTMSPP_FILEDATA;

	enum eTMS_FILETYPEVAL
	{
		TMS_FILETYPE_BINARY=0,
		TMS_FILETYPE_CONFIG=1,
		TMS_FILETYPE_JSON=2,
		TMS_FILETYPE_MAX,
	};

	typedef struct  
	{
		WCHAR				wchFilename[64];
		unsigned long		ulFileSize;
		eTMS_FILETYPEVAL	eFileTypeVal;
	}
	TMSPP_FILE_DETAILS, *PTMSPP_FILE_DETAILS;

	typedef struct  
	{
		int iCount;
		PTMSPP_FILE_DETAILS FileDetailsA;
	}
	TMSPP_FILE_LIST, *PTMSPP_FILE_LIST;

	typedef struct  
	{
		PBYTE pbData;
		unsigned long ulFileLen;
	}
	SAVETRANSFER_FILE_DETAILS;

	enum eGlobalStorage
	{
		eGlobalStorage_Title=0,
		eGlobalStorage_TitleUser,
		eGlobalStorage_Max
	};

	enum EMessageResult
	{
		EMessage_Undefined=0,
		EMessage_Busy,
		EMessage_Pending,
		EMessage_Cancelled,
		EMessage_ResultAccept,
		EMessage_ResultDecline,
		EMessage_ResultThirdOption,
		EMessage_ResultFourthOption
	};

	enum ESaveGameState
	{
		ESaveGame_Idle=0,
		ESaveGame_Save,
		ESaveGame_SaveCompleteSuccess,
		ESaveGame_SaveCompleteFail,
		ESaveGame_SaveIncomplete,
		ESaveGame_SaveIncomplete_WaitingOnResponse,
		ESaveGame_SaveSubfiles,
		ESaveGame_SaveSubfilesCompleteSuccess,
		ESaveGame_SaveSubfilesCompleteFail,
		ESaveGame_SaveSubfilesIncomplete,
		ESaveGame_SaveSubfilesIncomplete_WaitingOnResponse,
		ESaveGame_Load,
		ESaveGame_LoadComplete,
		ESaveGame_EnumerateSubfiles,
		ESaveGame_EnumerateSubfilesComplete,
		ESaveGame_LoadSubfiles,
		ESaveGame_LoadCompleteSuccess,
		ESaveGame_LoadCompleteFail,
		ESaveGame_Delete,
		ESaveGame_DeleteSuccess,
		ESaveGame_DeleteFail,
		ESaveGame_Rename,
		ESaveGame_RenameSuccess,
		ESaveGame_RenameFail,
		ESaveGame_GetSaveThumbnail,
		ESaveGame_GetSaveThumbnailComplete,
		ESaveGame_Copy,
		ESaveGame_CopyCompleteSuccess,
		ESaveGame_CopyCompleteFail,
	};

	enum ESaveGameStatus
	{
		EDeleteGame_Idle=0,
		EDeleteGame_InProgress,
	};

	enum EDLCStatus
	{
		EDLC_Error=0,
		EDLC_Idle,
		EDLC_NoOffers,
		EDLC_AlreadyEnumeratedAllOffers,
		EDLC_NoInstalledDLC,
		EDLC_Pending,
		EDLC_LoadInProgress,
		EDLC_Loaded,
		EDLC_ChangedDevice
	};

	enum ESavingMessage
	{
		ESavingMessage_None=0,
		ESavingMessage_Short,
		ESavingMessage_Long
	};

	enum ESaveIncompleteType
	{
		ESaveIncomplete_None,
		ESaveIncomplete_OutOfQuota,
		ESaveIncomplete_OutOfLocalStorage,
		ESaveIncomplete_Unknown
	};

	enum ETMSStatus
	{
		ETMSStatus_Idle=0,
		ETMSStatus_Fail,
		ETMSStatus_ReadInProgress,
		ETMSStatus_ReadFileListInProgress,
		ETMSStatus_WriteInProgress,
		ETMSStatus_Fail_ReadInProgress,
		ETMSStatus_Fail_ReadFileListInProgress,
		ETMSStatus_Fail_ReadDetailsNotRetrieved,
		ETMSStatus_Fail_WriteInProgress,
		ETMSStatus_DeleteInProgress,
		ETMSStatus_Pending,
	};

	enum eTMS_FileType
	{
		eTMS_FileType_Normal=0,
		eTMS_FileType_Graphic,
	};

	enum ESGIStatus
	{
		ESGIStatus_Error=0,
		ESGIStatus_Idle,
		ESGIStatus_ReadInProgress,
		ESGIStatus_NoSaves,
	};

	enum
	{
		PROFILE_READTYPE_ALL,
		PROFILE_READTYPE_XBOXSETTINGS
	};

	enum eOptionsCallback
	{
		eOptions_Callback_Idle,
		eOptions_Callback_Write,
		eOptions_Callback_Write_Fail_NoSpace,
		eOptions_Callback_Write_Fail,
		eOptions_Callback_Read,
		eOptions_Callback_Read_Fail,
		eOptions_Callback_Read_FileNotFound,
		eOptions_Callback_Read_Corrupt,
		eOptions_Callback_Read_CorruptDeletePending,
		eOptions_Callback_Read_CorruptDeleted
	};

	enum eSaveTransferState
	{
		eSaveTransfer_Idle,
		eSaveTransfer_Busy,
		eSaveTransfer_GettingFileSize,
		eSaveTransfer_FileSizeRetrieved,
		eSaveTransfer_GetFileData,
		eSaveTransfer_GettingFileData,
		eSaveTransfer_FileDataRetrieved,
		eSaveTransfer_Converting,
		eSaveTransfer_Saving,
	};

	C4JStorage();
	void						Tick(void);

	// Initialisation
	void						Init(unsigned int uiSaveVersion,LPCWSTR pwchDefaultSaveName,char *pszSavePackName,int iMinimumSaveSize,
									 int( *Func)(LPVOID, const ESavingMessage, int),LPVOID lpParam,
									 bool(*SetRetrieveProductIDFn)(XCONTENT_DATA &Data),WCHAR *pwchSCID,WCHAR *pwchTitleId);
	void						SetGameSaveFolderTitle(WCHAR *wszGameSaveFolderTitle);
	void						SetSaveCacheFolderTitle(WCHAR *wszSaveCacheFolderTitle);
	void						SetOptionsFolderTitle(WCHAR *wszOptionsFolderTitle);
	void						SetGameSaveFolderPrefix(char *szGameSaveFolderPrefix);
	void						SetMaxSaves(int iMaxC);
	void						SetDefaultImages(PBYTE pbSaveThumbnail,DWORD dwSaveThumbnailBytes);
	void						SetIncompleteSaveCallback(void( *Func)(LPVOID, const ESaveIncompleteType), LPVOID param);

	// Miscellaneous control
	void						SetSaveDisabled(bool bDisable);
	bool						GetSaveDisabled(void);
	void						ResetSaveData();
	C4JStorage::ESaveGameState	DoesSaveExist(bool *pbExists);
	bool						EnoughSpaceForAMinSaveGame();
	C4JStorage::ESaveGameState	GetSaveState();

	// Get details of existing savedata
	C4JStorage::ESaveGameState	GetSavesInfo(int iPad,int ( *Func)(LPVOID lpParam,SAVE_DETAILS *pSaveDetails,const bool),LPVOID lpParam,char *pszSavePackName);
	PSAVE_DETAILS				ReturnSavesInfo();
	void						ClearSavesInfo();
	C4JStorage::ESaveGameState	LoadSaveDataThumbnail(PSAVE_INFO pSaveInfo,int( *Func)(LPVOID lpParam,PBYTE pbThumbnail,DWORD dwThumbnailBytes), LPVOID lpParam, bool force=false);

	// Loading savedata
	C4JStorage::ESaveGameState	LoadSaveData(PSAVE_INFO pSaveInfo,int( *Func)(LPVOID lpParam,const bool, const bool), LPVOID lpParam);
	unsigned int				GetSaveSize();
	void						GetSaveData(void *pvData,unsigned int *puiBytes);
	bool						GetSaveUniqueNumber(INT *piVal);
	bool						GetSaveUniqueFilename(char *pszName);

	// Sub-files
	unsigned int				GetSubfileCount();
	void						ResetSubfiles();
	void						GetSubfileDetails(int idx, unsigned int *subfileId, unsigned char **data, unsigned int *sizeOut);
	void						UpdateSubfile(int idx, unsigned char *data, unsigned int size);
	int							AddSubfile(unsigned int subfileId);
	C4JStorage::ESaveGameState	SaveSubfiles(int( *Func)(LPVOID ,const bool),LPVOID lpParam);

	// Saving savedata
	void						SetSaveTitle(const wchar_t *UTF16String);
	PVOID						AllocateSaveData(unsigned int uiBytes);
	void						SetSaveDataSize(unsigned int uiBytes);
	void						GetDefaultSaveImage(PBYTE *ppbSaveImage,DWORD *pdwSaveImageBytes);
	void						GetDefaultSaveThumbnail(PBYTE *ppbSaveThumbnail,DWORD *pdwSaveThumbnailBytes);
	void						SetSaveImages( PBYTE pbThumbnail,DWORD dwThumbnailBytes,PBYTE pbImage,DWORD dwImageBytes, PBYTE pbTextData ,DWORD dwTextDataBytes);
	C4JStorage::ESaveGameState	SaveSaveData(int( *Func)(LPVOID ,const bool),LPVOID lpParam);

	// Incomplete saves
	void						ContinueIncompleteOperation();
	void						CancelIncompleteOperation();

	// Other file operations
	C4JStorage::ESaveGameState	DeleteSaveData(PSAVE_INFO pSaveInfo,int( *Func)(LPVOID lpParam,const bool), LPVOID lpParam);
	C4JStorage::ESaveGameState	CopySaveData(PSAVE_INFO pSaveInfo,int( *Func)(LPVOID ,const bool,C4JStorage::ESaveGameState state),bool( *FuncProg)(LPVOID ,const int),LPVOID lpParam);
	C4JStorage::ESaveGameState	RenameSaveData(int iRenameIndex,uint16_t*pui16NewName,int( *Func)(LPVOID lpParam,const bool), LPVOID lpParam);

	void						GetSaveImage(PBYTE *ppbSaveImage, int *puiSaveImageBytes);
	void						GetSaveThumbnail(PBYTE *ppbSaveThumbnail, int *puiSaveThumbnailBytes);
	void						SetSaveUniqueFilename(wchar_t *szFilename);

	// Profile data
	void						InitialiseProfileData(unsigned short usProfileVersion, UINT uiProfileValuesC, UINT uiProfileSettingsC, DWORD *pdwProfileSettingsA, int iGameDefinedDataSizeX4, unsigned int *puiGameDefinedDataChangedBitmask);
	int							SetDefaultOptionsCallback(int( *Func)(LPVOID,PROFILESETTINGS *, const int iPad),LPVOID lpParam);
	void						SetOptionsDataCallback(int( *Func)(LPVOID, int iPad, unsigned short usVersion, C4JStorage::eOptionsCallback),LPVOID lpParam);
	int							SetOldProfileVersionCallback(int( *Func)(LPVOID,unsigned char *, const unsigned short,const int),LPVOID lpParam);
	PROFILESETTINGS *			GetDashboardProfileSettings(int iPad);
	void *						GetGameDefinedProfileData(int iQuadrant);
	void						ReadFromProfile(int iQuadrant, int iReadType=PROFILE_READTYPE_ALL);
	void						WriteToProfile(int iQuadrant, bool bGameDefinedDataChanged=false, bool bOverride5MinuteLimitOnProfileWrites=false);
	void						DeleteOptionsData(int iPad);
	void						ForceQueuedProfileWrites(int iPad=-1);

	// DLC
	C4JStorage::EDLCStatus		GetInstalledDLC(int iPad,int( *Func)(LPVOID, int, int),LPVOID lpParam);
	void						SetLicenseChangeFn(void( *Func)(void));
	XCONTENT_DATA&				GetDLC(DWORD dw);
	DWORD						MountInstalledDLC(int iPad,DWORD dwDLC,int( *Func)(LPVOID, int, DWORD,DWORD),LPVOID lpParam,LPWSTR szMountDrive = nullptr);
	DWORD						UnmountInstalledDLC(LPWSTR szMountDrive = nullptr);
	void						GetMountedDLCFileList(const char* szMountDrive, std::vector<std::wstring>& fileList);
	std::wstring				GetMountedPath(std::wstring szMount);
	XCONTENT_DATA *				GetInstalledDLC(WCHAR *wszProductID);
	C4JStorage::EDLCStatus		GetDLCOffers(int iPad,int( *Func)(LPVOID, int, DWORD, int),LPVOID lpParam, DWORD dwOfferTypesBitmaskT);
	MARKETPLACE_CONTENTOFFER_INFO&		GetOffer(DWORD dw);
	DWORD								InstallOffer(int iOfferIDC,WCHAR *pwchProductId,int( *Func)(LPVOID, int, int),LPVOID lpParam, bool bTrial=false);
	void						UpdateDLCProductIDs();

	void						Suspend();
	bool						Suspended();

	void						SetSaveDeviceSelected(unsigned int uiPad,bool bSelected) {}
	bool						GetSaveDeviceSelected(unsigned int iPad) { return true; }
	void						ClearDLCOffers();
	bool						DeleteTMSFile(int iQuadrant,eGlobalStorage eStorageFacility,LPWSTR wszFilename);

	// TMS++
	C4JStorage::ETMSStatus		TMSPP_GetUserQuotaInfo(C4JStorage::eGlobalStorage eStorageFacility,int iPad);
	eTitleStorageState			TMSPP_WriteFile(int iQuadrant,C4JStorage::eGlobalStorage eStorageFacility,C4JStorage::eTMS_FILETYPEVAL eFileTypeVal,LPWSTR wszFilename,BYTE *pbBuffer,DWORD dwBufferSize,int( *Func)(LPVOID,int,int)=nullptr,LPVOID lpParam=nullptr, int iUserData=0);
	eTitleStorageState			TMSPP_ReadFile(int iQuadrant,C4JStorage::eGlobalStorage eStorageFacility,C4JStorage::eTMS_FILETYPEVAL eFileTypeVal,LPWSTR wszFilename,int( *Func)(LPVOID,int,int,LPVOID, WCHAR *),LPVOID lpParam, int iUserData);
	eTitleStorageState			TMSPP_DeleteFile(int iQuadrant,C4JStorage::eGlobalStorage eStorageFacility,C4JStorage::eTMS_FILETYPEVAL eFileTypeVal,LPWSTR wszFilename,int( *Func)(LPVOID,int,int),LPVOID lpParam, int iUserData);
	eTitleStorageState			TMSPP_ReadFileList(int iPad,C4JStorage::eGlobalStorage eStorageFacility,int( *Func)(LPVOID,int,int,LPVOID,WCHAR *)=nullptr,LPVOID lpParam=nullptr, int iUserData=0);
	bool						TMSPP_InFileList(eGlobalStorage eStorageFacility, int iPad,const wstring &Filename);
	eTitleStorageState			TMSPP_GetTitleStorageState(int iPad);
	void						TMSPP_ClearTitleStorageState(int iPad);

	// Save transfers
	C4JStorage::eSaveTransferState SaveTransferClearState();
	C4JStorage::eSaveTransferState SaveTransferGetDetails(int iPad, eGlobalStorage source, wchar_t *file, int ( *Func)(LPVOID lpParam,C4JStorage::SAVETRANSFER_FILE_DETAILS *pSaveTransferDetails),LPVOID lpParam);
	C4JStorage::eSaveTransferState SaveTransferGetData(int iPad, eGlobalStorage source, wchar_t *file,int ( *Func)(LPVOID lpParam,C4JStorage::SAVETRANSFER_FILE_DETAILS *pSaveTransferDetails),int ( *ProgressFunc)(LPVOID lpParam,unsigned long),LPVOID lpParam,LPVOID lpProgressParam);
	void CancelSaveTransfer(int ( *CancelCompleteFunc)(LPVOID lpParam),LPVOID lpParam);
};

extern C4JStorage StorageManager;

#ifndef _SP_EXC_H_
#define _SP_EXC_H_

#include "SNbase.h"
#include "SP_META_Wrapper.h"

#define  PreloaderUSB  1
#define  BootROMUSB   0
#define  MAX_MD_CHANNEL_NUM 8
/*
#define MT5921 0x5921
#define MT5931 0x5931
#define MT6620 0x6620
#define MT6628 0x6628
#define MT6571 0x6571
#define MT6572 0x6572
#define MT6582 0x6582
#define MT6592 0x6592
#define MT6595 0x6630
#define MT6752 0x6752
#define MT8127 0x8127
*/

typedef enum
{
    SP_MODEM_META = 0,
    SP_AP_META,
    SP_AP2MD_FAIL,
    SP_MD2AP_FAIL,
    SP_NOTIN_META = 256
}SP_METAMODE_e;

typedef struct  
{
    unsigned int number_of_md;
    unsigned int active_md_idx; 
    unsigned int current_mdtype; 
    unsigned int mdimg_type[16];
    unsigned int number_of_mdSwImg; 
    int          activeMdTypeIdx;
    unsigned int multi_md_capability_support;
}SP_MODEMInfo_s;

typedef struct r_buf
{
	char rd_buf[1000];

}ADB_READ_BUF;

class SmartPhoneSN : public SNBase
{
public:
    SmartPhoneSN();
    virtual ~SmartPhoneSN();

protected:
    
    virtual void ThreadMainEntryPoint();
    virtual void SPInit();
    virtual META_RESULT MetaHandle_Init();   
    virtual META_RESULT ModemMetaHandle_Init();   
    virtual SPMETA_DLL::META_RESULT APMetaHandle_Init();
    
    virtual void MetaHandle_DeInit();
    virtual void ModemMetaHandle_DeInit();
    virtual void APMetaHandle_DeInit();
    
    virtual void SetupMetaModeParameters();
    virtual int TryToOpenSPKernelComport(int KernelCom_Num);
    virtual int ConnectWithPreloader();
    virtual int ConnectWithKernelPort(SP_METAMODE_e spMetaMode);
	virtual int ConnectWithKernelPort_Ex(SP_METAMODE_e spMetaMode);

    virtual SPMETA_DLL::META_RESULT EnterAPMetaMode();
    virtual SPMETA_DLL::META_RESULT ExitAPMetaMode();

    virtual META_RESULT EnterSPModemMeta();
    virtual META_RESULT ExitSPModemMeta();

    virtual META_RESULT ModemSwithToAPMeta();   
    virtual META_RESULT APSwithToModemMeta();    //Old API  
    virtual META_RESULT APSwithToModemMeta_Ex(); //New API
    virtual META_RESULT SwitchMDByIndex(UINT MDIndex);

    //Enter ap meta first, you must switch to modem meta for init modem database
    //EnterModemMetaToInitModemDB combine switch to modem meta and int modem db function
    virtual META_RESULT EnterModemMetaToInitModemDB();

    
    virtual int GetSPModemInfo();
	virtual int GetSPModemInfo_Ex();
    virtual META_RESULT LoadModemDatabase();
    virtual META_RESULT LoadModemDatabase(int MDindex);
    virtual SPMETA_DLL::META_RESULT LoadAPDatabase();

    virtual SPMETA_DLL::META_RESULT REQ_ReadAP_NVRAM_Start(WriteData_Type_e dataType, char *pOutData, unsigned short iRID);
    virtual SPMETA_DLL::META_RESULT REQ_WriteAP_NVRAM_Start(WriteData_Type_e dataType, char *pInData, unsigned short iRID);
    virtual META_RESULT REQ_ReadModem_NVRAM_Start(WriteData_Type_e dataType, char *pOutData, unsigned short iRID);
    virtual META_RESULT REQ_WriteModem_NVRAM_Start(WriteData_Type_e dataType, char *pInData, unsigned short iRID);

    virtual SPMETA_DLL::META_RESULT ConductProdInfoData(unsigned char *pOutData, const char *pBarcodeData, const char (*pIMEIData)[IMEI_ARRAY_LEN], int iIMEINums, char *pBtAddr, char *pWiFiAddr, char *pReserved, int bufSize); 
    virtual SPMETA_DLL::META_RESULT REQ_WriteAP_PRODINFO_Start(char *pBarcode, char (*pIMEI)[IMEI_ARRAY_LEN], char *pBtAddr, char *pWiFiAddr, char *pReserved);
   
    virtual SPMETA_DLL::META_RESULT REQ_ReadFromAPNVRAM(SPMETA_DLL::FT_NVRAM_READ_REQ *psNVRAM_ReadReq, SPMETA_DLL::FT_NVRAM_READ_CNF *psNVRAM_ReadCnf);
    virtual SPMETA_DLL::META_RESULT REQ_WriteToAPNVRAM(SPMETA_DLL::FT_NVRAM_WRITE_REQ sNVRAM_WriteReq);
	
    
   

    virtual int LoadHDCPBinFile(const char *strHdcpBinPath);
    virtual int LoadDRMKeyFile(const char *strDrmKeyFilePath);
    virtual SPMETA_DLL::META_RESULT REQ_WriteHdcpBinToAPNvram_Start(const char *strHdcpBinPath);	
    virtual SPMETA_DLL::META_RESULT REQ_InstallDRMKey_Start(const char *strDrmKeyFilePath);
    virtual SPMETA_DLL::META_RESULT REQ_InstallHdcpData_Start(const char *strHdcpDataFilePath, const char *strHdcpCekFilePath);
	

    virtual SPMETA_DLL::META_RESULT REQ_WriteDRMKeyMCID_Start(const char *strDrmKeyMCIDData);
    virtual SPMETA_DLL::META_RESULT REQ_ReadDRMKeyMCID_Start(char *strDrmKeyMCIDData);

    virtual SPMETA_DLL::META_RESULT QuerySpeakerCalibrationSupport();
    virtual SPMETA_DLL::META_RESULT REQ_WriteTemperatureToNvram_Start(float *Temperature);

    virtual SPMETA_DLL::META_RESULT ReadNvToMakeFileName(char *NumFile);
    virtual SPMETA_DLL::META_RESULT REQ_BackupNvram2PC_Start(char *NumFile);

    virtual SPMETA_DLL::META_RESULT REQ_BackupNvram2BinRegion_Start(int BackUpOption);
	
    //For ROME DSDA Native Download and Backup
//    virtual int DSDA_QueryNativeDownload();
//	virtual SPMETA_DLL::META_RESULT DSDA_StartNativeDownload();
	virtual _BOOL DSDA_ExternalModemBackup();

    virtual META_RESULT WriteNvramLoop();
    virtual int REQ_FastbootLockOem(void);
	virtual int REQ_FastbootUnLockOem(void);
	int Fastboot_Lock_Oem();
	bool Adb_Manager_Init();
	bool Adb_WR_Cmd(char *cmd_line,int cmd_length);
	int Adb_Detect_Devact();
	int Adb_Manager_Deinit();
	int Set_Fastboot_EnvironmentVariable(void);

	bool QueryEncryptionSupport(int * MetaHandle);
	bool VeritifiEncryption(int *MetaHandle);

	void EnterC2KModemMeta(int * MetaResult, int * m_hSPMetaHandle, int *C2K_Flag);
	void DeinitC2KMeta(int * m_hSPMetaHandle, int * C2K_Flag);
	void DisconnectC2KMeta(int * m_hSPMetaHandle, int * C2K_Flag);
	//bool C2K_Meta();
	
private:
	int Adb_Manager_Write(char *cmd_line,int cmd_length);
	int Adb_Manager_Read(ADB_READ_BUF *adb_read_buf,int buf_size);	
	
private:	
    SPMETA_DLL::MODEM_CAPABILITY_LIST_CNF m_SpMdCapList;
    META_Connect_Ex_Req       m_tMetaReq_Ex;
    META_Connect_Report       m_tMetaConnReport_Ex;
    SP_BOOT_ARG_S m_stModeArg;
    UINT m_iKernelComport;
    SP_METAMODE_e m_eMetaMode;
    SP_MODEMInfo_s m_sMdInfo;
    bool m_bWorldPhone;
    bool m_bDualModem;
    bool m_bWithoutMD;
    bool m_bUseNewConnectMauiMetaAPI;
    bool m_bWriteProdInfo;
    //For MT6595 DSDA project
    bool m_bDSDAProject;
    bool m_bInitExtMDdb;


    char m_strHdcpFileFullName[1024];
    char m_strDRMFileFullName[1024];
    UINT m_iMDChannelIndex[MAX_MD_CHANNEL_NUM];
    UINT m_iCurMDChanelIndex;
	UINT m_iLastPercentage;

    SPMETA_DLL::FILE_CUSTOM_HDCP_KEY_STRUCT m_sHDCPNvramStruct;
    SPMETA_DLL::FILE_CUSTOM_HDCP_KEY_STRUCT m_sReadBackHdcp;
  
    SP_MODEM_CAPABILITY_LIST_CNF m_SpWrapperMdCapList;
	//dongck add for fastboot
	HANDLE hdle_write_cmd;
	HANDLE hdle_read_out;
	ADB_READ_BUF read_buf;
	int r_bufsize;
	//DEVICES_INFOS devices_infos;
};

META_MD_Query_Result_T __stdcall MdQueryHandler(void* MdQuery_CB_Arg);
int __stdcall MdTypeSwitchHandler(META_MDTYPE_Switch_Param_T mdtype_switch_param, void* MdTypeSwitch_CB_Arg);

#endif

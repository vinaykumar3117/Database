#include<stdio.h>
#include<oci.h>
FILE *flog;
OCIEnv *envhp;
OCIError *errhp;
OCISvcCtx *svchp;
static OCIStmt *stmthp;

void checkerr(OCIError *errhp, sword status)
{
	text errbuf[512];
	ub4 buflen;
	ub4 errcode;
	switch(status)
	{
		case OCI_SUCCESS : 
			break;
		case OCI_SUCCESS_WITH_INFO:
			fprintf(flog, "Error - OCI_SUCCESS_WITH_INFO\n");
			break;
		case OCI_NEED_DATA:
			fprintf(flog, "Error - OCI_NEED_DATA\n");
			break;
		case OCI_NO_DATA:
			fprintf(flog, "Error - OCI_NODATA\n");
			break;
		case OCI_ERROR:
			OCIErrorGet (errhp, (ub4)1, (text *)NULL, &errcode, errbuf, (ub4)sizeof(errbuf), OCI_HTYPE_ERROR);
			fprintf(flog, "Error - %s\n", errbuf);
			break;
		case OCI_INVALID_HANDLE:
			fprintf(flog, "Error - OCI_INVALID_HANDLE\n");
			break;
		case OCI_STILL_EXECUTING:
			fprintf(flog, "Error - OCI_STILL_EXECUTE\n");
			break;
		default:
			fprintf(flog, "Unkown Error\n");
			break;
	}
	fflush(flog);
}

/*********************** INSERT ***********************/
void insertDB()
{
	int rc = 0,errcode;
	char errbuf[256];
	unsigned char id[] = "1";
	unsigned char shortcode[] = "5555";
	unsigned char msdn[] = "9999999999";
	unsigned char txt[] = "hello";
	unsigned char num[] = "11";
	text *query = (text *)"INSERT INTO AUTUMN_PROMO_QUEUE(APQ_ID, APQ_SHORT_CODE, APQ_MSISDN, APQ_REQ_TEXT, APQ_PROC_NUM) VALUES(:a, :c, :d, :e, :f)";
	OCIStmtPrepare(stmthp, errhp, query, (ub4)strlen(query), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT);
	static OCIBind *bndhp = (OCIBind *)0;
	checkerr(errhp, OCIBindByName(stmthp, &bndhp, errhp, (text *)":a", strlen(":a"), (ub1 *)id, strlen(id)+1, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIBindByName(stmthp, &bndhp, errhp, (text *)":c", strlen(":c"), (ub1 *)shortcode, strlen(shortcode)+1, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIBindByName(stmthp, &bndhp, errhp, (text *)":d", strlen(":d"), (ub1 *)msdn, strlen(msdn)+1, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIBindByName(stmthp, &bndhp, errhp, (text *)":e", strlen(":e"), (ub1 *)txt, strlen(txt)+1, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIBindByName(stmthp, &bndhp, errhp, (text *)":f", strlen(":f"), (ub1 *)num, strlen(num)+1, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, OCI_DEFAULT));
	rc = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4)0, (CONST OCISnapshot *)NULL, (OCISnapshot *)NULL, OCI_COMMIT_ON_SUCCESS);
        if(rc != 0)
        {
                 OCIErrorGet((dvoid *)errhp, (ub4)1, (text *)NULL, &errcode, (char *)errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
                 fprintf(flog, "ORA:INSERT ERROR %d - %.*s\n",errcode, 512, errbuf);
        }
	else
		fprintf(flog, "\nRow Inserted...");
	fflush(flog);
}

/********************** UPDATE *********************/
void updateDB()
{ 
	int rc = 0,errcode;
	char errbuf[256];
	unsigned char gid[] = "3";
	unsigned char msd[] = "9090909090";
	text *query = (text *)"UPDATE SMSG_GROUP_DETAILS SET SGD_MSISDN = :b WHERE SGD_SGM_GROUP_ID = :a";
	OCIStmtPrepare(stmthp, errhp, query, (ub4)strlen(query), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT);
	static OCIBind *bndhp = (OCIBind *)0;
	checkerr(errhp, OCIBindByName(stmthp, &bndhp, errhp, (text *)":a", strlen(":a"), (ub1 *)gid, strlen(gid)+1, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIBindByName(stmthp, &bndhp, errhp, (text *)":b", strlen(":b"), (ub1 *)msd, strlen(msd)+1, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, OCI_DEFAULT));
	rc = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4)0, (CONST OCISnapshot *)NULL, (OCISnapshot *)NULL, OCI_COMMIT_ON_SUCCESS);
        if(rc != 0)
        {
                 OCIErrorGet((dvoid *)errhp, (ub4)1, (text *)NULL, &errcode, (char *)errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
                 fprintf(flog, "ORA:UPDATE ERROR %d - %.*s\n",errcode, 512, errbuf);
        }
	else
		fprintf(flog, "\nRow Updated...");
	fflush(flog);
}

/*********************** DELETE **********************/ 
void deleteDB()
{
	int rc = 0,errcode;
	char errbuf[256];
	unsigned char gid[] = "3";
	text *query = (text *)"DELETE FROM SMSG_GROUP_DETAILS WHERE SGD_SGM_GROUP_ID = :a";
	OCIStmtPrepare(stmthp, errhp, query, (ub4)strlen(query), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT);
	static OCIBind *bndhp = (OCIBind *)0;
	checkerr(errhp, OCIBindByName(stmthp, &bndhp, errhp, (text *)":a", strlen(":a"), (ub1 *)gid, strlen(gid)+1, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, (ub4)0, (ub4 *)0, OCI_DEFAULT));
	rc = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4)0, (CONST OCISnapshot *)NULL, (OCISnapshot *)NULL, OCI_COMMIT_ON_SUCCESS);
        if(rc != 0)
        {
                 OCIErrorGet((dvoid *)errhp, (ub4)1, (text *)NULL, &errcode, (char *)errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
                 fprintf(flog, "ORA:DELETE ERROR %d - %.*s\n",errcode, 512, errbuf);
        }
	else
		fprintf(flog, "\nRow Deleted...");
	fflush(flog);
}

/********************** SELECT ************************/
void selectDB()
{
	int rc = 0,errcode;
	char errbuf[256];
	OCIDefine *defnhp = (OCIDefine *) 0;
	char id[10];
	char date[30];
	char shortcode[10];
	char msdn[16];
	char txt[160];
	char num[3];
	text *query = (text *)"SELECT APQ_ID, APQ_DATE, APQ_SHORT_CODE, APQ_MSISDN, APQ_REQ_TEXT, APQ_PROC_NUM FROM AUTUMN_PROMO_QUEUE";
	OCIStmtPrepare(stmthp, errhp, query, (ub4)strlen(query), (ub4)OCI_NTV_SYNTAX, (ub4)OCI_DEFAULT);
	if (rc != 0)
	{
		OCIErrorGet((dvoid *)errhp, (ub4) 1, (text *) NULL, &errcode, errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
		fprintf(flog, "ORACLE:STMT-ERROR:%.*s\n",512, errbuf);
	}
	checkerr(errhp, OCIDefineByPos(stmthp, &defnhp, errhp, 1, (dvoid *)&id, (sword)10, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIDefineByPos(stmthp, &defnhp, errhp, 2, (dvoid *)&date, (sword)30, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIDefineByPos(stmthp, &defnhp, errhp, 3, (dvoid *)&shortcode, (sword)10, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIDefineByPos(stmthp, &defnhp, errhp, 4, (dvoid *)&msdn, (sword)16, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIDefineByPos(stmthp, &defnhp, errhp, 5, (dvoid *)&txt, (sword)160, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, OCI_DEFAULT));
	checkerr(errhp, OCIDefineByPos(stmthp, &defnhp, errhp, 6, (dvoid *)&num, (sword)3, SQLT_STR, (dvoid *)0, (ub2 *)0, (ub2 *)0, OCI_DEFAULT));
	
	rc = OCIStmtExecute(svchp, stmthp, errhp, (ub4)1, (ub4)0, (CONST OCISnapshot *)NULL, (OCISnapshot *)NULL, OCI_DEFAULT);
	if (rc == OCI_NO_DATA) 
	{
		fprintf(flog, "No Data available....\n");
	}
	else
	{
		fprintf(flog, "\nAUTUMN_PROMO_QUEUE:-\nID\tDATE      \tSHTCD\tMSISDN    \tTEXT \tNUM");
		fprintf(flog, "\n-----------------------------------------------------------");
		while(rc != OCI_NO_DATA)
		{
			fprintf(flog, "\n%s\t%s\t%s\t%s\t%s\t%s", id, date, shortcode, msdn, txt, num);
			rc = OCIStmtFetch2(stmthp, errhp, (ub4)1, (ub2)OCI_FETCH_NEXT, (sb4)0, OCI_DEFAULT);
		}
	}
}

/********************** MAIN ************************/
int main()
{
	int rc = 0,errcode;
	char errbuf[256];
	text *username = "iwa_mtni";
	text *password = "iwa_mtni";
	text *dbname = "//172.20.24.6:1521/mdxutf";
	flog = fopen("/data1/mtnismsg/programs/myOCI.log","a");
	rc = OCIEnvCreate  (
				(OCIEnv **) &envhp,
				OCI_DEFAULT,
				(dvoid *)0,
				(dvoid *(*)(dvoid *, size_t))0,
				(dvoid *(*)(dvoid *, dvoid *, size_t))0,
				(void (*)(dvoid *, dvoid *))0,
				(size_t)0,
				(dvoid **)0
		  	    );
        rc = OCIHandleAlloc((dvoid *)envhp, (dvoid **)&errhp, OCI_HTYPE_ERROR,(size_t) 0, (dvoid **)0);
        rc = OCIHandleAlloc((dvoid *)envhp, (dvoid **)&svchp, OCI_HTYPE_SVCCTX,(size_t) 0, (dvoid **)0);

	rc = OCILogon(envhp, errhp, &svchp, username, strlen(username), password, strlen(password), dbname, strlen(dbname));
        if (rc != 0)
        {
                OCIErrorGet((dvoid *)errhp, (ub4)1, (text *)NULL, &errcode, errbuf, (ub4)sizeof(errbuf), OCI_HTYPE_ERROR);
		fprintf(flog, "\n[ERROR]Oracle Error - %s ",errbuf);
        	rc = OCIHandleFree((dvoid *) svchp, OCI_HTYPE_SVCCTX);
        	rc = OCIHandleFree((dvoid *) errhp, OCI_HTYPE_ERROR);
		exit(0);
        }
	else
        {
		fprintf(flog, "Oracle Connectivity Established\n");
        }
	checkerr(errhp, OCIHandleAlloc((dvoid *)envhp, (dvoid **)&stmthp, OCI_HTYPE_STMT, (size_t)0, (dvoid **)0));
	
	//operations
	selectDB();
	insertDB();
	selectDB();
	//updateDB();
	//selectDB();
	//deleteDB();
	//selectDB();
	///////////

	rc = OCILogoff(svchp, errhp);
	rc = OCIHandleFree((dvoid *)stmthp, OCI_HTYPE_STMT);
        rc = OCIHandleFree((dvoid *)svchp, OCI_HTYPE_SVCCTX);
        rc = OCIHandleFree((dvoid *)errhp, OCI_HTYPE_ERROR);
	fprintf(flog, "\n\nClosing Oracle Connection - Successful\n");
	fflush(flog);
	fclose(flog);
	return 0;
}

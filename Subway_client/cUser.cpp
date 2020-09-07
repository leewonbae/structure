#include "cUser.h"

cUser::cUser() : cConect()
{
	mPlayGame = true;
	mSubwayPlay = true;
	mCheckVersion = false;
}

cUser::~cUser()
{

}

void cUser::Play()
{
	
	while (mPlayGame)
	{
		ShowMainMenu();
		OnRecv();

	}


}
void cUser::ShowMainMenu()
{
	 
	cout << "1. 회원 가입" << endl;
	cout << "2. 로그인" << endl;
	cout << "3. 나가기" << endl;
	int choice;
	cin >> choice;
	
	memset(&phead, 0, sizeof(PACKET_HEAD));
	switch (choice)
	{
	case 1:
		
		phead.mCmd = MSG_NEW_USER_REQ;
		memcpy(mDataBuf, &phead, sizeof(PACKET_HEAD));
		InputUserData();
		break;
	case 2:
	 
		phead.mCmd = MSG_CHECK_USER_REQ;
		memcpy(mDataBuf, &phead, sizeof(PACKET_HEAD));
		InputUserData();
		break;
	case 3:
		mPlayGame = false;
		break;
	default:
		cout << " 의미 없는 숫자 입니다." << endl;
			 
	}
	 
}
void cUser::RecvParsing(int _pasingnum, char* _ptr)
{
	int idata;
	switch (_pasingnum)
	{
	case MSG_NEW_USER_REQ:
		cout << "회원 가입 완료" << endl;
		break;
	case MSG_CHECK_USER_REQ:
		cout << "유저 확인" << endl;
		PACKET_USER_CHECK pusercheck;
	
		memcpy(&pusercheck, _ptr + sizeof(PACKET_HEAD), sizeof(PACKET_USER_CHECK));
		cout <<"recv check = " << pusercheck.mCheck << endl;
		if (CheckUser(pusercheck.mCheck))
		{
			InSUBWAY();
		}
		
		break;
	case MSG_CHECK_VERSION_REQ:
		cout << "버전 확인" << endl;
		PACKET_VERSION pver;
		memcpy(&pver, _ptr + sizeof(PACKET_HEAD), sizeof(PACKET_VERSION));
		mTextfile = fopen("textfile.txt", "r");
		fscanf(mTextfile, "%d", &idata);
		fclose(mTextfile);

		if (pver.mVersion == idata)
		{
			mCheckVersion = true;
		}
		else
		{
			mCheckVersion = false;
			phead.mCmd = MSG_NEW_VERSION_REQ;
			memset(mDataBuf, 0, sizeof(mDataBuf));
			memcpy(mDataBuf, &phead, sizeof(PACKET_HEAD));
			OnSend(mDataBuf);
		}
		break;
	case MSG_NEW_VERSION_REQ:
		cout << "새로운 파일 확인" << endl;
		SetFile(_ptr);
		break;
	case MSG_PAYMENT_REQ:
		memset(&puser, 0, sizeof(PACKET_USERINFO));
		memcpy(&puser, mDataBuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERINFO));
		if (puser.mMoney == -1)
		{
			cout << "결제 실패 보유 머니 확인 바람" << endl;
		}
		else
		{
			cout << "현재 남은 금액은  " << puser.mMoney << endl;
		}
		break;
	case MSG_RECHARGE_REQ:
		cout << "충전 완료" << endl;

		break;

	}
}
bool cUser::CheckUser(int _check)
{
	if (_check >= 0)
	{
		puser.mMoney = _check;
		return true;
		
	}
	else
	{
		cout << "비밀 번호 또는 등록된 회원이 아닙니다." << endl;

		return false;
	}
}
void cUser::InputUserData()
{
	char* p = mDataBuf;
	cout << " ID  - input" << endl;
	cin >> mName;
	cout << "PASSWORD -input " << endl;
	cin >> mPassword;
	memset(&puser,0 ,sizeof(puser));
	memcpy(puser.mName, mName, sizeof(puser.mName));
	puser.mPassword = mPassword;

	memcpy(p+sizeof(PACKET_HEAD), &puser, sizeof(PACKET_USERINFO));
	OnSend(mDataBuf);

}
bool cUser::VersionCheck()
{
	phead.mCmd = MSG_CHECK_VERSION_REQ;
	memset(mDataBuf, 0, sizeof(mDataBuf));
	memcpy(mDataBuf, &phead, sizeof(PACKET_HEAD));
	OnSend(mDataBuf);
	OnRecv();
	if (mCheckVersion)
	{
		mtree.getFileData();
		return true;
	}
	else
		return false;
	
}
bool cUser::ShowSubwayMenu()
{
	int choice;
	int order;
	cout << "1. 길찾기 " << endl;
	cout << "2. 돈 충전 " << endl;
	cout << "3. 나가기 " << endl;
	
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << " 길 찾기" << endl;
		
		while (1)
		{
			mtree.FindNode();
			cout << "결제 하시겠습니까?  yes=1/no=0/ replay =2" << endl;
			cin >> order;
			if (order == 1)
			{
				mSubwayPrice=  mtree.getPrice();
				memset(mDataBuf, 0, sizeof(BUFFER_SIZE));
				phead.mCmd = MSG_PAYMENT_REQ;
				memcpy(mDataBuf, &phead, sizeof(PACKET_HEAD));
				puser.mMoney = mSubwayPrice;
				memcpy(mDataBuf + sizeof(PACKET_HEAD), &puser, sizeof(PACKET_USERINFO));
				OnSend(mDataBuf);
				OnRecv();
				break;
			}
			else if (order == 0)
			{
				break;
			}
			else if(order ==2)
			{
				continue;
			}
			else
			{
				cout << "잘못된 숫자 입력" << endl;
			}
		}
		break;
	case 2:
		cout << " 돈 충전" << endl;
		RechargeMoney();
		break;
	case 3:
	 
		return false;
		break;
	default:
		break;
	}
}
void cUser::RechargeMoney()
{
	int money;
	cout << "얼마를 충전하시겠습니까? " << endl;
	cin >> money;
	phead.mCmd = MSG_RECHARGE_REQ;
	puser.mMoney =puser.mMoney+ money;
	memcpy(mDataBuf, &phead, sizeof(PACKET_HEAD));
	memcpy(mDataBuf + sizeof(PACKET_HEAD), &puser, sizeof(PACKET_USERINFO));

	OnSend(mDataBuf);
	OnRecv();
}
void cUser::SetFile(char* _ptr)
{
	PACKET_FILE pfile;
	mTextfile = fopen("textfile.txt", "wb");
	memcpy(&pfile, _ptr + sizeof(PACKET_HEAD), sizeof(PACKET_FILE));
	fwrite(pfile.Fdata, 1, pfile.Fbytes, mTextfile);
	cout << pfile.Fbytes << endl;
	fclose(mTextfile);
}
void cUser::InSUBWAY()
{
	
	system("cls");
	
	cout << " sub way 실행" << endl;
	while (mSubwayPlay)
	{
		if (!VersionCheck())
		{
			cout << "파일 버전이 다릅니다." << endl; // 파일 데이터 요청 
			OnRecv();
			 
			continue;
		}

		else
		{
			if (!ShowSubwayMenu())
			{
				cout << "메인 메뉴로 돌아 갑니다." << endl;
				break;
			}
			

		}


	}
	

}
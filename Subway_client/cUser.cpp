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
	 
	cout << "1. ȸ�� ����" << endl;
	cout << "2. �α���" << endl;
	cout << "3. ������" << endl;
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
		cout << " �ǹ� ���� ���� �Դϴ�." << endl;
			 
	}
	 
}
void cUser::RecvParsing(int _pasingnum, char* _ptr)
{
	int idata;
	switch (_pasingnum)
	{
	case MSG_NEW_USER_REQ:
		cout << "ȸ�� ���� �Ϸ�" << endl;
		break;
	case MSG_CHECK_USER_REQ:
		cout << "���� Ȯ��" << endl;
		PACKET_USER_CHECK pusercheck;
	
		memcpy(&pusercheck, _ptr + sizeof(PACKET_HEAD), sizeof(PACKET_USER_CHECK));
		cout <<"recv check = " << pusercheck.mCheck << endl;
		if (CheckUser(pusercheck.mCheck))
		{
			InSUBWAY();
		}
		
		break;
	case MSG_CHECK_VERSION_REQ:
		cout << "���� Ȯ��" << endl;
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
		cout << "���ο� ���� Ȯ��" << endl;
		SetFile(_ptr);
		break;
	case MSG_PAYMENT_REQ:
		memset(&puser, 0, sizeof(PACKET_USERINFO));
		memcpy(&puser, mDataBuf + sizeof(PACKET_HEAD), sizeof(PACKET_USERINFO));
		if (puser.mMoney == -1)
		{
			cout << "���� ���� ���� �Ӵ� Ȯ�� �ٶ�" << endl;
		}
		else
		{
			cout << "���� ���� �ݾ���  " << puser.mMoney << endl;
		}
		break;
	case MSG_RECHARGE_REQ:
		cout << "���� �Ϸ�" << endl;

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
		cout << "��� ��ȣ �Ǵ� ��ϵ� ȸ���� �ƴմϴ�." << endl;

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
	cout << "1. ��ã�� " << endl;
	cout << "2. �� ���� " << endl;
	cout << "3. ������ " << endl;
	
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << " �� ã��" << endl;
		
		while (1)
		{
			mtree.FindNode();
			cout << "���� �Ͻðڽ��ϱ�?  yes=1/no=0/ replay =2" << endl;
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
				cout << "�߸��� ���� �Է�" << endl;
			}
		}
		break;
	case 2:
		cout << " �� ����" << endl;
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
	cout << "�󸶸� �����Ͻðڽ��ϱ�? " << endl;
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
	
	cout << " sub way ����" << endl;
	while (mSubwayPlay)
	{
		if (!VersionCheck())
		{
			cout << "���� ������ �ٸ��ϴ�." << endl; // ���� ������ ��û 
			OnRecv();
			 
			continue;
		}

		else
		{
			if (!ShowSubwayMenu())
			{
				cout << "���� �޴��� ���� ���ϴ�." << endl;
				break;
			}
			

		}


	}
	

}
#ifndef Direc_H
#define Direc_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Treecomm.h"

//��Ʈ�� ������ ��� �� ������(�� ��ġ) ������ ����ϴ� Ŭ����.
//�� Ŭ������ �ٽ��� �Ʒ��� ���ǵ� 16�� �Լ��� ��� �������� �迭�� ���� ������ �� �ְ� �ϴ� ���̴�.
//���� ���̻� ������Ʈ�� ������ �ʰ� Direc::Action �迭�� ���� ������ �� �ִ�.
//���̻� Ŭ������ ������Ʈ�� ������ �ʿ䰡 ����.
class Direc {
	//private:
	//������ static �ƴ� ����.
	//char (*actionLocus)();
	
	public:
	//������
	Direc(){
	}
	
	//�Ҹ��� 
	~Direc(){
	}
			
	#ifndef __NoNeedMonitor
	//������� ��ġ�� �޾� ��Ʈ������ ���� �Լ�
	static const char *toString(const char direc){
		switch (direc){
			case 0:
				return "No Direction";
			case 1:
				return "North";
			case 2:
				return "East";
			case 3:
				return "North East";
			case 4:
				return "South";
			case 5:
				return "North South";
			case 6:
				return "East South";
			case 7:
				return "North East South";
			case 8:
				return "West";
			case 9:
				return "North West";
			case 10:
				return "East West";
			case 11:
				return "North East West";
			case 12:
				return "South West";
			case 13:
				return "North South West";
			case 14:
				return "East South West";
			case 15:
				return "North East South West";
		}
	}
	#endif

	// �� ������ ���� �� �ִ� ��Ʈ�� ������ ���� �����ϰ� ������(�� ��ġ)�� �����ϴ� �Լ���
	static char toLocus(); // �ƹ� ���⵵ �� �� ���� ��: (�ϴ¼� ���� ������ ���Ѵ�)
	static char toLocusNorth(); // ���ʸ� ������ ��� 
	static char toLocusEast(); // ���ʸ� ������ ��� 
	static char toLocusNorthEast(); // ���ʰ� ������ ������ ���. ���� ����. 
	static char toLocusSouth();
	static char toLocusNorthSouth();
	static char toLocusEastSouth();
	static char toLocusNorthEastSouth();
	static char toLocusWest();
	static char toLocusNorthWest();
	static char toLocusEastWest();
	static char toLocusNorthEastWest();
	static char toLocusSouthWest();
	static char toLocusNorthSouthWest();
	static char toLocusEastSouthWest();
	static char toLocusNorthEastSouthWest(); //������
	
	//�� �Լ����� �����͸� ���������� ���� �迭 
	typedef char (*ActionType)();
	static const ActionType Action[16];
};
#endif

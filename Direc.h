#ifndef Direc_H
#define Direc_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//��Ʈ�� ������ ��� �� ������(�� ��ġ) ������ ����ϴ� Ŭ����
//�� Ŭ������ �ٽ��� �Ʒ��� ���ǵ� 16�� �Լ��� ��� �����͸� ���� ������ �� �ְ� �ϴ� ���̴�.
//�Ʒ� 16�� �Լ��� ���� �ϳ��� �����ϴ� 16���� Direc ������Ʈ�� �����.
//�� ������Ʈ 16���� ���������� ��� ���� 16�� �迭�� ����� ���� �ٽ��̴�. 
class Direc {
	private:
	//������ static �ƴ� ����.
	//char (*actionLocus)();
	
	public:
	//������
	Direc(){
	}
	
	//�Ҹ��� 
	~Direc(){
	}
	
	//�Ʒ��� ������ static �Լ��� �������̴�. 
	//�����
	static const char Direct = 0; // �ƹ� ���⵵ �Ұ����Ѱ�� 
	static const char DirectNorth = 1; // ���ʸ� ������ ��� 
	static const char DirectEast = 2; // ���ʸ� ������ ��� 
	static const char DirectNorthEast = 3; // ���ʰ� ������ ������ ���. ���� ����. 
	static const char DirectSouth = 4;
	static const char DirectNorthSouth = 5;
	static const char DirectEastSouth = 6;
	static const char DirectNorthEastSouth = 7;
	static const char DirectWest = 8;
	static const char DirectNorthWest = 9;
	static const char DirectEastWest = 10;
	static const char DirectNorthEastWest = 11;
	static const char DirectSouthWest = 12;
	static const char DirectNorthSouthWest = 13;
	static const char DirectEastSouthWest = 14;
	static const char DirectNorthEastSouthWest = 15; //������

	//������� Complement, �� �� ���� �ִ� 
	static const char NotDirect = 15; // �ƹ� ���⵵ �Ұ����Ѱ�� 
	static const char NotDirectNorth = 14; // ���ʸ� ������ ��� 
	static const char NotDirectEast = 13; // ���ʸ� ������ ��� 
	static const char NotDirectNorthEast = 12; // ���ʰ� ������ ������ ���. ���� ����. 
	static const char NotDirectSouth = 11;
	static const char NotDirectNorthSouth = 10;
	static const char NotDirectEastSouth = 9;
	static const char NotDirectNorthEastSouth = 8;
	static const char NotDirectWest = 7;
	static const char NotDirectNorthWest = 6;
	static const char NotDirectEastWest = 5;
	static const char NotDirectNorthEastWest = 4;
	static const char NotDirectSouthWest = 3;
	static const char NotDirectNorthSouthWest = 2;
	static const char NotDirectEastSouthWest = 1;
	static const char NotDirectNorthEastSouthWest = 0; //������
	
	//�� ������ �ش��ϴ� �����ڰ� �����ϴ� ��Ʈ ���� 
	static const char GeneNorth = 0;
	static const char GeneEast = 1;
	static const char GeneSouth = 2;
	static const char GeneWest = 3;
		
	//������� ��ġ�� �޾� ��Ʈ������ ���� �Լ�
	#ifndef __NoNeedMonitor
	static const char * toString(const char direc){
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
	
	typedef char (*TypeAction)();
	static const TypeAction Action[16];
};
#endif

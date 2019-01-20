#ifndef Collis_H
#define Collis_H

#include <stdio.h>
#include <stdlib.h>

// �浹�� �����ϴ� Ŭ����. �� Ŭ������ ������Ʈ�� ������ �ʴ´�.
// static �ƴ� ������ �Լ��� ����. 
class Collis{
	public:
	//������
	Collis();

	//�Ҹ��� 
	~Collis();

	//�� ������ �ش��ϴ� �����ڰ� �����ϴ� ��Ʈ ����
	static const char GeneNorth = 0;
	static const char GeneEast  = 1;
	static const char GeneSouth = 2;
	static const char GeneWest  = 3;


	//�浹�� ����. ��ġ�� ������ ū �浹�̴�
	static const char Zero = 0; //�浹�� ���� 
	static const char A = 1; // ��Ʈ-��Ʈ �밢�� �浹 
	static const char B = 2; // ��Ʈ-��Ʈ �¿���� �⵿ 
	static const char C = 3; // ��Ʈ-��Ʈ ������ġ �浹 
	static const char D = 4; // ��Ʈ-���� ������ġ �浹
		
	//�浹�� ���� 
	static const char Collis01 [4][4]; //�ι�° ������ ù��° ������ X= 0, Y= 1 ���� 
	static const char Collis02 [4][4]; //�ι�° ������ ù��° ������ X= 0, Y= 2 ����
	static const char Collis03 [4][4]; //�ι�° ������ ù��° ������ X= 0, Y= 3 ����
	static const char Collis13n[4][4]; //�ι�° ������ ù��° ������ X= 1, Y=-3 ����
	static const char Collis12n[4][4]; //�ι�° ������ ù��° ������ X= 1, Y=-2 ����
	static const char Collis11n[4][4]; //�ι�° ������ ù��° ������ X= 1, Y=-1 ����
	static const char Collis10 [4][4]; //�ι�° ������ ù��° ������ X= 1, Y= 0 ����
	static const char Collis11 [4][4]; //�ι�° ������ ù��° ������ X= 1, Y= 1 ����
	static const char Collis12 [4][4]; //�ι�° ������ ù��° ������ X= 1, Y= 2 ����
	static const char Collis13 [4][4]; //�ι�° ������ ù��° ������ X= 1, Y= 3 ����
	static const char Collis22n[4][4]; //�ι�° ������ ù��° ������ X= 2, Y=-2 ����
	static const char Collis21n[4][4]; //�ι�° ������ ù��° ������ X= 2, Y=-1 ����
	static const char Collis20 [4][4]; //�ι�° ������ ù��° ������ X= 2, Y= 0 ����
	static const char Collis21 [4][4]; //�ι�° ������ ù��° ������ X= 2, Y= 1 ����
	static const char Collis22 [4][4]; //�ι�° ������ ù��° ������ X= 2, Y= 2 ����
	static const char Collis31n[4][4]; //�ι�° ������ ù��° ������ X= 3, Y=-1 ����
	static const char Collis30 [4][4]; //�ι�° ������ ù��° ������ X= 3, Y= 0 ����
	static const char Collis31 [4][4]; //�ι�° ������ ù��° ������ X= 3, Y= 1 ����
	
	//���� �� ���� ��ǥ�� �޾� �浹 üũ �ʿ伺�� �����ϰ�, �浹�� (char [4][4])�� �ּҸ� ���� 
	static const char (*toGetCollisMap (const char kX, const char kY, const char lX, const char lY))[4]{
		switch (lX - kX) {
			case 0:
				switch (lY - kY) {
					case 1:
						return Collis01;
					case 2:
						return Collis02;
					case 3:
						return Collis03;
					default:
						return NULL; //�浹���� ���� 
				}
			case 1:
				switch (lY - kY) {
					case -3:
						return Collis13n;
					case -2:
						return Collis12n;
					case -1:
						return Collis11n;
					case 0:
						return Collis10;
					case 1:
						return Collis11;
					case 2:
						return Collis12;
					case 3:
						return Collis13;
					default:
						return NULL; //�浹���� ���� 
				}
			case 2:
				switch (lY - kY) {
					case -2:
						return Collis22n;
					case -1:
						return Collis21n;
					case 0:
						return Collis20;
					case 1:
						return Collis21;
					case 2:
						return Collis22;
					default:
						return NULL; //�浹���� ���� 
				}
			case 3:
				switch (lY - kY) {
					case -1:
						return Collis31n;
					case 0:
						return Collis30;
					case 1:
						return Collis31;
					default:
						return NULL; //�浹���� ���� 
				}
			default:
				return NULL;
		}
	}
};

const char Collis::Collis01 [4][4] = {{2,0,0,4}, {4,4,4,4}, {0,0,2,4}, {0,0,0,4}}; //�ι�° ������ ù��° ������ X= 0, Y= 1 ����
const char Collis::Collis02 [4][4] = {{0,0,0,0}, {0,0,0,3}, {0,0,0,0}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 0, Y= 2 ����
const char Collis::Collis03 [4][4] = {{0,0,0,0}, {0,0,0,2}, {0,0,0,0}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 0, Y= 3 ����
const char Collis::Collis13n[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,1,0,0}}; //�ι�° ������ ù��° ������ X= 1, Y=-3 ����
const char Collis::Collis12n[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,2,0,0}, {2,2,0,0}}; //�ι�° ������ ù��° ������ X= 1, Y=-2 ����
const char Collis::Collis11n[4][4] = {{1,0,0,0}, {0,1,0,0}, {1,3,1,0}, {3,1,0,1}}; //�ι�° ������ ù��° ������ X= 1, Y=-1 ����
const char Collis::Collis10 [4][4] = {{4,0,0,0}, {4,2,0,0}, {4,4,4,4}, {4,0,0,2}}; //�ι�° ������ ù��° ������ X= 1, Y= 0 ����
const char Collis::Collis11 [4][4] = {{1,0,0,0}, {3,1,0,1}, {1,0,1,3}, {0,0,0,1}}; //�ι�° ������ ù��° ������ X= 1, Y= 1 ����
const char Collis::Collis12 [4][4] = {{0,0,0,0}, {2,0,0,2}, {0,0,0,2}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 1, Y= 2 ����
const char Collis::Collis13 [4][4] = {{0,0,0,0}, {0,0,0,1}, {0,0,0,0}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 1, Y= 3 ����
const char Collis::Collis22n[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,1,0,0}, {1,0,0,0}}; //�ι�° ������ ù��° ������ X= 2, Y=-2 ����
const char Collis::Collis21n[4][4] = {{0,0,0,0}, {0,0,0,0}, {2,2,0,0}, {2,0,0,0}}; //�ι�° ������ ù��° ������ X= 2, Y=-1 ����
const char Collis::Collis20 [4][4] = {{0,0,0,0}, {0,0,0,0}, {3,0,0,0}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 2, Y= 0 ����
const char Collis::Collis21 [4][4] = {{0,0,0,0}, {2,0,0,0}, {2,0,0,2}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 2, Y= 1 ����
const char Collis::Collis22 [4][4] = {{0,0,0,0}, {1,0,0,0}, {0,0,0,1}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 2, Y= 2 ����
const char Collis::Collis31n[4][4] = {{0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 3, Y=-1 ����
const char Collis::Collis30 [4][4] = {{0,0,0,0}, {0,0,0,0}, {2,0,0,0}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 3, Y= 0 ����
const char Collis::Collis31 [4][4] = {{0,0,0,0}, {0,0,0,0}, {1,0,0,0}, {0,0,0,0}}; //�ι�° ������ ù��° ������ X= 3, Y= 1 ����

//������
Collis::Collis(){
}

//�Ҹ���
Collis::~Collis(){
}

#endif

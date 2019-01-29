#ifndef Collis_H
#define Collis_H

#include <stdio.h>
#include <stdlib.h>

#include "Treecomm.h"

// �浹�� �����ϴ� Ŭ����. �� Ŭ������ ������Ʈ�� ������ �ʴ´�.
// static �ƴ� ������ �Լ��� ����. 
class Collis{
	public:
	//������
	Collis();

	//�Ҹ��� 
	~Collis();
	
	typedef const char HalfMapType;
	typedef HalfMapType &HalfMapReferenceType;
	typedef HalfMapType *HalfMapPointerType;
	typedef HalfMapType HalfMapArrayType[4];
	
	typedef HalfMapArrayType MapType;
	typedef HalfMapArrayType &MapReferenceType;
	typedef MapType MapArrayType[4];
	typedef MapType *MapPointerType;

	//�浹�� ���� 
	static MapArrayType Collis01; //�ι�° ������ ù��° ������ X= 0, Y= 1 ���� 
	static MapArrayType Collis02; //�ι�° ������ ù��° ������ X= 0, Y= 2 ����
	static MapArrayType Collis03; //�ι�° ������ ù��° ������ X= 0, Y= 3 ����
	static MapArrayType Collis13n; //�ι�° ������ ù��° ������ X= 1, Y=-3 ����
	static MapArrayType Collis12n; //�ι�° ������ ù��° ������ X= 1, Y=-2 ����
	static MapArrayType Collis11n; //�ι�° ������ ù��° ������ X= 1, Y=-1 ����
	static MapArrayType Collis10; //�ι�° ������ ù��° ������ X= 1, Y= 0 ����
	static MapArrayType Collis11; //�ι�° ������ ù��° ������ X= 1, Y= 1 ����
	static MapArrayType Collis12; //�ι�° ������ ù��° ������ X= 1, Y= 2 ����
	static MapArrayType Collis13; //�ι�° ������ ù��° ������ X= 1, Y= 3 ����
	static MapArrayType Collis22n; //�ι�° ������ ù��° ������ X= 2, Y=-2 ����
	static MapArrayType Collis21n; //�ι�° ������ ù��° ������ X= 2, Y=-1 ����
	static MapArrayType Collis20; //�ι�° ������ ù��° ������ X= 2, Y= 0 ����
	static MapArrayType Collis21; //�ι�° ������ ù��° ������ X= 2, Y= 1 ����
	static MapArrayType Collis22; //�ι�° ������ ù��° ������ X= 2, Y= 2 ����
	static MapArrayType Collis31n; //�ι�° ������ ù��° ������ X= 3, Y=-1 ����
	static MapArrayType Collis30; //�ι�° ������ ù��° ������ X= 3, Y= 0 ����
	static MapArrayType Collis31; //�ι�° ������ ù��° ������ X= 3, Y= 1 ����
	
	//���� �� ���� ��ǥ�� �޾� �浹 üũ �ʿ伺�� �����ϰ�, �浹�� (char [4][4])�� �ּҸ� ���� 
	static MapPointerType toGetCollisMap(const TreeCoordinate treeK, const TreeCoordinate treeL);
};

#endif

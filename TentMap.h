#ifndef TentMap_H
#define TentMap_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Treecomm.h"
#include "Direc.h"
#include "TentMap.h"
#include "Collis.h"

// Ǯ��� �ϴ� ������ ���� Ŭ����
class TentMap {
	public:
	//������
	//������ ���簢���� ���� �Ǵ� ���� ũ��
	char Size;
	
	// ���� ����
	char NumberTrees;
	
	// ������ ���簢������ ��Ÿ�� �׸���. size * size �迭.
	char **Map;
	
	// ���ο� �Ǵ� ���ο��� �־�� �ϴ� ��Ʈ�� ��
	char *Col; //����
	char *Row; //����		
	
	//���������� x, y ��ǥ�� ���� �迭
	TreeCoordinate *Tree;
	
	// �� ������ ���� �� �ִ� ��Ʈ�� ����� ���� �迭
	char *TreeDirection;
	
	//�浹üũ�ؾ� �ϴ� �������� �ְ� �� �浹 ����
	TreeCheck *TreeChecker;
	
	// �� �ֵ��� ����
	char NumberTreeCheck;
	
	//�Լ���
	//K��° ������ �����ڸ� ���� ��Ʈ�� X, Y��ǥ�� ��� �Լ�
	void toGetTentXY(const char k, const char locus, char *const tentX, char *const tentY) const;
	
	//������. ���� �����͸� ������ �ʴ´�
	TentMap();
	
	//�б�
	void toReadFromCSV(const char *const filename);
	
	//�Ҹ���
	~TentMap();
};

#endif

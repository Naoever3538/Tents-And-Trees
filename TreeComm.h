#ifndef TreeComm_H
#define TreeComm_H
// �������� ����ϴ� ����ü �� enum class�� ���� ����

//Ÿ���� ����
typedef const char CollisHalfMapType;
typedef CollisHalfMapType &CollisHalfMapReferenceType;
typedef CollisHalfMapType *CollisHalfMapPointerType;
typedef CollisHalfMapType CollisHalfMapArrayType[4];

typedef CollisHalfMapArrayType CollisMapType;
typedef CollisMapType &CollisMapReferenceType;
typedef CollisMapType *CollisMapPointerType;
typedef CollisMapType CollisMapArrayType[4];

//����ü 
// �������� ��ǥ
struct TreeCoordinate{
	public:
	char X; // ���ΰ� x��ǥ�̰� 
	char Y; // ���ΰ� y��ǥ�̴�. �Ϲ����� ��ǥ�Կ� �ٸ��Ƿ� ����.
	
	//������ 
	TreeCoordinate() : X(0), Y(0){
	}
	 
	//�Ҹ���
	~TreeCoordinate(){
	}
};


// �������� �浹üũ 
class TreeCheck{
	public:
	char K; // üũ�ؾ��� �� ���� �� �� ������ ��ȣ 
	char L; // üũ�ؾ��� �� ���� �� �� ������ ��ȣ. �ݵ�� K < L �̾�� �Ѵ�.
	CollisMapPointerType CollisMap; //�浹üũ
	
	
	//������
	TreeCheck() : K(0), L(0), CollisMap(nullptr){
	}

	//�Ҹ���
	~TreeCheck(){
	}

	//���� 
	CollisMapReferenceType operator[](const int i) const{
		return CollisMap[i];
	}
};

//enum class
//�����
enum class EnumDirec : char{
	Null = 0, // �ƹ� ���⵵ �Ұ����Ѱ�� 
	North = 1, // ���ʸ� ������ ��� 
	East = 2, // ���ʸ� ������ ��� 
	NorthEast = 3, // ���ʰ� ������ ������ ���. ���� ����. 
	South = 4,
	NorthSouth = 5,
	EastSouth = 6,
	NorthEastSouth = 7,
	West = 8,
	NorthWest = 9,
	EastWest = 10,
	NorthEastWest = 11,
	SouthWest = 12,
	NorthSouthWest = 13,
	EastSouthWest = 14,
	NorthEastSouthWest = 15, //������

	//������� Complement, �� �� ���� �ִ� 
	NotNull = 15, // �ƹ� ���⵵ �Ұ����Ѱ�� 
	NotNorth = 14, // ���ʸ� ������ ��� 
	NotEast = 13, // ���ʸ� ������ ��� 
	NotNorthEast = 12, // ���ʰ� ������ ������ ���. ���� ����. 
	NotSouth = 11,
	NotNorthSouth = 10,
	NotEastSouth = 9,
	NotNorthEastSouth = 8,
	NotWest = 7,
	NotNorthWest = 6,
	NotEastWest = 5,
	NotNorthEastWest = 4,
	NotSouthWest = 3,
	NotNorthSouthWest = 2,
	NotEastSouthWest = 1,
	NotNorthEastSouthWest = 0 //������
};

//�� ������ �ش��ϴ� �����ڰ� �����ϴ� ��Ʈ ���� 
enum class EnumGene: char{
	North = 0,
	East = 1,
	South = 2,
	West = 3
};

//�浹�� ����. ��ġ�� ������ ū �浹�̴�
enum class EnumCollis: char{
	Zero = 0, //�浹�� ���� 
	A = 1, // ��Ʈ-��Ʈ �밢�� �浹 
	B = 2, // ��Ʈ-��Ʈ �¿���� �⵿ 
	C = 3, // ��Ʈ-��Ʈ ������ġ �浹
	D = 4 // ��Ʈ-���� ������ġ �浹
};
#endif

#ifndef TreeComm_H
#define TreeComm_H
// 공통으로 사용하는 구조체 및 enum class를 담은 파일

//타입의 정의
typedef const char CollisHalfMapType;
typedef CollisHalfMapType &CollisHalfMapReferenceType;
typedef CollisHalfMapType *CollisHalfMapPointerType;
typedef CollisHalfMapType CollisHalfMapArrayType[4];

typedef CollisHalfMapArrayType CollisMapType;
typedef CollisMapType &CollisMapReferenceType;
typedef CollisMapType *CollisMapPointerType;
typedef CollisMapType CollisMapArrayType[4];

//구조체 
// 나무들의 좌표
struct TreeCoordinate{
	public:
	char X; // 가로가 x좌표이고 
	char Y; // 세로가 y좌표이다. 일반적인 좌표게와 다르므로 주의.
	
	//생성자 
	TreeCoordinate() : X(0), Y(0){
	}
	 
	//소멸자
	~TreeCoordinate(){
	}
};


// 나무들의 충돌체크 
class TreeCheck{
	public:
	char K; // 체크해야할 두 나무 중 앞 나무의 번호 
	char L; // 체크해야할 두 나무 중 뒤 나무의 번호. 반드시 K < L 이어야 한다.
	CollisMapPointerType CollisMap; //충돌체크
	
	
	//생성자
	TreeCheck() : K(0), L(0), CollisMap(nullptr){
	}

	//소멸자
	~TreeCheck(){
	}

	//접근 
	CollisMapReferenceType operator[](const int i) const{
		return CollisMap[i];
	}
};

//enum class
//방향들
enum class EnumDirec : char{
	Null = 0, // 아무 방향도 불가능한경우 
	North = 1, // 북쪽만 가능한 경우 
	East = 2, // 동쪽만 가능한 경우 
	NorthEast = 3, // 북쪽과 동쪽이 가능한 경우. 이하 같다. 
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
	NorthEastSouthWest = 15, //모든방향

	//방향들의 Complement, 다 쓸 데가 있다 
	NotNull = 15, // 아무 방향도 불가능한경우 
	NotNorth = 14, // 북쪽만 가능한 경우 
	NotEast = 13, // 동쪽만 가능한 경우 
	NotNorthEast = 12, // 북쪽과 동쪽이 가능한 경우. 이하 같다. 
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
	NotNorthEastSouthWest = 0 //모든방향
};

//각 나무에 해당하는 유전자가 지시하는 텐트 방향 
enum class EnumGene: char{
	North = 0,
	East = 1,
	South = 2,
	West = 3
};

//충돌의 종류. 수치가 높으면 큰 충돌이다
enum class EnumCollis: char{
	Zero = 0, //충돌이 없다 
	A = 1, // 텐트-텐트 대각선 충돌 
	B = 2, // 텐트-텐트 좌우상하 출동 
	C = 3, // 텐트-텐트 동일위치 충돌
	D = 4 // 텐트-나무 동일위치 충돌
};
#endif

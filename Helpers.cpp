#include "Helpers.h"


void ReadDataFromFile(LPCWSTR filename, byte** data, UINT* size) {

	using namespace Microsoft::WRL;

	CREATEFILE2_EXTENDED_PARAMETERS extendedParams = {};
	extendedParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
	extendedParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
	extendedParams.dwFileFlags = FILE_FLAG_SEQUENTIAL_SCAN;
	extendedParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
	extendedParams.lpSecurityAttributes = nullptr;
	extendedParams.hTemplateFile = nullptr;

	Wrappers::FileHandle file(CreateFile2(filename, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, &extendedParams));
	if (file.Get() == INVALID_HANDLE_VALUE) Error(L"Shader Load Error", filename);

	FILE_STANDARD_INFO fileInfo = {};
	if (!GetFileInformationByHandleEx(file.Get(), FileStandardInfo, &fileInfo, sizeof(fileInfo))) Error(L"Shader Load Error", filename);

	if (fileInfo.EndOfFile.HighPart != 0) throw std::exception();
	*data = reinterpret_cast<byte*>(malloc(fileInfo.EndOfFile.LowPart));
	*size = fileInfo.EndOfFile.LowPart;
	if (!ReadFile(file.Get(), *data, fileInfo.EndOfFile.LowPart, nullptr, nullptr)) Error(L"Shader Load Error", filename);



}

void Error(LPCWSTR header, LPCWSTR info){

	MessageBox(NULL, info, header, NULL);
	PostMessage(ghWnd, WM_CLOSE, NULL, NULL);
	//DestroyWindow(ghWnd);
	
}

bool IntersectsFloat(XMFLOAT4 & rectA, XMFLOAT4 & rectB) {

	return (rectA.z > rectB.x && rectA.x < rectB.z &&
		rectA.w > rectB.y && rectA.y < rectB.w);


}

bool AABBIntersect2D(XMFLOAT4& rectA, XMFLOAT3 & pos, XMFLOAT3 & vel, XMFLOAT4& rectB) {
	//Intersect(p->collision, p->velocity, p->position);


	return 0;



}





bool InRange(float value, float min, float max) {
	return (value >= min) && (value <= max);
}



float PercentToFloat(float p, float d) {


	float percPoint = (p / 100) * d;

	//screenPos.x = Input.pos2D.x / Input.pos2D.w / 2.0f + 0.5f;
	//screenPos.y = -Input.pos2D.y / Input.pos2D.w / 2.0f + 0.5f;
	return percPoint;

}


double GetNormalDist(double x, double y) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::normal_distribution<float> distribution(x, y);

	return distribution(generator);

}

double GetRealDist(double x, double y) {


	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<float>  distribution(x, y);
	return distribution(generator);


}

XMFLOAT3 GetDistanceVector2d(XMFLOAT3 position, XMFLOAT3 target) {

	XMFLOAT3 temp;
	temp.x = target.x - position.x;
	temp.y = target.y - position.y;
	temp.z = target.z - position.z;
	return temp;
}

XMFLOAT3 BasicTween(XMFLOAT3& position, XMFLOAT3 target, float ease) {

	XMFLOAT3 distance = GetDistanceVector2d(position, target);
	XMFLOAT3 velocity;
	velocity.x = distance.x * ease;
	velocity.y = distance.y * ease;
	velocity.z = distance.z * ease;
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;

	return position;

}



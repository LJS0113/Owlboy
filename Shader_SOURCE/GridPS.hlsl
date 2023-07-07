#include "globals.hlsli"

// VSIn은 버텍스셰이더로 들어오는 정보.(정점데이터)
struct VSIn
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

// VSOut은 나가는 데이터. 
struct VSOut
{
	// SV_POSITION은 무조건 float4로 맞춰줘야함. 3으로 하니까 오류났음.
    float4 Pos : SV_Position;
    float2 UV : TEXCOORD;
    float2 GridPos : POSITION;
};

float4 main(VSOut In) : SV_TARGET
{
	float4 Out = float4(1.0f, 0.0f, 1.0f, 1.0f);
    
    const int width = 100;
    const int Height = 100;
    
    int gridX = (int) In.GridPos.x;
    int gridY = (int) In.GridPos.y;
    
    if(abs((gridX+1) % width) <= 1.0f)
        return Out;
    if (abs((gridY + 1) % Height) <= 1.0f)
        return Out;
    
    discard;
    
    return Out;
}
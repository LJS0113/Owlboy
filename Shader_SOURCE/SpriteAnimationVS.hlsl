#include "globals.hlsli"

// VSIn은 버텍스셰이더로 들어오는 정보.(정점데이터)
struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

// VSOut은 나가는 데이터. 
struct VSOut
{
	// SV_POSITION은 무조건 float4로 맞춰줘야함. 3으로 하니까 오류났음.
    float4 Pos : SV_Position;
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};



VSOut main(VSIn In)
{
	// 0.0f로 모든값 초기화.
    VSOut Out = (VSOut) 0.0f;
    float4 world = mul(float4(In.Pos, 1.0f), WorldMatrix);
    float4 view = mul(world, ViewMatrix);
    float4 proj = mul(view, ProjectionMatrix);
    
    Out.Pos = proj;
    Out.WorldPos = world.xyz;
    Out.Color = In.Color;
    Out.UV = In.UV;

    return Out;
}
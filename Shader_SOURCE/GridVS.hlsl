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

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
    float2 gridPos = float2(0.0f, 0.0f);
    gridPos.x = In.Pos.x * 1.0f * Resolution.x + CameraPosition.x * CameraScale.x;
    gridPos.y = In.Pos.y * 1.0f * Resolution.y + CameraPosition.y * CameraScale.y;
    
    const float meshScale = 2.0f;
    Out.Pos = float4(In.Pos.xy * meshScale, 0.999f, 1.0f);
    Out.UV = In.UV;
    Out.GridPos = gridPos;
    
    return Out;
}
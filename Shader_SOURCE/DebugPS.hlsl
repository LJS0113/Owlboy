#include "globals.hlsli"


struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};



float4 main(VSOut In) : SV_TARGET
{
    float4 color = float4(0.0f, 1.0f, 0.0f, 1.0f);
    // 0이면 충돌X
    if(collision == 0)
    {
        color = float4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    // 1이면 충돌O
    else if(collision == 1)
    {
        color = float4(1.0f, 0.0f, 0.0f, 1.0f);
    }

    return color;
}
#include "globals.hlsli"

// VSIn�� ���ؽ����̴��� ������ ����.(����������)
struct VSIn
{
	float3 Pos : POSITION;
	float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

// VSOut�� ������ ������. 
struct VSOut
{
	// SV_POSITION�� ������ float4�� ���������. 3���� �ϴϱ� ��������.
	float4 Pos : SV_Position;
	float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

VSOut main(VSIn In) 
{
	// 0.0f�� ��簪 �ʱ�ȭ.
	VSOut Out = (VSOut)0.0f;

	Out.Pos = float4(In.Pos, 1.0f);
    //Out.Pos.x += Position.x;
    //Out.Pos.y += Position.y;
    Out.UV = In.UV;
	Out.Color = In.Color;

	return Out;
}
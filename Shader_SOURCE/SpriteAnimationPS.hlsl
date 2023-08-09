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
    float3 WorldPos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};



float4 main(VSOut In) : SV_TARGET
{
    float4 color = (float4) 0.0f;
    color = albedoTexture.Sample(anisotropicSampler, In.UV);

    if (animationType == 1)
    {
        float2 diff = (AtlasSize - SpriteSize) / 2.0f;
        float2 UV = (SpriteLeftTop - diff - SpriteOffset) + (AtlasSize * In.UV);
        
        if (UV.x < SpriteLeftTop.x || UV.x > SpriteLeftTop.x + SpriteSize.x 
            || UV.y < SpriteLeftTop.y || UV.y > SpriteLeftTop.y + SpriteSize.y)
            discard;
        
        if (reverse == 1)
            UV.x *= -1;
        
        color = atlasTexture.Sample(anisotropicSampler, UV);
    }
    
    if (color.r == 1.0f && color.g == 0.0f && color.b == 1.0f)
        discard;
        
    float4 lightColor = float4(0.2f, 0.2f, 0.2f, 1.0f);
    
    for (int i = 0; i < 2; i++)
    {
        CalculateLight2D(lightColor, In.WorldPos, i);
    }
    
    //color *= lightColor;
    
    if (color.a <= 0.0f)
        discard;
    
    return color;
}
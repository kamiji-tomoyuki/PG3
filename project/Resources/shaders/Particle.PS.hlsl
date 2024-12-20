#include "Particle.hlsli"

struct Material
{
    float4 color;
    int32_t enableLighting;
    float32_t4x4 uvTransform;
};
ConstantBuffer<Material> gMaterial : register(b0);

struct DirectionalLight
{
    float4 color; //ライトの色
    float3 direction; //ライトの向き
    float intensity; //輝度
};

struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};

Texture2D<float4> gTexture : register(t0);
SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    output.color = gMaterial.color * textureColor * input.color;
    
    //output.colorのα値が0のときにPixelを棄却
    if (output.color.a == 0.0)
    {
        discard;
    }
    
    return output;
}
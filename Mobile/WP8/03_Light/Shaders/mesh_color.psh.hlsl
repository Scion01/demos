
//////////////////////////////////////////////////////////////////
//
//  Arturo Cepeda Pérez
//  Game Engine
//
//  Pixel shader (3D mesh without texture)
//
//  --- mesh_color.psh.hlsl ---
//
//////////////////////////////////////////////////////////////////


struct PixelShaderInput
{
   float4 Position : SV_POSITION;
   float4 ObjectColor : COLOR0;
   float3 EyeSpaceVertexNormal : NORMAL0;
   float3 EyeSpaceVertexPosition : POSITION0;
   float3 EyeSpacePointLight1Position : POSITION1;
   float4 AmbientLightColor : COLOR1;
   float AmbientLightIntensity : TEXCOORD0;
   float4 PointLight1Color : COLOR2;
   float PointLight1Intensity : TEXCOORD1;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
   const float fSpecularExponent = 10.0f;

   float3 vColor;
   float fAlpha = input.ObjectColor.w;

   // material properties
   float3 vMaterialDiffuseColor = input.ObjectColor.xyz;
   float3 vMaterialSpecularColor = float3(0.1f, 0.1f, 0.1f);

   // get camera direction vector
   float3 vCameraDirection = normalize(-input.EyeSpaceVertexPosition).xyz;

   //   
   //  Add ambient light
   //
   vColor = (vMaterialDiffuseColor * input.AmbientLightColor.xyz * input.AmbientLightIntensity).xyz;

   //
   //  Add point light
   //   
   float3 vLightColor = input.PointLight1Color.xyz * input.PointLight1Intensity;
   float3 vLightDirection = normalize(input.EyeSpacePointLight1Position - input.EyeSpaceVertexPosition).xyz;
   float3 vHalfPlane = normalize(vLightDirection + vCameraDirection);
      
   float fDiffuseFactor = max(0.0, dot(input.EyeSpaceVertexNormal, vLightDirection));
   float fSpecularFactor = max(0.0, dot(input.EyeSpaceVertexNormal, vHalfPlane));
   fSpecularFactor = pow(fSpecularFactor, fSpecularExponent);
      
   vColor += (vMaterialDiffuseColor * vLightColor * fDiffuseFactor) + (vMaterialSpecularColor * fSpecularFactor);

   return float4(vColor, fAlpha);
}

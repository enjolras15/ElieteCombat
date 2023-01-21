/*
*スクロールする海用のシェーダーです。
*基本的な処理は全部元となったGbufferへの書き込みシェーダーと同じで、
*法線のみ波用に変更しています。
*めちゃくちゃ適当に書いてるのであまり参考にはしないでください。 by 錦織
*/

///////////////////////////////////////
// 構造体。
///////////////////////////////////////

// ピクセルシェーダーへの入力
struct SPSIn
{
    float4 pos : SV_POSITION;       //座標。
    float3 normal : NORMAL;         //法線。
    float3 tangent  : TANGENT;      //接ベクトル。
    float3 biNormal : BINORMAL;     //従ベクトル。
    float2 uv : TEXCOORD0;          //UV座標。
};

// ピクセルシェーダーからの出力
struct SPSOut
{
    float4 albedo : SV_Target0;         // アルベド
    float4 normal : SV_Target1;         // 法線
    float4 metaricShadowSmooth : SV_Target2;  // メタリック、影パラメータ、スムース。rにメタリック、gに影パラメータ、aにスムース。
};

//波のUVをスクロールさせる値
cbuffer ScrollValue : register(b1)
{
    float scrollValue1;
    float scrollValue2;
};

///////////////////////////////////////
// 頂点シェーダーの共通処理をインクルードする。
///////////////////////////////////////

#include "../ModelVSCommon.h"


///////////////////////////////////////
// シェーダーリソース
///////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);      //アルベドマップ
Texture2D<float4> g_normal : register(t1);      //法線マップ
Texture2D<float4> g_spacular : register(t2);    //スペキュラマップ
Texture2D<float4> g_extendNormal1 : register(t11);    //外部読み込み法線マップ1
Texture2D<float4> g_extendNormal2 : register(t12);    //外部読み込み法線マップ2

///////////////////////////////////////
// サンプラーステート
///////////////////////////////////////
sampler g_sampler : register(s0);

///////////////////////////////////////
// 関数
///////////////////////////////////////

// 法線マップから法線を取得。
float3 GetNormalFromNormalMap(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    //波用
     

    //2つの法線マップを合成する。

    //////////調整用の値//////////
    float waveTextureSize = 512.0f;		//波の法線テクスチャのサイズ 法線テクスチャを変更したらそのサイズに合わせる

    float UVRepeat1 = 300.0f;       //UVのループ数 増やすほど細かくループする
    float UVRepeat2 = 100.0f;
    float normalPower = 4.0f;       //法線を強調する強さ
    //////////調整用の値//////////

    //波をスクロールさせる値をピクセルからuv座標に変換
    float uvOffset = scrollValue1 / waveTextureSize;
    //通常のUV座標からオフセット分ずらす。
    float2 scrollUV1 = float2(uv.x + uvOffset,uv.y + uvOffset / 2);
    //UVのループ数を増やす。
    scrollUV1 *= UVRepeat1;
    //UV座標から法線マップをサンプリング
    float3 binSpaceNormal1 = g_extendNormal1.Sample(g_sampler, scrollUV1).xyz;
    //法線の値を-1から1の範囲に復元する。
    binSpaceNormal1 = (binSpaceNormal1 * 2.0f) - 1.0f;
    
    //2つ目の法線マップも同様に法線を計算。
    uvOffset = scrollValue2 / waveTextureSize;
    float2 scrollUV2 = float2(uv.x - uvOffset,uv.y);
    scrollUV2 *= UVRepeat2;
    float3 binSpaceNormal2 = g_extendNormal2.Sample(g_sampler, scrollUV2).xyz;
    binSpaceNormal2 = (binSpaceNormal2 * 2.0f) - 1.0f;

    //2つの法線の値を合成する
    float3 blendedNormal = (binSpaceNormal1 + binSpaceNormal2) / 2;
    //そのままだと波があまり目立たなかったので法線を強調させる。
    blendedNormal *= normalPower;
    
    return blendedNormal;
}



// モデル用の頂点シェーダーのエントリーポイント
SPSIn VSMainCore(SVSIn vsIn, float4x4 mWorldLocal, uniform bool isUsePreComputedVertexBuffer)
{
    SPSIn psIn;
    psIn.pos = CalcVertexPositionInWorldSpace(vsIn.pos, mWorldLocal, isUsePreComputedVertexBuffer);
    psIn.pos = mul(mView, psIn.pos); // ワールド座標系からカメラ座標系に変換
    psIn.pos = mul(mProj, psIn.pos); // カメラ座標系からスクリーン座標系に変換

    // ワールド空間の法線、接ベクトル、従ベクトルを計算する。
    CalcVertexNormalTangentBiNormalInWorldSpace(
		psIn.normal,
		psIn.tangent,
		psIn.biNormal,
		mWorldLocal,
		vsIn.normal,
		vsIn.tangent,
		vsIn.biNormal,
		isUsePreComputedVertexBuffer
	);

    psIn.uv = vsIn.uv;
    
    return psIn;
}
SPSOut PSMainCore( SPSIn psIn, int isShadowReciever)
{
    // G-Bufferに出力
    SPSOut psOut;
    // アルベドカラーと深度値を出力
    psOut.albedo = g_albedo.Sample(g_sampler, psIn.uv);
    
    clip(psOut.albedo.a - 0.2f);    // ピクセルキル

    psOut.albedo.w = psIn.pos.z;
    // 法線を出力
    psOut.normal.xyz = GetNormalFromNormalMap( 
        psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv ) ;
    psOut.normal.w = 1.0f;
    // メタリックスムースを出力。
    psOut.metaricShadowSmooth = g_spacular.Sample(g_sampler, psIn.uv);
    // 影パラメータ。
    psOut.metaricShadowSmooth.g = 255.0f * isShadowReciever;
    
    return psOut;
}
// モデル用のピクセルシェーダーのエントリーポイント
SPSOut PSMain(SPSIn psIn)
{
    return PSMainCore(psIn, 0);
}
SPSOut PSMainShadowReciever(SPSIn psIn)
{
    return PSMainCore(psIn, 1);
}

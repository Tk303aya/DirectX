#include "DirectShader.h"


namespace directx
//{
//void test()
//{
//
//  ////////////////////////////////////////////////////////////
//  // Z値テクスチャとZ値用深度バッファサーフェイスの作成
//  /////
//  // デバイスの深度バッファの幅と高さを取得
//  UINT uiDevZBufWidth;    // デバイスバッファ幅
//  UINT uiDevZBufHeight;   // デバイスバッファ高
//  IDirect3DSurface9 *pTmpSf;
//  cpDev->GetDepthStencilSurface(&pTmpSf);
//  GetSurfaceWH(pTmpSf, uiDevZBufWidth, uiDevZBufHeight);
//  pTmpSf->Release();
//
//  // Z値テクスチャを作成
//  IDirect3DTexture9 *pZBufTex;
//  if (FAILED(D3DXCreateTexture(cpDev.GetPtr(), uiDevZBufWidth, uiDevZBufHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pZBufTex)))
//    return 0;
//  Com_ptr<IDirect3DTexture9> cpZBufTex(pZBufTex);
//  // Z値テクスチャの幅高を保持
//  UINT uiZTexWidth;
//  UINT uiZTexHeight;
//  // Z値テクスチャサーフェイスを保持
//  IDirect3DSurface9 *pZTexSurf;
//  cpZBufTex->GetSurfaceLevel(0, &pZTexSurf);
//  GetSurfaceWH(pZTexSurf, uiZTexWidth, uiZTexHeight);
//
//  // 深度バッファサーフェイスの作成
//  Com_ptr<IDirect3DSurface9> cpZTexZBuf;
//  cpDev->CreateDepthStencilSurface(uiZTexWidth, uiZTexHeight, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, cpZTexZBuf.ToCreator(), NULL);
//
//
//  // Z値をレンダリングするエフェクトの読み込み
//  Com_ptr<ID3DXEffect> cpEffect;
//  if (FAILED(D3DXCreateEffectFromFile(cpDev.GetPtr(), _T("ZValuePlot.fx"), NULL, NULL, 0, NULL, cpEffect.ToCreator(), NULL)))
//    return 0;
//
//
//  // Xファイルオブジェクト読み込み
//  Com_ptr<ID3DXBuffer> cpMatBuf;
//  Com_ptr<ID3DXMesh> cpMesh;
//  DWORD dwMatNum;
//  D3DXMATERIAL *pMatAry;
//  D3DXLoadMeshFromX(_T("Cube2.x"), D3DXMESH_MANAGED, cpDev.GetPtr(), NULL, cpMatBuf.ToCreator(), NULL, &dwMatNum, cpMesh.ToCreator());
//  pMatAry = (D3DXMATERIAL*)cpMatBuf->GetBufferPointer();
//
//  // Z値テクスチャ描画用のスプライト生成
//  Com_ptr<ID3DXSprite> cpSprite;
//  D3DXCreateSprite(cpDev.GetPtr(), cpSprite.ToCreator());
//  float W_Scale = (float)uiDevZBufWidth / uiZTexWidth;   // 貼り付けるZ値テクスチャを画面サイズにする幅高スケール値
//  float H_Scale = (float)uiDevZBufHeight / uiZTexHeight;
//
//
//  // 描画デバイスサーフェイス群を取得保持
//  Com_ptr<IDirect3DSurface9> pDeviceSurf;
//  Com_ptr<IDirect3DSurface9> pDeviceZBufSurf;
//  g_pD3DDev->GetRenderTarget(0, pDeviceSurf.ToCreator());
//  g_pD3DDev->GetDepthStencilSurface(pDeviceZBufSurf.ToCreator())
//}
//
//void loop()
//{
//  ///////////////////////////////////////
//  //■パス1 : Z値テクスチャに描画
//  cpEffect->SetTechnique("ZValuePlotTec");
//  g_pD3DDev->SetRenderTarget(0, pZTexSurf);
//  g_pD3DDev->SetDepthStencilSurface(cpZTexZBuf.GetPtr());
//  g_pD3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);
//  for (z = 0; z<Num; z++)
//  {
//    for (x = 0; x<Num; x++)
//    {
//      cpEffect->Begin(&numPass, 0);
//      cpEffect->BeginPass(0);
//      D3DXMATRIX mat, RotY, RotZ;
//      D3DXMatrixIdentity(&mat);
//      D3DXMatrixRotationY(&RotY, D3DXToRadian(f));
//      D3DXMatrixRotationZ(&RotZ, D3DXToRadian(f*2.353f));
//      mat *= RotY * RotZ;
//      mat._41 = x * 15.0f;  mat._43 = z * 15.0f;
//      mat = mat * View * Proj;
//      cpEffect->SetMatrix("matWorldViewProj", &mat); // ワールドビュー射影変換行列設定
//      for (i = 0; i<dwMatNum; i++)
//        cpMesh->DrawSubset(i);        // メッシュ描画
//      cpEffect->EndPass();
//    }
//  }
//  cpEffect->End();
//
//  //////////////////////////////////////////
//  // ■パス2 : 通常描画＋スプライト描画
//  g_pD3DDev->SetVertexShader(NULL);    // 固定機能パイプラインに処理を戻す
//  g_pD3DDev->SetPixelShader(NULL);
//  g_pD3DDev->SetRenderTarget(0, pDeviceSurf.GetPtr());
//  g_pD3DDev->SetDepthStencilSurface(pDeviceZBufSurf.GetPtr());
//  g_pD3DDev->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(10, 150, 190), 1.0f, 0);
//  for (z = 0; z<Num; z++)
//  {
//    for (x = 0; x<Num; x++)
//    {
//      D3DXMATRIX mat, RotY, RotZ;
//      D3DXMatrixIdentity(&mat);
//      D3DXMatrixRotationY(&RotY, D3DXToRadian(f));
//      D3DXMatrixRotationZ(&RotZ, D3DXToRadian(f*2.353f));
//      mat *= RotY * RotZ;
//      mat._41 = x * 15.0f;  mat._43 = z * 15.0f;
//      mat = mat * View * Proj;
//      g_pD3DDev->SetTransform(D3DTS_WORLD, &mat);
//      for (i = 0; i<dwMatNum; i++)
//      {
//        g_pD3DDev->SetMaterial(&pMatAry[i].MatD3D);
//        cpMesh->DrawSubset(i);
//      }
//    }
//  }
//
//  // Z値テクスチャ適用のスプライト描画
//  D3DXMATRIX SpMat;
//  D3DXMatrixScaling(&SpMat, W_Scale, H_Scale, 1.0f);
//  cpSprite->SetTransform(&SpMat);
//  RECT SpRect;
//  SetRect(&SpRect, 0, 0, (int)((1 + sin(f / 20.0f))*uiZTexWidth / 2.0f), uiZTexHeight);
//  cpSprite->Begin(0);
//  cpSprite->Draw(cpZBufTex.GetPtr(), &SpRect, NULL, NULL, 0xffffffff);
//  cpSprite->End();
//}
}
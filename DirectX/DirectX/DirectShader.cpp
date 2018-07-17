#include "DirectShader.h"


namespace directx
//{
//void test()
//{
//
//  ////////////////////////////////////////////////////////////
//  // Z�l�e�N�X�`����Z�l�p�[�x�o�b�t�@�T�[�t�F�C�X�̍쐬
//  /////
//  // �f�o�C�X�̐[�x�o�b�t�@�̕��ƍ������擾
//  UINT uiDevZBufWidth;    // �f�o�C�X�o�b�t�@��
//  UINT uiDevZBufHeight;   // �f�o�C�X�o�b�t�@��
//  IDirect3DSurface9 *pTmpSf;
//  cpDev->GetDepthStencilSurface(&pTmpSf);
//  GetSurfaceWH(pTmpSf, uiDevZBufWidth, uiDevZBufHeight);
//  pTmpSf->Release();
//
//  // Z�l�e�N�X�`�����쐬
//  IDirect3DTexture9 *pZBufTex;
//  if (FAILED(D3DXCreateTexture(cpDev.GetPtr(), uiDevZBufWidth, uiDevZBufHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &pZBufTex)))
//    return 0;
//  Com_ptr<IDirect3DTexture9> cpZBufTex(pZBufTex);
//  // Z�l�e�N�X�`���̕�����ێ�
//  UINT uiZTexWidth;
//  UINT uiZTexHeight;
//  // Z�l�e�N�X�`���T�[�t�F�C�X��ێ�
//  IDirect3DSurface9 *pZTexSurf;
//  cpZBufTex->GetSurfaceLevel(0, &pZTexSurf);
//  GetSurfaceWH(pZTexSurf, uiZTexWidth, uiZTexHeight);
//
//  // �[�x�o�b�t�@�T�[�t�F�C�X�̍쐬
//  Com_ptr<IDirect3DSurface9> cpZTexZBuf;
//  cpDev->CreateDepthStencilSurface(uiZTexWidth, uiZTexHeight, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, FALSE, cpZTexZBuf.ToCreator(), NULL);
//
//
//  // Z�l�������_�����O����G�t�F�N�g�̓ǂݍ���
//  Com_ptr<ID3DXEffect> cpEffect;
//  if (FAILED(D3DXCreateEffectFromFile(cpDev.GetPtr(), _T("ZValuePlot.fx"), NULL, NULL, 0, NULL, cpEffect.ToCreator(), NULL)))
//    return 0;
//
//
//  // X�t�@�C���I�u�W�F�N�g�ǂݍ���
//  Com_ptr<ID3DXBuffer> cpMatBuf;
//  Com_ptr<ID3DXMesh> cpMesh;
//  DWORD dwMatNum;
//  D3DXMATERIAL *pMatAry;
//  D3DXLoadMeshFromX(_T("Cube2.x"), D3DXMESH_MANAGED, cpDev.GetPtr(), NULL, cpMatBuf.ToCreator(), NULL, &dwMatNum, cpMesh.ToCreator());
//  pMatAry = (D3DXMATERIAL*)cpMatBuf->GetBufferPointer();
//
//  // Z�l�e�N�X�`���`��p�̃X�v���C�g����
//  Com_ptr<ID3DXSprite> cpSprite;
//  D3DXCreateSprite(cpDev.GetPtr(), cpSprite.ToCreator());
//  float W_Scale = (float)uiDevZBufWidth / uiZTexWidth;   // �\��t����Z�l�e�N�X�`������ʃT�C�Y�ɂ��镝���X�P�[���l
//  float H_Scale = (float)uiDevZBufHeight / uiZTexHeight;
//
//
//  // �`��f�o�C�X�T�[�t�F�C�X�Q���擾�ێ�
//  Com_ptr<IDirect3DSurface9> pDeviceSurf;
//  Com_ptr<IDirect3DSurface9> pDeviceZBufSurf;
//  g_pD3DDev->GetRenderTarget(0, pDeviceSurf.ToCreator());
//  g_pD3DDev->GetDepthStencilSurface(pDeviceZBufSurf.ToCreator())
//}
//
//void loop()
//{
//  ///////////////////////////////////////
//  //���p�X1 : Z�l�e�N�X�`���ɕ`��
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
//      cpEffect->SetMatrix("matWorldViewProj", &mat); // ���[���h�r���[�ˉe�ϊ��s��ݒ�
//      for (i = 0; i<dwMatNum; i++)
//        cpMesh->DrawSubset(i);        // ���b�V���`��
//      cpEffect->EndPass();
//    }
//  }
//  cpEffect->End();
//
//  //////////////////////////////////////////
//  // ���p�X2 : �ʏ�`��{�X�v���C�g�`��
//  g_pD3DDev->SetVertexShader(NULL);    // �Œ�@�\�p�C�v���C���ɏ�����߂�
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
//  // Z�l�e�N�X�`���K�p�̃X�v���C�g�`��
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
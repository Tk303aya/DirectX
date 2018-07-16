#include "Direct2D.h"

namespace directx
{
HRESULT Draw2D(LPDIRECT3DVERTEXBUFFER9 buffer, LPDIRECT3DTEXTURE9 texture)
{
  //�QD�`��
  HRESULT hr;
  //�e�N�X�`�����|���S���ɏ������ޕ��@��ݒ�
  //SetTexture�@
  //    ���F�|���S���ɏ������ރe�N�X�`���̃X�e�[�W�ԍ��A�ő�W�o�^�ł���
  //    ���F�ݒ肷��e�N�X�`��
  hr = GetDirectDevice()->SetTexture(0, texture);
  if (FAILED(hr)) return E_FAIL;
  //�|���S���ɏ������ލۂ̌v�Z���@�̐ݒ�
  //SetTextureStageState
  //    ���F�v�Z�����w�肷��e�N�X�`���X�e�[�W�ԍ�
  //    ���F�ݒ肷��e�N�X�`���X�e�[�g�@D3DTEXTURESTAGESTATETYPE�񋓌^�Q��
  //    ��O�F�������ɂ���Ďw�肷��l���قȂ�
  
  //D3DTSS_COLORARG1  �F�̈����P�i�e�N�X�`�����j
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_COLOROP    �F�̉��Z�q 
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_COLORARG2  �F�̈����Q�i�|���S�����j
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_ALPHAARG1  �A���t�@�̈����P�i�e�N�X�`�����j
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_ALPHAOP    �A���t�@�̉��Z�q
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
  if (FAILED(hr)) return E_FAIL;
  //D3DTSS_ALPHAARG2  �A���t�@�̈����Q�i�|���S�����j
  hr = GetDirectDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); // �|���̃��l�𗘗p
  if (FAILED(hr)) return E_FAIL;
  
  // �����_�����O�X�e�[�g
  //SetRenderState 
  //  ���F�ύX�Ώۂ̃f�o�C�X�X�e�[�g�ϐ��@D3DRENDERSTATETYPE�񋓌^�Q��
  //  ���F�f�o�C�X�̃����_�����O�X�e�[�g�ɐݒ肷��V�����l�A���ɂ���ĈӖ����قȂ�
  hr = GetDirectDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
  if (FAILED(hr)) return E_FAIL;
  hr = GetDirectDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
  if (FAILED(hr)) return E_FAIL;
  hr = GetDirectDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
  if (FAILED(hr)) return E_FAIL;

  // �`��
  //�|���S����`��X�g���[���ɓo�^
  hr = GetDirectDevice()->SetStreamSource(0, buffer, 0, k2dSize);
  if (FAILED(hr))return E_FAIL;
  //���_�`����ݒ�
  hr = GetDirectDevice()->SetFVF(FVF_CONVERTED_CUSTOM);
  if (FAILED(hr))return E_FAIL;
  //�`��J�n
  hr = GetDirectDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
  if (FAILED(hr))return E_FAIL;

  return S_OK;
}

HRESULT Load2D(LPDIRECT3DTEXTURE9 *texture, LPCWSTR pass)
{
  //��������p
  HRESULT hr;

  LPDIRECT3DTEXTURE9 tex;
  hr = D3DXCreateTextureFromFile(
    GetDirectDevice(),//LPDIRECT3DDEVICE9         pDevice,
    pass,             //LPCWSTR                   pSrcFile,
    &tex              //LPDIRECT3DTEXTURE9*       ppTexture
  );
  if (FAILED(hr)) return E_FAIL;
  *texture = tex;
  return S_OK;
}
}
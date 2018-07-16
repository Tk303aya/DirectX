#include "DirectString.h"
#include "DirectX.h"
#include <string>

namespace directx
{
std::string debug_string;             //�f�o�b�O�o�͗p������
HRESULT CreateCharToTexture(LPCTSTR put_char, int font_size, float &get_width, float &get_height, LPDIRECT3DTEXTURE9 *get_texture)
{
  //��������
  HRESULT hr;

  //�`��t�H���g�̍쐬
  //�t�H���g���̎擾
  LOGFONT log_font =
  {
    font_size,                //LONG      lfHeight;                 �t�H���g�̍���
    0,                        //LONG      lfWidth;                  �t�H���g�̉���
    0,                        //LONG      lfEscapement;             �w�肵���p�x�i0.1�P�ʂ����W�A���ł͂Ȃ��j�ɔ����v���̕����ɕ�����`�悷��
    0,                        //LONG      lfOrientation;            �x�[�X���C���̊p�x
    0,                        //LONG      lfWeight;                 �t�H���g�̑��� 0�`1000 �܂�
    FALSE,                    //BYTE      lfItalic;                 �Α̗̂L��
    FALSE,                    //BYTE      lfUnderline;              �����̗L��
    FALSE,                    //BYTE      lfStrikeOut;              ���������̗L��
    SHIFTJIS_CHARSET,         //BYTE      lfCharSet;                �����Z�b�g�̎��ʎq�i�g�p�����R�[�h�j
    OUT_TT_ONLY_PRECIS,       //BYTE      lfOutPrecision;           �o�͐��x�@�ݒ肵�����ڂ��ǂ̒��x��v���Ȃ���΂Ȃ�Ȃ����̊
    CLIP_DEFAULT_PRECIS,      //BYTE      lfClipPrecision;          �N���b�s���O���x�@�������}�X�N�͈̔͊O�ɏo�����̐ݒ荀��
    PROOF_QUALITY,            //BYTE      lfQuality;                �o�͕i���@���ۂɕ`�悷��t�H���g�̍��ڂ��ǂ̒��x��v���Ȃ���΂Ȃ�Ȃ����̊
    FIXED_PITCH | FF_MODERN,  //BYTE      lfPitchAndFamily;         �s�b�`�i�������l�߂邩�ǂ����j�ƃt�@�~���i�t�H���g�̌����ځj�@
    _T("�l�r �S�V�b�N")        //WCHAR     lfFaceName[LF_FACESIZE];  �g�p�t�H���g
  };
  HFONT hfont = CreateFontIndirect(&log_font);
  if (!hfont) return E_FAIL;

  //�f�o�C�X�R���e�L�X�g(�`����)�̎擾
  HDC hdc = GetDC(NULL);  //�擾����f�o�C�X�R���e�L�X�g�̃E�B���h�E�n���h��
  if (!hdc) return E_FAIL;

  HFONT old_font = (HFONT)SelectObject(hdc, hfont);//�w�肵���f�o�C�X�R���e�L�X�g����w�肵���P�̃I�u�W�F�N�g��I������
  if (!old_font) return E_FAIL;


  //�����R�[�h�̎擾
  //�Q�o�C�g�����R�[�h�̏ꍇ�� �����R�[�h�~256�{�擱�R�[�h �ŋ��߂���
  //���[�h�E�o�C�g�F�����R�[�h��\�����̐擪�P�o�C�g�̂���
  //              �P�o�C�g�ȊO�̕����R�[�h�̓g���[���E�o�C�g���K�v�ɂȂ��Ă���
  //�g���[���E�o�C�g�F�}���`�o�C�g�����R�[�h�ɂ����ă��[�h�E�o�C�g�ɑ����o�C�g�̂���
  UINT code = 0;
#if UNICODE
  //Unicode�̏ꍇ�́A�����R�[�h�̓��C�h������UINT�ϊ����ł���
  code = (UINT)*put_char;

#else
  //ANSI�̏ꍇ�́A
  //�P�o�C�g�����R�[�h�͂P�o�C�g�ڂ�UINT�ϊ��A
  //�Q�o�C�g�����R�[�h��[���[�h�E�o�C�g]*256+[�����R�[�h]�ɂȂ�
  if (IsDBCSLeadByte((BYTE)*put_char)) //BYTE TestChar  ���ׂ镶�� �w�肳�ꂽ���������[�h�E�o�C�h�ł���ꍇ�O�ȊO�̒l���Ԃ�
  {
    code = (BYTE)put_char[0] << 8 | (BYTE)put_char[1];
  }
  else
  {
    code = put_char[0];
  }
#endif
  TEXTMETRIC tm;                //�t�H���g�����i�[����\����
  if (!GetTextMetrics(hdc, &tm))//���ݑI������Ă���t�H���g�̏����w�肳�ꂽ�o�b�t�@�Ɋi�[����
  {
    return E_FAIL;
  }

  GLYPHMETRICS gm;                            //�t�H���g�ʒu�擾�p�\����
  const MAT2 mat2 = {{0,1},{0,0},{0,0},{0,1}};//�r�b�g�}�b�v�擾���Ɏg�p����}�g���b�N�X�f�[�^
  //�r�b�g�}�b�v�̕K�v�ȃo�b�t�@�T�C�Y���擾
  DWORD size = GetGlyphOutline(
    hdc,              //HDC hdc,              �f�o�C�X�R���e�L�X�g�̃n���h��
    code,             //UINT uChar,           ���߂镶���R�[�h
    GGO_GRAY4_BITMAP, //UINT fuFormat,        �֐����Ԃ��f�[�^�t�H�[�}�b�g
    &gm,               //LPGLYPHMETRICS lpgm, �f�[�^���i�[����GLYPHMETRICS�\����
    0,                //DWORD cjBuffer,       ����pvBuffer�̃T�C�Y���w�肷��
    NULL,             //LPVOID pvBuffer,      �r�b�g�}�b�v�����󂯂�o�b�t�@�ւ̃|�C���^
    &mat2             //CONST MAT2 *lpmat2    �����̕ϊ��s��
  );
  if (size == GDI_ERROR) return E_FAIL;
  //�擾�����o�b�t�@�T�C�Y����t�H���g�r�b�g�}�b�v�̃s�N�Z���l���󂯎��z���ݒ肵�f�[�^���擾
  //�s�N�Z���f�[�^�͂Q�����z��ł͂Ȃ��P�����z��i������X�^�[�g�j�ɂȂ��Ă���̂ŎQ�Ƃ���Ƃ��ɒ��ӂ��K�v
  BYTE *pixel_value = new BYTE[size];
  if (GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, size, pixel_value, &mat2) == GDI_ERROR)return E_FAIL;

  //�I�u�W�F�N�g�̊J��
  SelectObject(hdc, old_font);
  DeleteObject(hfont);
  ReleaseDC(NULL, hdc);

  //�摜�T�C�Y�̊i�[
  get_width = static_cast<float>(gm.gmCellIncX);
  get_height = static_cast<float>(tm.tmHeight);

  //�t�H���g�e�N�X�`���̍쐬
  LPDIRECT3DTEXTURE9 texture;
  hr = GetDirectDevice()->CreateTexture(
    gm.gmCellIncX,    //THIS_ UINT Width,               �쐬����e�N�X�`���̉���
    tm.tmHeight,      //UINT Height,                    �쐬����e�N�X�`���̏c��
    1,                //UINT Levels,                    �~�b�v�}�b�v���x���@�~�b�v�}�b�v�Ƃ͘A�����ďk���������e�N�X�`���̂���
    D3DUSAGE_DYNAMIC, //DWORD Usage,                    �e�N�X�`���̐�����m�ۂ��郁�����̏ꏊ���w��ł��� D3DUSAGE�Q��
    D3DFMT_A8R8G8B8,  //D3DFORMAT Format,               �e�N�X�`���̃s�N�Z���t�H�[�}�b�g�@D3DFORMAT�Q��
    D3DPOOL_DEFAULT,  //D3DPOOL Pool,                   �e�N�X�`�����i�[���郁�����̈ʒu�ƊǗ��Ɋւ���t���O
    &texture,         //IDirect3DTexture9** ppTexture,  �쐬�����e�N�X�`���C���^�[�t�F�[�X�ւ̃|�C���^
    NULL              //HANDLE* pSharedHandle           NULL�Œ�A
  );
  if (FAILED(hr))
  {
    //���I�m�ۂ����s�����Ƃ��p�ɂ���ȊO�̍œK�ȃ������ɒu���悤�ɂ���
    hr = GetDirectDevice()->CreateTexture(gm.gmCellIncX, tm.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, NULL);
    if (FAILED(hr))
    {
      DirectRelease();
      delete[] pixel_value;
      return E_FAIL;
    }
  }

  //�e�N�X�`���Ƀt�H���g�}�b�v����������

  //���S�ɏ������ނ��߂Ƀ��b�N����
  D3DLOCKED_RECT lock_rect;
  hr = texture->LockRect(
    0,               //THIS_ UINT Level,             �~�b�v�}�b�v���x��
    &lock_rect,      //D3DLOCKED_RECT* pLockedRect,  ���b�N���������i�[����\����
    NULL,            //CONST RECT* pRect,            ���b�N�����`�̈� NULL�Ńe�N�X�`���̑S�Ă����b�N����
    D3DLOCK_DISCARD  //DWORD Flags                   ���b�N���̃I�v�V�����t���O�@D3DLOCK�񋓌^�Q��
  );
  if (FAILED(hr))
  {
    if (FAILED(texture->LockRect(0, &lock_rect, NULL, 0)))
    {
      DirectRelease();
      delete[] pixel_value;
      return E_FAIL;
    }
  }

  //�t�H���g���̏�������
  //�ȉ����͉摜�T�C�Y�ł͂Ȃ������o���t�H���g�̃X�^�[�g���W�ƃt�H���g�̑傫���Ȃ̂Œ���
  // start_x, start_y : �����o���ʒu(����)
  int start_x = gm.gmptGlyphOrigin.x;
  int start_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
  // bmp_width, bmp_height : �t�H���g�r�b�g�}�b�v�̕���
  int bmp_width = gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
  int bmp_height = gm.gmBlackBoxY;
  // Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
  int a_level = 17;

  int x, y;
  DWORD Alpha, Color;
  
  //���b�N�����r�b�g�ւ̃|�C���^�ipBits�j����P�s�̃T�C�Y�iPitch�j�ƍ������������͈͂̃r�b�g���O�i���j�œh��Ԃ�
  FillMemory(
    lock_rect.pBits,                //PVOID Destination,  �������u���b�N
    lock_rect.Pitch * tm.tmHeight,  //SIZE_T Length,      �������u���b�N�̃T�C�Y
    0);                             //BYTE Fill           �������݂����l
  //�������ރt�H���g�̃X�^�[�g���W����I�����W�܂ł͈̔͂ŏ������݂��s��
  for (y = start_y; y < start_y + bmp_height; y++)
  {
    for (x = start_x; x < start_x + (int)gm.gmBlackBoxX; x++)
    {
      //�s�N�Z���l����A���t�@�l���v�Z
      Alpha = (255 * pixel_value[x - start_x + bmp_width * (y - start_y)]) / (a_level - 1);
      //���߂��A���t�@�l���J���[�l�ɑ����ďo�̓J���[���v�Z
      Color = 0x00ffffff | (Alpha << 24);
      //�o�̓J���[���r�b�g�}�b�v�ɏ�������
      memcpy((BYTE*)lock_rect.pBits + lock_rect.Pitch*y + 4 * x, &Color, sizeof(DWORD));
    }
  }
  texture->UnlockRect(0);
  *get_texture = texture;
  delete[] pixel_value;
  
  return S_OK;
}

HRESULT Create2DObject(float x, float y, float width, float height, DWORD color, LPDIRECT3DVERTEXBUFFER9 *get_buffer)
{
  //��������p
  HRESULT hr;
  //�`�悷��|���쐬
  CustomVertexConverted v[] =
  {
    {x + width, y,          0.0f, 1.0f, color, 1.0f, 0.0f},
    {x + width, y + height, 0.0f, 1.0f, color, 1.0f, 1.0f},
    {x,         y,          0.0f, 1.0f, color, 0.0f, 0.0f},
    {x,         y + height, 0.0f, 1.0f, color, 0.0f, 1.0f}
  };
  IDirect3DVertexBuffer9 *buffer;
  // ���_�o�b�t�@�쐬
  hr = GetDirectDevice()->CreateVertexBuffer(
    k2dSize * 4,          //THIS_ UINT Length,                        �m�ۂ��钸�_�o�b�t�@�̃T�C�Y
    D3DUSAGE_WRITEONLY,   //DWORD Usage,                              ���\�[�X���@���`����t���O
    FVF_CONVERTED_CUSTOM, //DWORD FVF,                                ��`�������_�t�H�[�}�b�g
    D3DPOOL_MANAGED,      //D3DPOOL Pool,                             ���_�o�b�t�@���ǂ̃������Ɋi�[���邩�@D3DPOOL�񋓌^�Q��
    &buffer,              //IDirect3DVertexBuffer9** ppVertexBuffer,  �쐬�����o�b�t�@���i�[����A�h���X
    NULL                  //HANDLE* pSharedHandle                     DirectX�̕��ŗ\��ς݁ANULL�Œ�
  );
  if (FAILED(hr)) return E_FAIL;

  // ���_���̏�������
  //VRAM�ɒ��ڏ������ނ̂Ń��b�N���Ă��璸�_������������
  void *pData;
  hr = buffer->Lock(
    0,              //THIS_ UINT OffsetToLock,  ���b�N���郁�����̊J�n�T�C�Y
    k2dSize * 4,    //UINT SizeToLock,          ���b�N���郁�����̏I���T�C�Y
    (void**)&pData, //void** ppbData,           ���b�N���ꂽ�������̐擪�A�h���X
    0);             //DWORD Flags               ���b�N����Ƃ��̃I�v�V�����t���O�@D3DLOCK�Q��
  if (FAILED(hr)) return E_FAIL;

  //���ۂɏ�������
  memcpy(pData, v, k2dSize * 4);
  //���b�N�������������J���A�Y���ƎQ�Ƃł��Ȃ�
  buffer->Unlock();
  *get_buffer = buffer;
  return S_OK;
}

void AddDebugString(const char * FormatString, ...)
{
#if DEBUG_MODE
  char put_string[256];
  va_list arg;
  va_start(arg, FormatString);
  vsprintf_s(put_string, FormatString, arg);
  va_end(arg);
  debug_string += put_string;
#endif
}

void ClearDebugString()
{
#if DEBUG_MODE
  debug_string.clear();
#endif
}
void PutDebugString()
{
#if DEBUG_MODE
  
#endif
}
}
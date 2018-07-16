#include "DirectString.h"
#include "DirectX.h"
#include <string>

namespace directx
{
std::string debug_string;             //デバッグ出力用文字列
HRESULT CreateCharToTexture(LPCTSTR put_char, int font_size, float &get_width, float &get_height, LPDIRECT3DTEXTURE9 *get_texture)
{
  //成功判定
  HRESULT hr;

  //描画フォントの作成
  //フォント情報の取得
  LOGFONT log_font =
  {
    font_size,                //LONG      lfHeight;                 フォントの高さ
    0,                        //LONG      lfWidth;                  フォントの横幅
    0,                        //LONG      lfEscapement;             指定した角度（0.1単位かつラジアンではない）に反時計回りの方向に文字を描画する
    0,                        //LONG      lfOrientation;            ベースラインの角度
    0,                        //LONG      lfWeight;                 フォントの太さ 0～1000 まで
    FALSE,                    //BYTE      lfItalic;                 斜体の有無
    FALSE,                    //BYTE      lfUnderline;              下線の有無
    FALSE,                    //BYTE      lfStrikeOut;              取り消し線の有無
    SHIFTJIS_CHARSET,         //BYTE      lfCharSet;                文字セットの識別子（使用文字コード）
    OUT_TT_ONLY_PRECIS,       //BYTE      lfOutPrecision;           出力精度　設定した項目をどの程度一致しなければならないかの基準
    CLIP_DEFAULT_PRECIS,      //BYTE      lfClipPrecision;          クリッピング精度　文字がマスクの範囲外に出た時の設定項目
    PROOF_QUALITY,            //BYTE      lfQuality;                出力品質　実際に描画するフォントの項目をどの程度一致しなければならないかの基準
    FIXED_PITCH | FF_MODERN,  //BYTE      lfPitchAndFamily;         ピッチ（文字を詰めるかどうか）とファミリ（フォントの見た目）　
    _T("ＭＳ ゴシック")        //WCHAR     lfFaceName[LF_FACESIZE];  使用フォント
  };
  HFONT hfont = CreateFontIndirect(&log_font);
  if (!hfont) return E_FAIL;

  //デバイスコンテキスト(描画情報)の取得
  HDC hdc = GetDC(NULL);  //取得するデバイスコンテキストのウィンドウハンドル
  if (!hdc) return E_FAIL;

  HFONT old_font = (HFONT)SelectObject(hdc, hfont);//指定したデバイスコンテキストから指定した１つのオブジェクトを選択する
  if (!old_font) return E_FAIL;


  //文字コードの取得
  //２バイト文字コードの場合は 文字コード×256＋先導コード で求められる
  //リード・バイト：文字コードを表す時の先頭１バイトのこと
  //              １バイト以外の文字コードはトレール・バイトが必要になってくる
  //トレール・バイト：マルチバイト文字コードにおいてリード・バイトに続くバイトのこと
  UINT code = 0;
#if UNICODE
  //Unicodeの場合は、文字コードはワイド文字のUINT変換ができる
  code = (UINT)*put_char;

#else
  //ANSIの場合は、
  //１バイト文字コードは１バイト目のUINT変換、
  //２バイト文字コードは[リード・バイト]*256+[文字コード]になる
  if (IsDBCSLeadByte((BYTE)*put_char)) //BYTE TestChar  調べる文字 指定された文字がリード・バイドである場合０以外の値が返る
  {
    code = (BYTE)put_char[0] << 8 | (BYTE)put_char[1];
  }
  else
  {
    code = put_char[0];
  }
#endif
  TEXTMETRIC tm;                //フォント情報を格納する構造体
  if (!GetTextMetrics(hdc, &tm))//現在選択されているフォントの情報を指定されたバッファに格納する
  {
    return E_FAIL;
  }

  GLYPHMETRICS gm;                            //フォント位置取得用構造体
  const MAT2 mat2 = {{0,1},{0,0},{0,0},{0,1}};//ビットマップ取得時に使用するマトリックスデータ
  //ビットマップの必要なバッファサイズを取得
  DWORD size = GetGlyphOutline(
    hdc,              //HDC hdc,              デバイスコンテキストのハンドル
    code,             //UINT uChar,           求める文字コード
    GGO_GRAY4_BITMAP, //UINT fuFormat,        関数が返すデータフォーマット
    &gm,               //LPGLYPHMETRICS lpgm, データを格納するGLYPHMETRICS構造体
    0,                //DWORD cjBuffer,       下のpvBufferのサイズを指定する
    NULL,             //LPVOID pvBuffer,      ビットマップ情報を受けるバッファへのポインタ
    &mat2             //CONST MAT2 *lpmat2    文字の変換行列
  );
  if (size == GDI_ERROR) return E_FAIL;
  //取得したバッファサイズからフォントビットマップのピクセル値を受け取る配列を設定しデータを取得
  //ピクセルデータは２次元配列ではなく１次元配列（横からスタート）になっているので参照するときに注意が必要
  BYTE *pixel_value = new BYTE[size];
  if (GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &gm, size, pixel_value, &mat2) == GDI_ERROR)return E_FAIL;

  //オブジェクトの開放
  SelectObject(hdc, old_font);
  DeleteObject(hfont);
  ReleaseDC(NULL, hdc);

  //画像サイズの格納
  get_width = static_cast<float>(gm.gmCellIncX);
  get_height = static_cast<float>(tm.tmHeight);

  //フォントテクスチャの作成
  LPDIRECT3DTEXTURE9 texture;
  hr = GetDirectDevice()->CreateTexture(
    gm.gmCellIncX,    //THIS_ UINT Width,               作成するテクスチャの横幅
    tm.tmHeight,      //UINT Height,                    作成するテクスチャの縦幅
    1,                //UINT Levels,                    ミップマップレベル　ミップマップとは連続して縮小させたテクスチャのこと
    D3DUSAGE_DYNAMIC, //DWORD Usage,                    テクスチャの性質や確保するメモリの場所を指定できる D3DUSAGE参照
    D3DFMT_A8R8G8B8,  //D3DFORMAT Format,               テクスチャのピクセルフォーマット　D3DFORMAT参照
    D3DPOOL_DEFAULT,  //D3DPOOL Pool,                   テクスチャを格納するメモリの位置と管理に関するフラグ
    &texture,         //IDirect3DTexture9** ppTexture,  作成したテクスチャインターフェースへのポインタ
    NULL              //HANDLE* pSharedHandle           NULL固定、
  );
  if (FAILED(hr))
  {
    //動的確保が失敗したとき用にそれ以外の最適なメモリに置くようにする
    hr = GetDirectDevice()->CreateTexture(gm.gmCellIncX, tm.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture, NULL);
    if (FAILED(hr))
    {
      DirectRelease();
      delete[] pixel_value;
      return E_FAIL;
    }
  }

  //テクスチャにフォントマップを書き込む

  //安全に書き込むためにロックする
  D3DLOCKED_RECT lock_rect;
  hr = texture->LockRect(
    0,               //THIS_ UINT Level,             ミップマップレベル
    &lock_rect,      //D3DLOCKED_RECT* pLockedRect,  ロックした情報を格納する構造体
    NULL,            //CONST RECT* pRect,            ロックする矩形領域 NULLでテクスチャの全てをロックする
    D3DLOCK_DISCARD  //DWORD Flags                   ロック時のオプションフラグ　D3DLOCK列挙型参照
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

  //フォント情報の書き込み
  //以下情報は画像サイズではなく書き出すフォントのスタート座標とフォントの大きさなので注意
  // start_x, start_y : 書き出し位置(左上)
  int start_x = gm.gmptGlyphOrigin.x;
  int start_y = tm.tmAscent - gm.gmptGlyphOrigin.y;
  // bmp_width, bmp_height : フォントビットマップの幅高
  int bmp_width = gm.gmBlackBoxX + (4 - (gm.gmBlackBoxX % 4)) % 4;
  int bmp_height = gm.gmBlackBoxY;
  // Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
  int a_level = 17;

  int x, y;
  DWORD Alpha, Color;
  
  //ロックしたビットへのポインタ（pBits）から１行のサイズ（Pitch）と高さをかけた範囲のビットを０（黒）で塗りつぶす
  FillMemory(
    lock_rect.pBits,                //PVOID Destination,  メモリブロック
    lock_rect.Pitch * tm.tmHeight,  //SIZE_T Length,      メモリブロックのサイズ
    0);                             //BYTE Fill           書き込みたい値
  //書き込むフォントのスタート座標から終了座標までの範囲で書き込みを行う
  for (y = start_y; y < start_y + bmp_height; y++)
  {
    for (x = start_x; x < start_x + (int)gm.gmBlackBoxX; x++)
    {
      //ピクセル値からアルファ値を計算
      Alpha = (255 * pixel_value[x - start_x + bmp_width * (y - start_y)]) / (a_level - 1);
      //求めたアルファ値をカラー値に足して出力カラーを計算
      Color = 0x00ffffff | (Alpha << 24);
      //出力カラーをビットマップに書き込む
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
  //成功判定用
  HRESULT hr;
  //描画する板ポリ作成
  CustomVertexConverted v[] =
  {
    {x + width, y,          0.0f, 1.0f, color, 1.0f, 0.0f},
    {x + width, y + height, 0.0f, 1.0f, color, 1.0f, 1.0f},
    {x,         y,          0.0f, 1.0f, color, 0.0f, 0.0f},
    {x,         y + height, 0.0f, 1.0f, color, 0.0f, 1.0f}
  };
  IDirect3DVertexBuffer9 *buffer;
  // 頂点バッファ作成
  hr = GetDirectDevice()->CreateVertexBuffer(
    k2dSize * 4,          //THIS_ UINT Length,                        確保する頂点バッファのサイズ
    D3DUSAGE_WRITEONLY,   //DWORD Usage,                              リソース方法を定義するフラグ
    FVF_CONVERTED_CUSTOM, //DWORD FVF,                                定義した頂点フォーマット
    D3DPOOL_MANAGED,      //D3DPOOL Pool,                             頂点バッファをどのメモリに格納するか　D3DPOOL列挙型参照
    &buffer,              //IDirect3DVertexBuffer9** ppVertexBuffer,  作成したバッファを格納するアドレス
    NULL                  //HANDLE* pSharedHandle                     DirectXの方で予約済み、NULL固定
  );
  if (FAILED(hr)) return E_FAIL;

  // 頂点情報の書き込み
  //VRAMに直接書き込むのでロックしてから頂点情報を書き込む
  void *pData;
  hr = buffer->Lock(
    0,              //THIS_ UINT OffsetToLock,  ロックするメモリの開始サイズ
    k2dSize * 4,    //UINT SizeToLock,          ロックするメモリの終了サイズ
    (void**)&pData, //void** ppbData,           ロックされたメモリの先頭アドレス
    0);             //DWORD Flags               ロックするときのオプションフラグ　D3DLOCK参照
  if (FAILED(hr)) return E_FAIL;

  //実際に書き込み
  memcpy(pData, v, k2dSize * 4);
  //ロックしたメモリを開放、忘れると参照できない
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
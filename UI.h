//=============================================================================
//
// UI���� [UI.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

class UITexData
{
private:
	ID3D11Buffer *m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11ShaderResourceView	*m_Texture =  nullptr;	// �e�N�X�`�����
	char *m_TextureName = nullptr;

public:
	UITexData();
	UITexData(char *textureName);
	~UITexData();

	HRESULT Create(void);
	ID3D11Buffer **GetpVertexBuffer(void) { return &m_VertexBuffer; }
	ID3D11Buffer *GetVertexBuffer(void) { return m_VertexBuffer; }
	ID3D11ShaderResourceView **GetTexture(void) { return &m_Texture; }
	void SetTextureName(char *textureName) {m_TextureName = textureName;}
};


class UIObject
{
private:
	BOOL		m_isUse = FALSE;	
	XMFLOAT3	m_pos   = { 0.0f,0.0f,0.0f };
	float		m_rot     = 0.0f;		// ��]�p�x
	float		m_fWidth  = 0.0f;		// ��
	float		m_fHeight = 0.0f;		// ����
	int			m_TexNo   = 0;			// �e�N�X�`���ԍ�
	UITexData  *m_UITexData;

protected:

public:
	UIObject();
	virtual ~UIObject();

	XMFLOAT3 GetPos(void) { return m_pos; }
	float GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	UITexData *GetUITexData(void) { return m_UITexData; }

	void SetPos(XMFLOAT3 pos) {  m_pos = pos; }
	void SetRot(float rot) {  m_rot = rot; }
	void SetWidth(float width) { m_fWidth = width; }
	void SetHeight(float height) { m_fHeight = height; }


	virtual void Update(void);
	virtual void Draw(void);


};
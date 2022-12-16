//=============================================================================
//
// �p�[�e�B�N������ [particle.h]
// Author : 
//
//=============================================================================
#pragma once

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	PARTICLE_BUFFER		(10)		// �p�[�e�B�N���ő吔
#define	MAX_PARTICLE		(200)		// �p�[�e�B�N���ő��

enum
{  //�e�N�X�`���[�̎��
	EFFECT_BOM,
	EFFECT_KEMURI,
	EFFECT_KEMURI2,
	EFFECT_LIGHT,
	EFFECT_REFLECTION,
	EFFECT_MAX,
};

enum
{  //�e�N�X�`���[�̎��
	MOVE_PATTERN_UP,
	MOVE_PATTERN_UP_SMALL,
	MOVE_PATTERN_UPLEFT,
	MOVE_PATTERN_MAX,
};


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
class SPRITE_ANIMATION
{
private:
	int			m_patternAnim;	// �A�j���[�V�����p�^�[���i���o�[
	int		    m_uwnum;		// �e�N�X�`���̕\�����镔���̕�
	float		m_countAnim;	// �A�j���[�V�����J�E���g
	float		m_tw;			// �\������e�N�X�`���̕�
	float		m_th;			// �\������e�N�X�`���̍���
	float		m_tx;			// �\������e�N�X�`���̈ʒu
	float		m_ty;			// �\������e�N�X�`���̈ʒu
	BOOL		m_use;			// �g�p���Ă��邩�ǂ���

public:

	SPRITE_ANIMATION() {
	
		m_patternAnim = 0;
		m_uwnum = 0;
		m_countAnim = 0.0f;
		m_tw = 0.0f;
		m_th = 0.0f;
		m_tx = 0.0f;
		m_ty = 0.0f;
		m_use = FALSE;
	};

	~SPRITE_ANIMATION() {};

	void Init() {
		m_patternAnim = 0;
		m_uwnum = 0;
		m_countAnim = 0.0f;
		m_tw = 0.0f;
		m_th = 0.0f;
		m_tx = 0.0f;
		m_ty = 0.0f;
		m_use = FALSE;
	}

	void Update(int time);   
	XMFLOAT2 GetTexPos(void) { return XMFLOAT2{ m_tx,m_ty }; }   // �e�N�X�`���[���W�̎擾
	XMFLOAT2 GetTexWidth(void) { return XMFLOAT2{ m_tw,m_th }; }   // �e�N�X�`���[���W�̎擾
	void SetUse(BOOL flag) {  m_use = flag; };  
	BOOL GetUse(void) { return m_use; }
};

class PARTICLE
{
private:
	XMFLOAT3		m_posBase;		// �����ʒu
	XMFLOAT3		m_pos;			// �ʒu
	XMFLOAT3		m_rot;			// ��]
	XMFLOAT3		m_scale;		// �X�P�[��
	XMFLOAT3		m_move;			// �ړ���
	MATERIAL		m_material;		// �}�e���A��
	float			m_fSizeX;		// ��
	float			m_fSizeY;		// ����
	int				m_nLife;		// ����
	BOOL			m_bUse;			// �g�p���Ă��邩�ǂ���
	BOOL			m_bSwich;		// ON,OFF
	int			    m_nTexno;		// �e�N�X�`���[�i���o�[
	int			    m_Pattern;		// �p�^�[���i���o�[
	int				m_nextAnime;	// ���̃A�j���[�V�����ɍs���܂ł̎���

public:

	SPRITE_ANIMATION SpriteAnim;

	PARTICLE();
	~PARTICLE() {};

	void AddPos(XMFLOAT3 move) { 
		m_pos.x += move.x;
		m_pos.y += move.y;
		m_pos.z += move.z;
	};


	XMFLOAT3 GetPos(void)  { return m_pos; };		    // �p�[�e�B�N���̍��W�̎擾
	XMFLOAT3 GetMove(void) { return m_move; };		    // �p�[�e�B�N���̈ړ��ʂ̎擾
	BOOL	 GetUse(void)  { return m_bUse; };		    // �p�[�e�B�N���̎g�p���̎擾
	BOOL	 GetSwich(void) { return m_bSwich; };		// �p�[�e�B�N���o�b�t�@��ON OFF
	int		 GetAnimeTime(void) { return m_nextAnime; }
	void	 SetPosBase(XMFLOAT3 pos) { m_posBase = pos; };
	void	 SetPos(XMFLOAT3 pos)	  { m_pos = pos; };
	void	 SetSize(float size)      { m_fSizeX = size; m_fSizeY = size;};
	void	 SetUse(BOOL flag)        { m_bUse = flag; };
	void	 SetSwich(BOOL flag)      { m_bSwich = flag; };
	void	 SetTexno(int no)         { m_nTexno = no; };
	void	 SetPattern(int pattern)         { m_Pattern = pattern; };
	void	 SetParticle(/*XMFLOAT3 pos,*/ XMFLOAT3 move, XMFLOAT4 col, float fSizeX, float fSizeY, int nLife);
	void	 SetAnimeTime(int time)   { m_nextAnime = time; };

	void Update(void);       // �X�V����
	void Draw(void);         // �`�揈��

};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);

void CallParticle(XMFLOAT3 pos, float size, int num, int texID, int pattern);


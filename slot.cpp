#include "slot.h"
#include "input.h"
#include "debugproc.h"
#include "sound.h"


Slot::Slot()
{
	// ➑̂̏�����
	pHousing = new Housing();

	// ➑̂̑傫���Z�b�g
	XMFLOAT3 sclHousing = { 1.0f,1.0f,1.0f };
	pHousing->GetPrefab()->SetScl(sclHousing);

	// ➑̂̌����Z�b�g
	XMFLOAT3 rotHousing = { 0.0f,3.14f,0.0f };
	pHousing->GetPrefab()->SetRot(rotHousing);

	// �h����3D�̏�����
	pDrumL = new Drum3Dx1050();
	pDrumC = new Drum3D();
	pDrumR = new Drum3D();

	// �h����3D�̑傫���Z�b�g
	XMFLOAT3 scl = { 1.0f,1.0f,1.0f };
	pDrumL->GetPrefab()->SetScl(scl);
	pDrumC->GetPrefab()->SetScl(scl);
	pDrumR->GetPrefab()->SetScl(scl);

	// �h����3D�̃��[�J���ʒu�Z�b�g
	XMFLOAT3 posDrumL = { -5.0f,0.0f,0.0f };
	XMFLOAT3 posDrumC = { 0.0f,0.0f,0.0f };
	XMFLOAT3 posDrumR = { 5.0f,0.0f,0.0f };
	pDrumL->GetPrefab()->SetPos(posDrumL);
	pDrumC->GetPrefab()->SetPos(posDrumC);
	pDrumR->GetPrefab()->SetPos(posDrumR);

	m_pSwitch = new Switch();

}

Slot::~Slot()
{
	delete pDrumL;
	delete pDrumC;
	delete pDrumR;
	delete pHousing;
	delete m_pSwitch;
}


void Slot::Update(void)
{

	pDrumL->Update();
	pDrumC->Update();
	pDrumR->Update();
	pHousing->Update();
	m_pSwitch->Update();

	// ���Ԃ�i�߂�
	if (m_move)
	{
		m_count++;
	}

	// �~�߂�
	if ((GetKeyboardTrigger(DIK_SPACE) || IsButtonTriggered(0, BUTTON_B)) && (m_count > 40))
	{
		// �X���b�g���~�߂�
		if (pDrumR->GetMove())
		{
			pDrumR->Stop();
			m_move = false;
			m_pSwitch->SwitchON(0);

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
		else if (pDrumC->GetMove())
		{
			pDrumC->Stop();
			m_pSwitch->SwitchON(1);

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
		else if (pDrumL->GetMove())
		{
			pDrumL->Stop();
			m_shot = true;
			m_pSwitch->SwitchON(2);

			if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_RED;
			else if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_PURPLE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_PURPLE;
			else if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_ORANGE;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_ORANGE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_BLUE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_GREEN;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_GREEN;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_YELLOW;

			switch (pDrumL->GetColor())
			{
			case drum3D_x10:
				m_crowNum = 1;
				break;

			case drum3D_x30:
				m_crowNum = 2;
				break;

			case drum3D_x50:
				m_crowNum = 3;
				break;
			}

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
	}


	// �v���[���y
	// �~�߂�
	if ((GetKeyboardTrigger(DIK_4) || IsButtonTriggered(0, BUTTON_C)) && (m_count > 40))
	{
		// �X���b�g���~�߂�
		if (pDrumR->GetMove())
		{
			pDrumR->StopPresen(drum3D_red);
			m_move = false;
			m_pSwitch->SwitchON(0);

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
		else if (pDrumC->GetMove())
		{
			pDrumC->StopPresen(drum3D_red);
			m_pSwitch->SwitchON(1);

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
	}

	// �~�߂�
	if ((GetKeyboardTrigger(DIK_5) || IsButtonTriggered(0, BUTTON_X)) && (m_count > 40))
	{
		// �X���b�g���~�߂�
		if (pDrumR->GetMove())
		{
			pDrumR->StopPresen(drum3D_blue);
			m_move = false;
			m_pSwitch->SwitchON(0);

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
		else if (pDrumC->GetMove())
		{
			pDrumC->StopPresen(drum3D_blue);
			m_pSwitch->SwitchON(1);

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
	}

	// �~�߂�
	if ((GetKeyboardTrigger(DIK_6) || IsButtonTriggered(0, BUTTON_A)) && (m_count > 40))
	{
		// �X���b�g���~�߂�
		if (pDrumR->GetMove())
		{
			pDrumR->StopPresen(drum3D_yellow);
			m_move = false;
			m_pSwitch->SwitchON(0);

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
		else if (pDrumC->GetMove())
		{
			pDrumC->StopPresen(drum3D_yellow);
			m_pSwitch->SwitchON(1);

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
	}

	if ((GetKeyboardTrigger(DIK_7) || IsButtonTriggered(0, BUTTON_RIGHT)) && (m_count > 40))
	{
		// �X���b�g���~�߂�
		if (pDrumL->GetMove())
		{
			pDrumL->StopPresen(drum3D_red);
			m_shot = true;
			m_pSwitch->SwitchON(2);

			if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_RED;
			else if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_PURPLE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_PURPLE;
			else if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_ORANGE;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_ORANGE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_BLUE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_GREEN;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_GREEN;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_YELLOW;

			switch (pDrumL->GetColor())
			{
			case drum3D_x10:
				m_crowNum = 1;
				break;

			case drum3D_x30:
				m_crowNum = 2;
				break;

			case drum3D_x50:
				m_crowNum = 3;
				break;
			}

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
	}

	if ((GetKeyboardTrigger(DIK_9) || IsButtonTriggered(0, BUTTON_LEFT)) && (m_count > 40))
	{
		// �X���b�g���~�߂�
		if (pDrumL->GetMove())
		{
			pDrumL->StopPresen(drum3D_blue);
			m_shot = true;
			m_pSwitch->SwitchON(2);

			if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_RED;
			else if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_PURPLE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_PURPLE;
			else if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_ORANGE;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_ORANGE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_BLUE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_GREEN;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_GREEN;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_YELLOW;

			switch (pDrumL->GetColor())
			{
			case drum3D_x10:
				m_crowNum = 1;
				break;

			case drum3D_x30:
				m_crowNum = 2;
				break;

			case drum3D_x50:
				m_crowNum = 3;
				break;
			}

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
	}

	if ((GetKeyboardTrigger(DIK_8) || IsButtonTriggered(0, BUTTON_UP)) && (m_count > 40))
	{
		// �X���b�g���~�߂�
		if (pDrumL->GetMove())
		{
			pDrumL->StopPresen(drum3D_yellow);
			m_shot = true;
			m_pSwitch->SwitchON(2);

			if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_RED;
			else if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_PURPLE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_PURPLE;
			else if ((pDrumR->GetColor() == drum3D_red) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_ORANGE;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_red)) m_colorType = LAMP_TYPE_ORANGE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_BLUE;
			else if ((pDrumR->GetColor() == drum3D_blue) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_GREEN;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_blue)) m_colorType = LAMP_TYPE_GREEN;
			else if ((pDrumR->GetColor() == drum3D_yellow) && (pDrumC->GetColor() == drum3D_yellow)) m_colorType = LAMP_TYPE_YELLOW;

			switch (pDrumL->GetColor())
			{
			case drum3D_x10:
				m_crowNum = 1;
				break;

			case drum3D_x30:
				m_crowNum = 2;
				break;

			case drum3D_x50:
				m_crowNum = 3;
				break;
			}

			PlaySound(SOUND_LABEL_SE_se_slot_stop);
		}
	}







#ifdef _DEBUG	// �f�o�b�O����\������

	//m_debug = m_colorType;
	//m_debugR = pDrumR->GetColor();
	//m_debugC = pDrumC->GetColor();
	//PrintDebugProc("[%d]:�J���[�X�̐F�^�C�v\n", m_debug);
	//PrintDebugProc("[%d]:R�̐F�^�C�v\n", m_debugR);
	//PrintDebugProc("[%d]:C�̐F�^�C�v\n", m_debugC);
#endif

	// ��
	if ((GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_DOWN)))
	{
		PlaySound(SOUND_LABEL_SE_se_slot_lever_nomal); // �X���b�g�𓮂���
		pDrumR->SpinStart();
		if(!m_move) m_count = 0;
		m_move = true;

		m_pSwitch->SwitchOFF();

	}

	if (m_move)
	{
		if ((m_count > 20) && (!pDrumC->GetMove()))
		{
			pDrumC->SpinStart();
		}
		else if ((m_count > 40) && (!pDrumL->GetMove()))
		{
			pDrumL->SpinStart();
		}
	}
}

void Slot::Draw()
{
	pDrumL->Draw();
	pDrumC->Draw();
	pDrumR->Draw();
	pHousing->Draw();
	m_pSwitch->Draw();
}


XMFLOAT4 Slot::GetColor(void)
{
	XMFLOAT4 color = { 0.2f,0.2f,0.2f,1.0f };


	if (!pDrumR->GetMove())
	{
		switch (pDrumR->GetColor())
		{
		case drum3D_red:
			color.x += 0.7f;
			break;

		case drum3D_blue:
			color.z += 0.7f;
			break;

		case drum3D_yellow:
			color.x += 0.35f;
			color.y += 0.35f;
			break;
		}
	}

	if (!pDrumC->GetMove())
	{
		switch (pDrumC->GetColor())
		{
		case drum3D_red:
			color.x += 0.7f;
			break;

		case drum3D_blue:
			color.z += 0.7f;

			// �΂͓���
			if (pDrumR->GetColor() == drum3D_yellow)
			{
				color = { 0.2f,1.4f,0.2f,1.0f };
			}
			break;

		case drum3D_yellow:
			color.x += 0.35f;
			color.y += 0.35f;

			// �΂͓���
			if (pDrumR->GetColor() == drum3D_blue)
			{
				color = { 0.2f,1.4f,0.2f,1.0f };
			}
			break;
		}
	}

	return color;
}

void Slot::SetRainbowModel(void)
{
	pDrumL->SetRainbowModelL();
	pDrumC->SetRainbowModel();
	pDrumR->SetRainbowModel();
}

void Slot::ResetRainbowModel(void)
{
	pDrumL->ResetRainbowModelL();
	pDrumC->ResetRainbowModel();
	pDrumR->ResetRainbowModel();
}

void Slot::Init()
{
	m_shot = false;
	m_count = 0;
	m_move = false;

	m_colorType = 0;
	m_crowNum = 0;

	m_debug = 0;
	m_debugR = 0;
	m_debugC = 0;
	m_debugL = 0;

	ResetRainbowModel();

	pHousing->Init();
}
